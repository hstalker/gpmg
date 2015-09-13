/// \file      fallback-allocator.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines a simple composite allocator, containing a main and
/// fallback allocator.

#ifndef GPMG_ALLOCATORS_FALLBACK_ALLOCATOR_HPP
#define GPMG_ALLOCATORS_FALLBACK_ALLOCATOR_HPP

#include <type_traits>
#include <cstring>
#include "allocator-traits.hpp"
#include "utils.hpp"
#include "static-dispatchers.hpp"
#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/assert.hpp"

namespace gpmg {

/// Returns the minimum of two given values
/// \tparam T The type of the two value to be compared
/// (should be numerical in some way)
/// \param arg1 The first number
/// \param arg2 The second number
template <typename T>
constexpr T min(const T arg1, const T arg2) {
    return arg1 <= arg2 ? arg1 : arg2;
}

/// An allocator that utilises a primary allocator and a fallback.
/// When the allocator fails to allocate into the primary, it tries
/// to allocate with the fallback.
/// \tparam P The primary allocator type
/// \tparam F The fallback (reserve) allocator type
template <typename P, typename F>
class FallbackAllocator {
   public:
    static_assert(hasMemberFunc_allocate<P>::value &&
                      hasMemberFunc_allocate<F>::value,
                  "Allocaters MUST have a void allocate(size_t) function!");
    static_assert(hasMemberVar_alignment<P>::value &&
                      hasMemberVar_alignment<F>::value,
                  "Allocaters MUST have a uint alignment variable!");

    FallbackAllocator(const P& primary, const F& fallback)
        : alignment(min(primary_.alignment, fallback_.alignment)),
          primary_(primary),
          fallback_(fallback) {}
    ~FallbackAllocator() = default;
    FallbackAllocator(const FallbackAllocator&) = default;
    FallbackAllocator(FallbackAllocator&&) = default;
    FallbackAllocator& operator=(const FallbackAllocator&) = default;
    FallbackAllocator& operator=(FallbackAllocator&&) = default;

    /// Allocates a block of memory of a given size
    /// \param n The size of memory to try to allocate
    /// \return A pointer to the newly allocated block if successful,
    /// a nullptr if unsuccessful.
    void* allocate(std::size_t n) {
        auto r = primary_.allocate(n);
        if (r == nullptr) {
            r = fallback_.allocate(n);
        }
        return r;
    }

    /// Deallocates the given memory block if possible. Requires that the
    /// primary allocator has an 'owns' member function, and either the primary
    /// or fallback allocator have a 'deallocate' member function.
    /// \param b The memory block to try to deallocate
    void deallocate(void* b) {
        static_assert(
            hasMemberFunc_owns<P>::value,
            "Primary allocator must have a bool owns(void*) member function!");
        static_assert(hasMemberFunc_deallocate<P>::value ||
                          hasMemberFunc_deallocate<F>::value,
                      "Either primary or fallback allocator must have a void "
                      "deallocate(void*) member function!");

        if (primary_.owns(b)) {
            detail::tryToDeallocate<P>(primary_, b);
        } else {
            detail::tryToDeallocate<F>(fallback_, b);
        }
    }

    /// Attempts to reallocate the given memory block. Requires the primary
    /// allocator to have an 'owns' member function
    /// \param b A pointer to a chunk of memory
    /// \param oldSize The size for the old memory block
    /// \param newSize The size for the newly reallocated memory block
    /// \return Whether the reallocation was sucessful or not
    bool reallocate(void* b, const std::size_t oldSize, const std::size_t newSize) {
        static_assert(
            hasMemberFunc_owns<P>::value,
            "Primary allocator must have a bool owns(void*) member function!");
        
        // If the size of the reallocation is 0, then just try to deallocate the block
        // to unregister this memory block with the allocator and return reallocation success.
        if (newSize == 0) {
            detail::tryToDeallocate<FallbackAllocator>(this, b);
            return true;
        }
        
        // If the given memory block pointer is null, just attempt to allocate a new block of
        // memory of the given size and return reallocation success if it succeeds.
        if (b == nullptr) {
            b = allocate(newSize);
            return b != nullptr;
        }

        // If the memory block is owned by our primary allocator, then try to
        // reallocate with our primary allocator. If then this reallocation
        // fails, attempt to move the the memory from the primary allocator to
        // the fallback with the new size allocated.
        if (primary_.owns(b)) {
            if (primary_.reallocate(b, oldSize, newSize)) {
                return true;
            }
            
            // Move the memory from primary to fallback
            return crossAllocatorMove(b, primary_, fallback_, oldSize, newSize);
        }

        // Try to reallocate with the fallback, as if the function reaches this point, the fallback definitely owns 
        if (fallback_.reallocate(b, oldSize, newSize)) {
            return true;
        }

        // Try to move the memory from the fallback to the primary if all else fails
        return crossAllocatorMove(b, fallback_, primary_, oldSize, newSize);
    }

    /// Tests whether this allocator instance owns the memory given.
    /// Requires both the primary and fallback allocator to have 'owns' defined.
    /// \param b Pointer to the block of memory which is being checked for ownership
    /// \return Whether the memory is owned by this allocator or not
    bool owns(void* b) {
        static_assert(
            hasMemberFunc_owns<P>::value,
            "Primary allocator must have a bool owns(void*) member function!");
        static_assert(
            hasMemberFunc_owns<F>::value,
            "Fallback allocator must have a bool owns(void*) member function!");

        return primary_.owns(b) || fallback_.owns(b);
    }

    unsigned int alignment; /// The memory alignment the allocator should use

   private:    
    P primary_; /// The primary allocator
    F fallback_; /// The fallback allocator
};
}

#endif

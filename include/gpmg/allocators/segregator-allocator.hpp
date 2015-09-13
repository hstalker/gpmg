/// \file      segregator-allocator.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines a simple composite allocator, containing a small and
/// large allocator, segregating allocations using a threshold value.

#ifndef GPMG_ALLOCATORS_SEGREGATOR_ALLOCATOR_HPP
#define GPMG_ALLOCATORS_SEGREGATOR_ALLOCATOR_HPP

#include <type_traits>
#include "tools.hpp"
#include "utils.hpp"
#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/assert.hpp"

namespace gpmg {

/// An allocator that utilises both a small and a large allocator.
/// When the allocator segregates allocations into the two different allocators
/// based upon a set threshold size.
/// \tparam threshold A numerical size value determining the threshold size for
/// segregation
/// \tparam S The small allocator type
/// \tparam L The large allocator type
template <std::size_t threshold, typename S, typename L>
class SegregatorAllocator {
   public:
    ALLOCATOR_WELLFORMED(S)
    ALLOCATOR_WELLFORMED(L)

    SegregatorAllocator(const S& small, const L& large)
        : alignment(min(small_.alignment, large_.alignment)),
          small_(small),
          large_(large) {}
    ~SegregatorAllocator() = default;
    SegregatorAllocator(const SegregatorAllocator&) = default;
    SegregatorAllocator(SegregatorAllocator&&) = default;
    SegregatorAllocator& operator=(const SegregatorAllocator&) = default;
    SegregatorAllocator& operator=(SegregatorAllocator&&) = default;

    /// Allocates a block of memory of a given size
    /// \param n The size of memory to try to allocate
    /// \return A pointer to the newly allocated block if successful,
    /// a nullptr if unsuccessful.
    void* allocate(const std::size_t n) {
        return n <= threshold ? small_.allocate(n) : large_.allocate(n);
    }

    /// Expands a block of memory of a given size to a new size.
    /// \param b Pointer to a block of memory (presumably) owned by this
    /// allocator
    /// \param oldSize The original memory block size
    /// \param newSize The new memory block size to expand to
    /// \return Whether the expansion succeeded or not
    bool expand(void* b, const std::size_t oldSize, const std::size_t newSize) {
        static_assert(tools::hasMemberFunc_deallocate<S>::value ||
                          tools::hasMemberFunc_deallocate<L>::value,
                      "Either small or large allocator must have a conforming "
                      "expand member function!");

        if (newSize <= threshold) {
            // Old and new allocations handled by small allocator
            return tools::tryToExpand(small_, b, oldSize, newSize);
        }
        if (newSize > threshold) {
            // Old and new allocations handled by large allocator
            return tools::tryToExpand(large_, b, oldSize, newSize);
        }

        // Something went horribly wrong
        return false;
    }

    unsigned int alignment;  /// The memory alignment the allocator should use

   private:
    S small_;  /// The small allocator
    L large_;  /// The large allocator
};
}

#endif

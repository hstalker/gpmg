/// \file      region-allocator.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines a contiguous region allocator that takes a reserved
/// memory block.

#ifndef GPMG_ALLOCATORS_REGION_ALLOCATOR_HPP
#define GPMG_ALLOCATORS_REGION_ALLOCATOR_HPP

#include <type_traits>
#include "allocator-traits.hpp"
#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/assert.hpp"

namespace gpmg {

/// An allocator that takes a fixed size buffer and allocates linearly into
/// that.
/// Allocation is merely a pointer addition. Can not deallocate piecewise.
class RegionAllocator {
   public:
    RegionAllocator(void* b, unsigned int size)
        : beg_(static_cast<u8*>(b)), end_(beg_ + size), p_(beg_) {}
    ~RegionAllocator() = default;
    RegionAllocator(const RegionAllocator&) = default;
    RegionAllocator(RegionAllocator&&) = default;
    RegionAllocator& operator=(const RegionAllocator&) = default;
    RegionAllocator& operator=(RegionAllocator&&) = default;

    /// Allocates a block of memory of a given size
    /// \param n The size of memory to try to allocate
    /// \return A pointer to the newly allocated block if successful,
    /// a nullptr if unsuccessful.
    void* allocate(std::size_t n) {
        // If there isn't enough room for the allocation just return a nullptr
        if (static_cast<std::size_t>(end_ - p_) < n) {
            return nullptr;
        }

        // Store the current position and bump the pointer
        auto result = p_;
        p_ += n;

        // Return the old pointer position
        return result;
    }

    /// Tests whether this allocator instance owns the memory given
    /// \param b Pointer to the block of memory which is being checked for
    /// ownership
    /// \return Whether the memory is owned by this allocator or not
    bool owns(void* b) {
        // Check if the pointer address lies within the range between the
        // beginning and end of the region
        return beg_ <= static_cast<u8*>(b) && end_ >= static_cast<u8*>(b);
    }

    unsigned int alignment =
        1;  /// The memory alignment the allocator should use

   private:
    u8* beg_;  /// Pointer to the beginning of the region
    u8* end_;  /// Pointer to the end of the region
    u8* p_;    /// Pointer to the current position in the region
};
}

#endif

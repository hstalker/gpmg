/// \file      malloc-allocator.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines a basic malloc based allocator.

#ifndef GPMG_ALLOCATORS_MALLOC_ALLOCATOR_HPP
#define GPMG_ALLOCATORS_MALLOC_ALLOCATOR_HPP

#include <cstdlib>
#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/assert.hpp"

namespace gpmg {

/// A very basic allocator utilising malloc
class MallocAllocator {
   public:
    MallocAllocator() = default;
    ~MallocAllocator() = default;
    MallocAllocator(const MallocAllocator&) = default;
    MallocAllocator(MallocAllocator&&) = default;
    MallocAllocator& operator=(const MallocAllocator&) = default;
    MallocAllocator& operator=(MallocAllocator&&) = default;

    /// Allocates a block of memory of a given size
    /// \param n The size of memory to try to allocate
    /// \return A pointer to the newly allocated block if successful,
    /// a nullptr if unsuccessful.
    void* allocate(std::size_t n) { return malloc(n); }

    /// Deallocates the given memory block if possible
    /// \param b The memory block to try to deallocate
    void deallocate(void* b) { free(b); }

    unsigned int alignment = 1; /// The memory alignment the allocator should use
};
}

#endif

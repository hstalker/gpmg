/// \file      basic-allocator.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines a basic no-op allocator.

#ifndef GPMG_ALLOCATORS_BASIC_ALLOCATOR_HPP
#define GPMG_ALLOCATORS_BASIC_ALLOCATOR_HPP

#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/assert.hpp"

namespace gpmg {

/// The most basic allocator that is legal to be defined. This requires only an
/// alignment and an allocate method.
class BasicAllocator {
   public:
    BasicAllocator() = default;
    ~BasicAllocator() = default;
    BasicAllocator(const BasicAllocator&) = default;
    BasicAllocator(BasicAllocator&&) = default;
    BasicAllocator& operator=(const BasicAllocator&) = default;
    BasicAllocator& operator=(BasicAllocator&&) = default;

    void* allocate(std::size_t n) {
        // Does nothing
        UNUSED(n)
        return nullptr;
    }

    unsigned int alignment = 1;
};
}

#endif

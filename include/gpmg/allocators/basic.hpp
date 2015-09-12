/// \file      basic.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines a basic no-op allocator.

#ifndef GPMG_ALLOCATORS_BASIC_HPP
#define GPMG_ALLOCATORS_BASIC_HPP

#include <type_traits>
#include "allocator-traits.hpp"
#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/assert.hpp"

namespace gpmg {

class Basic {
   public:
    Basic() = default;
    ~Basic() = default;
    Basic(const Basic&) = default;
    Basic(Basic&&) = default;
    Basic& operator=(const Basic&) = default;
    Basic& operator=(Basic&&) = default;

    void* allocate(std::size_t n) {
        // Does nothing
        UNUSED(n)
        return nullptr;
    }

    unsigned int alignment = 1;
};
}

#endif

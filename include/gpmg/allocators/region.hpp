/// \file      region.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines a contiguous region allocator that takes a reserved
/// memory block.

#ifndef GPMG_ALLOCATORS_REGION_HPP
#define GPMG_ALLOCATORS_REGION_HPP

#include <type_traits>
#include "allocator-traits.hpp"
#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/assert.hpp"

namespace gpmg {

class Region {
   public:
    Region(void* b, unsigned int size)
        : b_(static_cast<u8*>(b)), e_(b_ + size), p_(b_) {}
    ~Region() = default;
    Region(const Region&) = default;
    Region(Region&&) = default;
    Region& operator=(const Region&) = default;
    Region& operator=(Region&&) = default;

    void* allocate(std::size_t n) {
        if (static_cast<std::size_t>(e_ - p_) < n) {
            return nullptr;
        }

        auto result = p_;
        p_ += n;

        return result;
    }

    void deallocate(void* b) {
        if (owns(b)) {
            p_ -= (static_cast<u8*>(b) - b_);
        }
    }

    bool owns(void* b) {
        return b_ <= static_cast<u8*>(b) && e_ >= static_cast<u8*>(b);
    }

    unsigned int alignment = 1;

   private:
    u8 *b_, *e_, *p_;
};
}

#endif

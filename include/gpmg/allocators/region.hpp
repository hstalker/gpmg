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
    Region(void* buf, unsigned int size)
        : b(static_cast<u8*>(buf)), e(b + size), p(b) {}
    ~Region() = default;
    Region(const Region&) = default;
    Region(Region&&) = default;
    Region& operator=(const Region&) = default;
    Region& operator=(Region&&) = default;

    void* allocate(std::size_t n) {
        if (static_cast<std::size_t>(e - p) < n) {
            return nullptr;
        }

        auto result = p;
        p += n;

        return result;
    }

    unsigned int alignment = 1;

   private:
    u8 *b, *e, *p;
};

/*
namespace detail {
template<typename T, typename
std::enable_if<!has_member_func_allocate1<T>::value>::type* = nullptr>
void allocateDispatch(const T& allocater)
{
}

template<typename T, typename
std::enable_if<has_member_func_allocate1<T>::value>::type* = nullptr>
void allocateDispatch(const T& allocater)
{
    allocater.allocate();
}
}*/
}

#endif

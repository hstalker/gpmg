/// \file      mallocator.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines a basic malloc based allocator.

#ifndef GPMG_ALLOCATORS_MALLOCATOR_HPP
#define GPMG_ALLOCATORS_MALLOCATOR_HPP

#include <cstdlib>
#include <type_traits>
#include "allocator-traits.hpp"
#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/assert.hpp"

namespace gpmg {

class Mallocator {
   public:
    Mallocator() = default;
    ~Mallocator() = default;
    Mallocator(const Mallocator&) = default;
    Mallocator(Mallocator&&) = default;
    Mallocator& operator=(const Mallocator&) = default;
    Mallocator& operator=(Mallocator&&) = default;

    void* allocate(std::size_t n) { return malloc(n); }

    unsigned int alignment = 1;
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

/// \file      fallback-allocator.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines a simple composite allocator, containing a main and
/// fallback allocator.

#ifndef GPMG_ALLOCATORS_FALLBACK_ALLOCATOR_HPP
#define GPMG_ALLOCATORS_FALLBACK_ALLOCATOR_HPP

#include <type_traits>
#include "allocator-traits.hpp"
#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/assert.hpp"

namespace gpmg {

template <typename T>
constexpr T min(const T arg1, const T arg2) {
    return arg1 <= arg2 ? arg1 : arg2;
}

template <typename P, typename F>
class FallbackAllocator {
   public:
    static_assert(has_member_func_allocate<P>::value &&
                      has_member_func_allocate<F>::value,
                  "Allocaters MUST have a void allocate(size_t) function!");
    static_assert(has_member_var_alignment<P>::value &&
                      has_member_var_alignment<F>::value,
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

    void* allocate(std::size_t n) {
        auto r = primary_.allocate(n);
        if (r == nullptr) {
            r = fallback_.allocate(n);
        }
        return r;
    }

    unsigned int alignment;

   private:
    P primary_;
    F fallback_;
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

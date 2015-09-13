/// \file      tools.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines standard utilities useful for defining statically
/// introspective allocators.

#ifndef GPMG_ALLOCATORS_TOOLS_HPP
#define GPMG_ALLOCATORS_TOOLS_HPP

#include "../misc/types.hpp"
#include "../misc/platform.hpp"
#include "../misc/static-introspection.hpp"

namespace gpmg {
namespace tools {
// Generate all the member function/variable determining traits
GENERATE_HAS_MEMBER_FUNC(void*, allocate, std::size_t)
GENERATE_HAS_MEMBER_VAR(unsigned int, alignment)
GENERATE_HAS_MEMBER_FUNC(bool, owns, void*)
GENERATE_HAS_MEMBER_FUNC(void, deallocate, void*)
GENERATE_HAS_MEMBER_FUNC(bool, reallocate, void*, std::size_t, std::size_t)
GENERATE_HAS_MEMBER_FUNC(bool, expand, void*, std::size_t, std::size_t)

// The SFINAE functions that attempt to call member functions of an allocator
/// Do nothing if the given allocator has no appropriate allocate method
template <typename T, typename std::enable_if<
                          !hasMemberFunc_deallocate<T>::value>::type* = nullptr>
void* tryToAllocate(T& allocator, std::size_t size) {
    UNUSED(allocator);
    UNUSED(size);
    return nullptr;
}

/// Deallocate given buffer using the given allocator's allocate method
template <typename T, typename std::enable_if<
                          hasMemberFunc_deallocate<T>::value>::type* = nullptr>
void* tryToAllocate(T& allocator, std::size_t size) {
    return allocator.allocate(size);
}

/// Do nothing if the given allocator has no appropriate deallocate method
template <typename T, typename std::enable_if<
                          !hasMemberFunc_deallocate<T>::value>::type* = nullptr>
void tryToDeallocate(T& allocator, void* b) {
    UNUSED(allocator);
    UNUSED(b);
}

/// Deallocate given buffer using the given allocator's deallocate method
template <typename T, typename std::enable_if<
                          hasMemberFunc_deallocate<T>::value>::type* = nullptr>
void tryToDeallocate(T& allocator, void* b) {
    allocator.deallocate(b);
}

/// Do nothing if the given allocator has no appropriate expand method
template <typename T, typename std::enable_if<
                          !hasMemberFunc_deallocate<T>::value>::type* = nullptr>
bool tryToExpand(T& allocator, void* b, const std::size_t oldSize,
                 const std::size_t newSize) {
    UNUSED(allocator);
    UNUSED(b);
    UNUSED(oldSize);
    UNUSED(newSize);
    return false;
}

/// Expand given buffer using the given allocator's expand method
template <typename T, typename std::enable_if<
                          hasMemberFunc_deallocate<T>::value>::type* = nullptr>
bool tryToExpand(T& allocator, void* b, const std::size_t oldSize,
                 const std::size_t newSize) {
    if (oldSize <= newSize && allocator.expand(b, newSize - oldSize)) {
        return true;
    }
}
}
}

/// A macro that checks if the bare necessities of one of our allocators are
/// present via static assertions
#define ALLOCATOR_WELLFORMED(Allocator)                                      \
    static_assert(tools::hasMemberFunc_allocate<Allocator>::value,           \
                  "Allocators MUST have a void allocate(size_t) function!"); \
    static_assert(tools::hasMemberVar_alignment<Allocator>::value,           \
                  "Allocators MUST have a uint alignment variable!");

#endif

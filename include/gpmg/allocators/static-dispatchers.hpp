/// \file      static-dispatchers.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines various SFINAE based static dispatch functions for use in
/// the allocators.

#ifndef GPMG_ALLOCATORS_STATIC_DISPATCHERS_HPP
#define GPMG_ALLOCATORS_STATIC_DISPATCHERS_HPP

#include "allocator-traits.hpp"
#include "../misc/platform.hpp"

namespace gpmg {    
    namespace detail {
        /// Do nothing if the given allocator has no appropriate allocate method
        template <typename T, typename std::enable_if<!hasMemberFunc_deallocate<T>::value>::type* = nullptr>
        void* tryToAllocate(T& allocator, std::size_t size) {
            UNUSED(allocator);
            UNUSED(size);
            return nullptr;
        }

        /// Deallocate given buffer using the given allocator's allocate method
        template <typename T,
                  typename std::enable_if<hasMemberFunc_deallocate<T>::value>::type* =
                  nullptr>
        void* tryToAllocate(T& allocator, std::size_t size) {
            return allocator.allocate(size);
        }

        /// Do nothing if the given allocator has no appropriate deallocate method
        template <typename T, typename std::enable_if<!hasMemberFunc_deallocate<T>::value>::type* = nullptr>
        void tryToDeallocate(T& allocator, void* b) {
            UNUSED(allocator);
            UNUSED(b);
        }

        /// Deallocate given buffer using the given allocator's deallocate method
        template <typename T,
                  typename std::enable_if<hasMemberFunc_deallocate<T>::value>::type* =
                  nullptr>
        void tryToDeallocate(T& allocator, void* b) {
            allocator.deallocate(b);
        }

        /// Do nothing if the given allocator has no appropriate expand method
        template <typename T, typename std::enable_if<!hasMemberFunc_deallocate<T>::value>::type* = nullptr>
        bool tryToExpand(T& allocator, void* b, const std::size_t oldSize, const std::size_t newSize) {
            UNUSED(allocator);
            UNUSED(b);
            UNUSED(oldSize);
            UNUSED(newSize);
            return false;
        }

        /// Expand given buffer using the given allocator's expand method
        template <typename T,
                  typename std::enable_if<hasMemberFunc_deallocate<T>::value>::type* =
                  nullptr>
        bool tryToExpand(T& allocator, void* b, const std::size_t oldSize, const std::size_t newSize) {
            if (oldSize <= newSize && allocator.expand(b, newSize - oldSize)) {
                return true;
            }
        }
    }
}

#endif

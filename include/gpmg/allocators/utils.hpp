/// \file      utils.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines various utility functions for use in the allocators.

#ifndef GPMG_ALLOCATORS_UTILS_HPP
#define GPMG_ALLOCATORS_UTILS_HPP

#include <cstring>
#include "static-dispatchers.hpp"

namespace gpmg {

    /// A global allocate function for our generic allocators
    /// \tparam T The allocator type
    /// \param a An instance of the allocator
    /// \param size Size of the block of memory to allocate
    /// \return A pointer to the allocated block of memory if successful,
    /// a nullptr if unsuccessful
    template <typename T>
    void* allocate(T& a, std::size_t size) {
        // Deallocate old buffer if possible
        return detail::tryToAllocate<T>(size);
    }

    /// A global deallocate function for our generic allocators
    /// \tparam T The allocator type
    /// \param a An instance of the allocator
    /// \param b Pointer to a given block of memory to deallocate
    template <typename T>
    void deallocate(T& a, void* b) {
        // Deallocate old buffer if possible
        detail::tryToDeallocate<T>(b);
    }
    
    /// A global reallocate function for our generic allocators
    /// \tparam T The allocator type
    /// \param a An instance of the allocator
    /// \param b Pointer to a given block of memory to reallocate
    /// \param oldSize The size of the old block of memory
    /// \param newSize The size of the new block of memory
    template <typename T>
    bool reallocate(T& a, void* b, const std::size_t oldSize, const std::size_t newSize) {
        // Break out successfully if the buffer hasn't changed size
        if (oldSize == newSize) {
            return true;
        }

        // Break out successfully if the buffer is able to be expanded to the new size
        if (detail::tryToExpand<T>(a, b, oldSize, newSize)) {
            return true;
        }

        // Try to allocate more memory of the new size
        void* r = a.allocate(newSize);
        if (r == nullptr) {
            return false;
        }

        // Deallocate old buffer if possible
        detail::tryToDeallocate<T>(b);
        
        b = r;
        return true;
    }

    /// Attempt to move a given buffer across primary and fallback allocators
    /// \tparam From The type of the allocator to move from
    /// \tparam To The type of the allocator to move to
    /// \param b Pointer to the block of memory to move
    /// \param from The allocator to move from
    /// \param to The allocator to move to
    /// \param oldSize The size of the old block of memory
    /// \parama newSize The size of the new block of memory
    template <typename From, typename To>
    bool crossAllocatorMove(void* b, From& from, To& to, std::size_t oldSize, std::size_t newSize) {
        // Try to allocate memory at the destination
        void* dest = to.allocate(newSize);
        // Return unsucessfully if the allocation failed
        if (dest == nullptr) {
            return false;
        }

        // Copy the buffer from 'from' to 'to'
        memcpy(dest, b, newSize);
    
        // Try to deallocate the old buffer if possible
        detail::tryToDeallocate<From>(b);

        // Set the input pointer to point at the newly allocated 
        b = dest;
        return true;
    }
}

#endif

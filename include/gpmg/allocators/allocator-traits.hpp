/// \file      allocator-traits.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines various static introspection traits for allocators.

#ifndef GPMG_ALLOCATORS_ALLOCATOR_TRAITS_HPP
#define GPMG_ALLOCATORS_ALLOCATOR_TRAITS_HPP

#include "../misc/static-introspection.hpp"

namespace gpmg {
GENERATE_HAS_MEMBER_FUNC(void*, allocate, std::size_t)
GENERATE_HAS_MEMBER_VAR(unsigned int, alignment)
GENERATE_HAS_MEMBER_FUNC(bool, owns, void*)
GENERATE_HAS_MEMBER_FUNC(void, deallocate, void*)
GENERATE_HAS_MEMBER_FUNC(bool, reallocate, void*, std::size_t, std::size_t)
GENERATE_HAS_MEMBER_FUNC(bool, expand, void*, std::size_t)
}

#endif

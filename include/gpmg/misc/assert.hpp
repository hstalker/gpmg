/// \file      assert.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines various assertion handling macros and functions.

#ifndef GPMG_MISC_ASSERT_HPP
#define GPMG_MISC_ASSERT_HPP

#include <cassert>
#include <type_traits>  // for static_assert

/// Assert macro. Has a description field for assert related
/// information
#define GPMG_ASSERT(expr, description) assert(expr&& description)

#endif

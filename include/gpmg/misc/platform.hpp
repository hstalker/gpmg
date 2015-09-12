/// \file      platform.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines various useful utilities wrapping around compiler
/// dependent functionality.

#ifndef GPMG_MISC_PLATFORM_HPP
#define GPMG_MISC_PLATFORM_HPP

/// No-op that stops unused parameter warnings in compilers
#define UNUSED(arg) ((void)&(arg));

#ifndef _MSC_VER
/// Indicates to the compiler the likely branch for optimisation purposes
#define UNLIKELY(expr) __builtin_expect(!!(expr), 0)
/// Indicates to the compiler the unlikely branch for optimisation purposes
#define LIKELY(expr) __builtin_expect(!!(expr), 1)
#else
#define UNLIKELY(expr) (expr)
#define LIKELY(expr) (expr)
#endif

#if defined(__GNUC__) || defined(__HP_aCC) || defined(__clang__)
/// Forces the compiler to inline the tagged function/method
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE __forceinline
#endif

#endif

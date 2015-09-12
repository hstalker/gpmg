/// \file      static-introspection.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines macros for generating traits for static introspection.

#ifndef GPMG_MISC_STATIC_INTROSPECTION_HPP
#define GPMG_MISC_STATIC_INTROSPECTION_HPP

/// Generate a trait has_member_func_***, where *** is the member function
/// name
#define GENERATE_HAS_MEMBER_FUNC(returnType, name, ...)                   \
    \
template<typename T> \
class has_member_func_##name {                                            \
    \
private:                                                                  \
        typedef char Yes;                                                 \
        typedef Yes No[2];                                                \
                                                                          \
        template <typename U, U>                                          \
        struct really_has;                                                \
                                                                          \
        template <typename C>                                             \
        static Yes& Test(                                                 \
            really_has<returnType (C::*)(__VA_ARGS__) const, &C::name>*); \
                                                                          \
        template <typename C>                                             \
        static Yes& Test(                                                 \
            really_has<returnType (C::*)(__VA_ARGS__), &C::name>*);       \
                                                                          \
        template <typename>                                               \
        static No& Test(...);                                             \
    \
\
public:                                                                   \
        static bool const value = sizeof(Test<T>(0)) == sizeof(Yes);      \
    \
};

/// Generate a trait has_member_var_*** where *** is the member variable name
#define GENERATE_HAS_MEMBER_VAR(type, name)                          \
    \
template<typename T> \
class has_member_var_##name {                                        \
    \
private:                                                             \
        typedef char Yes;                                            \
        typedef Yes No[2];                                           \
                                                                     \
        template <typename U, U>                                     \
        struct really_has;                                           \
                                                                     \
        template <typename C>                                        \
        static Yes& Test(really_has<type(C::*), &C::name>*);         \
                                                                     \
        template <typename>                                          \
        static No& Test(...);                                        \
    \
\
public:                                                              \
        static bool const value = sizeof(Test<T>(0)) == sizeof(Yes); \
    \
};

/// Generate a set of traits for checking for any member type
#define GENERATE_HAS_MEMBER_ANY(type, name) \
    GENERATE_HAS_MEMBER_FUNC(type, name)    \
    GENERATE_HAS_MEMBER_VAR(type, name)

#endif

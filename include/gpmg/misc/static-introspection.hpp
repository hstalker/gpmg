/// \file      static-introspection.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines macros for generating traits for static introspection.

#ifndef GPMG_MISC_STATIC_INTROSPECTION_HPP
#define GPMG_MISC_STATIC_INTROSPECTION_HPP

/// Generate a trait hasMemberFunc_***, where *** is the member function
/// name
#define GENERATE_HAS_MEMBER_FUNC(returnType, name, ...)                     \
    \
template<typename T_> \
class hasMemberFunc_##name {                                                \
    \
private:                                                                    \
        typedef char Yes_;                                                  \
        typedef Yes_ No_[2];                                                \
                                                                            \
        template <typename U_, U_>                                          \
        struct ReallyHas_;                                                  \
                                                                            \
        template <typename C_>                                              \
        static Yes_& test_(                                                 \
            ReallyHas_<returnType (C_::*)(__VA_ARGS__) const, &C_::name>*); \
                                                                            \
        template <typename C_>                                              \
        static Yes_& test_(                                                 \
            ReallyHas_<returnType (C_::*)(__VA_ARGS__), &C_::name>*);       \
                                                                            \
        template <typename>                                                 \
        static No_& test_(...);                                             \
    \
\
public:                                                                     \
        static bool const value = sizeof(test_<T_>(0)) == sizeof(Yes_);     \
    \
};

/// Generate a trait hasMemberVar_*** where *** is the member variable name
#define GENERATE_HAS_MEMBER_VAR(type, name)                             \
    \
template<typename T_> \
class hasMemberVar_##name {                                             \
    \
private:                                                                \
        typedef char Yes_;                                              \
        typedef Yes_ No_[2];                                            \
                                                                        \
        template <typename U_, U_>                                      \
        struct ReallyHas_;                                              \
                                                                        \
        template <typename C_>                                          \
        static Yes_& test_(ReallyHas_<type(C_::*), &C_::name>*);        \
                                                                        \
        template <typename>                                             \
        static No_& test_(...);                                         \
    \
\
public:                                                                 \
        static bool const value = sizeof(test_<T_>(0)) == sizeof(Yes_); \
    \
};

/// Generate a set of traits for checking for any member type
#define GENERATE_HAS_MEMBER_ANY(type, name) \
    GENERATE_HAS_MEMBER_FUNC(type, name)    \
    GENERATE_HAS_MEMBER_VAR(type, name)

#endif

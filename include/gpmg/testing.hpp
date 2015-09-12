/// \file      testing.hpp
/// \author    Hector Stalker
/// \copyright Copyright 2015 Hector Stalker. All rights reserved.
///            This project is released under the MIT License.
/// \brief     Defines very basic code testing macros (Designed to be
/// lightweight).

#ifndef GPMG_TESTING_HPP
#define GPMG_TESTING_HPP

#include <cstdio>
#include "misc/platform.hpp"

namespace gpmg {
namespace detail {
/// \brief Returns the number of failed tests in the current compilation module
/// \return The number of currently failed tests
FORCE_INLINE int& failedCount() {
    static int failedTestCount = 0;
    return failedTestCount;
}

/// \brief Returns the number of successfully run tests in the current
/// compilation module
/// \return The number of currently successful tests
FORCE_INLINE int& successfulCount() {
    static int successfulTestCount = 0;
    return successfulTestCount;
}

/// \brief Runs a test and prints a failure message upon failure
/// \param success The boolean resulting test statement
/// \param expr The test statement in string format
/// \param description Description of the test being run
/// \param sourceFile Name of the file in which the test is found
/// \param lineNo Line number of the test being run
FORCE_INLINE void runTest(const bool success, const char* const expr,
                          const char* const description,
                          const char* const sourceFile, const int lineNo) {
    if (!success) {
        ++failedCount();
        std::printf("Failed test: %s\nCode: %s\nFile: %s, Line %d\n",
                    description, expr, sourceFile, lineNo);
    } else {
        ++successfulCount();
    }
}
}
}

/// A boolean check that prints to stdout upon failure
#define CHECK(expr, description)                                             \
    gpmg::detail::runTest(expr ? true : false, #expr, description, __FILE__, \
                          __LINE__);

/// Macro for returning the number of currently failed tests
#define FAILED_TEST_RESULTS() gpmg::detail::failedCount();

/// Macro for returning the number of currently failed tests
#define SUCCESSFUL_TEST_RESULTS() gpmg::detail::successfulCount();

#endif

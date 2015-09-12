enable_testing()

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1
                        ${CMAKE_CTEST_COMMAND} -C $<CONFIG>
                        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
)

include_directories(${PROJECT_SOURCE_DIR}/include)

function(makeTest name source)
    add_executable(${name} ${source})
    add_test(NAME ${name} COMMAND ${name})
    add_dependencies(check ${name})
endfunction(makeTest)


# Add tests ####################################################################
makeTest(test-allocators test-allocators.cpp)

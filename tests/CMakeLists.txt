# Creates the test executable that will run all unit tests
add_executable(dstruct-test Example-Test.cpp)

# Link to the header-only library and GoogleTest
target_link_libraries(dstruct-test 
    PRIVATE 
        # Links to the header-only dstruct library
        dstruct
        
        # Links to GoogleTest main library, which provides the main() function
        # to run the tests and the testing framework itself
        GTest::gtest_main
)

# Includes GoogleTest-specific CMake macros
include(GoogleTest)

# Searches the compiled executable for all defined tests (using TEST/TEST_F macros)
# and registers them with CTest. This allows you to run tests using the 'ctest' command
gtest_discover_tests(dstruct-test)

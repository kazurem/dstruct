cmake_minimum_required(VERSION 3.15)
project(dstruct)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Header-Only Library Definition ---

# Create an interface library for the header-only template library
add_library(dstruct INTERFACE)

# Include directories - PUBLIC so consumers automatically get these paths
target_include_directories(dstruct INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Compiler options
target_compile_options(dstruct INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)

# --- Main Executable for Testing ---

# Add executable for main.cpp to test the header library
add_executable(main main.cpp)
target_link_libraries(main PRIVATE dstruct)

# --- Testing Support ---

# Optional: Enable testing if tests are added
option(BUILD_TESTING "Build the testing tree" OFF)

if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
    
    # Include the CTest module for test registration and management
    include(CTest)
    
    # Add the 'tests' subdirectory
    add_subdirectory(tests)
endif()

# --- Installation ---

# Install the header files
install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")

# Install the library target
install(TARGETS dstruct EXPORT dstructTargets)
install(EXPORT dstructTargets
    FILE dstructTargets.cmake
    NAMESPACE dstruct::
    DESTINATION lib/cmake/dstruct
)

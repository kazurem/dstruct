# dstruct
A header-only library containing famous data structures implemented from scratch using C++.

## Installation:
### Option 1: System-wide (or Local Install)
You can install the headers and CMake configuration files to a specific directory to use them in multiple projects.
```bash
# Clone the repository
git clone https://github.com/yourusername/dstruct.git
cd dstruct

# Configure and install to a local 'dist' folder
cmake -B build -DCMAKE_INSTALL_PREFIX=./dist
cmake --install build
```

### Option 2: Integration via FetchContent (Recommended)
Add dstruct directly to your project's CMakeLists.txt without downloading it manually:
```bash
include(FetchContent)

FetchContent_Declare(
    dstruct
    GIT_REPOSITORY https://github.com/yourusername/dstruct.git
    GIT_TAG main  # Or a specific commit/version
)
FetchContent_MakeAvailable(dstruct)

# Link your target
target_link_libraries(your_project_name PRIVATE dstruct::dstruct)
```

### Usage
If you installed dstruct using Option 1, use find_package in your project's CMakeLists.txt:
```cmake
find_package(dstruct REQUIRED)

add_executable(MyProject main.cpp)
target_link_libraries(MyProject PRIVATE dstruct::dstruct)
```

## Development and Testing
### Building the Test Suite
dstruct uses GoogleTest for unit testing. Testing is disabled by default to keep builds fast for users.

To build and run tests:
```bash
# Enable testing during configuration
cmake -B build -DBUILD_TESTING=ON

# Build the tests
cmake --build build

# Run the tests
cd build && ctest
```

## References:
Some useful references:
1. [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/): A convention for commit messages.
2. [CMake](https://cmake.org/documentation/): Meta build system
3. [EditorConfig](https://editorconfig.org/): Consistent coding styles for multiple developers working on the same project across various editors and IDEs
4. [gitattributes](https://git-scm.com/docs/gitattributes)
5. [Commitizen](https://commitizen-tools.github.io/commitizen/): For standardized commit messages and automatic changelog updation.
6. [clang-format](https://clang.llvm.org/docs/ClangFormat.html): Automatic code formatter provided by LLVM.
7. [clang-tidy](https://clang.llvm.org/extra/clang-tidy/): A Linter provided by LLVM.
8. [pre-commit](https://pre-commit.com/)
9. [Google Test](https://github.com/google/googletest)
10. [Keep a changelog](https://keepachangelog.com/en/1.1.0/)


## Acknowledgements
Thanks to [Nyx-4](https://github.com/nyx-4) for informing me of tools like commitizen and pre-commit-hooks. I modified the CI configuration made by him in [this pull request](https://github.com/kr8457/MicroMouse-Simulator/pull/15).




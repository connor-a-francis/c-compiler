cmake_minimum_required(VERSION 3.16)
project(compiler VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source code
add_subdirectory(src)

# Add tests
enable_testing()
add_subdirectory(tests)


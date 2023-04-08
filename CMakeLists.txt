cmake_minimum_required(VERSION 3.10)
project(bhs_vis VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

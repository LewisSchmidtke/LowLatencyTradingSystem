cmake_minimum_required(VERSION 3.28)
project(LLTS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LLTS_SANITIZER "none" CACHE STRING "Sanitizer: none, address or thread")
set_property(CACHE LLTS_SANITIZER PROPERTY STRINGS none address thread)

if(LLTS_SANITIZER STREQUAL "address")
    add_compile_options(-fsanitize=address,undefined -fno-sanitize-recover=undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
elseif(LLTS_SANITIZER STREQUAL "thread")
    add_compile_options(-fsanitize=thread)
    add_link_options(-fsanitize=thread)
elseif(NOT LLTS_SANITIZER STREQUAL "none")
    message(FATAL_ERROR "LLTS_SANITIZER must be none, address or thread, not '${LLTS_SANITIZER}'")
endif()

option(LLTS_BUILD_BENCHMARKS "Build the benchmark programs" ON)

include(FetchContent)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "" FORCE)

FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        SYSTEM)
FetchContent_Declare(benchmark
        URL https://github.com/google/benchmark/archive/refs/tags/v1.9.1.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        SYSTEM)
FetchContent_MakeAvailable(googletest benchmark)

enable_testing()
include(GoogleTest)

include(cmake/CompilerWarnings.cmake)

add_subdirectory(libs/common)
add_subdirectory(libs/exchange)
add_subdirectory(libs/feed)
add_subdirectory(libs/sim)
add_subdirectory(libs/book)
add_subdirectory(libs/strategy)
add_subdirectory(libs/risk)
add_subdirectory(libs/gateway)
add_subdirectory(libs/logging)
# add_subdirectory(tools/alloc_counter)

add_subdirectory(apps)
if(LLTS_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

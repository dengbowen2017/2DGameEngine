cmake_minimum_required(VERSION 3.15)

project(2DGameEngine 
 LANGUAGES CXX 
 VERSION 1.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME})

set(ECS_FILES
 "src/ECS/Registry.h"
 "src/ECS/Entity.h" 
 "src/ECS/EntityManager.h" 
 "src/ECS/ComponentPool.h" 
 "src/ECS/View.h" 
 "src/ECS/ComponentManager.h" 
)

target_sources(${PROJECT_NAME} PRIVATE 
 ${ECS_FILES} 
 "src/main.cpp"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
 $<$<CONFIG:Debug>:GE_DEBUG>
 $<$<CONFIG:Release>:GE_RELEASE>
)

# Lib for test
add_library(ECS_lib INTERFACE)
target_include_directories(ECS_lib INTERFACE "src/ECS")

# Google Test
include(FetchContent)
FetchContent_Declare(
 googletest
 URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_subdirectory("tests")

# Google Benchmark
FetchContent_Declare(
  google_benchmark
  URL https://github.com/google/benchmark/archive/refs/heads/main.zip
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_DOCS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(google_benchmark)

add_subdirectory("benchmark")
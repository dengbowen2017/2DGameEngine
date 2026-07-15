cmake_minimum_required(VERSION 3.22)

project(2DGameEngine 
	LANGUAGES CXX 
	VERSION 1.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory("vendors")
add_subdirectory("src")

# Lib for test
add_library(ECS_lib INTERFACE)
target_include_directories(ECS_lib INTERFACE "src/ECS")

add_subdirectory("tests")
add_subdirectory("benchmark")
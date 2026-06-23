cmake_minimum_required(VERSION 3.15)

project(2DGameEngine
  LANGUAGES CXX
  VERSION 1.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME})

set(SRC_FILES
 "src/main.cpp"
 "src/ECS/Entity.h")

target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES})

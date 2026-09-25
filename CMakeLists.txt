cmake_minimum_required(VERSION 3.20)
project(dotpack CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_include_directories(dotpack PRIVATE src)

add_executable(dotpack 
  src/main.cpp
  src/commands/link.cpp
  src/config.cpp
)

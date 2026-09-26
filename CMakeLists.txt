cmake_minimum_required(VERSION 3.20)
project(dotpack CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(dotpack 
  src/main.cpp
  src/config.cpp
  src/utils.cpp
  src/commands/push.cpp
  src/commands/link.cpp
  src/commands/scan.cpp
  src/commands/update.cpp
)

target_include_directories(dotpack PRIVATE src)


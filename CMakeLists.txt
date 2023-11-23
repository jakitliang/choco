cmake_minimum_required(VERSION 3.23)
project(choco)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include)

set(THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

add_subdirectory(./src)
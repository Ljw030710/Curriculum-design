cmake_minimum_required(VERSION 3.26)
project(zhuabao)

set(CMAKE_CXX_STANDARD 17)

add_executable(zhuabao main.cpp)
target_link_libraries(zhuabao wsock32 ws2_32)
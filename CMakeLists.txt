cmake_minimum_required(VERSION 3.10)
project(Message-Broker)

set(CMAKE_CXX_STANDARD 17)

add_executable(server server.cpp main.cpp handlers.cpp)


target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.10)
project(NATSServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(nats_server nats_server.cpp main.cpp handlers.cpp)


target_include_directories(nats_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
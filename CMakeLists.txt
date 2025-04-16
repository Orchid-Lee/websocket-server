# 服务端
project(ws-socket)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(HOME ..)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/output)

include_directories(include)

add_executable(websocket-server src/server.cpp)
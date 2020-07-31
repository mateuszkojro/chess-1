cmake_minimum_required(VERSION 3.15)
project(chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(chess main.cpp piece.cpp piece.h board.cpp board.h node.cpp node.h mov.h compare.h compare.cpp)
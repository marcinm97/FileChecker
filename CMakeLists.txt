cmake_minimum_required(VERSION 3.13)
project(FileChecker)

set(CMAKE_CXX_STANDARD 17)
link_libraries(stdc++fs)
add_executable(FileChecker main.cpp FileChecker.h)
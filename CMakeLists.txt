cmake_minimum_required(VERSION 3.16)
project(vmiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(main vmi.cc
        Token.cpp
        TokenTree.cpp
        Logger.cpp
        )

target_include_directories(main PRIVATE .)

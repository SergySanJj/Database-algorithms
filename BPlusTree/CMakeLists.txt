cmake_minimum_required(VERSION 3.12)
project(BPlusTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(BPlusTree main.cpp words.h random.hpp News.h generators.h BPlusTree.h)
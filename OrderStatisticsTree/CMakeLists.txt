cmake_minimum_required(VERSION 3.0)
project(OrderStatisticsTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(OrderStatisticsTree main.cpp words.h random.hpp News.h ostree.h generators.h)
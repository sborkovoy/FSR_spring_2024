cmake_minimum_required(VERSION 3.25)
project(knapsack_2_split)

set(CMAKE_CXX_STANDARD 17)

add_executable(knapsack_2_split main.cpp Parcer.cpp Parcer.h Solver.cpp Solver.h Item.h)

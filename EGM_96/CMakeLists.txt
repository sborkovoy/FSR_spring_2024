cmake_minimum_required(VERSION 3.25)
project(EGM_96_split)

set(CMAKE_CXX_STANDARD 17)

add_executable(EGM_96_split main.cpp Analyser.cpp Analyser.h Presenter.cpp Presenter.h Solver.cpp Solver.h Parcer.cpp Error.h )

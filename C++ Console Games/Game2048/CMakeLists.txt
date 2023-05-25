cmake_minimum_required(VERSION 3.24)
project(Project_2048_game_)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project_2048_game_ main.cpp Game2048.h Game2048.cpp Game.h Game.cpp HallOfFame.h HallOfFame.cpp)

cmake_minimum_required(VERSION 3.19)
project(Game C)

set(CMAKE_C_STANDARD 11)

add_executable(Game main.c Riddles.h Game.h Game.c Highscore.h Highscore.c)
cmake_minimum_required(VERSION 3.16)

project(octopus_games)

set(CMAKE_CXX_STANDARD 11)

add_executable(octopus_games main.cpp AVLTree.h Player.h Group.h Player.cpp PlayerByLevel.h PlayerByLevel.cpp PlayerById.cpp Group.cpp PlayerById.h GameManager.h GameManager.cpp)
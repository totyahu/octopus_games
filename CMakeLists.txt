cmake_minimum_required(VERSION 3.16)

project(octopus_games)

set(CMAKE_CXX_STANDARD 11)

add_executable(octopus_games main.cpp AVLTree.h TreeNode.h Utils.h
        PlayerById.cpp PlayerById.h PlayerByLevel.cpp PlayerByLevel.h
        Group.cpp Group.h GameManager.cpp GameManager.h)
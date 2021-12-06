cmake_minimum_required(VERSION 2.8)
#cmake_minimum_required(VERSION 3.16)

project(octopus_games)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        octopus_games
        main1.cpp
        library1.cpp
        GameManager.cpp
        PlayerInGroup.cpp
        PlayerById.cpp
        PlayerByLevel.cpp
        Group.cpp
        common_fwd.h
        GroupNotEmpty.h GroupNotEmpty.cpp)

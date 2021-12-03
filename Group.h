//
// Created by keren on 29/11/2021.
//
#ifndef GROUP_H
#define GROUP_H
#include "PlayerByLevel.h"
#include "AVLTree.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;
namespace WET1{
    class PlayerByLevel;
    class Group
    {
        int group_id;
        PlayerByLevel * best_player;
        AVLTree<PlayerByLevel>* group_players;

    public:
        Group();
        explicit Group(int group_id);
        ~Group()=default;
        bool operator==(const Group& other_group);
        bool operator<(const Group& other_group);
        bool playerExist(const PlayerByLevel& player);
        void addPlayer(const PlayerByLevel& player);
        void removePlayer(const PlayerByLevel& player);//TODO:find max player after remove
        void increaseLevel(PlayerByLevel& player,int increase_level);
        int getHighestLevel();
        bool isEmpty() const;
        int getId();
        int getSize();
        int getBestPlayerId();
        bool mergeGroup(Group* other_group);
        void printPlayers();

        void toSortedArray(PlayerByLevel* dest_arr);
    };
}
#endif //OCTOPUS_GAMES_GROUP_H

//
// Created by keren on 29/11/2021.
//
#ifndef GROUP_H
#define GROUP_H
#include "PlayerByLevel.h"
#include "AVLTree.h"

namespace WET1{

    class Group
    {
        int group_id;
        PlayerByLevel * best_player;
        AVLTree<PlayerByLevel> * group_players;

    public:
        Group(int group_id);
        ~Group()=default;
        bool operator==(const Group& other_group);
        bool operator<(const Group& other_group);
        bool playerExist(const PlayerByLevel& player);
        void addPlayer(const PlayerByLevel& player);
        void removePlayer(const PlayerByLevel& player);//TODO:find max player after remove
        bool margeGroups(Group& other_group);
        void increaseLevel(PlayerByLevel& player,int increase_level);
        int getHighestLevel();
        bool isEmpty();


    };
}
#endif //OCTOPUS_GAMES_GROUP_H

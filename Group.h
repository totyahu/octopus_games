#ifndef GROUP_H
#define GROUP_H


#include <string>
#include <iostream>
#include <cstdio>

#include "AVLTree.h"
#include "common_fwd.h"


using namespace std;

namespace WET1{



    class Group
    {
        int group_id;
        PlayerInGroup * best_player;
        AVLTree<PlayerInGroup>* group_players;


    public:
        Group();
        explicit Group(int group_id);
        ~Group();
        bool operator==(const Group& other_group);
        bool operator<(const Group& other_group);
        bool playerExist(const PlayerInGroup& player);
        void addPlayer(const PlayerInGroup& player);
        void removePlayer(const PlayerInGroup& player);//TODO:find max player after remove
        void increaseLevel(PlayerInGroup& player,int increase_level);
        int getHighestLevel();
        bool isEmpty() const;
        int getId();
        int getSize();
        int getBestPlayerId();
        bool mergeGroup(Group* other_group);
        void printPlayers();

        void toSortedArray(PlayerInGroup* dest_arr);
    };
}
#endif //OCTOPUS_GAMES_GROUP_H

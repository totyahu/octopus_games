//
// Created by keren on 30/11/2021.
//

#ifndef PLAYERBYLEVEL_H
#define PLAYERBYLEVEL_H
#include "Group.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;
namespace WET1{
    class Group;
    class PlayerByLevel{
        int player_id;
        int player_level;
        Group* player_group;
    public:
        PlayerByLevel()=default;
        PlayerByLevel(int player_id, int player_level, Group* player_group);
        PlayerByLevel(const PlayerByLevel& other)=default;
        ~PlayerByLevel()=default;//destructor
        bool operator<(const PlayerByLevel& other_player)const;
        PlayerByLevel& operator=(const PlayerByLevel& player);
        bool operator==(const PlayerByLevel& other_player)const;
        void increaseLevel(int LevelIncrease);
        int getIdPlayer();
        Group* getGroup();
        int getLevelPlayer();
        friend std::ostream& operator<<(std::ostream& os,const PlayerByLevel& player);

    };
}

#endif //PLAYERBYLEVEL_H

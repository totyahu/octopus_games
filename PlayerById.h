
#ifndef PLAYERBYID_H
#define PLAYERBYID_H
#include "Group.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;
namespace WET1{
    class Group;
    class PlayerById{
        int player_id;
        int player_level;
        Group* player_group;
    public:
        PlayerById()=default;
        PlayerById(int player_id, int player_level, Group* player_group);
        PlayerById(const PlayerById& other)=default;
        ~PlayerById()=default;//destructor
        bool operator<(const PlayerById& other_player)const;
        PlayerById& operator=(const PlayerById& player);
        bool operator==(const PlayerById& other_player)const;
        void increaseLevel(int LevelIncrease);
        int getIdPlayer();
        Group* getGroup();
        int getLevelPlayer();
        friend std::ostream& operator<<(std::ostream& os,const PlayerById& player);
    };
}

#endif //PLAYERBYID_H

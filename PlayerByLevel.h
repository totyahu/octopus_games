//
// Created by keren on 30/11/2021.
//

#ifndef PLAYERBYLEVEL_H
#define PLAYERBYLEVEL_H
#include "Group.h"
namespace WET1{
    class PlayerByLevel{
        int player_id;
        int player_level;
        Group * player_group;
    public:
        PlayerByLevel(int player_id,int player_level,Group * player_group);
        PlayerByLevel(const PlayerByLevel& other)=default;
        ~PlayerByLevel()=default;//destructor
        bool operator<(const PlayerByLevel& other_player);
        PlayerByLevel& operator=(const PlayerByLevel& player);
        bool operator==(const PlayerByLevel& other_player);
        void increaseLevel(int LevelIncrease);
        int getIdPlayer();
        Group* getGroup();
        int getLevelPlayer()

    };
}

#endif //PLAYERBYLEVEL_H

#ifndef PLAYERBYLEVEL_H
#define PLAYERBYLEVEL_H

//#pragma once

#include <string>
#include <iostream>

//#include "PlayerByLevel.fwd.h"
//#include "Group.fwd.h"

#include "common_fwd.h"


using namespace std;

namespace WET1{


    class PlayerByLevel{
        int player_id;
        int player_level;
        Group* player_group;

    public:
        PlayerByLevel()=default;
        PlayerByLevel(int player_id, int player_level, Group* player_group);
        PlayerByLevel(const PlayerByLevel& other)=default;
        ~PlayerByLevel()=default;
        PlayerByLevel& operator=(const PlayerByLevel& player);
        bool operator<(const PlayerByLevel& other_player)const;
        bool operator==(const PlayerByLevel& other_player)const;
        void increaseLevel(int LevelIncrease);
        int getIdPlayer() const;
        Group* getGroup() const;
        int getLevelPlayer() const;
        void changeGroup(Group* new_group);
        friend std::ostream& operator<<(std::ostream& os, const PlayerByLevel& player);
    };
}

#endif //PLAYERBYLEVEL_H

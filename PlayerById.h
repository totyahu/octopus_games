
#ifndef PLAYERBYID_H
#define PLAYERBYID_H
#include "Group.h"

namespace WET1{
    class PlayerById{
        int player_id;
        int player_level;
        Group* player_group;
    public:
        PlayerById(int player_id, int player_level, Group* player_group);
        PlayerById(const PlayerById& other)=default;
        ~PlayerById()=default;//destructor
        bool operator<(const PlayerById& other_player);
        PlayerById& operator=(const PlayerById& player);
        bool operator==(const PlayerById& other_player);
        void increaseLevel(int LevelIncrease);
        int getIdPlayer();
        Group* getGroup();
        int getLevelPlayer();
    };
}

#endif //PLAYERBYID_H

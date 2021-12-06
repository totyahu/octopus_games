#ifndef PLAYERINGROUP_H
#define PLAYERINGROUP_H


#include <string>
#include <iostream>

#include "common_fwd.h"


using namespace std;

namespace WET1{




    class PlayerInGroup {
        int player_id;
        int player_level;
        Group* player_group;
        PlayerById* by_id_instance;
        PlayerByLevel* by_level_instance;

    public:
        PlayerInGroup()=default;
        PlayerInGroup(int player_id, int player_level, Group* player_group,
                      PlayerById* by_id_instance,
                      PlayerByLevel* by_level_instance) noexcept;
        explicit PlayerInGroup(const PlayerByLevel& player);
        PlayerInGroup(const PlayerInGroup& other)=default;
        ~PlayerInGroup()=default;

        bool operator<(const PlayerInGroup& other_player)const;
        PlayerInGroup& operator=(const PlayerInGroup& player);
        bool operator==(const PlayerInGroup& other_player)const;
        void increaseLevel(int LevelIncrease);
        int getIdPlayer();
        Group* getGroup();
        int getLevelPlayer();
        void changeGroup(Group* new_group);
        friend std::ostream& operator<<(std::ostream& os,const PlayerInGroup& player);
    };

}

#endif //PLAYERINGROUP_H

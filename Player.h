
#ifndef PLAYER_H
#define PLAYER_H
#include "Group.h"

using namespace std;
namespace WET1{

    class Player
    {
        int player_id;
        int player_level;
        Group* player_group;

    public:
        Player(int player_id, int player_level, Group* player_group);
        Player(Player)
        ~Player()=default;//destructor
        Player& operator=(const Player& player);
        bool operator==(const Player& other_player);
        //bool operator<(const Player& player)=0; //virtual function
        void increaseLevel(int LevelIncrease);
        int getIdPlayer();
        Group* getGroup();
        int getLevelPlayer();

    };
}


#endif //OCTOPUS_GAMES_PLAYER_H

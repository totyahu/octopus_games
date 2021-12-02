//
// Created by keren on 30/11/2021.
//

#include "PlayerByLevel.h"
using namespace WET1;

PlayerByLevel::PlayerByLevel(int player_id, int player_level, Group* player_group):
player_id(player_id),player_level(player_level){
    this->player_group = player_group;
}

bool PlayerByLevel::operator<(const PlayerByLevel& other_player) {
    if(this->player_level == other_player.player_level){
     return this->player_id > other_player.player_id;
    }
      return this->player_level < other_player.player_level;
}

PlayerByLevel& PlayerByLevel::operator=(const PlayerByLevel& player){
    this->player_id = player.player_id;
    this->player_level = player.player_level;
    this->player_group = player.player_group;
    return *this;
}

bool PlayerByLevel::operator==(const PlayerByLevel &other_player) {
    return (this->player_id == other_player.player_id);
}

void PlayerByLevel::increaseLevel(int LevelIncrease){
    this->player_level += LevelIncrease;
}

int PlayerByLevel::getIdPlayer() {
    return this->player_id;
}

Group* PlayerByLevel::getGroup(){
    return this->player_group;
}

int PlayerByLevel::getLevelPlayer() {
    return this->player_level;
}



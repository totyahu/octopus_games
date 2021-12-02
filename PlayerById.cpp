//
// Created by keren on 30/11/2021.
//
#include "PlayerById.h"
using namespace WET1;

PlayerById::PlayerById(int player_id, int player_level, Group *player_group):
        player_id(player_id),player_level(player_level)
{
    this->player_group=player_group;
}

bool PlayerById::operator<(const PlayerById & other_player) {

    return this->player_id<other_player.player_id;
}

PlayerById& PlayerById::operator=(const PlayerById& player){
    this->player_id=player.player_id;
    this->player_level=player.player_level;
    this->player_group=player.player_group;
    return *this;
}

bool PlayerById::operator==(const PlayerById &other_player) {
    return (this->player_id==other_player.player_id);
}

void PlayerById::increaseLevel(int LevelIncrease){
    this->player_level+=LevelIncrease;
}

int PlayerById::getIdPlayer() {
    return this->player_id;
}

Group* PlayerById::getGroup(){
    return this->player_group;
}

int PlayerById::getLevelPlayer() {
    return this->player_level;
}

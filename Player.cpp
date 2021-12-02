//
// Created by keren on 30/11/2021.
//

#include "Player.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace WET1;

Player::Player(int player_id, int player_level, Group *player_group):
player_id(player_id),player_level(player_level)
{
    this->player_group=player_group;
}

Player& Player::operator=(const Player& player){
    this->player_id=player.player_id;
    this->player_level=player.player_level;
    this->player_group=player.player_group;
    return *this;
}

bool Player::operator==(const Player &other_player) {
    return (this->player_id==other_player.player_id);
}

void Player::increaseLevel(int LevelIncrease){
    this->player_level+=LevelIncrease;
}

int Player::getIdPlayer() {
    return this->player_id;
}

Group* Player::getGroup(){
    return this->player_group;
}

int Player::getLevelPlayer() {
    return this->player_level;
}

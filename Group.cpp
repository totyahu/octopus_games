//
// Created by keren on 30/11/2021.
//
#include "Group.h"
using namespace WET1;
Group::Group(int group_id):group_id(group_id){
    this->group_players=new AVLTree<PlayerByLevel>;
    this->best_player= nullptr;
};

bool Group::operator==(const Group& other_group){
    return this->group_id==other_group.group_id;
}

bool Group::operator<(const Group& other_group){
    return this->group_id<other_group.group_id;
}

bool Group::playerExist(const PlayerByLevel& player){
    return this->group_players->exists(player);
}

void Group::addPlayer(const PlayerByLevel& player){
    this->group_players->insert(player);
    if(this->best_player != nullptr){
        if(this->best_player->operator<(player)){
            this->best_player = new PlayerByLevel(player);
        }
    }
    else{
        this->best_player = new PlayerByLevel(player);
    }
}

void Group::removePlayer(const PlayerByLevel& player){
    this->group_players->remove(player);
    this->best_player = this->group_players->getMax();
}

//bool Group::margeGroups(Group& other_group){
//
//}

void Group::increaseLevel(PlayerByLevel& player,int increase_level){
    PlayerByLevel * temp=this->group_players->find(player);
    this->removePlayer(player);
    temp->increaseLevel(increase_level);
    this->addPlayer(*temp);
}

int Group::getHighestLevel(){
    return this->best_player->getIdPlayer();
}
bool Group::isEmpty(){
    return (this->best_player == nullptr);
}

bool Group::mergeGroup(Group* other_group){
    AVLTree<PlayerByLevel>* merged_tree = AVLTree<PlayerByLevel>::merge(this->group_players, other_group->group_players);

    if(merged_tree == nullptr){
        return false;
    }

    AVLTree<PlayerByLevel>* tmp1 = this->group_players;
    AVLTree<PlayerByLevel>* tmp2 = other_group->group_players;
    this->group_players = merged_tree;

    delete tmp1;
    delete tmp2;
    return true
}


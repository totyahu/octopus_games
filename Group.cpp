//
// Created by keren on 30/11/2021.
//

#define DEFAULT_ID -1

#include "Group.h"
using namespace WET1;

Group::Group():group_id(DEFAULT_ID){
    this->group_players = nullptr;
    this->best_player = nullptr;
};

Group::Group(int group_id):group_id(group_id){
    this->group_players=new AVLTree<PlayerByLevel>;
    this->best_player= nullptr;
};

Group::~Group() {
    delete this->group_players;
    if(this->best_player) {
        delete this->best_player;
    }
}

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
        this->best_player = new PlayerByLevel(player);//TODO:Check
    }
}

void Group::removePlayer(const PlayerByLevel& player){
    this->group_players->remove(player);

    this->best_player = this->group_players->getMax();
}


void Group::increaseLevel(PlayerByLevel& player,int increase_level){
    this->removePlayer(player);
    PlayerByLevel * tmp = new PlayerByLevel(player);
    tmp->increaseLevel(increase_level);
    this->addPlayer(*tmp);
}

int Group::getHighestLevel(){
    return this->best_player->getIdPlayer();
}
bool Group::isEmpty() const{
    return (this->best_player== nullptr);
}

bool Group::mergeGroup(Group* other_group){
    AVLTree<PlayerByLevel>* merged_tree = AVLTree<PlayerByLevel>::merge(this->group_players, other_group->group_players);

    if(merged_tree == nullptr){
        return false;
    }
    AVLTree<PlayerByLevel>* tmp1 = this->group_players;
    AVLTree<PlayerByLevel>* tmp2 = other_group->group_players;
    this->group_players = merged_tree;
    this->best_player = Utils::max(this->best_player, other_group->best_player);

    return true;
}

int Group::getId() {
    return this->group_id;
}

int Group::getSize(){
    return this->group_players->getSize();
}

int Group::getBestPlayerId(){
    return this->best_player ? this->best_player->getIdPlayer() : DEFAULT_ID;
}

void Group::printPlayers(){
    cout<<"Group id: "<<this->group_id<<endl;
    if(!this->isEmpty()){
        cout<<"Best player by level is:"<< this->best_player->getIdPlayer()<<endl;
    }else{
        cout<<"no players"<<endl;
    }
    this->group_players->print2D();
}

void Group::toSortedArray(PlayerByLevel* dest_arr){
    this->group_players->toSortedArray(dest_arr);
}


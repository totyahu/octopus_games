
#include "Group.h"
#include "PlayerInGroup.h"


#define DEFAULT_ID -1

namespace WET1{
    Group::Group():group_id(DEFAULT_ID){
        this->group_players = nullptr;
        this->best_player = nullptr;
    }

    Group::Group(int group_id):group_id(group_id){
        this->group_players = new AVLTree<PlayerInGroup>;
        this->best_player = nullptr;
    }

    Group::~Group(){
        if(this->group_players){
            delete this->group_players;
            this->group_players = nullptr;
            delete best_player;
        }
    }


    bool Group::operator==(const Group& other_group){
        return this->group_id == other_group.group_id;
    }

    bool Group::operator<(const Group& other_group){
        return this->group_id < other_group.group_id;
    }

    bool Group::playerExist(const PlayerInGroup& player){
        return this->group_players->exists(player);
    }

    void Group::addPlayer(const PlayerInGroup& player){
        this->group_players->insert(player);
        if(this->best_player != nullptr){
            if(this->best_player->operator<(player)){
                this->best_player = new PlayerInGroup(player);
            }
        }
        else{
            this->best_player = new PlayerInGroup(player);//TODO:Check
        }
    }

    void Group::removePlayer(const PlayerInGroup& player){
        this->group_players->remove(player);
        if(!this->isEmpty()){
            this->best_player = this->group_players->getMax();
        }
        else{
            this->best_player = nullptr;
        }
    }


//    void Group::increaseLevel(PlayerInGroup& player, int increase_level){
//        this->removePlayer(player);
//        PlayerInGroup * tmp = new PlayerInGroup(player);
//        tmp->increaseLevel(increase_level);
//        this->addPlayer(*tmp);
//    }

    int Group::getHighestLevel(){
        return this->best_player->getIdPlayer();
    }
    bool Group::isEmpty() const{
        return (this->group_players && !this->group_players->getSize());
    }

    void updateGroup(PlayerInGroup* player, void* new_group){
        if(!(player->getGroup() == (Group*)new_group)){
            player->changeGroup((Group*)new_group);
        }
    }


    bool Group::mergeGroup(Group* other_group){
        if(this->isEmpty()){
            this->group_players = other_group->group_players;
            other_group->group_players = nullptr;
            this->best_player = other_group->best_player;

            this->group_players->apply(updateGroup, this);
            return true;
        }
        AVLTree<PlayerInGroup>* merged_tree = AVLTree<PlayerInGroup>::merge(this->group_players, other_group->group_players);

        if(merged_tree == nullptr){
            return false;
        }


        this->group_players = merged_tree;
        this->group_players->apply(updateGroup, this);

        if(*(this->best_player) < *(other_group->best_player)){
            this->best_player = other_group->best_player;
            this->best_player->changeGroup(this);
        }

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

    void Group::toSortedArray(PlayerInGroup* dest_arr){
        this->group_players->toSortedArray(dest_arr);
    }
}



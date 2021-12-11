
#include "PlayerInGroup.h"
#include "Group.h"
#include "PlayerById.h"
#include "PlayerByLevel.h"




namespace WET1{
    PlayerInGroup::PlayerInGroup(int player_id, int player_level, Group* player_group,
                                 PlayerById* by_id_instance,
                                 PlayerByLevel* by_level_instance) noexcept:
            player_id(player_id), player_level(player_level){
        this->player_group = player_group;
        this->by_id_instance = by_id_instance;
        this->by_level_instance = by_level_instance;
    }

    PlayerInGroup::PlayerInGroup(const PlayerByLevel& player){
        this->player_id = player.getIdPlayer();
        this->player_level = player.getLevelPlayer();
        this->player_group = player.getGroup();
        this->by_id_instance = nullptr;
        this->by_level_instance = nullptr;
    }

    PlayerInGroup::PlayerInGroup(PlayerById* player_by_id, PlayerByLevel* player_by_level){
        this->player_id = player_by_level->getIdPlayer();
        this->player_level = player_by_level->getLevelPlayer();
        this->player_group = player_by_level->getGroup();
        this->by_id_instance = player_by_id;
        this->by_level_instance = player_by_level;
    }

    bool PlayerInGroup::operator<(const PlayerInGroup& other_player) const {
        if(this->player_level == other_player.player_level){
            return this->player_id > other_player.player_id;
        }
        return this->player_level < other_player.player_level;
    }

    PlayerInGroup& PlayerInGroup::operator=(const PlayerInGroup& player){
        this->player_id = player.player_id;
        this->player_level = player.player_level;
        this->player_group = player.player_group;
        this->by_id_instance = player.by_id_instance;
        this->by_level_instance = player.by_level_instance;
        return *this;
    }

    bool PlayerInGroup::operator==(const PlayerInGroup &other_player)const {
        return (this->player_id == other_player.player_id);
    }

    void PlayerInGroup::increaseLevel(int LevelIncrease){
        this->player_level += LevelIncrease;
    }

    int PlayerInGroup::getIdPlayer() {
        return this->player_id;
    }

    Group* PlayerInGroup::getGroup(){
        return this->player_group;
    }

    int PlayerInGroup::getLevelPlayer() {
        return this->player_level;
    }

    void PlayerInGroup::changeGroup(Group* new_group){
        this->by_id_instance->changeGroup(new_group);
        this->by_level_instance->changeGroup(new_group);
        this->player_group = new_group;
    }

    ostream& operator<<(std::ostream& os,const PlayerInGroup& player)
    {
        if(player.player_group!= nullptr)
        {
            return os <<"Pl, "<< "i: "<< player.player_id
                      <<",l: "<<player.player_level<<",g_i: "<< player.player_group->getId() <<endl;
        }
        return os <<"Pl,"<< "i: "<< player.player_id
                  <<",l: "<<player.player_level<<", No group "<<endl;

    }


    void PlayerInGroup::resetPlayer() {
       this->by_id_instance = nullptr;
       this->by_level_instance = nullptr;
       this->player_group = nullptr;
    }

//    PlayerInGroup::~PlayerInGroup() {
//        this->resetPlayer();
//    }
}




//namespace WET1
//{
//    ostream& operator<<(std::ostream& os,const PlayerInGroup& player)
//    {
//        if(player.player_group!= nullptr)
//        {
//            return os <<"Pl, "<< "i: "<< player.player_id
//                      <<",l: "<<player.player_level<<",g_i: "<< player.player_group->getId() <<endl;
//        }
//        return os <<"Pl,"<< "i: "<< player.player_id
//                  <<",l: "<<player.player_level<<", No group "<<endl;
//
//    }
//
//}
//

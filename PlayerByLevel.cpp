
#include "PlayerByLevel.h"
#include "Group.h"



namespace WET1{
    PlayerByLevel::PlayerByLevel(int player_id, int player_level, Group* player_group):
            player_id(player_id),player_level(player_level){
        this->player_group = player_group;
    }

    bool PlayerByLevel::operator<(const PlayerByLevel& other_player) const {
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

    bool PlayerByLevel::operator==(const PlayerByLevel &other_player)const {
        return (this->player_id == other_player.player_id);
    }

    void PlayerByLevel::increaseLevel(int LevelIncrease){
        this->player_level += LevelIncrease;
    }

    int PlayerByLevel::getIdPlayer() const{
        return this->player_id;
    }

    Group* PlayerByLevel::getGroup() const{
        return this->player_group;
    }

    int PlayerByLevel::getLevelPlayer() const{
        return this->player_level;
    }

    void PlayerByLevel::changeGroup(Group* new_group) {
        this->player_group = new_group;
    }


    ostream& operator<<(std::ostream& os,const PlayerByLevel& player)
    {
        if(player.player_group!= nullptr)
        {
            return os <<"Pl, "<< "i: "<< player.player_id
                      <<",l: "<<player.player_level<<",g_i: "<< player.player_group->getId() <<endl;
        }
        return os <<"Pl,"<< "i: "<< player.player_id
                  <<",l: "<<player.player_level<<", No group "<<endl;

    }
}

//
//namespace WET1
//{
//    ostream& operator<<(std::ostream& os,const PlayerByLevel& player)
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



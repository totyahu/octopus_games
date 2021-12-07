//
// Created by keren on 06/12/2021.
//

#include "GroupNotEmpty.h"

 namespace WET1{
     GroupNotEmpty::GroupNotEmpty(){
         this->group = nullptr;
     }

     GroupNotEmpty::GroupNotEmpty(Group * group){
         this->group=group;
     }

     bool GroupNotEmpty::operator==(const GroupNotEmpty& other_group){
         return *group==*other_group.group;
     }

     bool GroupNotEmpty::operator<(const GroupNotEmpty& other_group){
         return *group<*other_group.group;
     }

    int GroupNotEmpty::getHighestLevel(){
        return group->getHighestLevel();
    }

    int GroupNotEmpty::getBestPlayerId(){
        return group->getBestPlayerId();
    }

}

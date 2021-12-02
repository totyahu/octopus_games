//
// Created by keren on 30/11/2021.
//
#include"GameManager.h"

using namespace WET1;

GameManager::GameManager(){
    this->players_by_id=new AVLTree<PlayerById>;
    this->players_by_level=new AVLTree<PlayerByLevel>;
    this->groups=new AVLTree<Group>;
    this->best_player= nullptr;
}

GameManager * GameManager::Init() {
    return new GameManager;
}

StatusType GameManager::AddGroup(int GroupID){
    if(GroupID<=0){
        return  INVALID_INPUT;
    }
    Group * temp= new Group(GroupID);
    if(this->groups->exists(*temp)){
        return FAILURE;
    }
    this->groups->insert(*temp);
    return SUCCESS;
}

StatusType GameManager::AddPlayer( int PlayerID, int GroupID, int Level){
    if(PlayerID <= 0 || GroupID <= 0 || Level < 0){
        return INVALID_INPUT;
    }
    PlayerById* temp = new PlayerById(PlayerID, Level, nullptr);
    Group* temp2 = new Group(GroupID);
    if((this->players_by_id->exists(*temp)) || !(this->groups->exists(*temp2))){
        return FAILURE;
    }

    Group* player_group = this->groups->find(*temp2);
    PlayerById* player_by_id = new PlayerById(PlayerID, Level, player_group);
    PlayerByLevel* player_by_level = new PlayerByLevel(PlayerID, Level, player_group);
    player_group->addPlayer(*player_by_level);
    this->players_by_id->insert(*player_by_id);
    this->players_by_level->insert((*player_by_level));
    if(this->best_player != nullptr){
        if(this->best_player->operator<(*player_by_level)){
            best_player = player_by_level;
        }
    } else{
        best_player = player_by_level;
    }
    return SUCCESS;
}

StatusType GameManager::RemovePlayer(int PlayerID){
    if(PlayerID <= 0){
        return INVALID_INPUT;
    }

    PlayerById* temp = new PlayerById(PlayerID, 0, nullptr);
    if(!this->players_by_id->exists(*temp)){
        return FAILURE;
    }

    PlayerById* player_by_id = this->players_by_id->find(*temp);
    PlayerByLevel* player_by_level = new PlayerByLevel(player_by_id->getIdPlayer(),
                                                       player_by_id->getLevelPlayer(),
                                                       player_by_id->getGroup());
    player_by_id->getGroup()->removePlayer(*player_by_level);
    this->players_by_id->remove(*player_by_id);
    this->players_by_level->remove(*player_by_level);
    this->best_player = this->players_by_level->getMax();
    return SUCCESS;
}

StatusType GameManager::IncreaseLevel(int PlayerID, int LevelIncrease){//TODO: delete temp
    if(PlayerID <= 0 || LevelIncrease <= 0){
        return INVALID_INPUT;
    }
    PlayerById* temp = new PlayerById(PlayerID,0, nullptr);
    if(!this->players_by_id->exists(*temp)){
        return FAILURE;
    }
    PlayerById * player_by_id = this->players_by_id->find(*temp);
    PlayerByLevel * player_by_level = new PlayerByLevel(player_by_id->getIdPlayer(),
                                                        player_by_id->getLevelPlayer(),
                                                        player_by_id->getGroup());
    player_by_id->getGroup()->increaseLevel(*player_by_level,LevelIncrease);
    this->players_by_level->remove(*player_by_level);
    player_by_level->increaseLevel(LevelIncrease);
    this->players_by_level->insert(*player_by_level);
    player_by_id->increaseLevel(LevelIncrease);
    this->players_by_id->remove(*player_by_id);
    this->players_by_id->insert(*player_by_id);
    if(this->best_player!= nullptr){
        if(this->best_player->operator<(*player_by_level)){
            best_player=player_by_level;
        }
    }
    else{
        best_player=player_by_level;
    }

    return SUCCESS;
}

StatusType GameManager::GetHighestLevel(int GroupID, int *PlayerID) {
    if(PlayerID == NULL || GroupID == 0){
        return INVALID_INPUT;
    }

    if(GroupID < 0){
        if(this->best_player == nullptr){
            *PlayerID= -1;
            return SUCCESS;
        }
        *PlayerID= this->best_player->getIdPlayer();
        return SUCCESS;
    }

    Group* temp=new Group(GroupID);
    if(!this->groups->exists(*temp)){
        return FAILURE;
    }

    Group* group = this->groups->find(*temp);
    if(group->isEmpty()){
        *PlayerID=-1;
        return SUCCESS;
    }
    *PlayerID=group->getHighestLevel();
    return SUCCESS;
}

StatusType GameManager::ReplaceGroup(int GroupID, int ReplacementID){
    if(GroupID <= 0 || ReplacementID <= 0 || GroupID == ReplacementID){
        return INVALID_INPUT;
    }

    Group* delete_group = this->findGroupById(GroupID);
    Group* replace_group = this->findGroupById(GroupID);

    if(delete_group == nullptr || replace_group == nullptr){
        return FAILURE;
    }

    if(!replace_group->mergeGroup(delete_group)){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GameManager::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers){
    if(GroupID == 0 || Players == nullptr || numOfPlayers == nullptr){
        return INVALID_INPUT;
    }

    if(groupID < 0){
        *numOfPlayers = this->players_by_level->getSize();
        *Players = new int[*numOfPlayers];
        this->players_by_level->toSortedArray(*Players); //TODO: add a temp array of players then put ids in players array
        return SUCCESS;
    }

    Group* group = this->findGroupById(GroupID);
    if(group == nullptr){
        return FAILURE;
    }

    *numOfPlayers = group->players_by_level->getSize();
    *Players = new int[*numOfPlayers];
    group->group_players->toSortedArray(*Players);
    return SUCCESS;
}

bool isGroupEmpty(Group* group){
    return group->isEmpty()
}

StatusType GameManager::GetGroupsHighestLevel(int numOfGroups, int **Players){
    if(Players == nullptr || numOfGroups < 1){
        return INVALID_INPUT;
    }

    PlayersByLevel *filteredPlayers = new PlayersByLevel[numOfGroups];
    if(!this->groups->query(filteredPlayers, isGroupEmpty, numOfGroups)){
        return FAILURE;
    }

    *Players = new int[numOfGroups];
    for(int i = 0; i < numOfGroups; i++){
        *Players[i] = filteredPlayers[i].best_player->player_id;
    }

    return SUCCESS;
}


void GameManager::Quit(){
    delete this->groups;
    delete this->players_by_id;
    delete this->players_by_level;
    delete this->best_player;
}


Group* GameManager::findGroupById(int groupId){
    Group* tmp = new Group(groupId);
    Group* res = this->groups->find(*tmp);
    delete tmp;
    return res;
}





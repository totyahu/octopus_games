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

    PlayerById* player = findPlayerById(PlayerID);
    Group* group = findGroupById(GroupID);

    if(player != nullptr || group == nullptr){
        return FAILURE;
    }

    PlayerById* player_by_id = new PlayerById(PlayerID, Level, group);
    PlayerByLevel* player_by_level = new PlayerByLevel(PlayerID, Level, group);
    group->addPlayer(*player_by_level);

    this->players_by_id->insert(*player_by_id);
    this->players_by_level->insert((*player_by_level));
    if(this->best_player != nullptr){
        if(this->best_player->operator<(*player_by_level)){
            this->best_player = player_by_level;
        }
    } else{
        this->best_player = player_by_level;
    }
    return SUCCESS;
}

StatusType GameManager::RemovePlayer(int PlayerID){
    if(PlayerID <= 0){
        return INVALID_INPUT;
    }

    PlayerById* player_by_id = findPlayerById(PlayerID);
    if(players_by_id== nullptr){
        return FAILURE;
    }

    PlayerByLevel* player_by_level = findPlayerByLevel(player_by_id);
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
    PlayerById* player_by_id =findPlayerById(PlayerID);
    if(player_by_id== nullptr){
        return FAILURE;
    }
    PlayerByLevel * player_by_level = findPlayerByLevel(player_by_id);
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
    if(PlayerID == nullptr || GroupID == 0){
        return INVALID_INPUT;
    }

    if(GroupID < 0){
        if(this->best_player == nullptr){
            *PlayerID = -1;
            return SUCCESS;
        }
        *PlayerID = this->best_player->getIdPlayer();
        return SUCCESS;
    }

    Group* group = findGroupById(GroupID);
    if(group== nullptr){
        return FAILURE;
    }

    if(group->isEmpty()){
        *PlayerID = -1;
        return SUCCESS;
    }

    *PlayerID = group->getHighestLevel();
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

    if(GroupID < 0){
        *numOfPlayers = this->players_by_level->getSize();
        *Players = new int[*numOfPlayers];
        PlayerByLevel* tmp = new PlayerByLevel[*numOfPlayers];
        this->players_by_level->toSortedArray(tmp); //TODO: add a temp array of players then put ids in players array
        for(int i = 0; i < *numOfPlayers; i++){
            *Players[i] = tmp[i].getIdPlayer();
        }
        return SUCCESS;
    }

    Group* group = findGroupById(GroupID);
    if(group == nullptr){
        return FAILURE;
    }

    *numOfPlayers = group->getSize();
    *Players = new int[*numOfPlayers];

    PlayerByLevel* tmp = new PlayerByLevel[*numOfPlayers];
    group->toSortedArray(tmp);
    for(int i = 0; i < *numOfPlayers; i++){
        *Players[i] = tmp[i].getIdPlayer();
    }

    return SUCCESS;
}


bool isGroupEmpty(const Group& group){
    return group.isEmpty();
}
//
//StatusType GameManager::GetGroupsHighestLevel(int numOfGroups, int **Players){
//    if(Players == nullptr || numOfGroups < 1){
//        return INVALID_INPUT;
//    }
//
//    PlayerByLevel *filteredPlayers = new PlayerByLevel[numOfGroups];
//    if(!this->groups->query(filteredPlayers, isGroupEmpty, numOfGroups)){
//        return FAILURE;
//    }
//
//    *Players = new int[numOfGroups];
//    for(int i = 0; i < numOfGroups; i++){
//        *Players[i] = filteredPlayers[i].best_player->player_id;
//    }
//
//    return SUCCESS;
//}


void GameManager::Quit(){
    delete this->groups;
    delete this->players_by_id;
    delete this->players_by_level;
    delete this->best_player;
}


Group* GameManager::findGroupById(int groupId){
    Group* tmp = new Group(groupId);
    Group* res = this->groups->find(*tmp);
//    delete tmp;
    return res;
}

PlayerById* GameManager::findPlayerById(int playerId){
    PlayerById* tmp = new PlayerById(playerId, 0, nullptr);
    PlayerById* res = this->players_by_id->find(*tmp);
//    delete tmp;
    return res;
}

PlayerByLevel* GameManager::findPlayerByLevel(PlayerById* player){
    PlayerByLevel* tmp = new PlayerByLevel(player->getIdPlayer(), player->getLevelPlayer(), nullptr);
    PlayerByLevel* res = this->players_by_level->find(*tmp);
//    delete tmp;
    return res;
}






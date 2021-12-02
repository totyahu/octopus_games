//
// Created by keren on 30/11/2021.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Group.h"
#include "PlayerById.h"
#include "PlayerByLevel.h"
#include "AVLTree.h"

namespace WET1{
    typedef enum {
        SUCCESS = 0,
        FAILURE = -1,
        ALLOCATION_ERROR = -2,
        INVALID_INPUT = -3
    } StatusType;

    class GameManager{
        AVLTree<Group> * groups;
        AVLTree<PlayerById> * players_by_id;
        AVLTree<PlayerByLevel> * players_by_level;
        PlayerByLevel * best_player;

    public:
        GameManager();
        GameManager *Init();
        StatusType AddGroup(int GroupID);
        StatusType AddPlayer( int PlayerID, int GroupID, int Level);
        StatusType RemovePlayer(int PlayerID);
        StatusType ReplaceGroup(int GroupID, int ReplacementID);
        StatusType IncreaseLevel(int PlayerID, int LevelIncrease);
        StatusType GetHighestLevel( int GroupID, int *PlayerID);
        StatusType GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);
        StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);
        void Quit();

    };
}
#endif //GAMEMANAGER_H

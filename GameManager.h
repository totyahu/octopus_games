//
// Created by keren on 30/11/2021.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "library1.h"
#include "AVLTree.h"

#include "common_fwd.h"


namespace WET1{



    class GameManager{
        AVLTree<Group> * groups;
        AVLTree<PlayerById> * players_by_id;
        AVLTree<PlayerByLevel> * players_by_level;
        PlayerByLevel * best_player;
        AVLTree<GroupNotEmpty> * not_empty_groups;

    public:
        explicit GameManager();
        ~GameManager()=default;
        GameManager *Init();
        StatusType AddGroup(int GroupID);
        StatusType AddPlayer( int PlayerID, int GroupID, int Level);
        StatusType RemovePlayer(int PlayerID);
        StatusType ReplaceGroup(int GroupID, int ReplacementID);
        StatusType IncreaseLevel(int PlayerID, int LevelIncrease);
        StatusType GetHighestLevel( int GroupID, int *PlayerID);
        StatusType GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);
        StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);
        static void Quit(GameManager * gameManager);
        Group* findGroupById(int groupId);
        PlayerById* findPlayerById(int playerId);
        PlayerByLevel* findPlayerByLevel(PlayerById* player);
        void printGame();
    };
}
#endif //GAMEMANAGER_H

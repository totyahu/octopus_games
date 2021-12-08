/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Winter 2021-2022                                     */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
    NONE_CMD = -2,
    COMMENT_CMD = -1,
    INIT_CMD = 0,
    ADDGROUP_CMD = 1,
    ADDPLAYER_CMD = 2,
    REMOVEPLAYER_CMD = 3,
    REPLACEGROUP_CMD = 4,
    INCREASELEVEL_CMD = 5,
    GETHIGHESTLEVEL_CMD = 6,
    GETALLPLAYERS_CMD = 7,
    GETGROUPSHIGHEST_CMD = 8,
    QUIT_CMD = 9
} commandType;

static const int numActions = 10;
static const char *commandStr[] = {
        "Init",
        "AddGroup",
        "AddPlayer",
        "RemovePlayer",
        "ReplaceGroup",
        "IncreaseLevel",
        "GetHighestLevel",
        "GetAllPlayersByLevel",
        "GetGroupsHighestLevel",
        "Quit" };

static const char* ReturnValToStr(int val) {
    switch (val) {
        case SUCCESS:
            return "SUCCESS";
        case ALLOCATION_ERROR:
            return "ALLOCATION_ERROR";
        case FAILURE:
            return "FAILURE";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        default:
            return "";
    }
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
    error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
    char buffer[MAX_STRING_INPUT_SIZE];

    // Reading commands
    while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
        fflush(stdout);
        if (parser(buffer) == error)
            break;
    };
    return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
                                const char** const command_arg) {
    if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
        return (NONE_CMD);
    if (StrCmp("#", command)) {
        if (strlen(command) > 1)
            printf("%s", command);
        return (COMMENT_CMD);
    };
    for (int index = 0; index < numActions; index++) {
        if (StrCmp(commandStr[index], command)) {
            *command_arg = command + strlen(commandStr[index]) + 1;
            return ((commandType) index);
        };
    };
    return (NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddGroup(void* DS, const char* const command);
static errorType OnAddPlayer(void* DS, const char* const command);
static errorType OnRemovePlayer(void* DS, const char* const command);
static errorType OnReplaceGroup(void* DS, const char* const command);
static errorType OnIncreaseLevel(void* DS, const char* const command);
static errorType OnGetHighestLevel(void* DS, const char* const command);
static errorType OnGetAllPlayersByLevel(void* DS, const char* const command);
static errorType OnGetGroupsHighestLevel(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
    static void *DS = NULL; /* The general data structure */
    const char* command_args = NULL;
    errorType rtn_val = error;

    commandType command_val = CheckCommand(command, &command_args);

    switch (command_val) {

        case (INIT_CMD):
            rtn_val = OnInit(&DS, command_args);
            break;
        case (ADDGROUP_CMD):
            rtn_val = OnAddGroup(DS, command_args);
            break;
        case (ADDPLAYER_CMD):
            rtn_val = OnAddPlayer(DS, command_args);
            break;
        case (REMOVEPLAYER_CMD):
            rtn_val = OnRemovePlayer(DS, command_args);
            break;
        case (REPLACEGROUP_CMD):
            rtn_val = OnReplaceGroup(DS, command_args);
            break;
        case (INCREASELEVEL_CMD):
            rtn_val = OnIncreaseLevel(DS, command_args);
            break;
        case (GETHIGHESTLEVEL_CMD):
            rtn_val = OnGetHighestLevel(DS, command_args);
            break;
        case (GETALLPLAYERS_CMD):
            rtn_val = OnGetAllPlayersByLevel(DS, command_args);
            break;
        case (GETGROUPSHIGHEST_CMD):
            rtn_val = OnGetGroupsHighestLevel(DS, command_args);
            break;
        case (QUIT_CMD):
            rtn_val = OnQuit(&DS, command_args);
            break;

        case (COMMENT_CMD):
            rtn_val = error_free;
            break;
        case (NONE_CMD):
            rtn_val = error;
            break;
        default:
            assert(false);
            break;
    };
    return (rtn_val);
}

/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
    if (isInit) {
        printf("Init was already called.\n");
        return (error_free);
    };
    isInit = true;

    *DS = Init();
    if (*DS == NULL) {
        printf("Init failed.\n");
        return error;
    };
    printf("Init done.\n");

    return error_free;
}

/***************************************************************************/
/* OnAddGroup                                                             */
/***************************************************************************/
static errorType OnAddGroup(void* DS, const char* const command) {
    int groupID;
    ValidateRead(sscanf(command, "%d", &groupID), 1, "AddGroup failed.\n");
    StatusType res = AddGroup(DS, groupID);

    if (res != SUCCESS) {
        printf("AddGroup: %s\n", ReturnValToStr(res));
        return error_free;
    } else {
        printf("AddGroup: %s\n", ReturnValToStr(res));
    }

    return error_free;
}

/***************************************************************************/
/* OnAddPlayer                                                          */
/***************************************************************************/
static errorType OnAddPlayer(void* DS, const char* const command) {
    int playerID;
    int groupID;
    int level;
    ValidateRead(
            sscanf(command, "%d %d %d", &playerID, &groupID, &level),
            3, "AddPlayer failed.\n");
    StatusType res = AddPlayer(DS, playerID, groupID, level);

    if (res != SUCCESS) {
        printf("AddPlayer: %s\n", ReturnValToStr(res));
        return error_free;
    }

    printf("AddPlayer: %s\n", ReturnValToStr(res));
    return error_free;
}

/***************************************************************************/
/* OnRemovePlayer                                                            */
/***************************************************************************/
static errorType OnRemovePlayer(void* DS, const char* const command) {
    int playerID;
    ValidateRead(sscanf(command, "%d", &playerID), 1,
                 "RemovePlayer failed.\n");
    StatusType res = RemovePlayer(DS, playerID);
    if (res != SUCCESS) {
        printf("RemovePlayer: %s\n", ReturnValToStr(res));
        return error_free;
    }

    printf("RemovePlayer: %s\n", ReturnValToStr(res));
    return error_free;
}

/***************************************************************************/
/* OnReplaceGroup                                                            */
/***************************************************************************/
static errorType OnReplaceGroup(void* DS, const char* const command) {
    int groupID;
    int replacementID;
    ValidateRead(sscanf(command, "%d %d", &groupID, &replacementID), 2,
                 "ReplaceGroup failed.\n");
    StatusType res = ReplaceGroup(DS, groupID, replacementID);

    if (res != SUCCESS) {
        printf("ReplaceGroup: %s\n", ReturnValToStr(res));
        return error_free;
    }

    printf("ReplaceGroup: %s\n", ReturnValToStr(res));
    return error_free;
}

/***************************************************************************/
/* OnIncreaseLevel                                                         */
/***************************************************************************/
static errorType OnIncreaseLevel(void* DS, const char* const command) {
    int playerID;
    int levelIncrease;
    ValidateRead(sscanf(command, "%d %d", &playerID, &levelIncrease), 2,
                 "IncreaseLevel failed.\n");
    StatusType res = IncreaseLevel(DS, playerID, levelIncrease);

    if (res != SUCCESS) {
        printf("IncreaseLevel: %s\n", ReturnValToStr(res));
        return error_free;
    }

    printf("IncreaseLevel: %s\n", ReturnValToStr(res));
    return error_free;
}


/***************************************************************************/
/* OnGetHighestLevel                                                         */
/***************************************************************************/
static errorType OnGetHighestLevel(void* DS, const char* const command) {
    int groupID;
    ValidateRead(sscanf(command, "%d", &groupID), 1, "GetHighestLevel failed.\n");
    int playerID;
    StatusType res = GetHighestLevel(DS, groupID, &playerID);

    if (res != SUCCESS) {
        printf("GetHighestLevel: %s\n", ReturnValToStr(res));
        return error_free;
    }

    cout << "Highest level player is: " << playerID << endl;
    return error_free;
}

/***************************************************************************/
/* OnGetAllPlayersByLevel                                                        */
/***************************************************************************/

void PrintAll(int *playerIDs, int numOfPlayers) {
    if (numOfPlayers > 0) {
        cout << "Rank	||	Player" << endl;
    }

    for (int i = 0; i < numOfPlayers; i++) {
        cout << i + 1 << "\t||\t" << playerIDs[i] << endl;
    }
    cout << "and there are no more players!" << endl;

    free (playerIDs);
}

static errorType OnGetAllPlayersByLevel(void* DS, const char* const command) {
    int groupID;
    ValidateRead(sscanf(command, "%d", &groupID), 1,
                 "GetAllPlayersByLevel failed.\n");
    int* playerIDs;
    int numOfPlayers;
    StatusType res = GetAllPlayersByLevel(DS, groupID, &playerIDs, &numOfPlayers);

    if (res != SUCCESS) {
        printf("GetAllPlayersByLevel: %s\n", ReturnValToStr(res));
        return error_free;
    }

    PrintAll(playerIDs, numOfPlayers);
    return error_free;
}

/***************************************************************************/
/* OnGetGroupsHighestLevel                                                        */
/***************************************************************************/

void PrintGroupsHighest(int *playerIDs, int numOfGroups) {
    if (numOfGroups > 0) {
        cout << "GroupIndex	||	Player" << endl;
    }

    for (int i = 0; i < numOfGroups; i++) {
        cout << i + 1 << "\t||\t" << playerIDs[i] << endl;
    }
    cout << "and there are no more players!" << endl;

    free (playerIDs);
}

static errorType OnGetGroupsHighestLevel(void* DS, const char* const command) {
    int numOfGroups;
    ValidateRead(sscanf(command, "%d", &numOfGroups), 1,
                 "GetGroupsHighestLevel failed.\n");
    int* playerIDs;
    StatusType res = GetGroupsHighestLevel(DS, numOfGroups, &playerIDs);

    if (res != SUCCESS) {
        printf("GetGroupsHighestLevel: %s\n", ReturnValToStr(res));
        return error_free;
    }

    PrintGroupsHighest(playerIDs, numOfGroups);
    return error_free;
}

/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
    Quit(DS);
    if (*DS != NULL) {
        printf("Quit failed.\n");
        return error;
    };

    isInit = false;
    printf("Quit done.\n");

    return error_free;
}

#ifdef __cplusplus
}
#endif



//#include <iostream>
//#include "GameManager.h"
//
//
//using namespace std;
//using namespace WET1;
//
//
//int main(){
//    GameManager* g = new GameManager();
//
//    g->AddGroup(97);
//    g->AddGroup(172);
//    g->AddGroup(143);
//    g->AddGroup(158);
//    g->AddGroup(152);
//    g->AddGroup(2);
//    g->AddGroup(45);
//    g->AddGroup(82);
//    g->AddGroup(161);
//    g->AddGroup(99);
//    g->AddGroup(17);
//    g->AddGroup(103);
//    g->AddGroup(113);
//    g->AddGroup(68);
//    g->AddGroup(162);
//    g->AddGroup(128);
//    g->AddGroup(58);
//    g->AddGroup(57);
//    g->AddPlayer(1308, 68, 8);
//    g->AddPlayer(1024, 152, 7);
//    g->AddPlayer(299, 45, 6);
//    g->AddPlayer(736, 128, 5);
//    g->AddPlayer(1453, 152, 7);
//    g->AddPlayer(127, 113, 6);
//    g->AddPlayer(188, 68, 9);
//    g->AddPlayer(1520, 103, 8);
//    g->AddPlayer(37, 57, 1);
//    g->AddPlayer(241, 96, 6);
//    g->AddPlayer(1985, 82, 0);
//    g->AddPlayer(770, 162, 2);
//    g->AddPlayer(1196, 152, 8);
//    g->AddPlayer(1221, 158, 9);
//    g->AddPlayer(882, 161, 1);
//    g->AddPlayer(849, 45, 0);
//    g->AddPlayer(896, 172, 5);
//    g->AddPlayer(40, 99, 7);
//    g->AddPlayer(1584, 45, 7);
//    g->AddPlayer(1321, 158, 2);
//    g->AddPlayer(1763, 143, 4);
//    g->AddPlayer(1079, 161, 6);
//    g->AddPlayer(287, 172, 7);
//    g->AddPlayer(1689, 96, 4);
//    g->AddPlayer(830, 57, 8);
//    g->AddPlayer(1904, 97, 1);
//    g->AddPlayer(185, 68, 9);
//    g->AddPlayer(1034, 97, 7);
//    g->AddPlayer(1975, 128, 0);
//    g->AddPlayer(511, 57, 3);
//    g->AddPlayer(1078, 45, 7);
//    g->AddPlayer(800, 82, 3);
//    g->AddPlayer(938, 45, 9);
//    g->AddPlayer(669, 143, 8);
//    g->AddPlayer(1036, 161, 4);
//    g->AddPlayer(191, 45, 2);
//    g->AddPlayer(1958, 172, 6);
//    g->AddPlayer(283, 161, 9);
//    g->AddPlayer(1540, 161, 9);
//    g->AddPlayer(1403, 17, 3);
//    g->AddPlayer(1331, 143, 4);
//    g->AddPlayer(1494, 99, 2);
//    g->AddPlayer(1028, 99, 9);
//    g->AddPlayer(303, 161, 0);
//    g->AddPlayer(482, 58, 1);
//    g->AddPlayer(598, 97, 7);
//    g->AddPlayer(1360, 152, 7);
//    g->AddPlayer(1484, 161, 6);
//    g->AddPlayer(845, 68, 3);
//    g->AddPlayer(1359, 99, 0);
//    g->AddPlayer(470, 143, 0);
//    g->AddPlayer(1427, 158, 0);
//    g->AddPlayer(1630, 82, 1);
//    g->AddPlayer(1282, 161, 2);
//    g->AddPlayer(702, 58, 7);
//    g->AddPlayer(469, 152, 9);
//    g->AddPlayer(1696, 113, 1);
//    g->AddPlayer(1866, 172, 0);
//    g->AddPlayer(1830, 103, 7);
//    g->AddPlayer(3, 158, 6);
//    g->AddPlayer(1566, 68, 2);
//    g->AddPlayer(1377, 58, 1);
//    g->AddPlayer(1135, 68, 8);
//    g->AddPlayer(1949, 68, 5);
//    g->AddPlayer(1634, 17, 9);
//    g->AddPlayer(51, 96, 7);
//    g->AddPlayer(1921, 99, 9);
//    g->AddPlayer(1867, 57, 0);
//    g->AddPlayer(1076, 158, 3);
//    g->AddPlayer(1195, 143, 6);
//    g->AddPlayer(1837, 161, 7);
//    g->AddPlayer(1324, 17, 1);
//    g->AddPlayer(1071, 45, 4);
//    g->AddPlayer(300, 97, 1);
//    g->AddPlayer(1274, 143, 4);
//    g->AddPlayer(757, 58, 8);
//    g->AddPlayer(1688, 17, 6);
//    g->AddPlayer(1553, 68, 7);
//    g->AddPlayer(897, 58, 7);
//    g->AddPlayer(1252, 82, 5);
//    g->AddPlayer(1302, 143, 3);
//    g->AddPlayer(1051, 99, 7);
//    g->AddPlayer(798, 99, 2);
//    g->AddPlayer(1981, 57, 7);
//    g->AddPlayer(217, 143, 9);
//    g->AddPlayer(1216, 162, 2);
//    g->AddPlayer(1456, 103, 7);
//    g->AddPlayer(261, 96, 4);
//    g->AddPlayer(180, 68, 2);
//    g->AddPlayer(1060, 172, 3);
//    g->AddPlayer(78, 97, 7);
//    g->AddPlayer(70, 2, 2);
//    g->AddPlayer(232, 97, 4);
//    g->AddPlayer(402, 99, 0);
//    g->AddPlayer(1151, 162, 6);
//    g->AddPlayer(1710, 97, 6);
//    g->AddPlayer(340, 57, 4);
//    g->AddPlayer(1961, 113, 3);
//    g->AddPlayer(666, 96, 6);
//    g->AddPlayer(1310, 113, 8);
//    g->AddPlayer(164, 68, 2);
//    g->AddPlayer(361, 162, 9);
//    g->AddPlayer(1045, 2, 3);
//    g->AddPlayer(544, 152, 9);
//    g->AddPlayer(1983, 45, 9);
//    g->AddPlayer(672, 161, 8);
//    g->AddPlayer(674, 158, 6);
//    g->AddPlayer(9, 113, 0);
//    g->AddPlayer(1199, 57, 8);
//    g->AddPlayer(1226, 2, 8);
//    g->AddPlayer(1093, 96, 7);
//    g->AddPlayer(1220, 96, 1);
//    g->AddPlayer(972, 103, 0);
//    g->AddPlayer(505, 45, 4);
//    g->AddPlayer(1739, 113, 6);
//    g->AddPlayer(1027, 17, 4);
//    g->AddPlayer(867, 103, 6);
//    g->AddPlayer(1860, 17, 2);
//    g->AddPlayer(1211, 57, 1);
//    g->AddPlayer(508, 172, 2);
//    g->AddPlayer(1090, 97, 8);
//    g->AddPlayer(1945, 17, 3);
//    g->AddPlayer(737, 17, 5);
//    g->AddPlayer(1341, 113, 4);
//    g->AddPlayer(75, 2, 2);
//    g->AddPlayer(475, 17, 7);
//    g->AddPlayer(1061, 2, 0);
//    g->AddPlayer(1993, 45, 0);
//    g->AddPlayer(1176, 128, 9);
//    g->AddPlayer(620, 97, 1);
//    g->AddPlayer(986, 58, 5);
//    g->AddPlayer(373, 103, 7);
//    g->AddPlayer(42, 2, 2);
//    g->AddPlayer(362, 113, 1);
//    g->AddPlayer(1097, 143, 4);
//    g->AddPlayer(797, 158, 7);
//    g->AddPlayer(1399, 113, 4);
//    g->AddPlayer(558, 162, 8);
//    g->AddPlayer(874, 162, 0);
//    g->AddPlayer(1380, 96, 8);
//    g->AddPlayer(161, 113, 7);
//    g->AddPlayer(460, 161, 5);
//    g->AddPlayer(1723, 58, 2);
//    g->AddPlayer(1657, 57, 8);
//    g->AddPlayer(1171, 96, 8);
//    g->AddPlayer(851, 113, 2);
//    g->AddPlayer(99, 99, 3);
//    g->AddPlayer(543, 57, 2);
//    g->AddPlayer(1709, 96, 9);
//    g->AddPlayer(1025, 45, 2);
//    g->AddPlayer(284, 172, 6);
//    g->AddPlayer(1096, 45, 4);
//    g->AddPlayer(1674, 2, 4);
//    g->AddPlayer(695, 97, 3);
//    g->AddPlayer(1849, 113, 3);
//    g->AddPlayer(368, 172, 4);
//    g->AddPlayer(1939, 99, 9);
//    g->AddPlayer(612, 158, 8);
//    g->AddPlayer(700, 99, 2);
//    g->AddPlayer(49, 113, 5);
//    g->AddPlayer(383, 161, 3);
//    g->AddPlayer(1257, 97, 6);
//    g->AddPlayer(1417, 17, 2);
//    g->AddPlayer(136, 17, 6);
//    g->AddPlayer(199, 17, 6);
//    g->AddPlayer(425, 143, 9);
//    g->AddPlayer(1991, 103, 2);
//    g->AddPlayer(358, 58, 8);
//    g->AddPlayer(116, 172, 1);
//    g->AddPlayer(1037, 161, 8);
//    g->AddPlayer(880, 103, 3);
//    g->AddPlayer(101, 152, 5);
//    g->AddPlayer(994, 143, 8);
//    g->AddPlayer(1488, 57, 8);
//    g->AddPlayer(1564, 143, 4);
//    g->AddPlayer(1238, 96, 3);
//    g->AddPlayer(651, 113, 1);
//    g->AddPlayer(481, 103, 8);
//    g->AddPlayer(1243, 162, 3);
//    g->AddPlayer(577, 162, 9);
//    g->IncreaseLevel(674, 4);
//    g->IncreaseLevel(1890, 5);
//    g->ReplaceGroup(96, 17);
//
//    int *players;
//    int x = 0;
//
//    g->GetGroupsHighestLevel(14, &players);
//    g->ReplaceGroup(68, 152);
//    g->GetAllPlayersByLevel(-1, &players, &x);
//    g->GetGroupsHighestLevel(9, &players);
//    g->RemovePlayer(177);
//    g->GetAllPlayersByLevel(96, &players, &x);
//    g->GetGroupsHighestLevel(6, &players);
//    g->GetHighestLevel(96, &x);
//
//    GameManager::Quit(g);
//
//    return 0;
//}
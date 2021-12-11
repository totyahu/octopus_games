//
// Created by keren on 06/12/2021.
//

#ifndef GROUPNOTEMPTY_H
#define GROUPNOTEMPTY_H


#include <string>
#include <iostream>
#include <cstdio>

#include "common_fwd.h"
#include "Group.h"

using namespace std;

namespace WET1{

    class GroupNotEmpty
    {
       Group * group;

    public:
        GroupNotEmpty();
        explicit GroupNotEmpty(Group * group);
        ~GroupNotEmpty();
        bool operator==(const GroupNotEmpty& other_group);
        bool operator<(const GroupNotEmpty& other_group);
        int getHighestLevel();
        int getBestPlayerId();

    };
}

#endif //GROUPNOTEMPTY_H

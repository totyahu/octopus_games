#ifndef OCTOPUS_GAMES_UTILS_H
#define OCTOPUS_GAMES_UTILS_H

#define MAX(l,r) ((l) < (r) ? (r) : (l))

#include "PlayerInGroup.h"
//#include "Group.h"
#include "common_fwd.h"


namespace WET1 {
    class Utils {
    public:

        template<class T>
        static T* mergeArrays(T arr1[], T arr2[], int size1, int size2){
            T* arr_merge = new T[size1 + size2];

            int idx1 = 0, idx2 = 0, idx3 = 0;
            while(idx1 < size1 && idx2 < size2){
                if(arr1[idx1] < arr2[idx2]){
                    arr_merge[idx3++] = arr1[idx1++];
                }
                else {
                    arr_merge[idx3++] = arr2[idx2++];
                }
            }
            while(idx1 < size1){
                arr_merge[idx3++] = arr1[idx1++];
            }
            while(idx2 < size2){
                arr_merge[idx3++] = arr2[idx2++];
            }

            return arr_merge;
        }

    };
}


#endif //OCTOPUS_GAMES_UTILS_H

#include "core.h"


int myRanNum(int max) { 
    return (rand() % max + 1);
}


//alle zahen unterschiedlich
void setAllDisctinctRanNums(int *p_nums, int max) {
    //alldistinct machen
    for (int i = 0; i < max; i++) {
        p_nums[i] = i;
    }

    //mischen
    for (int i = ; i < max; i++) {
        int temp = p_nums[i];
        int randI = myRanNum(max);

        p_nums[i] = p_nums[randI];
        p_nums[randI] = temp;
    }
}


//alle zahlen random, können auch gleiche mehrmals vorkommen
void setRanNums(int *p_nums, int max) {
    for (int i = 0; i < max; i++) {
        p_nums[i] = myRanNum(max);
    }
}
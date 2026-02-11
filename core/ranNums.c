#include "core.h"


int myRanNum(int max) { 
    return (rand() % max + 1);
}

void shuffleNums(int *p_nums, int maxIndex) {
    for (int i = 0; i < maxIndex; i++) {
        int temp = p_nums[i];
        int randI = myRanNum(maxIndex);

        p_nums[i] = p_nums[randI];
        p_nums[randI] = temp;
    }
}

//alle zahen unterschiedlich
void setAllDisctinctRanNums(int *p_nums, int max) {
    //alldistinct machen
    for (int i = 0; i < max; i++) {
        p_nums[i] = i;
    }

    //mischen
    shuffleNums(p_nums, max);
}

//alle zahlen random, können auch gleiche mehrmals vorkommen
void setRanNums(int *p_nums, int max) {
    for (int i = 0; i < max; i++) {
        p_nums[i] = myRanNum(max);
    }
}

void setOrderedNums(int *p_nums, int max) {
    for (int i = 0; i < max; i++) {
        p_nums[i] = i;
    }
}

void setReverseOrderedNums(int *p_nums, int max) {
    for (int i = 0; i < max; i++) {
        p_nums[i] = max - i;
    }
}
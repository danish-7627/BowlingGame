#pragma once
#include<iostream>

enum SCORETYPE {
    NORMAL = 0,
    SPARE = 1,
    STRIKE = 2,
    UNDEFINED
}prevScoreType, currScoreType;

void enterScore(int* score1, int* score2) {

    do {
        std::cout << "Enter first Score: ";
        std::cin >> *score1;
        if (*score1 > 10 || *score1 < 0)
            std::cout << "Invalid Score! Try again \n";
    } while (*score1 > 10 || *score1 < 0);
    if (*score1 == 10)
    {
        currScoreType = STRIKE;
        std::cout << "STRIKE!!\n";
        return;
    }
    do {
        std::cout << "Enter second Score: ";
        std::cin >> *score2;
        if ((*score1 + *score2) > 10 || *score2 > 10 || *score2 < 0)
            std::cout << "Invalid Score! Try again \n";
    } while (*score2 > 10 || *score2 < 0);
    if (*score1 + *score2 == 10)
    {
        currScoreType = SPARE;
        std::cout << "SPARE!!\n";
        return;
    }
    currScoreType = NORMAL;
}
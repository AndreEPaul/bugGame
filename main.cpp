/***********************************************
Program Name:   Final Project
Author:         Andre Paul
Date:           12/8/2019
Description:
************************************************/

#include "Menu.hpp"
#include <ctime>
#include <cstdlib>

int main()
{
    // For dice rolls.
    unsigned seed = time(0);
    srand(seed);

    Menu finalProjGame;

    finalProjGame.start();

    return 0;
}   
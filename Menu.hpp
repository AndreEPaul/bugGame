/***********************************************
Program Name:   Final Project
Author:         Andre Paul
Date:           11/20/2019
Description:    This is the header file for the
                Menu class. It reuses a lot of the Menu code
                from previous assignments. Variations
                have been made to validChoice() and 
                start(). Overall, this handles all of
                the user I/O and input validation.
************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include "Space.hpp"
#include "Rock.hpp"
#include "Puddle.hpp"
#include "Lettuce.hpp"

#include <string>
#include <stack>

using std::string;
using std::stack;

class Menu
{
private:
    string userString;
    int roundCount;
    int health;
    bool checkedForItem;
    stack <Item> itemBag;
    Space* spotInBoard;
    Rock rock1;
    Rock rock2;
    Puddle puddle1;
    Puddle puddle2;
    Lettuce lettuce1;
    Lettuce lettuce2;
public:
    void start();
    void spaceOccurence();
    void menuChoice(int);
    bool fullBag();
    void readInString();
    bool validChoice();
    bool validNum();
    void printMain();
    void printRock();
    void printLettuce();
    void printPuddle();
    void printSpaceChoice();
    void printMove();
    void printError();
    int stringToInt();
    string getUserString();
};

#endif
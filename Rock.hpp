/***********************************************
Program Name:   Final Project
Author:         Andre Paul
Date:           12/8/2019
Description:    Header for Rock class, derived
                from Space class. Overrides constructor
                and healthAffect().
************************************************/

#include "Space.hpp"

#ifndef ROCK_HPP
#define ROCK_HPP

class Rock : public Space
{
public:
    Rock() : Space()
    {
        this->type = ARock; 
    };
    int healthAffect()
    {
        return 0;
    };
};

#endif
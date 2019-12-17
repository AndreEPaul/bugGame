/***********************************************
Program Name:   Final Project
Author:         Andre Paul
Date:           12/8/2019
Description:    Header for Puddle class, derived
                from Space class. Overrides constructor
                and healthAffect().
************************************************/

#include "Space.hpp"

#ifndef PUDDLE_HPP
#define PUDDLE_HPP

class Puddle : public Space
{
public:
    Puddle() : Space()
    {
        this->type = BigPuddle; 
    };
    int healthAffect()
    {
        return -4;
    };
};

#endif
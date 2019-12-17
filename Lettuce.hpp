/***********************************************
Program Name:   Final Project
Author:         Andre Paul
Date:           12/8/2019
Description:    Header for Lettuce class, derived
                from Space class. Overrides constructor
                and healthAffect().
************************************************/

#include "Space.hpp"

#ifndef LETTUCE_HPP
#define LETTUCE_HPP

class Lettuce : public Space
{
public:
    Lettuce() : Space()
    {
        this->type = HeadOfLettuce; 
    };
    int healthAffect()
    {
        return 2;
    };
};

#endif
/***********************************************
Program Name:   Final Project
Author:         Andre Paul 
Date:           10/19/2019
Description:    This is the implement file for the 
                Die class. It has a member that 
                represents the number of sides for 
                a die object. It also has a function
                that returns a random "rolled" number
                to represent rolling a die.
                This has been taken from the Die class
                used in Lab 3, but roll() and the destructor
                have been modified back to *not* being
                virtual, since they don't need to be
                overridden.
************************************************/

#include "Die.hpp"
#include <cstdlib>

/***********************************************
Description:    Default Constructor. Default to 6 sided die.
************************************************/

Die::Die()
{
    this->numSides = 6;
}

/***********************************************
Description:    Regular constructor.
************************************************/

Die::Die(int numSidesIn)
{
    this->numSides = numSidesIn;
}

/***********************************************
Description:    Roll function. 
************************************************/

int Die::roll()
{
    // Local variable to store roll.
    int roll;

    roll = (rand() % numSides);

    return roll + 1;
}

/***********************************************
Description:    Getter function for numSides.
************************************************/

int Die::getNumSides()
{
    return numSides;
}
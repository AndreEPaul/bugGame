/***********************************************
Program Name:   Final Project
Author:         Andre Paul 
Date:           11/30/2019
Description:    This is the header file for the 
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

#ifndef DIE_HPP
#define DIE_HPP

class Die
{
private:
    int numSides;
public:
    Die();
    Die(int);
    int roll();
    int getNumSides();
};

#endif
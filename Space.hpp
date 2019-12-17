/***********************************************
Program Name:   Final Project
Author:         Andre Paul
Date:           12/8/2019
Description:    Header for Space class (abstract).
                This also contains the declarations of
                the enums Item and Type. This also utilizes
                the Die class from previous assignments
                in order to generate a "random" item
                for a space. The rest of the implementation
                is self documenting since it's almost
                all setters/getters.
************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include "Die.hpp"

enum Item{Nothing=1, Ant, Blueberry, BeetleShell, Poisonberry, Grass};
enum Type{HeadOfLettuce, BigPuddle, ARock};

class Space
{
protected:
    Space* top;
    Space* right;
    Space* left;
    Space* bottom;
    Item item;
    Type type;
    Die itemChoice;     
public:
    Space()
    {
        this->item = static_cast<Item>(this->itemChoice.roll());    
        this->top = nullptr;
        this->right = nullptr;
        this->left = nullptr;
        this->bottom = nullptr;
    };
    void generateItem()
    {
        this->item = static_cast<Item>(this->itemChoice.roll());    
    };
    virtual int healthAffect()=0;
    Space* getTop()
    {
        return this->top;
    };
    Space* getRight()
    {
        return this->right;
    };
    Space* getLeft()
    {
        return this->left;
    };
    Space* getBottom()
    {
        return this->bottom;
    };
    Item getItem()
    {
        return this->item;
    };
    void setTop(Space* topIn)
    {
        this->top = topIn;
    };
    void setRight(Space* rightIn)
    {
        this->right = rightIn;
    };
    void setLeft(Space* leftIn)
    {
        this->left = leftIn;
    };
    void setBottom(Space* bottomIn)
    {
        this->bottom = bottomIn;
    };
    void setItem(Item itemIn)
    {
        this->item = itemIn;
    };
    Type getType()
    {
        return this->type;
    };
};

#endif
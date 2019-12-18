/***********************************************
Program Name:   Final Project
Author:         Andre Paul
Date:           11/20/2019
Description:    This is the implement file for the
                Menu class. It reuses a lot of the Menu code
                from previous assignments. Variations
                have been made to validChoice() and 
                start(). All the gameflow is in start().
                Uses Spaces for the game board and a 
                stack for the game container of items.
                test commit from CLion
************************************************/

#include "Menu.hpp"
#include "Puddle.hpp"
#include "Rock.hpp"
#include "Lettuce.hpp"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::stoi;


/***********************************************
Description:    Control flow for this assignment.
************************************************/

void Menu::start()
{
    this->roundCount = 1;
    this->health = 10;

    // Board initialization.
    // Make some temp ptrs to assist in building board.
    Space* ptrToRock1 = &(this->rock1);
    Space* ptrToRock2 = &(this->rock2);
    Space* ptrToPuddle1 = &(this->puddle1);
    Space* ptrToPuddle2 = &(this->puddle2);
    Space* ptrToLettuce1 = &(this->lettuce1);
    Space* ptrToLettuce2 = &(this->lettuce2);

    // Adjust all the space ptrs as needed.
    // Desired board is as follows:
    // This is built manually but could later be
    // adjusted to be randomized (to a reasonable degree).
    //       ^            ^             ^
    // <   puddle 1 <-> rock2    <-> lettuce2   >
    // <   rock1    <-> lettuce1 <-> puddle2    >
    //       v              v           v
    rock1.setTop(ptrToPuddle1);
    rock1.setRight(ptrToLettuce1);
    rock1.setLeft(ptrToPuddle2);
    rock1.setBottom(ptrToPuddle1);

    puddle1.setBottom(ptrToRock1);
    puddle1.setRight(ptrToRock2);
    puddle1.setLeft(ptrToLettuce2);
    puddle1.setTop(ptrToRock1);
    
    lettuce1.setLeft(ptrToRock1);
    lettuce1.setTop(ptrToRock2);
    lettuce1.setBottom(ptrToRock2);
    lettuce1.setRight(ptrToPuddle2);
    
    rock2.setBottom(ptrToLettuce1);
    rock2.setTop(ptrToLettuce1);
    rock2.setLeft(ptrToPuddle1);
    rock2.setRight(ptrToLettuce2);
    
    lettuce2.setLeft(ptrToRock2);
    lettuce2.setRight(ptrToPuddle1);
    lettuce2.setTop(ptrToPuddle2);
    lettuce2.setBottom(ptrToPuddle2);
    
    puddle2.setTop(ptrToLettuce2);
    puddle2.setBottom(ptrToLettuce2);
    puddle2.setRight(ptrToRock1);
    puddle2.setLeft(ptrToLettuce1);

    // All the other ptrs in each space defaulted to nullptr upon
    // instantiation, so no need to adjust further. 

    // game STARTS at rock1.
    this->spotInBoard = ptrToRock1;

    // Gameflow.
    this->printMain();

    while(this->health > 0 && this->roundCount < 10)
    {
        this->spaceOccurence();
        
        this->checkedForItem = false;

        do
        {
            // Asks for action to be made.
            this->printSpaceChoice();
            this->readInString();

            // Validate.
            while(!this->validChoice())
            {
                this->printError();
                this->readInString();
            }

            int choice = this->stringToInt();
            // Moving is a special case.

            this->menuChoice(choice);

        }while(this->getUserString() != "3");


        // If choice is "3", then user is moving spaces.
        // Loop until move is successful.
        /* UPDATE: changed the pointer linked spaces to ALL
         * point to another space. Thus, impossible to make an invalid
         * move. So we can remove this loop.*/

        // Use a temp ptr for moving spaces.
        // Initialized at spotInBoard.
        // will reinitialize every loop.
        Space* toMove = this->spotInBoard;
        this->printMove();
        this->readInString();

        // validate.
        while(!this->validChoice())
        {
            this->printError();
            this->readInString();
        }

        // Switch on user choice.
        int direction = this->stringToInt();
        switch(direction)
        {
            case 1:
            {
                toMove = this->spotInBoard->getTop();
                break;
            }
            case 2:
            {
                toMove = this->spotInBoard->getBottom();
                break;
            }
            case 3:
            {
                toMove = this->spotInBoard->getLeft();
                break;
            }
            case 4:
            {
                toMove = this->spotInBoard->getRight();
                break;
            }
            default:
                break;
        }

        
        // Once this loop breaks, toMove points to valid space.
        // So assign as the new spotInBoard. Also, a space move
        // is a "day"
        this->spotInBoard = toMove;
        this->roundCount++;
    }

    // Main gameplay is over. Alert user if they won.
    if(this->roundCount >= 10)
    {
        cout << "Congratulations!! You made it, you turned into a butterfly!" << endl;
    }
    else
    {
        cout << "Sorry. The life of a caterpillar was simply too challenging for you. Try again!" << endl;
    }
}

/***********************************************
Description:    Takes in current spot in the board.
                Switches on the space type, also
                checks for helpful item (in case
                of puddle). Also adjusts health.
************************************************/

void Menu::spaceOccurence()
{
    switch(this->spotInBoard->getType())
    {
        case ARock:
        {
            this->printRock();

            break;
        }
        case HeadOfLettuce:
        {
            this->printLettuce();

            this->health += this->spotInBoard->healthAffect();

            break;
        }
        case BigPuddle:
        {
            this->printPuddle();

            Item localItem = Nothing;
            if(!this->itemBag.empty())
            {
                localItem = this->itemBag.top();
            }

            if(localItem == BeetleShell)
            {
                cout << "What luck! You were able to use the beetle shell like a boat \n";
                cout << "to float safely on the puddle." << endl;
                this->itemBag.pop();
            }
            else
            {
                // Puddle makes you lose health.
                this->health += this->spotInBoard->healthAffect();
            }
            break;
        }
        default:
        break;
    }
}

void Menu::menuChoice(int choice)
{
    switch(choice)
    {
        case 1:
        {
            if(this->fullBag())
            {
                cout << "You can't carry any more items!" << endl;
            }
            else if(checkedForItem)
            {
                cout << "You already checked this space for an item today." << endl;
            }
            else
            {
                // localitem gets whatever the item is in the space.
                // Then we need to generate a new one and change
                // checkedForItem to true.
                Item localItem = this->spotInBoard->getItem();
                this->spotInBoard->generateItem();
                this->checkedForItem = true;

                switch(localItem)
                {
                    case Nothing:
                    {
                        cout << "There's nothing here!" << endl;
                        break;
                    }
                    case Ant:
                    {
                        cout << "Uh oh! It's an ant, and it is not happy that you got in its way!\n";
                        cout << "You're able to get away, but lost some health in the process." << endl;
                        this->health -= 3;
                        break;
                    }
                    case Blueberry:
                    {
                        cout << "Yum! Looks like some sort of berry. You put it on your back \n";
                        cout << "to save for later." << endl;
                        this->itemBag.push(Blueberry);
                        break;
                    }
                    case BeetleShell:
                    {
                        cout << "Interesting... looks like some sort of beetle exoskeleton. You're\n";
                        cout << "not sure if it could be of use to you, but you bring it along anyway." << endl;
                        this->itemBag.push(BeetleShell);
                        break;
                    }
                    case Poisonberry:
                    {
                        cout << "Yum! Looks like some sort of berry. You put it on your back \n";
                        cout << "to save for later." << endl;
                        this->itemBag.push(Poisonberry);
                        break;
                    }
                    case Grass:
                    {
                        cout << "It's just a blade of grass, but this is still nutritious.\n";
                        cout << "You save it for eating later." << endl;
                        this->itemBag.push(Grass);
                        break;
                    }
                    default:
                        break;
                }
            }
            break;
        }
        case 2:
        {
            if(this->itemBag.empty())
            {
                cout << "You don't have anything on your back!" << endl;
            }
            else
            {
                // "peeking" at the top of the stack
                const Item localItem = this->itemBag.top();

                switch(localItem)
                {
                    case Blueberry:
                    {
                        cout << "Mmmm, it's a blueberry. You munch on it and gain some health!" << endl;
                        this->health += 1;
                        this->itemBag.pop();
                        break;
                    }
                    case BeetleShell:
                    {
                        cout << "It's just the beetle shell... you can't think of a way to use it, so\n";
                        cout << "you put it back on your back." << endl;
                        break;
                    }
                    case Poisonberry:
                    {
                        cout << "Blech!! That berry was a poisonberry. You lose some health." << endl;
                        this->health -= 3;
                        this->itemBag.pop();
                        break;
                    }
                    case Grass:
                    {
                        cout << "This grass will hold you over for a little. You gain a bit of health." << endl;
                        this->health += 1;
                        this->itemBag.pop();
                        break;
                    }
                    default:
                        break;
                }
            }
            break;
        }
        case 4:
        {
            cout << "Your health is " << this->health << "\n";
            cout << "It is day number " << this->roundCount << endl;
            break;
        }
        default:
            break;
    }
}

/***********************************************
Description:    Checks if bag is full.
************************************************/

bool Menu::fullBag()
{
    bool answer = false;

    if(this->itemBag.size() >= 3)
    {
        answer = true;
    }

    return answer;
}

/***********************************************
Description:    This reads in the user input.
************************************************/

void Menu::readInString()
{
    // Clear out any leftover contents of the string.
    userString.clear();

    getline(cin, userString, '\n');
}

/***********************************************
Description:    Validating the user menu choice.
************************************************/

bool Menu::validChoice()
{
    bool result = false;

    // Check they only entered one digit.
    if(this->userString.length() == 1)
    {
        // Check the character is correct range.
        if((this->userString[0] >= '1' && this->userString[0] <= '4'))
        {
            result = true;
        }
    }
    
    return result;
}

/***********************************************
Description:    This checks that a number has been entered.
                Specifically, an int (could be 
                modified to double, etc.). The loop
                runs through each character in the
                string to see if it has the ASCII values
                of numbers.
************************************************/

bool Menu::validNum()
{
    // Local bool variable.
    bool result = true;

    // Make sure string is nonempty.
    if(userString.length() == 0)
    {
        result = false;
    }

    // Modification to allow for negative numbers.
    if(!(userString[0] == '-' || userString[0] >= '0' || userString[0] <= '9'))
    {
        result = false;
    }

    for(unsigned i = 1; i < userString.length(); i++)
    {
        if((userString[i] < '0') || (userString[i] > '9'))
        {
            result = false;
        }
    }

    // Check if the number is too many digits.
    if(userString.length() > 7)
    {
        result = false;
    }

    return result;
}

/***********************************************
Description:    These are all the print statements
                for the different prompts/errors/etc.
************************************************/

void Menu::printMain()
{
    cout << "A BUG'S STRIFE \n";
    cout << "by Andre Paul \n";
    cout << "Welcome to A Bug's Strife! This is a text-based \n";
    cout << "game where you are a caterpillar trying to turn into a butterfly. \n";
    cout << "You will turn into a butterfly if you can last 10 days! \n";
    cout << "Every time you move to a new space, it takes you a day.\n";
    cout << "There's food to munch on to keep your health up. But look out... \n";
    cout << "There's also plenty of stuff out there that'll hurt a caterpillar! \n";
    cout << "You also can carry a few things on your back. But you can only grab an item\n";
    cout << "that's up by your head, since your little caterpillar arms are too small.\n";
    cout << "Be careful and have fun!" << endl;
}

void Menu::printRock()
{
    cout << "You crawl your way to a run-of-the-mill rock. Nothing special here.\n";
    cout << "Pretty boring rock, but at least there's nothing bad!\n";
    cout << "There could be something underneath it..." << endl;
}

void Menu::printLettuce()
{
    cout << "Fantastic luck! It's a head of lettuce, your favorite thing to eat!\n";
    cout << "You gain some health by munching on some lettuce.\n";
    cout << "Is there something behind the lettuce head?" << endl;
}

void Menu::printPuddle()
{
    cout << "Oh no!! It's a huge puddle and your little caterpillar legs\n";
    cout << "are having a tough time staying above water!\n";
    cout << "You might lose some health in this struggle!\n";
    cout << "But maybe there's something on the other side of the puddle..." << endl;
}

void Menu::printSpaceChoice()
{
    cout << "1: Check for an item in the space. \n";
    cout << "2: Use an item on your back.\n";
    cout << "3: Move to a new space.\n";
    cout << "4: Check your health and day." << endl;
}

void Menu::printMove()
{
    cout << "1: Move forward.\n";
    cout << "2: Move backward.\n";
    cout << "3: Move to the left.\n";
    cout << "4: Move to the right." << endl;
}

void Menu::printError()
{
    cout << "Invalid input. Please try again." << endl;
}

/***********************************************
Description:    This uses stoi to convert userString
                into an int, then it assigns it to
                userInt.
************************************************/

int Menu::stringToInt()
{
    return stoi(this->userString);
}

/***********************************************
Description:    Getters.
************************************************/

string Menu::getUserString()
{
    return this->userString;
}
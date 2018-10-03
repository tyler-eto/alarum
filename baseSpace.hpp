/********************************************************************* 
** Program name: baseSpace.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file base space class. Each square holds stack 
for storing dialogue when interacting with room. Each also has a
container to hold 3 items. Nullptr should occupy any spaces not filled

runScenario contains function that will be specific to each space type
*********************************************************************/

#ifndef BASE_SPACE_HPP
#define BASE_SPACE_HPP

#include <string>
#include <stack>
#include <array>
#include <iostream>
#include "item.hpp"
#include "player.hpp"


class BaseSpace 
{
protected:
    std::array<Item*, 3> itemContainer;
    std::stack<std::string> dialogue;
    std::string type;
    // std::string name;
public:
    BaseSpace();
    virtual ~BaseSpace();
    virtual void runScenario(Player *p) {};  // will run scenario for room if there is one
    
    std::string getType();
    std::string getItemNameByIndex(int index);
    // std::string getName();
    // void setName(std::string n);
    bool hasItems();

    void showItems();
    Item* selectItem(int index);
    std::string describe();
    std::string storyText(std::string text);

    // for setup
    void pushDialogue(std::string s);
    bool pushItem(Item *item);
    bool pushItemWithIndex(Item *item, int index);
};

#endif  // BASE_SPACE_HPP

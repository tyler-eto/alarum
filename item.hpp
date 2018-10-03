/********************************************************************* 
** Program name: item.hpp
** Author: Tyler Eto
** Date: 6/7/18
** Description: design file for base "item" class. they're mostly just
objects with names. Items like weapons, painkillers, and oxygen tanks
are derived objects
*********************************************************************/

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>


class Item 
{
protected:
    std::string name;
    std::string description;
    int attackStat;
public:
    Item(std::string n, std::string d, int as);
    Item(std::string n, std::string d);
    // virtual ~Item() {};
    std::string getName();
    void setName(std::string n);
    std::string getDescription();
    void setDescription(std::string d);
    int getAttackStat();
    void setAttackStat(int as);
};

#endif  // ITEM_HPP

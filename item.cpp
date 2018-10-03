/********************************************************************* 
** Program name: item.cpp
** Author: Tyler Eto
** Date: 6/7/18
** Description: implementation file for base Item class
*********************************************************************/

#include <string>
#include "item.hpp"


// constructors
Item::Item(std::string n, std::string d, int as=0) {
    this->name = n;
    this->description = d;
    this->attackStat = as;
}


Item::Item(std::string n, std::string d) {
    this->name = n;
    this->description = d;
    this->attackStat = 0;
}


// getters and setters
std::string Item::getName() { return this->name; }
void Item::setName(std::string n) { this->name = n; }

std::string Item::getDescription() { return this->description; }
void Item::setDescription(std::string d) { this->description = d; }

int Item::getAttackStat() { return this->attackStat; }
void Item::setAttackStat(int as) { this->attackStat = as; };

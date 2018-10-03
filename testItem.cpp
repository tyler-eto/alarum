/********************************************************************* 
** Author: Tyler Eto
** Compile: g++ -std=c++11 -Wall item.cpp testItem.cpp -o builds/testItem
*********************************************************************/


#include "item.hpp"
#include <iostream>
#include "assert.h"

using std::cout;
using std::endl;


int main() {
	Item i = Item("rune1", "A red, glowing chunk of necrozite inscribed with an unreadable language", 0);
	assert(i.getName() == "rune1" && "instantiate Item failed");
	assert(i.getDescription() == "A red, glowing chunk of necrozite inscribed with an unreadable language" && "instantiate Item failed");
	assert(i.getAttackStat() == 0 && "instantiate Item failed");
	
	i.setDescription("collectible");
	assert(i.getDescription() == "collectible" && "setDescription failed");
	cout << "Complete" << endl;
}
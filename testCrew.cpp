/********************************************************************* 
** Author: Tyler Eto
** Compile: g++ -std=c++11 -Wall helpers.cpp item.cpp crewMember.cpp player.cpp infected.cpp testCrew.cpp -o builds/testCrew
*********************************************************************/

#include "player.hpp"
#include "infected.hpp"
#include "assert.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	Player p = Player();
	cout << "should be 100, 100, fists" << endl;
	p.showStats();
	cout << endl;

	assert(p.attack() == 5 && "Player attack failed");

	cout << "should say empty" << endl;
	p.showItems();
	cout << endl;

	Item *rifle = new Item("rifle", "standard guard firearm", 10);
	Item *exosuit = new Item("exosuit", "usually used for construction", 30);
	p.addItem(rifle);
	p.addItem(exosuit);
	assert(p.inspectInventory("rifle") && "inspectInventory failed");
	p.showItems();

	cout << "selecting new weapon" << endl;
	p.selectEquippedWeapon();

	cout << "should be 100, 90, rifle" << endl;
	p.useO2();
	p.showStats();

	p.removeItem("exosuit");
	p.removeItem("rifle");
	p.showItems();
	p.showStats();


	Infected i = Infected();
	assert(i.getHP() == 30 && "instantiation of Infected failed");
	int damage = i.attack();
	assert(damage > 0 && damage <= 5 && "Infected attack failed");

	Item *map = new Item("map", "map of the wreckage");
	p.addItem(map);

	p.viewMap("Galley");

	// delete rifle;
	rifle = nullptr;
	// delete exosuit;
	exosuit = nullptr;
	// delete map;
	map = nullptr;

	return 0;
}
/********************************************************************* 
** Author: Tyler Eto
** Compile: g++ -std=c++11 -Wall baseSpace.cpp player.cpp crewMember.cpp helpers.cpp item.cpp testBaseSpace.cpp -o builds/testBaseSpace
*********************************************************************/

#include "baseSpace.hpp"
#include <iostream>
#include "assert.h"

using std::cout;
using std::endl;


int main() {
	BaseSpace bs = BaseSpace();
	bs.pushDialogue("With the fire out, you begin to recognize the room. It's the galley.");
	bs.pushDialogue("The room is on fire!");
	// describe space
	assert(bs.describe() == "The room is on fire!" && "describeSpace failed");
	assert(bs.describe() == "With the fire out, you begin to recognize the room. It's the galley." && "describeSpace last failed");
	assert(bs.describe() == "With the fire out, you begin to recognize the room. It's the galley." && "describeSpace re-stack failed");

	Item *i1 = new Item("chainsaw", "Looks like it still works...");
	Item *i2 = new Item("extinguisher", "I could put out fires with this");
	Item *i3 = new Item("keycard", "the captain's card");
	Item *i4 = new Item("crowbar", "Crowbar V3.0");

	assert(bs.pushItem(i1) == true && "pushItem failed");
	assert(bs.pushItem(i2) == true && "pushItem failed");
	assert(bs.pushItem(i3) == true && "pushItem failed");
	assert(bs.pushItem(i4) == false && "pushItem maxLimit failed");

	cout << "should have 3 items" << endl;
	bs.showItems();

	Item *myItem = bs.selectItem(1);
	assert(myItem->getName() == "extinguisher" && "selectItem failed");
	assert(myItem->getAttackStat() == 0 && "selectItem failed");

	cout << "should have 2 items" << endl;
	bs.showItems();

	// cleanup
	delete myItem;
	myItem = nullptr;
	i1 = nullptr;
	i2 = nullptr;
	i3 = nullptr;
	i4 = nullptr;
}
/********************************************************************* 
** Program name: fireSpace.cpp
** Author: Tyler Eto
** Date: 6/7/18
** Description: implementation file for derived FireSpace class
*********************************************************************/

#include "fireSpace.hpp"
#include "helpers.hpp"


// constructor
FireSpace::FireSpace() {
	onFire = true;
	type = "fire";
}


/*********************************************************************
runScenario :	check for extinguisher in player inventory. if yes,
set onFire to false else damage 15 and use oxygen to be in the space
*********************************************************************/
void FireSpace::runScenario(Player *p) {
	if (p->inspectInventory("extinguisher")) {
		if (onFire) {
			typeText(storyText("the room is on fire! though flames threaten to snuff you out, you used the extinguisher to put an end to them"));
			onFire = false;
		}
	} else if (onFire) {
		typeText(storyText("the room is on fire! there is black smoke everywhere and the smell is awful.\nthough the suit protect you a bit, you still take damage"));
		p->takeDamage(15);
		p->useO2();
	}
}


// getter for onFire
bool FireSpace::isOnFire() {
	return onFire;
}

/********************************************************************* 
** Program name: blackHoleSpace.cpp
** Author: Tyler Eto
** Date: 6/9/18
** Description: implementation file for derived blackHoleSpace class
*********************************************************************/

#include "blackHoleSpace.hpp"


// constructor
BlackHoleSpace::BlackHoleSpace() {
	type = "blackHole";
}


/*********************************************************************
runScenario :	check for runes in inventory to win game; otherwise
end game
*********************************************************************/
void BlackHoleSpace::runScenario(Player *p) {
	if (!p->inspectInventory("redRune") || !p->inspectInventory("blueRune") || !p->inspectInventory("blackRune")) {
		p->takeDamage(100);
	}
}
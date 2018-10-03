/********************************************************************* 
** Program name: infected.cpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: implementation file for derived Infected class
*********************************************************************/

#include "infected.hpp"
#include "helpers.hpp"


// constructor
Infected::Infected() {
	this->HP = 30;
	this->equippedWeapon = new Item("fists", "simple fisticuffs", 10);  // originally 5
}

// destructor
Infected::~Infected() {
	delete this->equippedWeapon;
	this->equippedWeapon = nullptr;
}


/*********************************************************************
attack :	use equipped weapon (fists) to attack and return damage
			between 1-5
*********************************************************************/
int Infected::attack() {
	return generateInt(1, this->equippedWeapon->getAttackStat());
}


/*********************************************************************
takeDamage:	takes damage input and subtracts it from the characters hp	
*********************************************************************/
void Infected::takeDamage(int damage) {
	this->HP -= damage;
}

/********************************************************************* 
** Program name: abomination.cpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: implementation file for derived Abomination class
*********************************************************************/

#include "abomination.hpp"
#include "helpers.hpp"


// constructor
Abomination::Abomination() {
	this->HP = 100; // originally 50
	this->equippedWeapon = nullptr;
}

// destructor
// Abomination::~Abomination() {
// 	delete this->equippedWeapon;
// 	this->equippedWeapon = nullptr;
// }


/*********************************************************************
attack :	causes loss of sanity between 1-10
*********************************************************************/
int Abomination::attack() {
	return generateInt(10, 15);  // originally 1, 10
}


/*********************************************************************
takeDamage:	takes damage input and subtracts it from the characters hp	
*********************************************************************/
void Abomination::takeDamage(int damage) {
	this->HP -= damage;
}

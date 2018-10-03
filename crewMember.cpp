/********************************************************************* 
** Program name: crewMember.cpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: implementation file for base CrewMember class
*********************************************************************/

#include "crewMember.hpp"
#include "helpers.hpp"
#include <iostream>

using std::cout;
using std::endl;


CrewMember::CrewMember() {
	this->HP = 0;
	this->equippedWeapon = nullptr;
}


// getter and setter
int CrewMember::getHP() { return this->HP; }


void CrewMember::setEquippedWeapon(Item *i) {
	// delete fists weapon once filled with new weapon from inventory
	if (equippedWeapon->getName() == "fists") {
		delete equippedWeapon;
		equippedWeapon = nullptr;
	}
	this->equippedWeapon = i;
}


/*********************************************************************
takeDamage:	takes damage input and subtracts it from the characters hp	
*********************************************************************/
void CrewMember::takeDamage(int damage) {
	this->HP -= damage;
}


/*********************************************************************
showStats:	show current stats for crew member
*********************************************************************/
void CrewMember::showStats() {
	cout << "HP: " << this->HP << endl;
}


/*********************************************************************
attack :	for base version of attack, it uses primaryWeapon to roll
			a number between 1 and max attackDamage of weapon
*********************************************************************/
int CrewMember::attack() {
	return generateInt(1, this->equippedWeapon->getAttackStat());
}

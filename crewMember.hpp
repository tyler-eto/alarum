/********************************************************************* 
** Program name: crewMember.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file for base CrewMember class. All crew members
have HP and equipped weapon slot.
*********************************************************************/

#ifndef CREWMEMBER_HPP
#define CREWMEMBER_HPP

#include "item.hpp"

class CrewMember
{
protected:
	int HP;
	Item *equippedWeapon;
public:
	CrewMember();
	virtual ~CrewMember() {};

	int getHP();
	virtual void takeDamage(int damage);
	void setEquippedWeapon(Item *i);
	virtual void showStats();
	virtual int attack();
};

#endif  // CREWMEMBER_HPP
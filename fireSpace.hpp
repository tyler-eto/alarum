/********************************************************************* 
** Program name: fire.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file derived FireSpace class.

runScenario: simple scenario, will look for extinguisher in inventory.
if exists, fire will be put out; if not, damage player 15 and use 10 O2
*********************************************************************/

#ifndef FIRE_SPACE_HPP
#define FIRE_SPACE_HPP

#include "baseSpace.hpp"


class FireSpace : public BaseSpace
{
protected:
	bool onFire;
public:
	FireSpace();
	void runScenario(Player *p);
	bool isOnFire();
};

#endif  // FIRE_SPACE_HPP
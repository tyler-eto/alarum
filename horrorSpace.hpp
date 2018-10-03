/********************************************************************* 
** Program name: horrorSpace.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file for derived HorrorSpace class. These squares
may hold a single eldritch abomination that is rather challenging. with 
every turn it'll take sanity from the player from its mere existence.
after enemy is clear, space becomes like baseSquare
*********************************************************************/

#ifndef HORROR_SPACE_HPP
#define HORROR_SPACE_HPP

#include <string>
#include <queue>
#include <iostream>
#include "item.hpp"
#include "abomination.hpp"
#include "baseSpace.hpp"


class HorrorSpace : public BaseSpace
{
protected:
	bool enemyDefeated;
	Abomination *enemy;
public:
	HorrorSpace();
	~HorrorSpace();

	void runScenario(Player *p);
	void confront(Player *p, Abomination *a);
	void fight(Player *p, Abomination *a);
	bool flee();
};

#endif  // HORROR_SPACE_HPP

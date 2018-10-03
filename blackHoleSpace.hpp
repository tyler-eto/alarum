/********************************************************************* 
** Program name: blackHoleSpace.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file base BlackHole class. Represents instant
death for the player unless certain criteria are met

runScenario kills player instantly and ends game unless player has
collected the 3 runes. The 3 runes will cause the black hole to reverse
time, reverting the ship and crew members back normal
*********************************************************************/

#ifndef BLACK_HOLE_HPP
#define BLACK_HOLE_HPP

#include "baseSpace.hpp"


class BlackHoleSpace : public BaseSpace 
{
protected:
public:
	BlackHoleSpace();
	void runScenario(Player *p);
};

#endif  // BLACK_HOLE_HPP
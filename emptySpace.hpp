/********************************************************************* 
** Program name: emptySpace.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file derived EmptySpace class. These squares won't
have a scenario
*********************************************************************/

#ifndef EMPTY_SPACE_HPP
#define EMPTY_SPACE_HPP

#include "baseSpace.hpp"


class EmptySpace : public BaseSpace
{
protected:
public:
	EmptySpace();
	void runScenario(Player *p);
};

#endif  // EMPTY_SPACE_HPP
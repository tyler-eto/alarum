/********************************************************************* 
** Program name: infected.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file derived infected class. just uses default
behavior except starts with fists item as equipped weapon
*********************************************************************/

#ifndef INFECTED_HPP
#define INFECTED_HPP

#include "crewMember.hpp"


class Infected : public CrewMember
{
protected:
public:
	Infected();
	~Infected();

	int attack();
	void takeDamage(int damage);
};

#endif  // INFECTED_HPP


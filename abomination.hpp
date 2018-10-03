/********************************************************************* 
** Program name: abomination.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file derived abomination class. just uses default
behavior except no item since it causes loss of sanity
*********************************************************************/

#ifndef ABOMINATION_HPP
#define ABOMINATION_HPP

#include "crewMember.hpp"


class Abomination : public CrewMember
{
protected:
public:
	Abomination();
	// ~Abomination();

	int attack();
	void takeDamage(int damage);
};

#endif  // ABOMINATION_HPP


/********************************************************************* 
** Program name: driftSpace.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file derived DriftSpace class.
*********************************************************************/

#ifndef DRIFT_SPACE_HPP
#define DRIFT_SPACE_HPP

#include "baseSpace.hpp"


class DriftSpace : public BaseSpace
{
protected:
public:
	DriftSpace();
	void runScenario(Player *p);
};

#endif  // DRIFT_SPACE_HPP

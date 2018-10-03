/********************************************************************* 
** Program name: EmptySpace.cpp
** Author: Tyler Eto
** Date: 6/7/18
** Description: implementation file for EmptySpace class
*********************************************************************/

#include "emptySpace.hpp"
#include "helpers.hpp"


// constructor
EmptySpace::EmptySpace() {
	type = "empty";
}


/*********************************************************************
runScenario :	do nothing
*********************************************************************/
void EmptySpace::runScenario(Player *p) {
	typeText(storyText("you enter an empty room. somehow this room has been untouched by the destruction."));
}

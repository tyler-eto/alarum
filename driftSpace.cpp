/********************************************************************* 
** Program name: infestedSpace.cpp
** Author: Tyler Eto
** Date: 6/7/18
** Description: implementation file for derived DriftSpace class
*********************************************************************/

#include "driftSpace.hpp"
#include "helpers.hpp"
#include <chrono>
#include <thread>


// constructor
DriftSpace::DriftSpace() {
	type = "drift";
}


void DriftSpace::runScenario(Player *p) {
	typeText(storyText("you drift through space. your heart pounding in your ears"));
	typeText(storyText(".."), 10);
	typeText(storyText(".."), 10);
	
	p->useO2();
}
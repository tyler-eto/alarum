/********************************************************************* 
** Program name: main.cpp
** Author: Tyler Eto
** Date: 6/12/18
** Description: implementation file for base Item class
*********************************************************************/

#include <string>
#include "helpers.hpp"
#include "player.hpp"
#include "baseSpace.hpp"
#include "setupGame.hpp"


int main() {
	int gameChoice;
	std::string gameOptions[2] = {"play again", "quit"};
	
	do {
		play();
		gameChoice = selectOptions(gameOptions, 2, "would you like to play again?");
	} while (gameChoice != 2);

	return 0;
}

// increase attack of infected
// increase sanity and health of abomination
// increase fire damage to be like an actual block
// increase drift o2 usage
// increase inventory speed

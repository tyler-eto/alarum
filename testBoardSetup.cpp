/********************************************************************* 
** Author: Tyler Eto
** Compile: 
g++ -std=c++11 -Wall helpers.cpp crewMember.cpp player.cpp setupGame.cpp testBoardSetup.cpp baseSpace.cpp blackHoleSpace.cpp driftSpace.cpp emptySpace.cpp fireSpace.cpp horrorSpace.cpp infestedSpace.cpp item.cpp -o builds/testBoardSetup
*********************************************************************/

#include <iostream>
#include "assert.h"
#include "setupGame.hpp"
#include "helpers.hpp"

using std::cout;
using std::endl;




int main() {
	/*typeText(
"############################################################################\n"
"############################################################################\n"
"######     ###  ##############     ###       ####  ####  ###          ######\n"
"#####  ##  ###  #############  ##  ###  ###  ####  ####  ###  ###  ##  #####\n"
"####  ###  ###  ############  ###  ###  ###  ####  ####  ###  ###  ###  ####\n" 
"###        ###  ###########        ###      #####  ####  ###  ###  ####  ###\n"
"##  #####  ###  ##########  #####  ###  ###  ####  ####  ###  ###  #####  ##\n" 
"#  ######  ###        ###  ######  ###  ####  ###        ###  ###  ######  #\n"
"############################################################################\n"
"############################################################################\n", 1);*/

	Node ***board = createBoard();
	bool r = false;

	typeText("making board");
	boardSetup(board, r);
	typeText("got board");

	typeText("populating board with items");
	populateItems(board, r);
	cout << "board populated" << endl;

	// make sure current is the garage
	Node *current = findStartingRoom(board);
	viewMap(board, current->name);

	assert(current->name == "Bridge" && "boardSetup failed");
	current->space->showItems();
	assert(current->space->hasItems() == true && "populateItems failed");

	if (!r) {
		current = current->right;
		assert(current->name == "Armory" && "board linking failed");
		current = current->down;
		assert(current == nullptr  && "board linking failed");
	}

	deleteBoard(board);

	return 0;
}
/********************************************************************* 
** Program name: setupGame.hpp
** Author: Tyler Eto
** Date: 6/12/18
** Description: design file for game functions
*********************************************************************/

#include "node.hpp"


int const SIZE = 5;

Node*** createBoard();

void boardSetup(Node ***board, bool random=false);

void populateItems(Node ***board, bool random=false);

void roomSetup(Node ***board);

Node* findStartingRoom(Node ***board);

// void writeStory(Node ***board);

void viewMap(Node ***board, std::string currentRoom);

void deleteBoard(Node ***board);

void play();

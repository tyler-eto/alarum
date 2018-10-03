/********************************************************************* 
** Program name: baseSpace.cpp
** Author: Tyler Eto
** Date: 6/7/18
** Description: implementation file for BaseSpace class
*********************************************************************/

#include "baseSpace.hpp"
#include "helpers.hpp"

using std::cout;
using std::endl;


// constructor
BaseSpace::BaseSpace() {
	itemContainer.fill(nullptr);
	type = "";
	// name = "";
}

// destructor
BaseSpace::~BaseSpace() {
	for (int i=0; i<(int)itemContainer.size(); ++i) {
		if (itemContainer[i] != nullptr) {
			delete itemContainer[i];
			itemContainer[i] = nullptr;
		}
	}
}


// getters
std::string BaseSpace::getType() { return type; }
// std::string BaseSpace::getName() { return name; }
// void BaseSpace::setName(std::string n) { this->name = n; }


/*********************************************************************
getItemByIndex:	retrieve item name by index. used for investigation
*********************************************************************/
std::string BaseSpace::getItemNameByIndex(int index) {
	if (itemContainer[index] != nullptr) {
		return itemContainer[index]->getName();
	}
	return "";
}


/*********************************************************************
hasItems :	quick check if space has items in itemContainer
*********************************************************************/
bool BaseSpace::hasItems() {
	for (int i=0; i<(int)itemContainer.size(); ++i) {
		if (itemContainer[i] != nullptr) {
			return true;
		}
	}
	return false;
}


/*********************************************************************
showItems :	prints the items available in the room's itemContainer
*********************************************************************/
void BaseSpace::showItems() {
	for (int i=0; i<(int)itemContainer.size(); ++i) {
		if (itemContainer[i] != nullptr) {
			cout << i+1 << ") " << itemContainer[i]->getName() << " : " << itemContainer[i]->getDescription() << endl;
		}
	}
}


/********************************************************************* 
selectItem :	takes in index of item wanted by player and returns
				the item at the index
*********************************************************************/
Item* BaseSpace::selectItem(int index) {
	Item *tmp = itemContainer[index];
	// delete spot in itemContainer?
	// delete itemContainer[index];
	itemContainer[index] = nullptr;
	return tmp;
}


/********************************************************************* 
describeSpace :	grabs first dialogue from top of stack and prints it
*********************************************************************/
std::string BaseSpace::describe() {
	// set variable to dialogue
	std::string tmp = dialogue.top();

	// pop dialogue
	dialogue.pop();

	// add it back if stack is now empty
	if (dialogue.empty()) {
		dialogue.push(tmp);
	}
	return tmp;
}


/********************************************************************* 
storyText :	just does some formatting around story text
*********************************************************************/
std::string BaseSpace::storyText(std::string text) {
	// choose a color
	return text;
}


/********************************************************************* 
push_dialogue :	for game setup, push dialogue
*********************************************************************/
void BaseSpace::pushDialogue(std::string s) {
	dialogue.push(s);
}

/********************************************************************* 
pushItem :	for game setup, push item
*********************************************************************/
bool BaseSpace::pushItem(Item *item) {
	bool wasAdded = false;
	for (int i=0; i<(int)itemContainer.size(); ++i) {
		if (itemContainer[i] == nullptr && !wasAdded) {
			itemContainer[i] = item;
			wasAdded = true;
		}
	}
	return wasAdded;
}


/********************************************************************* 
pushItemWithIndex :	for setting items back if player doesn't want them
*********************************************************************/
bool BaseSpace::pushItemWithIndex(Item *item, int index) {
	if (itemContainer[index] == nullptr) {
		// push item
		itemContainer[index] = item;
		return true;
	}
	return false;
}

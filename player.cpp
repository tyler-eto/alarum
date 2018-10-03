/********************************************************************* 
** Program name: player.cpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: implementation file for derived player class
*********************************************************************/

#include "player.hpp"
#include "helpers.hpp"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;


//constructor
Player::Player() {
	this->HP = 100;
	this->O2 = 100;
	this->sanity = 100;
	this->equippedWeapon = new Item("fists", "simple fisticuffs", 5);
}


// destructor
Player::~Player() {
	// clean up equipped weapon
	if (equippedWeapon->getName() == "fists") {
		delete equippedWeapon;
		equippedWeapon = nullptr;
	}

	// clean up inventory
	for (int i=0; i<(int)inventory.size(); ++i) {
		delete inventory[i];
		inventory[i] = nullptr;
	}
}


// getter
int Player::getO2() { return this->O2; }
int Player::getSanity() { return this->sanity; }
void Player::setO2(int oxygen) { this->O2 = oxygen; }


/*********************************************************************
playerText :	formatting for text pertaining to player
*********************************************************************/
std::string Player::playerText(std::string text) {
	/*
	// cout << "@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @" << endl;
	cout << " -- " << endl;
	cout << " -- " << text << endl;
	cout << " -- " << endl;
	// cout << "@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @" << endl;
	*/
	return text;
}


/*********************************************************************
attack :	uses primary weapon to get attack damage. no random roll
*********************************************************************/
int Player::attack() {
	if (equippedWeapon == nullptr) {
		selectEquippedWeapon();
	}
	typeText(playerText("You attacked with your " + equippedWeapon->getName()));
	return equippedWeapon->getAttackStat();
}


/*********************************************************************
selectEquippedWeapon :	ask player to choose primary weapon
*********************************************************************/
void Player::selectEquippedWeapon() {
	if (inventory.size() > 0) {
		// show inventory
		for (int i=0; i<(int)inventory.size(); ++i) {
			cout << i+1 << ") " << inventory[i]->getName() << ": " << inventory[i]->getAttackStat() << endl;
		}
		cout << (int)inventory.size() + 1 << ") " << "Keep equipped weapon: " << equippedWeapon->getName() << ": " << equippedWeapon->getAttackStat() << endl;
		int index = promptUserInt("Select item to use as equipped weapon:", 1, inventory.size() + 1);
		
		// if elected not to keep equipped weapon, else do nothing
		if (index != (int)inventory.size() + 1) {
			setEquippedWeapon(inventory[index-1]);
		}
	} else {
		cout << "no items in inventory" << endl;
	}
}


/*********************************************************************
useO2 :	decrement oxygen by standard amount - 10
*********************************************************************/
void Player::useO2() {
	typeText(playerText(redText("15 oxygen lost")));
	this->O2 -= 15;  // originally 10

	if (O2 <= 0 && inspectInventory("oxygen_tank")) {
		typeText(playerText("you ran out of oxygen. luckily, you had a spare tank"));
		O2 = 100;
		removeItem("oxygen_tank");
	}
}


/*********************************************************************
takeDamage:	takes damage input and subtracts it from the characters hp
if lower than 0, use painkillers if available	
*********************************************************************/
void Player::takeDamage(int damage) {
	typeText(redText(std::to_string(damage) + " HP lost"));
	this->HP -= damage;

	if (HP <= 0 && inspectInventory("painkillers")) {
		playerText("you used the painkillers to restore your health");
		HP = 100;
		removeItem("painkillers");
	}
}


/*********************************************************************
loseSanity:	different things will cause the player to lose sanity	
*********************************************************************/
void Player::loseSanity(int horrors) {
	typeText(redText(std::to_string(horrors) + " sanity lost"));
	this->sanity -= horrors;
}


/*********************************************************************
gainSanity:	successful pleas with enemies will increase sanity
*********************************************************************/
void Player::gainSanity(int hope) {
	typeText(greenText(std::to_string(hope) + " sanity restored"));
	this->sanity += hope;
	if (this->sanity > 100) {
		this->sanity = 100;
	}
}


/*********************************************************************
showStats :	show HP, O2, and current primary weapon
*********************************************************************/
void Player::showStats() {
	// HP
	if (HP > 66) {
		typeText(boldText("HP: ") + greenText(std::to_string(HP)), 2);
	} else if (HP <= 66 && HP > 33) {
		typeText(boldText("HP: ") + yellowText(std::to_string(HP)), 2);
	} else {
		typeText(boldText("HP: ") + redText(std::to_string(HP)), 2);
	}
	// sanity
	if (sanity > 66) {
		typeText(boldText("sanity: ") + greenText(std::to_string(sanity)), 2);
	} else if (sanity <= 66 && sanity > 33) {
		typeText(boldText("sanity: ") + yellowText(std::to_string(sanity)), 2);
	} else {
		typeText(boldText("sanity: ") + redText(std::to_string(sanity)), 2);
	}
	// o2
	if (O2 > 66) {
		typeText(boldText("O2: ") + greenText(std::to_string(O2)), 2);
	} else if (O2 <= 66 && O2 > 33) {
		typeText(boldText("O2: ") + yellowText(std::to_string(O2)), 2);
	} else {
		typeText(boldText("O2: ") + redText(std::to_string(O2)), 2);
	}
	typeText("Equipped: " + equippedWeapon->getName() + " (" + std::to_string(equippedWeapon->getAttackStat()) + ")", 2);
}


/*********************************************************************
showItems :	show items in inventory
*********************************************************************/
void Player::showItems() {
	if (inventory.size()) {
		typeText(boldText("= = = = = = = Inventory = = = = = = ="));
		for (int i=0; i<(int)inventory.size(); ++i) {
			if (inventory[i] != nullptr) {
				typeText(cyanText("Inventory Slot: " + std::to_string(i+1)), 0);
				typeText(cyanText("Name: ") + boldText(inventory[i]->getName()), 0);
				typeText(cyanText("Description: " + inventory[i]->getDescription()), 0);
				typeText(cyanText("Attack: ") + boldText(std::to_string(inventory[i]->getAttackStat())), 0);
				typeText(boldText("= = = = = = = = = = = = = = = = = = ="), 0);
			}
		}
		// typeText(boldText("= = = = = = = = = = = = = = = = = "));
	} else {
		typeText(magentaText("inventory is empty"));
	}
}


/*********************************************************************
addItem :	push item to inventory vector
*********************************************************************/
bool Player::addItem(Item *i) {
	if (inventory.size() < INVENTORY_SIZE) {
		typeText(playerText("you added the " + greenText(i->getName()) + " to your inventory"));
		inventory.push_back(i);
		return true;
	} else {
		typeText(playerText(redText("your inventory is full")));
		showItems();
		int discard = simpleYesNo("would you like to discard an item?");
		if (discard) {
			int inventoryChoice = promptUserInt("choose item to discard:", 1, (int)inventory.size()) - 1;
			if (inventory[inventoryChoice] != nullptr) {
				removeItem(inventory[inventoryChoice]->getName());
				typeText(playerText("you added the " + greenText(i->getName()) + " to your inventory"));
				inventory.push_back(i);
				return true;
			}
		}
		return false;
	}
}


/*********************************************************************
removeItem :	remove item that takes in index
*********************************************************************/
void Player::removeItemViaIndex(int index) {
	// remove item
	delete inventory[index];
	inventory[index] = nullptr;

	// erase from vector
	inventory.erase(inventory.begin() + index);

	// put fists in if equipped weapon was removed
	if (equippedWeapon == nullptr) {
		equippedWeapon = new Item("fists", "simple fisticuffs", 5);
	}
}


/*********************************************************************
removeItem :	remove item from inventory via item name
*********************************************************************/
void Player::removeItem(std::string itemName) {
	int index;
	bool found = false;
	for (int i=0; i<(int)inventory.size(); ++i) {
		if (inventory[i]->getName() == itemName && !found) {
			typeText(playerText("removing " + redText(itemName) + " from inventory"));
			index = i;
			found = true;
		}
	}

	// get object
	// Item *tmp = inventory[index];

	// cleanup
	// delete tmp;
	// tmp = nullptr;
	delete inventory[index];
	inventory[index] = nullptr;

	// erase from vector
	inventory.erase(inventory.begin() + index);

	// put fists in if equipped weapon was removed
	if (equippedWeapon->getName() == itemName) {
		equippedWeapon = nullptr;
		equippedWeapon = new Item("fists", "simple fisticuffs", 5);
	}
}


/*********************************************************************
viewMap :	open file and print map highlighting current space
*********************************************************************/
void Player::viewMap(std::string currentRoom) {
	if (inspectInventory("map")) {
		std::ifstream ifs;
		std::string mapLine;

		ifs.open("media/map.txt");
		while (std::getline(ifs, mapLine)) {
			// replace text with green text for current room
			size_t startPos = mapLine.find(currentRoom);
			if (startPos != std::string::npos) {
				mapLine.replace(startPos, currentRoom.length(), greenText(currentRoom));
			}
			cout << mapLine << endl;
		}
		ifs.close();
	} else {
		playerText(redText("you don't have a map"));
	}
}


/*********************************************************************
inspectInventory :	return bool if item in inventory
*********************************************************************/
bool Player::inspectInventory(std::string check) {
	for (int i=0; i<(int)inventory.size(); ++i) {
		if (inventory[i] != nullptr) {
			if (inventory[i]->getName() == check) {
				return true;
			}
		}
	}
	return false;
}

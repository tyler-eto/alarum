/********************************************************************* 
** Program name: player.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file derived player class. Has inventory to hold
items. has slot for primary weapon. has HP and O2 stats. has selectWeapon
function to choose primary weapon. has see stats function to view HP 
and O2. 
*********************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include "crewMember.hpp"


int const INVENTORY_SIZE = 10;

class Player : public CrewMember
{
protected:
	int O2;
	int sanity;
	std::vector<Item*> inventory;
public:
	Player();
	~Player();

	int attack();
	void selectEquippedWeapon();
	void useO2();
	void setO2(int oxygen);
	void takeDamage(int damage);
	int getSanity();
	void loseSanity(int horrors);
	void gainSanity(int hope);
	int getO2();
	std::string playerText(std::string text);
	
	void showStats();
	void showItems();
	bool addItem(Item *i);
	void removeItemViaIndex(int index);
	void removeItem(std::string itemName);

	bool inspectInventory(std::string check);
	void viewMap(std::string currentRoom);
};

#endif  // PLAYER_HPP


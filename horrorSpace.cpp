/********************************************************************* 
** Program name: horrorSpace.cpp
** Author: Tyler Eto
** Date: 6/7/18
** Description: implementation file for HorrorSpace class
*********************************************************************/

#include "horrorSpace.hpp"
#include "helpers.hpp"
#include "abomination.hpp"
#include <cstdlib>
#include <iomanip>

using std::cout;
using std::endl;


// constructor
HorrorSpace::HorrorSpace() {
	type = "horror";

	if (generateInt(1, 100) > 75) {
		enemy = new Abomination();
		enemyDefeated = false;
	} else {
		enemy = nullptr;
		enemyDefeated = true;
	}
}

// destructor
HorrorSpace::~HorrorSpace() {
	// cleanup monster
	if (enemy != nullptr) {
		delete enemy;
		enemy = nullptr;
	}

	// cleanup itemContainer
	for (int i=0; i<(int)itemContainer.size(); ++i) {
		if (itemContainer[i] != nullptr) {
			delete itemContainer[i];
			itemContainer[i] = nullptr;
		}
	}
}


/*********************************************************************
runScenario :	lose sanity as the horrors of the room confound you. 
also chance of an abomination being in the room
*********************************************************************/
void HorrorSpace::runScenario(Player *p) {
	std::string phrases[5] = {
		"ph'nglui", "mglw'nafh", "R'lyeh", "wgah-nagl", "fhtagn"
	};
	int choice = generateInt(0, 5);
	typeText(storyText("you step into the room. pulsating walls and tendriled masses of flesh and metal. \nyou struggle to comprehend what you see. a strange word echoes in your head ~" + phrases[choice] + "~"));
	// p->loseSanity(5); original
	p->loseSanity(10);
	if (enemyDefeated == false) {
		confront(p, enemy);
		if (enemy->getHP() <= 0) {
			delete enemy;
			enemy = nullptr;
			typeText(storyText(boldText("you defeated the abomination. however, it might've taken something from you, that you can never physically get back")));
			enemyDefeated = true;
		}
	}

}


/*********************************************************************
confront :	launches once player enters InfestedSpace. will prompt to 
			plead or fight, if plead fails, deal damage, and loop 
			around. if fight, will battle with enemy
*********************************************************************/
void HorrorSpace::confront(Player *p, Abomination *a) {
	std::string confrontOptions[2] = {
		"fight",
		"flee"
	};

	typeText(storyText(magentaText("unspeakable terror in physical form, the abomination approaches!")));
	// while loop to fight or plead
	bool fled = false;
	while (p->getSanity() > 0 && a->getHP() > 0 && !fled) {
		cout << boldText("= = = = = = = = = = = = = ") << endl;
		cout << greenText("player") << endl;
		p->showStats();
		cout << endl;
		cout << magentaText("abomination") << endl;
		a->showStats();
		int confrontChoice = selectOptions(confrontOptions, 2, "what will you do?");
		switch (confrontChoice) {
			case 1:
				fight(p, a);
				break;
			case 2:
				fled = flee();
				break;
		}
	}
}



/*********************************************************************
fight :	loop goes 1) player asked if want to switch weapon and attacks,
		2) enemy attacks damaging between 1-10
*********************************************************************/
void HorrorSpace::fight(Player *p, Abomination *a) {
	// ask if want to switch weapons
	p->selectEquippedWeapon();

	// have player attack
	int damage = p->attack();
	a->takeDamage(damage);
	typeText("you did " + greenText(std::to_string(damage)) + " damage to the abomination");

	// have enemy attack
	if (a->getHP() > 0) {
		p->loseSanity(a->attack());
	}
}


/*********************************************************************
flee :	just prints a message and returns true
*********************************************************************/
bool HorrorSpace::flee() {
	typeText(boldText("its too much to handle, you can't defeat it right now in this state of mind"
		"\nyou flee for now."));
	return true;
}

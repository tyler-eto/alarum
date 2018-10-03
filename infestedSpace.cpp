/********************************************************************* 
** Program name: infestedSpace.cpp
** Author: Tyler Eto
** Date: 6/7/18
** Description: implementation file for InfestedSpace class
*********************************************************************/

#include "infestedSpace.hpp"
#include "helpers.hpp"
#include <cstdlib>
#include <iomanip>

using std::cout;
using std::endl;


// constructor
InfestedSpace::InfestedSpace() {
	enemiesDefeated = false;
	type = "infested";

	populateEnemies();
}

// destructor
InfestedSpace::~InfestedSpace() {
	// cleanup enemyQueue
	while (!enemyQueue.empty()) {
		Infected *tmp = enemyQueue.front();
		delete tmp;
		tmp = nullptr;
		enemyQueue.pop();
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
pushInfested :	add Infested object to enemy queue
*********************************************************************/
void InfestedSpace::populateEnemies() {
	int numEnemies = generateInt(1, 3);
	Infected *e;

	for (int i=0; i<numEnemies; ++i) {
		e = new Infected();
		pushInfested(e);
		e = nullptr;
	}
	// cout << numEnemies << " enemies created" << endl;
}

/*********************************************************************
pushInfested :	add Infested object to enemy queue
*********************************************************************/
void InfestedSpace::pushInfested(Infected *in) {
	enemyQueue.push(in);
}


/*********************************************************************
runScenario :	if enemies not defeated, it will run matches between
				infected and player until someone wins
*********************************************************************/
void InfestedSpace::runScenario(Player *p) {
	if (enemiesDefeated == false) {
		while (enemyQueue.size()) {
			Infected *tmp = enemyQueue.front();
			confront(p, tmp);
			if (tmp->getHP() <= 0) {
				enemyQueue.pop();
				delete tmp;
				tmp = nullptr;
				typeText(storyText(boldText("you defeated the \"infected\" crewmember. the face doesn't look familiar..anymore")));
			}
			if (p->getHP() <= 0) {
				break;
			}
		}
		enemiesDefeated = true;
	} else {
		typeText("despite their grotesque appearances, the crewmembers look at peace now");
	}
}


/*********************************************************************
confront :	launches once player enters InfestedSpace. will prompt to 
			plead or fight, if plead fails, deal damage, and loop 
			around. if fight, will battle with enemy
*********************************************************************/
void InfestedSpace::confront(Player *p, Infected *in) {
	std::string confrontOptions[2] = {
		"plead",
		"fight"
	};

	typeText(storyText(magentaText("an \"infected\" crewmember is attacking!")));
	// while loop to fight or plead
	while (in->getHP() > 0 && p->getHP() > 0) {
		cout << boldText("= = = = = = = = = = = = = ") << endl;
		cout << greenText("player") << endl;
		p->showStats();
		cout << endl;
		cout << magentaText("infected") << endl;
		in->showStats();
		int confrontChoice = selectOptions(confrontOptions, 2, "what will you do?");
		switch (confrontChoice) {
			case 1:
				plead(p, in);
				break;
			case 2:
				fight(p, in);
				break;
		}
	}
}


/*********************************************************************
plead :	will roll for success of plead. plead % is increased based on
		number of runes in inventory. starts at 10% chance. if fails,
		will do damage to player between 1-5 and lose 5 sanity
*********************************************************************/
void InfestedSpace::plead(Player *p, Infected *in) {
	int pleadSuccess = 10;

	// check for runes and add 30% for each one
	pleadSuccess += (p->inspectInventory("red_rune") + p->inspectInventory("blue_rune") + p->inspectInventory("black_rune")) * 30;
	
	// get int between 1 - 100, if greater than pleadMultipler, do damage between 1-5
	if (generateInt(1, 100) > pleadSuccess) {
		typeText(storyText("your pleas fell on deaf ears. dread wraps around you as the infected attacks!"));
		p->takeDamage(in->attack());
		p->loseSanity(5);
	} else {
		in->takeDamage(1000);
		typeText(storyText("as if remembering its humanity, the infected stayed its hand and walked away."));
		p->gainSanity(10);
	}
}



/*********************************************************************
fight :	loop goes 1) player asked if want to switch weapon and attacks,
		2) enemy attacks damaging between 1-5
		fight goes until someone wins
*********************************************************************/
void InfestedSpace::fight(Player *p, Infected *in) {
	// ask if want to switch weapons
	p->selectEquippedWeapon();

	// have player attack, have enemy attack
	int damage = p->attack();
	in->takeDamage(damage);
	typeText("you did " + greenText(std::to_string(damage)) + " damage to the 'infected' crewmember");

	if (in->getHP() > 0) {
		typeText("the crew member hits back");
		p->takeDamage(in->attack());
	}
}

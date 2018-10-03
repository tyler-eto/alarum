/********************************************************************* 
** Author: Tyler Eto
** Compile: 
g++ -std=c++11 -Wall helpers.cpp item.cpp crewMember.cpp player.cpp infected.cpp baseSpace.cpp blackHoleSpace.cpp driftSpace.cpp emptySpace.cpp fireSpace.cpp infestedSpace.cpp testSpaces.cpp -o builds/testSpaces
*********************************************************************/

#include "player.hpp"
#include "infected.hpp"
#include "blackHoleSpace.hpp"
#include "driftSpace.hpp"
#include "emptySpace.hpp"
#include "fireSpace.hpp"
#include "infestedSpace.hpp"
#include "item.hpp"

#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;


int main() {
	// make player
	Player player = Player();

	cout << "Printing stats:" << endl;
	player.showStats();
	cout << endl;

	// encounter empty space
	EmptySpace *es = new EmptySpace();
	assert(es->getType() == "empty" && "EmptySpace instantiation failed");
	es->runScenario(&player);
	assert(player.getHP() == 100 && "EmptySpace scenario failed");

	// encounter fire space
	FireSpace *fs = new FireSpace();
	assert(fs->isOnFire() == true && "FireSpace instantiation failed");
	assert(fs->getType() == "fire" && "FireSpace instantiation failed");
	fs->runScenario(&player);
	assert(player.getHP() == 85 && "fire damage failed");
	// make extinguisher item
	Item *extinguisher = new Item("extinguisher", "I could put out fires with this", 10);
	player.addItem(extinguisher);
	// run scenario with extinguisher in inventory
	fs->runScenario(&player);
	assert(fs->isOnFire() == false && "fire failed with extinguisher");
	assert(player.getHP() == 85 && "extinguisher failed");

	// encounter drift space
	DriftSpace *ds = new DriftSpace();
	assert(ds->getType() == "drift" && "DriftSpace instantiation failed");
	ds->runScenario(&player);
	assert(player.getO2() == 80 && "DriftSpace runScenario failed");

	// encounter black hole
	BlackHoleSpace *bh = new BlackHoleSpace();
	bh->runScenario(&player);
	assert(player.getHP() == -15 && "BlackHole runScenario failed");
	// add rune items to inventory and re-run scenario
	Item *red = new Item("redRune", "glow red");
	Item *blue = new Item("blueRune", "glow blue");
	Item *black = new Item("blackRune", "glow black");
	player.addItem(red);
	player.addItem(blue);
	player.addItem(black);
	// re-run scenario
	bh->runScenario(&player);
	assert(player.getHP() == -15 && "BlackHole runScenario failed with runes");

	// killed player, make another
	Player player2 = Player();

	// encounter infested space
	InfestedSpace *is = new InfestedSpace();
	// make enemies
	Infected *e1 = new Infected();
	is->pushInfested(e1);
	Infected *e2 = new Infected();
	is->pushInfested(e2);
	// run scenario
	Item *exosuit = new Item("exosuit", "typically used for ship repair", 30);
	player2.addItem(exosuit);
	is->runScenario(&player2);

	delete es;
	delete fs;
	delete ds;
	delete bh;
	delete is;
	es = nullptr;
	fs = nullptr;
	ds = nullptr;
	bh = nullptr;
	is = nullptr;

	return 0;
}
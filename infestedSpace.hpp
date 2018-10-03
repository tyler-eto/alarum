/********************************************************************* 
** Program name: infestedSpace.hpp
** Author: Tyler Eto
** Date: 6/8/18
** Description: design file derived infested class. These squares will
have infested crewmembers that you have to interact with. Player can
fight or plead with infested. Plead has a 10% chance of being an instant
win as the attacker remembers its humanity.  After enemies "cleared",
space becomes like BaseSquare
*********************************************************************/

#ifndef INFESTED_HPP
#define INFESTED_HPP

#include <string>
#include <queue>
#include <iostream>
#include "item.hpp"
#include "infected.hpp"
#include "baseSpace.hpp"


class InfestedSpace : public BaseSpace
{
protected:
    std::queue<Infected*> enemyQueue;
    bool enemiesDefeated;
public:
    InfestedSpace();
    ~InfestedSpace();

    void populateEnemies();
    void pushInfested(Infected *in);

    void runScenario(Player *p);
    void confront(Player *p, Infected *in);
    void plead(Player *p, Infected *in);
    void fight(Player *p, Infected *in);
};

#endif  // INFESTED_HPP
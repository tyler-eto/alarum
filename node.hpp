/********************************************************************* 
** Program name: node.hpp
** Author: Tyler Eto
** Date: 6/12/18
** Description: design file for node struct which will be used in the
board
*********************************************************************/

#ifndef NODE_HPP
#define NODE_HPP

#include "baseSpace.hpp"
#include "helpers.hpp"


struct Node
{
    std::string name;
    std::string printedName;
    BaseSpace *space;
    struct Node *up;
    struct Node *right;
    struct Node *down;
    struct Node *left;

    // messing around
    std::string describe;
    std::string searchSpots[4];
    std::string searchYText[3];
    std::string searchNText[3];

    // test with BoardSetup via rooms map in testNode.cpp
    void investigate(Player *p) {
        // describe room
        typeText(storyTextH(describe));
        int spot;
        do {
            // choose what to investigate
            spot = selectOptions(searchSpots, 4, "what will you search?");
            // decrement spot for indexing
            --spot;

            if (spot != 3) {
                if (space->getItemNameByIndex(spot) != "") {
                    // get item name to replace <placeholder>
                    std::string itemName = space->getItemNameByIndex(spot);
                    // describe successful search
                    typeText(replaceText(searchYText[spot], "<placeholder>", itemName));
                    int pickup = simpleYesNo("do you want to take it?");
                    if (pickup) {
                        Item *tmp = space->selectItem(spot);
                        if (!p->addItem(tmp)) {
                            // item not added need to put it back
                            space->pushItemWithIndex(tmp, spot);
                        }
                    } else {
                        typeText(storyTextH("you put it down"));
                    }
                } else {
                    // describe failed search
                    typeText(storyTextH(searchNText[spot]));
                }
            }
        }
        while (spot != 3);  // go back
    }
};

#endif  // NODE_HPP
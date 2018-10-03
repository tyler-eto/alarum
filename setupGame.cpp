/********************************************************************* 
** Program name: setupGame.cpp
** Author: Tyler Eto
** Date: 6/12/18
** Description: implementation file for game functions

shuffle vector taken from -- http://www.cplusplus.com/reference/algorithm/random_shuffle/
*********************************************************************/

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <map>

#include "setupGame.hpp"
#include "baseSpace.hpp"
#include "infestedSpace.hpp"
#include "fireSpace.hpp"
#include "blackHoleSpace.hpp"
#include "driftSpace.hpp"
#include "emptySpace.hpp"
#include "horrorSpace.hpp"
#include "helpers.hpp"

using std::cout;
using std::endl;


/*********************************************************************
createBoard :	create the game board
*********************************************************************/
Node*** createBoard() {
	// create Node board
	Node ***board = new Node**[SIZE];
	// populate Node board
	for(int i = 0; i < SIZE; i++) {
    	board[i] = new Node*[SIZE];
	}
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			board[i][j] = nullptr; 
		}
	}
	return board;
}

int myrandom (int i) { return std::rand()%i;}


/*********************************************************************
boardSetup:	uses setupBoard.txt to create Spaces then links them
			together.  If I could figure out how to print the map,
			I could shuffle the text file to make the board setup random
*********************************************************************/
void boardSetup(Node ***board, bool r) {
	// set seed
	srand(time(NULL));

	std::ifstream ifs;
	// int row;
	// int col;
	std::string name;
	std::string pName;
	std::string spaceType;

	std::vector<std::string> v;
	std::string line;
	std::string rSpaces[5] = {"empty", "infested", "fire", "empty", "horror"};
	int rSpaceInt;

	ifs.open("setupBoard.txt");
	// put it in a vector
	while (std::getline(ifs, line)) {
		// std::getline(ifs, line);
		v.push_back(line);
		// cout << "line: " << line << endl;
	}
	ifs.close();

	if (r) {
		// shuffle the vector
		//auto rng = std::default_random_engine {};
		//std::shuffle(v.begin(), v.end(), rng);
		std::random_shuffle(v.begin(), v.end(), myrandom);
	}


	// create board dynamically and randomly
	for (int i=0; i<SIZE; ++i) {
		for (int j=0; j<SIZE; ++j) {
			// ifs >> row >> col >> name >> spaceType >> pName
			// ifs >> name >> spaceType >> pName;
			line = v.front();

			std::stringstream(line) >> name >> spaceType >> pName;
			// line >> name >> spaceType >> pName;
			struct Node *n = new Node();
			n->name = name;
			n->printedName = pName;
			// cout << "got this: " << row << " " << col << " " << name << " " << pName << endl;
			// cout << "got this: " << name << " " << spaceType << " " << pName << endl;

			if (r) {
				// randomize placement of infected, fire, and empty spacesTypes
				if (spaceType != "blackHole" && spaceType != "drift" && name != "Bridge") {
					rSpaceInt = generateInt(0, 5);
					spaceType = rSpaces[rSpaceInt];
					// cout << name << " space made into " << spaceType << endl;
				}
			}

			if (spaceType == "infested") {
				n->space = new InfestedSpace();
			} else if (spaceType == "blackHole") {
				n->space = new BlackHoleSpace();
			} else if (spaceType == "drift") {
				n->space = new DriftSpace();
			} else if (spaceType == "fire") {
				n->space = new FireSpace();
			} else if (spaceType == "empty") {
				n->space = new EmptySpace();
			} else if (spaceType == "horror") {
				n->space = new HorrorSpace();
			}

			n->up = nullptr;
			n->right = nullptr;
			n->down = nullptr;
			n->left = nullptr;
			// board[row][col] = n;
			board[i][j] = n;
			n = nullptr;

			v.erase(v.begin());
		}
	}

	// cout << "finished reading file" << endl;

	int rowNum = SIZE;
	int colNum = SIZE;
	// link everything together
	for (int i=0; i<rowNum; ++i) {
		for (int j=0; j<colNum; ++j) {
			// cout << "in the nested loop: " << i << " " << j << endl;
			if (i > 0) {
				board[i][j]->up = board[i-1][j];
			}
			if (i < rowNum-1) {
				board[i][j]->down = board[i+1][j];
			}
			if (j > 0) {
				board[i][j]->left = board[i][j-1];
			}
			if (j < colNum-1) {
				board[i][j]->right = board[i][j+1];
			}
		}
	}
}


/*********************************************************************
roomSetup:	populate node board with dialogue
*********************************************************************/
void roomSetup(Node ***board) {
	// instantiate mapping
	std::map<std::string, std::map<std::string, std::string>> dialogue;
	std::map<std::string, std::string> data;

	std::ifstream ifs;
	ifs.open("setupRooms.txt");

	std::string line;
	std::string header;

	while (!ifs.eof()) {
		for (int i=0; i<11; ++i) {
			std::getline(ifs, line);
			// cout << "line: " << line << endl;
			
			switch (i) {
				case 0:  // name
					header = line;
					break;
				case 1:  // description
					data["description"] = line;
					break;
				case 2:  // slot 1
					data["slot1"] = line;
					break;
				case 3:  // slot 2
					data["slot2"] = line;
					break;
				case 4:  // slot 3
					data["slot3"] = line;
					break;
				case 5:  // slot 1 Y
					data["slot1Y"] = line;
					break;
				case 6:  // slot 2 Y
					data["slot2Y"] = line;
					break;
				case 7:  // slot 3 Y
					data["slot3Y"] = line;
					break;
				case 8:  // slot 1 N
					data["slot1N"] = line;
					break;
				case 9:  // slot 2 N
					data["slot2N"] = line;
					break;
				case 10: // slot 3 N
					data["slot3N"] = line;
					break;
			}
		}
		dialogue[header] = data;
	}
	ifs.close();


	for (int i=0; i<SIZE; ++i) {
		for (int j=0; j<SIZE; ++j) {
			data = dialogue[board[i][j]->name];
			// populate dialogue in node
			board[i][j]->describe = data["description"];
			board[i][j]->searchSpots[0] = data["slot1"];
			board[i][j]->searchSpots[1] = data["slot2"];
			board[i][j]->searchSpots[2] = data["slot3"];
			board[i][j]->searchSpots[3] = "return";
			board[i][j]->searchYText[0] = data["slot1Y"];
			board[i][j]->searchYText[1] = data["slot2Y"];
			board[i][j]->searchYText[2] = data["slot3Y"];
			board[i][j]->searchNText[0] = data["slot1N"];
			board[i][j]->searchNText[1] = data["slot2N"];
			board[i][j]->searchNText[2] = data["slot3N"];
		}
	}
}


/*********************************************************************
populateItems:	add items to the board either randomly or as designed
*********************************************************************/
void populateItems(Node ***board, bool r) {
	// set seed
	srand(time(NULL));

	// vector
	std::vector<std::string> v;

	std::string line;
	std::ifstream ifs;
	ifs.open("setupItems.txt");
	// put it in a vector
	while (std::getline(ifs, line)) {
		v.push_back(line);
	}
	ifs.close();

	// shuffle if random
	if (r) {
		std::random_shuffle(v.begin(), v.end(), myrandom);
	}

	int row, col, stat;
	std::string itemName;
	std::string itemDescription;
	Item *tmp;
	for (int i=0; i<(int)v.size(); ++i) {
		line = v[i];
		// cout << "line: " << line << endl;

		std::stringstream(line) >> row >> col >> stat >> itemName >> itemDescription;
		// cout << "got this: " << row << " " << col << " " << itemName << " " << itemDescription << " " << stat << endl;

		// replace underscore with space
		std::replace(itemDescription.begin(), itemDescription.end(), '_', ' ');

		tmp = new Item(itemName, itemDescription, stat);

		bool pushed = false;
		while (!pushed) {
			if (r) {
				row = generateInt(0, SIZE);
				col = generateInt(0, SIZE);
			}

			// ensure map and crowbar get placed in Garage
			if (itemName == "map" || itemName == "crowbar") {
				Node *garage = findStartingRoom(board);
				garage->space->pushItem(tmp);
				pushed = true;
			} else if (board[row][col]->space->getType() != "drift" 
				&& board[row][col]->space->getType() != "blackHole" 
				&& board[row][col]->name != "Bridge") {
				if (board[row][col]->space->pushItem(tmp)) {
					// cout << tmp->getName() << " item pushed to space " << row << " " << col << " in " << board[row][col]->name << endl;
					pushed = true;
				}
			}
		}
		tmp = nullptr;
	}
	// tmp = nullptr;
}


/*********************************************************************
findStartingRoom:	starting position is always the Garage
*********************************************************************/
Node* findStartingRoom(Node ***board) {
	for (int i=0; i<SIZE; ++i) {
		for (int j=0; j<SIZE; ++j) {
			if (board[i][j]->name == "Bridge") {
				return board[i][j];
			}
		}
	}
	return nullptr;  // this'll break everything. shouldn't happen
}


/*********************************************************************
viewMap: prints the map
*********************************************************************/
void viewMap(Node ***board, std::string currentRoom) {
	// print board
	std::string mapLine;
	for (int i=0; i<SIZE; ++i) {
		cout << "+------------+------------+------------+------------+------------+" << endl;
		for (int x=0; x<4; ++x) {
			cout << "|";
			for (int j=0; j<SIZE; ++j) {
				mapLine = board[i][j]->printedName;
				size_t startPos = mapLine.find(currentRoom);
				if (startPos != std::string::npos) {
					mapLine.replace(startPos, currentRoom.length(), greenText(currentRoom));
				}
				cout << mapLine << "|";
			}
			cout << endl;
		}
	}
	cout << "+------------+------------+------------+------------+------------+" << endl;
}


/*********************************************************************
deleteBoard:	cleanup board
*********************************************************************/
void deleteBoard(Node ***board) {
	for (int i=0; i<SIZE; ++i) {
		for (int j=0; j<SIZE; ++j) {
			delete board[i][j]->space;
			board[i][j]->space = nullptr;
			board[i][j]->up = nullptr;
			board[i][j]->down = nullptr;
			board[i][j]->left = nullptr;
			board[i][j]->right = nullptr;
			delete board[i][j];
			board[i][j] = nullptr;
		}
		delete [] board[i];
	}
	delete [] board;
}


/*********************************************************************
play:	runs the game loop
*********************************************************************/
void play() {
	// prompt for tailored setup or random setup
	std::string setupOptions[2] = {"tailored (as designed)", "random (rogue-like)"};
	int setupChoice;
	setupChoice = selectOptions(setupOptions, 2, "choose game setup:");
	bool rogue = false;
	if (setupChoice == 2) { rogue = true; }
	
	// create board
	Node ***board = createBoard();
	// setup board
	boardSetup(board, rogue);
	// populate board with items
	populateItems(board, rogue);
	// push dialogue
	roomSetup(board);

	// get starting position = Garage
	Node *currentNode = findStartingRoom(board);

	// create player
	Player player = Player();

	// intro
	typeText("you wake up on the bridge to screams and the smell of smoke. last thing you remember..."
		"\npure darkness, a pulling sensation, then a crash. you look out the window.");
	typeText("...", 10);
	typeText("the ship is destroyed! pieces of the once-beautiful ship, SONUM, strewn about space. "
		"pulling your wits about you, you...");

	bool hasWon = false;
	bool hasLost = false;
	bool firstRoom = true;
	std::string loseText;
	std::string winText;
	std::string navigationOptions[8] = {
		"move up", "move right", "move down", "move left",
		"investigate room",
		"view stats", "view inventory", "view map"
	};
	int navigationChoice;
	while (!hasWon && !hasLost) {
		// run scenario
		if (!firstRoom) {
			currentNode->space->runScenario(&player);
		}

		// if survive, present navigation options (directions, investigate, view stats, view inventory, view map)
		if (currentNode->name == "Black_Hole") {
			// if all runes skip this and go to win condition
			if (!(player.inspectInventory("red_rune") && player.inspectInventory("blue_rune") && player.inspectInventory("black_rune"))) {
				typeText("you drift towards the black hole. whatever awaits you can't be worse than the dangers and horrors that wait for you back on the ship"
					"\nas everything goes black, you feel a pulling sensation, as if something has grabbed you."
					"\nyou struggle to adjust your eyes to the darkness. a shadowy figure of monstrous size begins to come into focus.");
				hasLost = true;
			}
		} else if (player.getHP() <= 0) {
			// lose condition
			typeText(currentNode->space->storyText("falling to your knees, you throw your helmet off, dashing it on the floor. "
				"you take solace in the fact that your fate won't be like that of your fellow crew members, "
				"but peace of mind is a lot like letting go."));
			hasLost = true;
		} else if (player.getO2() <= 0) {
			// lose condition
			typeText(currentNode->space->storyText("short of breath, that pulling sensation returns. you've seen too much to panic."));
			typeText(currentNode->space->storyText("breath in..."), 10);
			typeText(currentNode->space->storyText("pity"), 2);

			hasLost = true;
		} else if (player.getSanity() <= 0) {
			// lose condition
			typeText(currentNode->space->storyText("the horrors you've endured have grown too great. you lost your mind. you will wander the ship with"));
			typeText(currentNode->space->storyText("the r3st"), 10);
			typeText(currentNode->space->storyText("0hf' th'egm"), 15);
			hasLost = true;
		} else {
			do {
				// to account for drift spaces, you just retain choice from previous loop to continue to next space
				if (currentNode->space->getType() != "drift") {
					navigationChoice = selectOptions(navigationOptions, 8, "action:");
				}

				switch (navigationChoice) {  // will kill player if they go beyond play board
					case 1:  // up
						if (currentNode->up == nullptr) {
							typeText(currentNode->space->storyText("you're drifting too far! as your oxygen runs out, the wreckage of SONUM and your chance to save the crew disappears"));
							hasLost = true;
						} else {
							currentNode = currentNode->up;
						}
						break;
					case 2:  // right
						if (currentNode->right == nullptr) {
							typeText(currentNode->space->storyText("you're drifting too far! as your oxygen runs out, the wreckage of SONUM and your chance to save the crew disappears"));
							hasLost = true;
						} else {
							currentNode = currentNode->right;
						}
						break;
					case 3:  // down
						if (currentNode->down == nullptr) {
							typeText(currentNode->space->storyText("you're drifting too far! as your oxygen runs out, the wreckage of SONUM and your chance to save the crew disappears"));
							hasLost = true;
						} else {
							currentNode = currentNode->down;
						}
						break;
					case 4:  // left
						if (currentNode->left == nullptr) {
							typeText(currentNode->space->storyText("you're drifting too far! as your oxygen runs out, the wreckage of SONUM and your chance to save the crew disappears"));
							hasLost = true;
						} else {
							currentNode = currentNode->left;
						}
						break;
					case 5:  // investigate
						currentNode->investigate(&player);
						break;
					case 6:  // view stats
						player.showStats();
						break;
					case 7:  // view inventory
						player.showItems();
						break;
					case 8:  // view map
						if (player.inspectInventory("map")) {
							viewMap(board, currentNode->name);
						} else {
							typeText(player.playerText("you don't have a map"));
						}
						break;
					default:
						break;
				}
			}
			while (navigationChoice > 4);  // if not directional choice, run loop again

			// starting text and title screen
			if (firstRoom && !hasWon && !hasLost && currentNode->name != "Black_Hole") {
				firstRoom = false;
				typeText("looking as if hell was unleashed, the ship, once utopic, lively, and pristine, lay in waste.\n"
					"shattered, a hull of bodies, metal, and waste. you embark on a terrible journey.\n"
					"goal: find the captain's keycard, reach the escape pods in the garage, survive..\n");
				// use Lacey's text after the player finishes the first room, then print the title
				typeText(
"############################################################################\n"
"############################################################################\n"
"######     ###  ##############     ###       ####  ####  ###          ######\n"
"#####  ##  ###  #############  ##  ###  ###  ####  ####  ###  ###  ##  #####\n"
"####  ###  ###  ############  ###  ###  ###  ####  ####  ###  ###  ###  ####\n"
"###        ###  ###########        ###      #####  ####  ###  ###  ####  ###\n"
"##  #####  ###  ##########  #####  ###  ###  ####  ####  ###  ###  #####  ##\n"
"#  ######  ###        ###  ######  ###  ####  ###        ###  ###  ######  #\n"
"############################################################################\n"
"############################################################################\n", 1);
			}

			// check win conditions
			// is character in blackhole space with 3 runes
			if (currentNode->name == "Black_Hole" &&
				player.inspectInventory("red_rune") && player.inspectInventory("blue_rune") && player.inspectInventory("black_rune")) {
				hasWon = true;
				winText = 
"based purely on what you read in the war room, you push off into the black hole.\n"
"at peace with this destiny, you think about the ship and all those you lost. you wish things could've gone differently.\n"
"but just as the darkness engulfs you, the glow from the 3 runes intensifies.\n"
"you wake up on the bridge...";
			}
			// is character in the captains quarter with the key card
			if (currentNode->name == "Garage" && player.inspectInventory("captain_key_card")) {
				hasWon = true;
				winText = 
"with a swipe of the captain's key card, you made it to the escape pod.\n"
"it's been horrifying but you're finally headed home.\n"
"as the whirr of the hyperdrive increases, you look back at the wreckage.\n"
"the survivor's guilt will stay with you, but you're alive...";
			}
		}
	}

	// if win, print text and exit
	if (hasWon) {
		typeText(greenText(winText));
		cout << cyanText(" * * * * * * * * * * * * * * * * * * * * * * ") << endl;
		cout << cyanText(" * * * * * * * congratulations! * * * * * * * ") << endl;
		cout << cyanText(" * * * * * * * * * * * * * * * * * * * * * * ") << endl;
		cout << endl;
		typeText(boldText("thanks for playing."));
	} else if (hasLost) {
		typeText(redText(boldText("YOU LOSE")));
	}

	// cleanup
	deleteBoard(board);
}
/********************************************************************* 
** Author: Tyler Eto
** Compile:
g++ -std=c++11 -Wall testNode.cpp -o builds/testNode
*********************************************************************/

#include "assert.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

using std::cout;
using std::endl;


int main() {
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

	cout << dialogue["Lab"]["description"] << endl;

	return 0;
}
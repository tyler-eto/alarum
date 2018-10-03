/********************************************************************* 
** Program name: helpers.cpp
** Author: Tyler Eto
** Date: 4/27/18
** Description: implementation file for helpers
*********************************************************************/

#include "helpers.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>


/********************************************************************* 
** Description: takes reference to int and returns bool if user input
is int. used as helper for selectOptions and promptUserInt
*********************************************************************/
bool validateInt(int *num) {
    std::string temp;  // accounts for decimal input, converts to int
    std::getline(std::cin, temp);
    std::stringstream s(temp);
    if (s >> *num) {
        *num = std::stoi(temp, nullptr);
        return true;
    }
    return false;
}


/********************************************************************* 
** Description: takes reference to double and returns bool if user input
is double. used as helper for selectOptions and promptUserDouble
*********************************************************************/
bool validateDouble(double *num) {
    std::string temp;
    std::getline(std::cin, temp);
    std::stringstream s(temp);
    if (s >> *num) {
        *num = std::stod(temp, nullptr);
        return true;
    }
    return false;
}

/********************************************************************* 
** Description: takes reference to string and returns bool if user input
is string without invalid characters. used as helper for selectOptions 
and promptUserStr
*********************************************************************/
bool validateStr(std::string *str) {
    // std::cin.clear();
    // std::cin.ignore();
    
    std::string temp;
    std::getline(std::cin, temp);
    if (((int)temp.find_first_of("") != -1)) {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }
    *str = temp;
    return true;
}


/********************************************************************* 
** Description: takes prompt string and can accept min and max values
for prompt. returns user's input when it passes validateInt
*********************************************************************/
int promptUserInt(std::string prompt, int acceptableMin, int acceptableMax) {
    // arbitrarilly set max to 100k and min to -1k for acceptable inputs
    std::cout << prompt << std::endl;
    int response;
    bool isInvalid = true;
    do {
        if (validateInt(&response)) {
            if (response > acceptableMax || response < acceptableMin) {
                std::cout << "    Please enter integer between " << acceptableMin << " and " << acceptableMax << std::endl;
            }
            else {
                isInvalid = false;
            }
        }
        else {
            std::cout << "    Please enter valid integer." << std::endl;
        }
    }
    while (isInvalid);

    std::cin.clear();

    return response;
}


/********************************************************************* 
** Description: takes prompt string and can accept min and max values
for prompt. returns user's input when it passes validateDouble
*********************************************************************/
double promptUserDouble(std::string prompt, double acceptableMin, double acceptableMax) {
    // arbitrarilly set max to 100k and min to -1k for acceptable inputs
    std::cout << prompt << std::endl;
    double response;
    bool isInvalid = true;
    do {
        if (validateDouble(&response)) {
            if (response > acceptableMax || response < acceptableMin) {
                std::cout << "    Please enter double between " << acceptableMin << " and " << acceptableMax << std::endl;
            }
            else {
                isInvalid = false;
            }
        }
        else {
            std::cout << "    Please enter valid double." << std::endl;
        }
    }
    while (isInvalid);

    std::cin.clear();

    return response;
}


/********************************************************************* 
** Description: takes prompt string and just passes back user's input
*********************************************************************/
std::string promptUserStr(std::string prompt) {
    std::cout << prompt << std::endl;
    
    std::string response;
    bool isInvalid = true;
    do {
        if (validateStr(&response)) {
            isInvalid = false;
        }
        else {
            std::cout << "    Please, no integers." << std::endl;
        }
    }
    while (isInvalid);

    std::cin.clear();

    return response;
}


/********************************************************************* 
** Description: takes reference to array containing menu options,
prompts user to select an option from the menu, and returns response if
it passes validateInt
*********************************************************************/
int selectOptions(std::string *optionArr, int arrLength, std::string prompt) {
    std::cout << prompt << std::endl;
    for (int i=0; i<arrLength; i++) {
        std::cout << i+1 << ": " << optionArr[i] << std::endl;
    }
    // loop until valid input
    int response;
    bool isInvalid = true;
    do {
        if (validateInt(&response)) {
            if (response > 0 && response <= arrLength) {
                isInvalid = false;
            }
            else {
                std::cout << "    Please enter a valid option." << std::endl;
            }
        }
        else {
            std::cout << "    Please enter a valid option." << std::endl;
        }
    }
    while (isInvalid);

    return response;
}


/********************************************************************* 
** Description: takes reference to vector containing menu options,
prompts user to select an option from the menu, and returns response if
it passes validateInt
*********************************************************************/
int selectOptions(std::vector<std::string> *optionVector, std::string prompt) {
    std::cout << prompt << std::endl;
    for (int i=0; i<(int)optionVector->size(); i++) {
        std::cout << i+1 << ": " << (*optionVector)[i] << std::endl;
    }
    // loop until valid input
    int response;
    bool isInvalid = true;
    do {
        if (validateInt(&response)) {
            if (response > 0 && response <= (int)optionVector->size()) {
                isInvalid = false;
            }
            else {
                std::cout << "    Please enter a valid option." << std::endl;
            }
        }
        else {
            std::cout << "    Please enter a valid option." << std::endl;
        }
    }
    while (isInvalid);

    return response;
}


/********************************************************************* 
** generateInt: generate a random number between min and max, inclusive on min
*********************************************************************/
int generateInt(int min, int max) {
    return (rand() % max) + min;
}


/********************************************************************* 
** simpleYesNo: its what it is
*********************************************************************/
int simpleYesNo(std::string prompt) {
    std::cout << prompt << std::endl;
    std::cout << "1: yes" << std::endl;
    std::cout << "2: no" << std::endl;
    // loop until valid input
    int response;
    bool isInvalid = true;
    do {
        if (validateInt(&response)) {
            if (response > 0 && response <= 2) {
                isInvalid = false;
            }
            else {
                std::cout << "    Please enter a valid option." << std::endl;
            }
        }
        else {
            std::cout << "    Please enter a valid option." << std::endl;
        }
    }
    while (isInvalid);

    if (response == 1) {
        return 1;  // so can be used in if statements
    }
    return 0;

}


// colored text
std::string redText(std::string text) { return "\033[0;31m" + text + "\033[0m"; }
std::string greenText(std::string text) { return "\033[1;32m" + text + "\033[0m"; }
std::string yellowText(std::string text) { return "\033[1;33m" + text + "\033[0m"; }
std::string cyanText(std::string text) { return "\033[0;36m" + text + "\033[0m"; }
std::string magentaText(std::string text) { return "\033[0;35m" + text + "\033[0m"; }
std::string boldText(std::string text) { return "\033[1;m" + text + "\033[0m"; }  // originally "\033[1;30m"
std::string storyTextH(std::string text) { return text; }

void typeText(std::string text, int ms) {
    ms *= 10000;
    // std::cout << "waiting " << ms << " milliseconds" << std::endl;
    for (std::size_t i=0; i<text.size(); ++i)
    {
        std::cout << text[i] << std::flush;
        
        // sleep milliseconds
        usleep(ms);
    }
    // pause at end of phrase
    usleep(600000);
    std::cout << std::endl;
}

// replace <placeholder>
std::string replaceText(std::string text, std::string replaceText, std::string insertText) {
    size_t startPos = text.find(replaceText);
    if (startPos != std::string::npos) {
        text.replace(startPos, replaceText.length(), greenText(insertText));
    }
    return text;
}

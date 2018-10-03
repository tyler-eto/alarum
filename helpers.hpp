/********************************************************************* 
** Program name: helpers.hpp
** Author: Tyler Eto
** Date: 4/27/18
** Description: design file for helper functions pertaining to menu
*********************************************************************/

#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <vector>


bool validateInt(int *num);

bool validateDouble(double *num);

bool validateStr(std::string *str);

int promptUserInt(std::string prompt, int acceptableMin=1, int acceptableMax=10000);

double promptUserDouble(std::string prompt, double acceptableMin=1.0, double acceptableMax=10000.0);

std::string promptUserStr(std::string prompt);

int selectOptions(std::string *optionArr, int arrLength, std::string prompt="Please select an option from following list:");

int selectOptions(std::vector<std::string> *optionVector, std::string prompt="Please select an option from the following list:");

int generateInt(int min, int max);

int simpleYesNo(std::string prompt);

std::string redText(std::string text);
std::string greenText(std::string text);
std::string yellowText(std::string text);
std::string cyanText(std::string text);
std::string magentaText(std::string text);
std::string boldText(std::string text);
std::string storyTextH(std::string text);
void typeText(std::string text, int ms=5);

std::string replaceText(std::string text, std::string replaceText, std::string insertText);

#endif  // HELPERS_HPP
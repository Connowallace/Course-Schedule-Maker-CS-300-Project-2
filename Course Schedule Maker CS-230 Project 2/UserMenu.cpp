//============================================================================
// Name        : UserMenu.cpp
// Author      : Connor Wallace
// Version     : 1.2
// Description : Template to implement a simple text user menu
//============================================================================

#include <string>
#include <iostream>
#include <iomanip>
#include "UserMenu.h"

UserMenu::UserMenu() {}

// Print the menu
void UserMenu::printMenu() const {
	cout << endl; // Whitespace
	cout << "\t1. Load Data Structure." << endl;
	cout << "\t2. Print Course List." << endl;
	cout << "\t3. Print Course." << endl;
	cout << "\t9. Exit" << endl;
	cout << endl; // Whitespace
	cout << "What would you like to do ? ";
}

// Get and validate user input
int UserMenu::getUserInput() const {
	
	const int LOWEST_USER_CHOICE = 1;
	const int HIGHEST_USER_CHOICE = 9;
	string userInput;
	int inputToInt;


	// While loop breaks on return only 
	// Catches in the while loop to be able to use continue
	while (true) {
		try {
			// Get and convert input
			cin >> userInput;
			inputToInt = stoi(userInput);

			// Bounds test
			if ((inputToInt < LOWEST_USER_CHOICE || inputToInt > HIGHEST_USER_CHOICE)) {
				throw std::runtime_error(userInput + string(" is not a valid option"));
			}
			else if (inputToInt > 3 && inputToInt < 9) {
				throw std::runtime_error(userInput + string(" is not a valid option"));
			}
			else {
				return inputToInt;
			}
		}
		catch (std::invalid_argument const& excpt) {
			// New line for whitespace
			cout << endl;
			std::cout << "Bad input: Please enter a number" << std::endl;
			// New line for whitespace
			cout << endl;
			continue;
		}
		catch (std::out_of_range const& excpt) {
			// New line for whitespace
			cout << endl;
			std::cout << "Integer overflow: please enter a smaller number" << std::endl;
			// New line for whitespace
			cout << endl;
			continue;
		}
		catch (std::runtime_error& excpt) {
			// New line for whitespace
			cout << endl;
			cout << excpt.what() << endl;
			// New line for whitespace
			cout << endl;
			continue;
		}
	}
}

// Funtion to allow main menus to print menu text then set sentinel accordingly
// Note switch statement should be in main
// The only public function
int UserMenu::useMenu() {
	int userChoice;

	cout << "Welcome to the course planner." << endl;

	printMenu();
	userChoice = getUserInput();
	
	return userChoice;
}
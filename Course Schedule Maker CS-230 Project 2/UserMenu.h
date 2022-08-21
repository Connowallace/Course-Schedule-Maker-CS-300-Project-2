//============================================================================
// Name        : UserMenu.h
// Author      : Connor Wallace
// Version     : 1.2
// Description : Template to implement a simple text user menu
//============================================================================


#include <string>
#pragma once

#ifndef COURSE SCHEDULE MAKER CS-230 PROJECT 2_USERMENU_H__
#define COURSE SCHEDULE MAKER CS-230 PROJECT 2_USERMENU_H__

using namespace std;

class UserMenu {
public:
	UserMenu();
	int useMenu();

private:
	void printMenu() const;
	int getUserInput() const;
};
#endif
#include <iostream>
#include <fstream>  // File stream
#include <sstream>  // String stream
#include "UserMenu.h"
#include "BinarySearchTree.h"


using namespace std;

void loadCourses(string filePath, BinarySearchTree* bst);

int main() {
	int userChoice = 0;  // Menu sentinel
	string userInput;
	Course searchCourse;
	auto um = new UserMenu();  // User menu object 

	BinarySearchTree* bst;  // BST object
	bst = new BinarySearchTree();

	while (userChoice != 9) {

		try {
			// Print user menu, validate user input, and update sentinel with user input
			userChoice = um->useMenu();

			cout << endl; // Whitespace

			switch (userChoice) {

			case 1:
				cout << "Please enter the path to the file to load: ";
				cin >> userInput;

				cout << endl; // Whitespace

				loadCourses(userInput, bst);
				break;

			case 2:
				bst->InOrder();
				break;

			case 3:
				cout << "What course do you want to know about? ";
				cin >> userInput;

				cout << endl; // Whitespace

				searchCourse = bst->Search(userInput);

				cout << "findings: " << endl;

				bst->displayCourse(searchCourse);
				bst->displayPrerequisites(searchCourse);

				break;

			case 9:
				cout << "Thank you for using the course planner!" << endl;
				break;

			default:
				// Impossible to reach (hopefully) default case
				cout << "Something has gone wrong, please contact Obi-Wan Kenobi!!!" << endl;
			}

			cout << endl; // Whitespace
		}

		catch (std::runtime_error& excpt) {
			cout << endl;  // Whitespace

			cout << excpt.what() << endl;
			
			cout << endl;  // Whitespace
			continue;
		}
	}

	return 0;
}


/**
 * Load courses into binary search tree
 * 
 * Borrows heavily from : geeksforgeeks.org/csv-file-management-using-c/
 */
void loadCourses(string filePath, BinarySearchTree* bst){
	fstream fin; // File pointer
	vector<string> row; // Vector for splitting rows
	vector<string> allPrerequisites;  // Vector for checking all prereqs are valid
	string line, word;  // Strings for storing lines and words in lines
	char delimiter = ',';  // Delimiter in each line
	Course course;  // Course pointer

	// Open an existing file
	fin.open(filePath, ios::in);

	// If opening fails, throw exception
	if (!fin.is_open()) {
		throw std::runtime_error("CSV file not found at path " + filePath);
	}
	
	// Read the Data from the file
	// as String Vector
	// and add vector data to binary tree
	// each iteration reads in a line
	while (getline(fin, line)) {

		row.clear();

		// Used for breaking words
		stringstream s(line);

		// Read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, delimiter)) {

			// Add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		// Format check
		if (row.size() < 2) {
			throw std::runtime_error("CSV file in wrong format, missing course name/number");
		}

		// Create new course
		course = *new Course();

		// First two lines are class ID and name
		course.courseNumber = row.at(0);
		course.courseName = row.at(1);

		// Add the rest of the row to course prereqs and all prereqs list
		for (int i = 2; i < row.size(); ++i) {
			course.prerequisites.push_back(row.at(i));
			allPrerequisites.push_back(row.at(i));
		}

		// Insert new course
		bst->Insert(course);
	}

	// Close file
	fin.close();

	// Test all prereqs are valid
	for (int i = 0; i < allPrerequisites.size(); ++i) {
		
		// Set the value at course to the result of searching for the prereq
		course = bst->Search(allPrerequisites.at(i));

		// If prereq is not found (blank course returned) throw an error
		if (course.courseName == "Empty course") {
			throw std::runtime_error("CSV file in wrong format, prerequisite " + allPrerequisites.at(i) + " does not exist.");
		}
	}
}
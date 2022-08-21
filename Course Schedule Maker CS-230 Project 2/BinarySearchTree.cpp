//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Connor Wallace
// Version     : 1.1
// Description : Create a binary search tree with course objects as the data
//============================================================================

#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // Root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // Recurse from root deleting every node
    // using postorder deletion
    recursiveDeleteAllNodes(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // Call recursive function with root
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // Call recursive function with root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // Call recursive function with root
    preOrder(root);
}

/**
 * Insert a Course
 */
void BinarySearchTree::Insert(Course course) {

    Node* nodeToInsert = new Node(course);

    // If tree is empty new node is the root
    if (root == nullptr) {
        root = nodeToInsert;
    }

    // Else call recursive insert
    else {
        addNode(root, nodeToInsert);
    }
}

/**
 * Remove a Course
 */
void BinarySearchTree::Remove(string courseNumber) {

    // Set variables using helper functions
    Node* nodeToRemove = search(root, courseNumber);
    Node* parent = getParent(root, nodeToRemove);

    // Call recursive remove
    removeNode(nodeToRemove, parent);
}

/**
 * Display the Course information to the console (std::out)
 *
 * @param Course struct containing the Course info
 */
void BinarySearchTree::displayCourse(Course course){
    cout << course.courseNumber << ", " << course.courseName << endl;
    return;
}

void BinarySearchTree::displayPrerequisites(Course course){

    int i = 0;

    if (i < course.prerequisites.size()) {
        cout << "Prerequisites: ";

        // Print all but the last prereq with a comma and space
        while (i < (course.prerequisites.size() - 1)) {
            cout << course.prerequisites.at(i) << ", ";
            ++i;
        }

        // Print the last prereq without space and comma, end line
        cout << course.prerequisites.at(i) << endl;
    }
}

/**
 * Load courses
 * 
 * Given a path to a CSV file, load all data into tree
 */
void BinarySearchTree::loadCourseFromFile(string filePath)
{
    cout << "method to load from csv";
}

/**
 * Search for a Course
 */
Course BinarySearchTree::Search(string courseNumber) {

    // Call recursive search
    Node* result = search(root, courseNumber);

    // If result is null, return empty Course
    if (result == nullptr) {
        Course course;
        return course;
    }

    // Else return result's Course
    else {
        return result->course;
    }
}

/**
 * Add a Course to some node (recursive)
 *
 * @param node Current node in tree
 * @param Course Course to be added
 */
void BinarySearchTree::addNode(Node* parent, Node* newNode) {

    // Less than fork
    if (newNode->course.courseNumber < parent->course.courseNumber) {

        // Open place to add new node found
        if (parent->left == nullptr) {
            parent->left = newNode;
        }

        // Else recur function on left node
        else {
            addNode(parent->left, newNode);
        }
    }

    // Greater than or equal to fork
    else {

        // Open place to add new node found
        if (parent->right == nullptr) {
            parent->right = newNode;
        }

        // Else recur function on right node
        else {
            addNode(parent->right, newNode);
        }
    }
}

/**
 * Print list in order (recursive)
 * in order = lowest key to highest key
 *
 * @param node Current node in tree
 */
void BinarySearchTree::inOrder(Node* node) {

    // Base case
    if (node == nullptr) {
        return;
    }

    // Recursively call down the left side
    inOrder(node->left);

    // Print
    displayCourse(node->course);

    // Recursively call down the right side
    inOrder(node->right);
}

/**
 * Print list in postorder (recursive)
 * Postorder = left side leaves to root, then right side leaves to root, with the root last
 *
 * @param node Current node in tree
 */
void BinarySearchTree::postOrder(Node* node) {

    // Base case
    if (node == nullptr) {
        return;
    }

    // Recursively call down the left side
    postOrder(node->left);

    // Recursively call down the right side
    postOrder(node->right);

    // Print
    displayCourse(node->course);
}

/**
 * Print list in preorder (recursive)
 *
 * @param node Current node in tree
 */
void BinarySearchTree::preOrder(Node* node) {

    // Base case
    if (node == nullptr) {
        return;
    }

    // Print
    displayCourse(node->course);

    // Recursively call down the left side
    preOrder(node->left);

    // Recursively call down the right side
    preOrder(node->right);
}

/**
 * Remove a Course from some node (recursive)
 *
 * @param node Current node in tree
 * @param courseNumber Course Id to find
 */
void BinarySearchTree::removeNode(Node* nodeToRemove, Node* parent) {

    Node* successor = nullptr;
    Node* successorParent = nullptr;
    Node* temp = nullptr;

    // Base Case node not found
    if (nodeToRemove == nullptr) {
        return;
    }

    // Case node with 2 children
    else if (nodeToRemove->left != nullptr && nodeToRemove->right != nullptr) {

        // Find successor node
        successor = nodeToRemove->right;
        successorParent = nodeToRemove;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        // Place successor's value in node to remove
        nodeToRemove->course = successor->course;

        // Remove successor
        removeNode(successor, successorParent);

        // Return because we don't need to delete in this case
        return;
    }

    // Case root node with 1 or less children
    else if (nodeToRemove == root) {

        // Left side has child
        if (nodeToRemove->left != nullptr) {
            root = nodeToRemove->left;
        }

        // Else right side has child or no child
        else {
            root = nodeToRemove->right;
        }
    }

    // Case internal with left child only
    else if (nodeToRemove->left != nullptr) {

        // Move correct parent pointer
        if (parent->left == nodeToRemove) {
            parent->left = nodeToRemove->left;
        }
        else {
            parent->right = nodeToRemove->left;
        }
    }

    // Case internal with right child or leaf
    else {
        // Move correct parent pointer
        if (parent->left == nodeToRemove) {
            parent->left = nodeToRemove->right;
        }
        else {
            parent->right = nodeToRemove->right;
        }
    }

    // Delete the node to remove
    temp = nodeToRemove;
    delete temp;
}


/**
 * Search for a course (recursive)
 *
 * @param node Current node in tree
 * @param courseNumber Course Id to find
 */
Node* BinarySearchTree::search(Node* node, string courseNumber) {

    // Base case node not found
    if (node == nullptr) {
        return nullptr;
    }

    // Node found case
    if (node->course.courseNumber == courseNumber) {
        return node;
    }

    // Search left side if lower
    if (courseNumber < node->course.courseNumber) {
        return search(node->left, courseNumber);
    }

    // Else search right side
    return search(node->right, courseNumber);
}

/**
 * Search for parent of child node (recursive)
 *
 * @param subTreeRoot Current node in tree
 * @param childNode node to fid parent of
 */
Node* BinarySearchTree::getParent(Node* subtreeRoot, Node* childNode) {

    // Base case parent not found, or node DNE
    if (subtreeRoot == nullptr || childNode == nullptr) {
        return nullptr;
    }

    // Parent found case
    if (subtreeRoot->left == childNode || subtreeRoot->right == childNode) {
        return subtreeRoot;
    }

    // Search left side if lower
    if (childNode->course.courseNumber < subtreeRoot->course.courseNumber) {
        return getParent(subtreeRoot->left, childNode);
    }

    // Else search right side
    return getParent(subtreeRoot->right, childNode);
}

/**
 * Delete nodes in post order (recursive)
 */
void BinarySearchTree::recursiveDeleteAllNodes(Node* node) {

    // Base case
    if (node == nullptr) {
        return;
    }

    // Recursively call down the left side
    recursiveDeleteAllNodes(node->left);

    // Recursively call down the right side
    recursiveDeleteAllNodes(node->right);

    // Delete the node
    delete node;
}
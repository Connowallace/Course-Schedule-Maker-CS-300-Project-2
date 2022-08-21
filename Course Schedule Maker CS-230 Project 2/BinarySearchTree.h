//============================================================================
// Name        : BinarySearchTree.h
// Author      : Connor Wallace
// Version     : 1.1
// Description : Create a binary search tree with course objects as the data
//============================================================================

#pragma once
#include <iostream>
#include <vector>

#define COURSE SCHEDULE MAKER CS-230 PROJECT 2_BINARYSEARCHTREE_H__

using namespace std;

//============================================================================
// Global definitions
//============================================================================

// Define a structure to hold Course information
struct Course {
    string courseNumber; // Unique identifier
    string courseName;  // Course Name
    vector<string> prerequisites;  // Required prereqs
    Course() {
        this->courseName = "Empty course"; // initialized value for testing if course is empty
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a Course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

class BinarySearchTree {
public:  
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseId);
    void displayCourse(Course course);
    void displayPrerequisites(Course course);
    void loadCourseFromFile(string filePath);
    Course Search(string courseId);

private:
    Node* root;

    void addNode(Node* parent, Node* newNode);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    void removeNode(Node* nodeToRemove, Node* parent);
    void recursiveDeleteAllNodes(Node* node);
    Node* search(Node* node, string courseId);
    Node* getParent(Node* subtreeRoot, Node* childNode);
};
//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : JYour name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm>    // needed for strToDouble()

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// FIXME (1) DONE: Internal structure for tree node
struct Node {
    Bid bid;
    Node* leftNode;
    Node* rightNode;

    //default constructor
    Node() {
        leftNode = nullptr;
        rightNode = nullptr;
    }

    //constructor to initialize w/ a bid
    Node(Bid passedBid) {
        this->bid = passedBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root = nullptr;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

    //helper pointers
    Node* currNode = nullptr;
    Node* anchorNode = nullptr;

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);

    //NOTE: delete this before turning in
    int nodeCounter = 0;
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    //NOTE: this is for testing/debug purposes. Delete before turn in
    cout << "Root bid ID is: " << this->root->bid.bidId << endl;
    cout << "Total nodes in the tree: " << nodeCounter << endl;
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) DONE: Implement inserting a bid into the tree

    //create the new node and assign the passed bid to it
    Node* aNewNode = new Node;
    addNode(aNewNode, bid);


    //if the tree is empty
    if (this->root == nullptr) {
        //this->root = new Node(bid);
        this->root = aNewNode;
    }
    else {
        //set current node to root so that we can traverse the tree
        this->currNode = this->root;

        while (currNode != nullptr) {

            //logic for navigating left branch (less than)
            if (bid.bidId < this->currNode->bid.bidId) {
                if (this->currNode->leftNode == nullptr) {
                    //this->currNode->leftNode = new Node(bid);
                    this->currNode->leftNode = aNewNode;
                    break;
                }
                else {
                    this->currNode = currNode->leftNode;
                }
            }

            //logic for navigating right branch (greater than)
            // if (strToDouble(bid.bidId, ' ') > strToDouble(this->currNode->bid.bidId, ' '))
            else if (bid.bidId > this->currNode->bid.bidId) {
                if (this->currNode->rightNode == nullptr) {
                    //this->currNode->rightNode = new Node(bid);
                    this->currNode->rightNode = aNewNode;
                    break;
                }
                else {
                    this->currNode = currNode->rightNode;
                }
            }
        }
    }
    nodeCounter++;
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (4a) Implement removing a bid from the tree
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (3) DONE: Implement searching the tree for a bid
    this->currNode = this->root;

    while (currNode != nullptr) {
        cout << "CURRENT BID: " << currNode->bid.bidId << endl;
        if (currNode->bid.bidId == bidId) {
            return currNode->bid;
        }
        else if (bidId < currNode->bid.bidId) {
                currNode = currNode->leftNode;
        }

        else if (bidId > currNode->bid.bidId) {
                currNode = currNode->rightNode;
        }
    }
	Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (2b) DONE: Implement inserting a bid into the tree
    //why is this function here when you can just initialize a node with a bid via non-default constructor???

    node->bid = bid;

   //BinarySearchTree::Search(node->bid.bidId) = bid;
}
void BinarySearchTree::inOrder(Node* node) {
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        //csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        csvPath = "eBid_Monthly_Sales_Dec_2016_debug.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            //for debug/testing purposes
            cout << "Enter bid ID: ";
            cin >> bidKey;

            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            //for debug/testing purposes
            cout << "Enter bid ID: ";
            cin >> bidKey;

            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}

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
    Node* prevNode = nullptr;
    Node* currNode = nullptr;
    Node* anchorNode = nullptr;

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(Node* node, string bidId);
    Bid Search(string bidId);
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
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) DONE: Implement inserting a bid into the tree

    //if the tree is empty
    if (this->root == nullptr) {
        this->root = new Node;
        addNode(this->root, bid);
    }
    else {
        //set current node to root so that we can traverse the tree
        this->currNode = this->root;

        while (currNode != nullptr) {

            //logic for navigating left branch (less than)
            if (bid.bidId <= this->currNode->bid.bidId) {
                if (this->currNode->leftNode == nullptr) {
                    this->currNode->leftNode = new Node;
                    addNode(this->currNode->leftNode, bid);
                    break;
                }
                else {
                    this->currNode = currNode->leftNode;
                }
            }

            //logic for navigating right branch (greater than)
            else if (bid.bidId > this->currNode->bid.bidId) {
                if (this->currNode->rightNode == nullptr) {
                    this->currNode->rightNode = new Node;
                    addNode(this->currNode->rightNode, bid);
                    break;
                }
                else {
                    this->currNode = currNode->rightNode;
                }
            }
        }
    }
    currNode = nullptr;
}

/**
 * Remove a bid
 */
//I changed this function to take a pointer argument so that the function can be called recursively at a
//node that isn't the root node. This allows the function to be used when deleting a node with two child nodes.
void BinarySearchTree::Remove(Node* passedNode, string bidId) {
    // FIXME (4a) DONE: Implement removing a bid from the tree

    //logic for differentiating between recursive call or normal call
    if (passedNode == nullptr) {
        this->anchorNode = this->root;
        this->prevNode = this->root;
        this->currNode = this->root;
    }
    else {
        this->anchorNode = passedNode;
        this->prevNode = passedNode;
        this->currNode = passedNode;
    }

    //find the bid and delete
    while (currNode != nullptr) {
        if (currNode->bid.bidId == bidId){
            anchorNode = currNode;

            //logic for deleting a leaf
            if (currNode->leftNode == nullptr && currNode->rightNode == nullptr) {
                if (prevNode->leftNode == currNode) {           //delete a left leaf
                    cout << prevNode->leftNode->bid.bidId << " has been deleted!" << endl;
                    delete prevNode->leftNode;
                    prevNode->leftNode = nullptr;
                }
                else if (prevNode->rightNode == currNode) {     //delete a right leaf
                    cout << prevNode->rightNode->bid.bidId << " has been deleted!" << endl;
                    delete prevNode->rightNode;
                    prevNode->rightNode = nullptr;
                }
            }

            //logic for deleting an internal node with only a LEFT child
            else if (currNode->leftNode != nullptr && currNode->rightNode == nullptr) {
                currNode = currNode->leftNode;
                if (prevNode->leftNode == anchorNode) {         //delete a left successor
                    cout << prevNode->leftNode->bid.bidId << " has been deleted!" << endl;
                    delete prevNode->leftNode;
                    prevNode->leftNode = currNode;
                }
                else if (prevNode->rightNode == anchorNode) {   //delete a right successor
                    cout << prevNode->rightNode->bid.bidId << " has been deleted!" << endl;
                    delete prevNode->rightNode;
                    prevNode->rightNode = currNode;
                }
            }

            //logic for deleting an internal node with only a RIGHT child
            else if (currNode->leftNode == nullptr && currNode->rightNode != nullptr) {
                currNode = currNode->rightNode;
                if (prevNode->leftNode == anchorNode) {         //delete a left successor
                    cout << prevNode->leftNode->bid.bidId << " has been deleted!" << endl;
                    delete prevNode->leftNode;
                    prevNode->leftNode = currNode;
                }
                else if (prevNode->rightNode == anchorNode) {   //delete a right successor
                    cout << prevNode->rightNode->bid.bidId << " has been deleted!" << endl;
                    delete prevNode->rightNode;
                    prevNode->rightNode = currNode;
                }
            }

            //logic for deleting an internal node with both a right and left child
            else if (currNode->leftNode != nullptr && currNode->rightNode != nullptr) {
                currNode = currNode->rightNode;
                while (currNode->leftNode != nullptr) {
                    currNode = currNode->leftNode;
                }

                //sets the anchor node to the current node
                addNode(anchorNode, currNode->bid);

                //call Remove() recursively with specification on where to begin search for the node/bid to delete
                Remove(anchorNode->rightNode, currNode->bid.bidId);
            }
            break;
        }

        //navigate the tree LEFT
        else if (bidId < currNode->bid.bidId) {
            prevNode = currNode;
            currNode = currNode->leftNode;
        }

        //navigate the tree RIGHT
        else if (bidId > currNode->bid.bidId) {
            prevNode = currNode;
            currNode = currNode->rightNode;
        }
    }

    //output for if the bidID isn't in the tree
    if (currNode == nullptr) {
        cout << bidId << " not found!" << endl;
    }

    //reset helper pointers to null
    this->anchorNode = nullptr;
    this->prevNode = nullptr;
    this->currNode = nullptr;
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (3) DONE: Implement searching the tree for a bid

    this->currNode = this->root;

    while (currNode != nullptr) {

        //return the bid when found
        if (currNode->bid.bidId == bidId) {
            return currNode->bid;
        }

        //navigate the tree LEFT
        else if (bidId < currNode->bid.bidId) {
                currNode = currNode->leftNode;
        }
        //navigate the tree RIGHT
        else if (bidId > currNode->bid.bidId) {
                currNode = currNode->rightNode;
        }
    }

    //reset currNode and return empty bid;
    currNode = nullptr;
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

    node->bid = bid;
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
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        //csvPath = "eBid_Monthly_Sales_Dec_2016_debug.csv";    //debug csv with fewer values
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
/*
            //for debug/testing purposes
            cout << "Enter bid ID: ";
            cin >> bidKey;
*/

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
/*
            //for debug/testing purposes
            cout << "Enter bid ID: ";
            cin >> bidKey;
*/

            bst->Remove(nullptr, bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}

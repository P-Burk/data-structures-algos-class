//============================================================================
// Name        : LinkedList.cpp
// Author      : Preston Burkhardt
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

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

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    // FIXME (1): Internal structure for list entries, housekeeping variables

    //node to hold each bid in the linked list
    struct bidNode {
        Bid bid;
        bidNode *nextNode;
        //default constuctor for bidNode
        bidNode() {
            nextNode = nullptr;
        };
        //constuctor with a bid passed in
        bidNode(Bid passedBid) {
            this->bid = passedBid;
            nextNode = nullptr;
        };
    };

    //helper and navigation pointers
    bidNode *headNode;
    bidNode *tailNode;
    bidNode *currNode;
    bidNode *prevNode;

    //for tracking list size
    int size = 0;

    //for printing bid info
    string printBid(Bid bid);

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // FIXME (2): Initialize housekeeping variables
    headNode = nullptr;
    tailNode = nullptr;
    currNode = nullptr;
    prevNode = nullptr;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

//prints bid info for specific bid
string LinkedList::printBid(Bid bid) {
    return bid.bidId + ": " + bid.title + " | " + to_string(bid.amount) + " | " + bid.fund;
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // FIXME (3): Implement append logic

    //create new bidNode
    bidNode *newNode = new bidNode(bid);

    //assign the newNode as head and tail if no head exists
    if (this->headNode == nullptr) {
        this->headNode = newNode;
        this->tailNode = newNode;
    }
    //assigns the nextNode pointer of the current tail node to the new node and sets the tail as that node
    else {
        this->tailNode->nextNode = newNode;
        this->tailNode = newNode;
    }
    // increment size tracker
    size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // FIXME (4): Implement prepend logic

    //create new bidNode
    bidNode *newNode = new bidNode(bid);

    //assign as head and tail if no head exists
    if (this->headNode == nullptr) {
        this->headNode = newNode;
        this->tailNode = newNode;
    }
    //assigns new node's nextNode pointer to the current head node, then tags the new node as the head node
    else {
        newNode->nextNode = this->headNode;
        this->headNode = newNode;
    }
    // increment size tracker
    size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (5): Implement print logic

    //sets current node as the head node
    this->currNode = this->headNode;

    //iterates through all the nodes until this->currNode is assigned null
    //prints bid info for each node
    while (this->currNode != nullptr) {
        cout << this->currNode->bid.bidId << ": " << this->currNode->bid.title << " | " << this->currNode->bid.amount
             << " | " << this->currNode->bid.fund << endl;
        this->currNode = this->currNode->nextNode;
    }
    //reset this->currNode to null
    this->currNode = nullptr;
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (6): Implement remove logic

    //set current node to head node
    this->currNode = this->headNode;

    //iterate through list until current node is a null pointer
    while (this->currNode != nullptr) {

        //branch for if the removed node is the head node
        if (this->currNode->bid.bidId == bidId && this->currNode == this->headNode) {
            this->headNode = this->headNode->nextNode;
            delete this->currNode;
            break;
        }

        //branch for if the removed node is the tail node
        else if (this->currNode->bid.bidId == bidId && this->currNode == this->tailNode) {
            this->tailNode = this->prevNode;
            this->prevNode->nextNode = nullptr;
            delete this->currNode;
            break;
        }

        //moves previous node to the current node and current node to the next node
        else if (this->currNode->bid.bidId != bidId) {
            this->prevNode = this->currNode;
            this->currNode = this->currNode->nextNode;
        }

        //branch for when the removed node is found within the list
        //sets the previous node's nextNode to current node's nextNode then deletes current node
        else {
            this->prevNode->nextNode = this->currNode->nextNode;
            delete this->currNode;
            break;
        }
    }

    //reset current node and previous node to null and decrement size
    this->currNode = nullptr;
    this->prevNode = nullptr;

    //decrement size counter
    size--;
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIXME (7): Implement search logic

    //set current node to head node
    this->currNode = this->headNode;

    //iterate through list until current node is null
    while (this->currNode != nullptr) {

        //if the current node bidID == argument bidID, return that bid
        //Otherwise increment currNode to the next node
        if (this->currNode->bid.bidId == bidId) {
            return this->currNode->bid;
        }
        else {
            this->currNode = this->currNode->nextNode;
        }
    }
    //if no bid is found, empty bid is returned
    return Bid();
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //outputs bid info to ensure csv is being read properly
            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
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
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
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
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

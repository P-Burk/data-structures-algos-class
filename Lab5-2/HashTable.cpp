//============================================================================
// Name        : HashTable.cpp
// Author      : Preston Burkhardt
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <utility>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

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
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // FIXME (1) DONE: Define structures to hold bids
    //node to hold each bid in the linked list
    struct bidNode {
        Bid bid;
        unsigned bidKey;
        bidNode *nextNode;

        //default constructor
        bidNode() {
            bidKey = UINT_MAX;
            nextNode = nullptr;
        };

        //constructor with a bid passed in
        bidNode(Bid passedBid) : bidNode() {
            this->bid = passedBid;
        };

        //constructor with bid and key
        bidNode(Bid passedBid, unsigned passedKey) : bidNode(passedBid) {
            this->bidKey = passedKey;
        };
    };

    //use tableSize for vector resizing operations if needed
    unsigned tableSize = DEFAULT_SIZE;

    //vector to hold all the nodes
    vector<bidNode> nodesVector;

    //helper pointer for traversing linked lists
    bidNode* currNode = nullptr;

    unsigned int hash(int key);

public:
    HashTable();
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // FIXME (2) DONE: Initialize the structures used to hold bids
    nodesVector.resize(tableSize);
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    // FIXME (3) DONE: Implement logic to free storage when class is destroyed
    nodesVector.erase(nodesVector.begin());
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // FIXME (4) DONE: Implement logic to calculate a hash value
    //calculates the key based on the size of the hash table
    return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // FIXME (5) DONE: Implement logic to insert a bid

    //calculate key
    unsigned key = hash(atoi(bid.bidId.c_str()));

    //initializes oldNode as the node in the vector at the hash key
    bidNode* oldNode = &(nodesVector.at(key));

    //oldNode is null (bid isn't in the table)
    if (oldNode == nullptr) {
        bidNode* newNode = new bidNode(bid, key);
        nodesVector.insert(nodesVector.begin() + key, (*newNode));
    }

    //oldNode is not null (bid does exist in the table)
    else {
        /*
         * if/else to see if the bid @ oldNode is the only one in the bucket.
         * Finds the last node in the bucket if not the only bid.
         */
        if (oldNode->bidKey == UINT_MAX) {
            oldNode->bidKey = key;
            oldNode->bid = bid;
            oldNode->nextNode = nullptr;
        }
        else {
            //find the last node in the linked list
            while (oldNode->nextNode != nullptr) {
                oldNode = oldNode->nextNode;
            }
            //add new bidNode to the end of the list
            oldNode->nextNode = new bidNode(bid, key);
        }
    }
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (6) DONE: Implement logic to print all bids

    //loop through all the baskets in the vector
    for (auto & bidNode : nodesVector) {

        //if the key is not the default key, then print the bid's info
        if (bidNode.bidKey != UINT_MAX) {
            cout << bidNode.bid.bidId << ": " << bidNode.bid.title << " | " << bidNode.bid.amount << " | "
                 << bidNode.bid.fund << endl;

            //set currNode equal to the next node that the current node points to
            currNode = bidNode.nextNode;

            //print bid info if currNode isn't null and increment currNode to the next node via bid.nextNode
            while (currNode != nullptr) {
                cout << currNode->bid.bidId << ": " << currNode->bid.title << " | " << currNode->bid.amount << " | "
                     << currNode->bid.fund << endl;
                currNode = currNode->nextNode;
            }
        }
    }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // FIXME (7) DONE: Implement logic to remove a bid

    //calculate key
    unsigned key = hash(atoi(bidId.c_str()));

    //assign currNode to the next node in the linked list
    currNode = nodesVector.at(key).nextNode;

    //erase the bid in the bucket if it's the only one
    if (nodesVector.at(key).bid.bidId == bidId && nodesVector.at(key).nextNode == nullptr) {
        nodesVector.erase(nodesVector.begin() + key);
    }

    //erase the first bid in the bucket
    else if (nodesVector.at(key).bid.bidId == bidId && nodesVector.at(key).nextNode != nullptr) {
        nodesVector.erase(nodesVector.begin() + key);
        nodesVector.at(key).bid = currNode->bid;
    }

    //erase subsequent bids in the bucket
    else if (nodesVector.at(key).bid.bidId != bidId && nodesVector.at(key).nextNode != nullptr) {
        while (currNode != nullptr) {
            if (currNode->bid.bidId == bidId && currNode->nextNode != nullptr) {
                nodesVector.at(key).nextNode = currNode->nextNode;
                break;
            }
            else if (currNode->bid.bidId == bidId) {
                nodesVector.at(key).nextNode = nullptr;
                break;
            }
            currNode = currNode->nextNode;
        }
    }
    currNode = nullptr;
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;
    // FIXME (8) DONE: Implement logic to search for and return a bid

    //calculate key
    unsigned key = hash(atoi(bidId.c_str()));

    //return the bid at the key if it's id matches the bidId argument
    if (nodesVector.at(key).bid.bidId == bidId) {
        return nodesVector.at(key).bid;
    }

    //search the other nodes in the linked list if the head node doesn't match
    else {
        currNode = nodesVector.at(key).nextNode;
        while (currNode != nullptr) {
            if (currNode->bid.bidId == bidId) {
                return currNode->bid;
            }
            currNode = currNode->nextNode;
        }
    }
    //returns empty bid
    return bid;
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
void loadBids(string csvPath, HashTable* hashTable) {
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
            hashTable->Insert(bid);
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
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

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
            bidTable = new HashTable();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

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
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

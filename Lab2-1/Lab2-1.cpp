//============================================================================
// Name        : Lab2-2.cpp
// Author      : Preston Burkhardt
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 2-2 Up to Speed in C++, Part 2
//============================================================================

#include <algorithm>
#include <iostream>
#include <utility>
#include <time.h>

// FIXME (1): Reference the CSVParser library
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

struct Bid {
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
    //added constructor with 3 arguments in order to fully construct a Bid object
    Bid(string bidTitle, string bidFund, double bidAmount) {
        title = move(bidTitle);
        fund = move(bidFund);
        amount = bidAmount;
    }

};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter title: ";
    cin.ignore();
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
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
	// FIXME (2): Define a vector data structure to hold a collection of bids.
    // vector to hold all bids for output
    vector<Bid> holdBids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

	// loop to read rows of a CSV file
    // reads CSV file, initializes currentBid with bid info, adds current bid to vector for output
	for (int i = 0; i < file.rowCount(); i++) {
        // FIXME (3): create a data structure to hold data from each row and add to vector
        // can use declaration + constructor OR declare + define each attribute
        // comment out one or the other. can't run both at same time

        Bid currentBid = {file[i][0], file[i][8], strToDouble(file[i][4], '$')};
/*
        Bid currentBid;
        currentBid.title = file[i][0];
        currentBid.fund = file[i][8];
        currentBid.amount = strToDouble(file[i][4], '$');
*/

        holdBids.push_back(currentBid);
    }
    cout << file.rowCount() << " bids read." << endl;
    return holdBids;
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
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        // had to add the full path to the CSV file for my code to work
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // FIXME (4): Define a vector to hold all the bids
    // vector to hold all of the bids
    vector<Bid> holdAllBids;

    // FIXME (7a): Define a timer variable
    //variable for calculating run time
    double timerVariable;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
        	cout << "Not currently implemented." << endl;

            break;
        case 2:
            // FIXME (7b): Initialize a timer variable before loading bids
            timerVariable = clock();

            // FIXME (5): Complete the method call to load the bids
            holdAllBids = loadBids(csvPath);

            // FIXME (7c): Calculate elapsed time and display result
            timerVariable = clock() - timerVariable;
            cout << "Time: " << timerVariable << " milliseconds." << endl;
            cout << "Time: " << (timerVariable * 0.001) << " seconds." << endl;

            break;
        case 3:
            // FIXME (6): Loop and display the bids read
            // loops through all of the bids in holdAllBidsVector and displays each
            for (int i = 0; i < holdAllBids.size(); ++i) {
            	displayBid(holdAllBids.at(i));
            }
            cout << endl;

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

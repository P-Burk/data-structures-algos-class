//============================================================================
// Name        : Lab1-3.cpp
// Author      : Your Name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 1-3 Up to Speed in C++
//============================================================================

#include <algorithm>
#include <iostream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// FIXME (1): Define a data structure to hold bid information together as a single unit of storage.
struct bidInfo{
    string bidTitle;
    string fundType;
    string vehicleType;
    double bidAmount;
};

// FIXME (4): Display the bid values passed in data structure
/**
 * Display the bid information
 *
 * @param ?type? data structure containing the bid info
 */
void displayBid(bidInfo userBid) {
    cout << "Title: " << userBid.bidTitle << endl;
    cout << "Fund: " << userBid.fundType << endl;
    cout << "Vehicle: " << userBid.vehicleType << endl;
    cout << "Bid Amount: " << userBid.bidAmount << endl;

    return;
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


// FIXME (3): Store input values in data structure
/**
 * Prompt user for bid information
 *
 * @return data structure containing the bid info
 */
bidInfo getBid() {
    bidInfo userBid;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, userBid.bidTitle);

    cout << "Enter fund: ";
    cin >> userBid.fundType;

    cout << "Enter vehicle: ";
    cin.ignore();
    getline(cin, userBid.vehicleType);

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    userBid.bidAmount = strToDouble(strAmount, '$');

    return userBid;
}


/**
 * The one and only main() method
 */
int main() {

    // FIXME (2): Declare instance of data structure to hold bid information
	bidInfo userBid1;

    // loop to display menu until exit chosen
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter Bid" << endl;
        cout << "  2. Display Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        // FIXME (5): Complete the method calls then test the program
        switch (choice) {
            case 1:
            	userBid1 = getBid();
                break;
            case 2:
                displayBid(userBid1);
                break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

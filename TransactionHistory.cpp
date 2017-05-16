// TransactionHistory class implementation
#include "TransactionHistory.h"
#include <iostream>

// Add a new transaction to the history
void TransactionHistory::addTransaction(transaction t) {
    history.push_back(t);
}

// A simple sanity check for customer transaction assignment
void TransactionHistory::check() {
    cout << to_string(history.size()) << "\n";
}

// Get the value representing the date of the last transaction in this customer's transaction history
int TransactionHistory::getLastDay() {
    if(!history.empty()) {
        return history.back().day.day;
    } else {
        return 0;
    }
}

// Return the number of transactions in the customer's history which were made online
int TransactionHistory::getNumOnlineTransactions() {
    int numOnline = 0;

    for(transaction t : history) {
        if(t.online) {
            numOnline = numOnline + 1;
        }
    }
    return numOnline;
}

// Return the 'n' most recent transaction is this customer's transaction history
vector<transaction> TransactionHistory::getRecentHistory(int howRecent) {
    vector<transaction> recentHistory(history.end() - howRecent, history.end());
    return recentHistory;
}
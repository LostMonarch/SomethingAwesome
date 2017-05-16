// Behavioural credit card fraud detector - main routine
#include <iostream>
#include "Bank.h"
#include "DecisionTree.h"

#define PRINT_SUMMARY 0
#define SHOW_TREE 0
#define EXIT 0
#define RUNNING true

void displayTransaction(transaction t);

int main(int argc, char* argv[]) {
    Bank * b = new Bank(DECISION_TREE);

    // Indicate that the fraud detection system is starting
    cout << "Starting credit card fraud detector...\n";

    // Use the first command line argument to add a list of customers to the bank
    cout << "Adding customers...\n";    
    b->customersFromFile(argv[1]);

    // Summarise customers who are now part of the system
    #if PRINT_SUMMARY == 1
    b->displayCustomerInfo();
    #endif

    // Learn about the behaviour of each customer using a list of transactions - also known as customer profiling
    cout << "Using transaction history to learn about customers...\n";
    b->learnAboutCustomers(argv[2]);

    // Construct the system's decision tree (keep nodes in a vector to keep them in scope)
    vector<DecisionTree> treeNodes;
    b->constructTree(treeNodes);

    // Check that the tree was constructed correctly
    #if SHOW_TREE == 1
    b->showTree();
    #endif

    // Wait for new transactions and classify them as they arrive
    cout << "\nPlease enter a new transaction: \n";
    string input;
    transaction newTransaction;
    while(RUNNING) {
        getline(cin, input);
        newTransaction = b->newTransactionFromString(input);
        displayTransaction(newTransaction);
        cout << "\nPlease enter a new transaction: \n";
    }

    return EXIT;
}

void displayTransaction(transaction t) {
    cout << "\nNew transaction\n----------------\n";
    cout << "Card: " << to_string(t.card) << "\n";
    cout << "Location: " << to_string(t.postcode) << "\n";
    cout << "Amount: " << to_string(t.value) << "\n";
    cout << "Date: " << to_string(t.day.day) << "." << to_string(t.day.year) << "\n";
    cout << "Time: " << to_string(t.when.hours) << ":" << to_string(t.when.minutes) << "\n";
    cout << "\n";
}
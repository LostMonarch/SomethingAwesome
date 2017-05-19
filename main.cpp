// Behavioural credit card fraud detector - main routine
#include <iostream>
#include "Bank.h"
#include "DecisionTree.h"

#define PRINT_SUMMARY 0
#define SHOW_TREE 0
#define DISPLAY_NEW_TRANSACTIONS 1
#define EXIT 0
#define ADD_AND_PROFILE 1
#define RUNNING true

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
        #if DISPLAY_NEW_TRANSACTIONS == 1
        b->displayTransactionSummary(newTransaction);
        cout << "\n";
        #endif
        bool isFraud = b->detect(newTransaction);
        if(isFraud) {
            cout << "Decision: FRAUD\n";
        } else {
            cout << "Decision: NOT FRAUD\n";
        }
        #if ADD_AND_PROFILE == 1
        cout << "Updating cusomter profile with new transaction...\n"
        b->assignTransaction(newTransaction);
        b->updateCustomerProfile(newTransaction);
        #endif
        cout << "\nPlease enter a new transaction: \n";
    }

    return EXIT;
}
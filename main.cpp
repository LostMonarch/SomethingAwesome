// Behavioural credit card fraud detector - main routine
#include <iostream>
#include "Bank.h"
#include "DecisionTree.h"

#define PRINT_SUMMARY 0

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

    // Construct the system's decision tree
    vector<DecisionTree> treeNodes;
    b->constructTree(treeNodes);

    // Check that the tree was constructed correctly
    b->showTree();

    return 0;
}
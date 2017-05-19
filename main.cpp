// Behavioural credit card fraud detector - main routine
#include <sstream>
#include <fstream>
#include "Bank.h"
#include "DecisionTree.h"

#define PRINT_SUMMARY 0
#define SHOW_TREE 0
#define DISPLAY_NEW_TRANSACTIONS 1
#define EXIT 0
#define ADD_AND_PROFILE 1
#define INPUT_FROM_FILE 1
#define INDICATE_TRANSACTION 0
#define GIVE_FEEDBACK 0
#define RUNNING true

int main(int argc, char* argv[]) {
    Bank * b = new Bank(DECISION_TREE);

    // Indicate that the fraud detection system is starting
    #if GIVE_FEEDBACK == 1
    cout << "Starting credit card fraud detector...\n";
    #endif

    // Use the first command line argument to add a list of customers to the bank
    #if GIVE_FEEDBACK == 1
    cout << "Adding customers...\n";
    #endif
    b->customersFromFile(argv[1]);

    // Summarise customers who are now part of the system
    #if PRINT_SUMMARY == 1
    b->displayCustomerInfo();
    #endif

    // Learn about the behaviour of each customer using a list of transactions - also known as customer profiling
    #if GIVE_FEEDBACK == 1
    cout << "Using transaction history to learn about customers...\n";
    #endif
    b->learnAboutCustomers(argv[2]);

    // Construct the system's decision tree (keep nodes in a vector to keep them in scope)
    vector<DecisionTree> treeNodes;
    b->constructTree(treeNodes);

    // Check that the tree was constructed correctly
    #if SHOW_TREE == 1
    b->showTree();
    #endif

    #if INPUT_FROM_FILE == 0
    // Wait for new transactions from the user and classify them as they arrive
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
        // Only update the customer's profile if the transaction was NOT fraudulent
        b->assignTransaction(newTransaction);
        if(!isFraud) {
            b->updateCustomerProfile(newTransaction);
        }
        #endif
        cout << "\nPlease enter a new transaction: \n";
    }
    #else
    // Read new transactions from a text file and classify them one by one - makes testing multiple transactions at once much easier
    #if GIVE_FEEDBACK == 1
    cout << "Reading new transactions from file...\n";
    #endif
    // Store lines of verification fil in a list
    ifstream input(argv[3]);
    vector<string> v;
	back_insert_iterator< vector<string> > backInserter = back_inserter(v);
    // Read transaction list line by line
    for(string line; getline(input, line);) {
        *(backInserter++) = line;
    }
    // For each line, parse it by creating a new transaction, then indicate it's classification
    vector<string>::iterator i;
    transaction newTransaction;
    int count = 0;
    for(i = begin(v); i != end(v); ++i) {
        count++;
        string s = * i;
        #if INDICATE_TRANSACTION == 1
        cout << "Parsing transaction: " << to_string(count) << "\n";
        #endif
        newTransaction = b->newTransactionFromString(s);
        bool isFraud = b->detect(newTransaction);
        if(isFraud) {
            cout << "Decision: FRAUD\n";
        } else {
            cout << "Decision: NOT FRAUD\n";
        }
        #if ADD_AND_PROFILE == 1
        // Only update the customer's profile if the transaction was NOT fraudulent
        b->assignTransaction(newTransaction);        
        if(!isFraud) {
            b->updateCustomerProfile(newTransaction);
        }
        #endif
    }
    #endif

    // Finish
    return EXIT;
}
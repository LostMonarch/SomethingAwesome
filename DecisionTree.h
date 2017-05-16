// Header file defining the decision tree class
#ifndef DECISION_TREE_H_
#define DECISION_TREE_H_

#include <iostream>

// Include header files for transactions and customers
#include "transaction.h"
#include "Customer.h"

using namespace std;

typedef enum nodeType {
    VENDOR_TYPE,
    LOCATION,
    ONLINE_THRESHOLD,
    ONLINE_CHANGE,
    VOLUME_THRESHOLD,
    VOLUME_DISTANCE,
    FREQUENCY_THRESHOLD,
    FREQUENCY_DISTANCE,
    LEAF_FRAUD,
    LEAF_NOT_FRAUD
} nodeTypeID;

// Decision Tree defines a single node in the tree - the root of the tree is referred to as 'the tree' but is actually just another node
class DecisionTree {
    public:
        DecisionTree(int nID, nodeTypeID tID);
        bool classify(transaction t, Customer c);
        void addChild(bool left, DecisionTree * c);
        void sayHi() { cout << "My name is node " << to_string(nodeID) << "\n"; };
        void showTree();
    private:
        bool classify_child(bool left, transaction t, Customer c);
        int nodeID;
        nodeTypeID typeID;
        DecisionTree * leftChild;
        DecisionTree * rightChild;
};

#endif
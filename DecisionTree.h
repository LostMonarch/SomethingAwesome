// Header file defining the decision tree class
#ifndef DECISION_TREE_H_
#define DECISION_TREE_H_

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
    FREQUENCY_DISTANCE
} nodeTypeID;

class DecisionTree {
    public:
        DecisionTree(int nID, nodeTypeID tID);
        virtual bool classify(transaction t, Customer c) { return true; };
        void addChild(bool left_right, DecisionTree * c);
    private:
        int nodeID;
        nodeTypeID typeID;
        vector<DecisionTree *> children;
};

#endif
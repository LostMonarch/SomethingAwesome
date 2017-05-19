// Implementation of the Fraud Detector class
#include "FraudDetector.h"

// For readability
#define LEFT true
#define RIGHT false

// Fraud Detector initialisation method - create a new fraud detector with specified type
FraudDetector::FraudDetector(detectorTypeID i) {
    typeID = i;
}

// Set the Fraud Detector's decision tree - the one it will use to make classifications
void FraudDetector::setTree(DecisionTree * t) {
    tree = t;
}

// Simple function to check the structure of the Fraud Dectector's decision tree
void FraudDetector::showTree() {
    tree->showTree();
}

// Construct the decision tree based on calculations made ealier in the project
void FraudDetector::constructTree(vector<DecisionTree> &nodes) {
    // Create the tree's nodes (refer to Decision Tree diagram for more information)
    DecisionTree * node1 = new DecisionTree(1, VENDOR_TYPE);
    DecisionTree * node2 = new DecisionTree(2, ONLINE_THRESHOLD);
    DecisionTree * node3 = new DecisionTree(3, VOLUME_DISTANCE);
    DecisionTree * node4 = new DecisionTree(4, LOCATION);
    DecisionTree * node5 = new DecisionTree(5, ONLINE_CHANGE);
    DecisionTree * node6 = new DecisionTree(6, VOLUME_DISTANCE);
    DecisionTree * node7 = new DecisionTree(7, FREQUENCY_THRESHOLD);
    DecisionTree * node8 = new DecisionTree(8, VOLUME_THRESHOLD);
    DecisionTree * nodeI = new DecisionTree(9, LEAF_NOT_FRAUD);
    DecisionTree * nodeII = new DecisionTree(10, LEAF_FRAUD);
    DecisionTree * nodeIII = new DecisionTree(11, LEAF_NOT_FRAUD);
    DecisionTree * nodeIV = new DecisionTree(12, LEAF_FRAUD);
    DecisionTree * nodeV = new DecisionTree(13, LEAF_NOT_FRAUD);
    DecisionTree * nodeVI = new DecisionTree(14, LEAF_NOT_FRAUD);
    DecisionTree * nodeVII = new DecisionTree(15, LEAF_NOT_FRAUD);
    DecisionTree * nodeVIII = new DecisionTree(16, LEAF_FRAUD);
    DecisionTree * nodeIX = new DecisionTree(17, LEAF_NOT_FRAUD);
    
    // Ensure nodes stay in system scope for the duration of the program
    nodes.push_back(* node1);
    nodes.push_back(* node2);
    nodes.push_back(* node3);
    nodes.push_back(* node4);
    nodes.push_back(* node5);
    nodes.push_back(* node6);
    nodes.push_back(* node7);
    nodes.push_back(* node8);
    nodes.push_back(* nodeI);
    nodes.push_back(* nodeII);
    nodes.push_back(* nodeIII);
    nodes.push_back(* nodeIV);
    nodes.push_back(* nodeV);
    nodes.push_back(* nodeVI);
    nodes.push_back(* nodeVII);
    nodes.push_back(* nodeVIII);
    nodes.push_back(* nodeIX);

    // Make node connections
    node1->addChild(LEFT, node2);
    node1->addChild(RIGHT, node3);
    node2->addChild(LEFT, node4);
    node2->addChild(RIGHT, node5);
    node3->addChild(LEFT, nodeI);
    node3->addChild(RIGHT, nodeII);
    node4->addChild(LEFT, nodeIII);
    node4->addChild(RIGHT, nodeIV);
    node5->addChild(LEFT, nodeV);
    node5->addChild(RIGHT, node6);
    node6->addChild(LEFT, node7);
    node6->addChild(RIGHT, nodeVI);
    node7->addChild(LEFT, node8);
    node7->addChild(RIGHT, nodeVII);
    node8->addChild(RIGHT, nodeVIII);
    node8->addChild(LEFT, nodeIX);

    // Set the fraud detector's root node
    setTree(node1);
}

// Given a new transaction, classify it's fraudulence
bool FraudDetector::detect(transaction t, Customer c) {
    return tree->classify(t, c);
}
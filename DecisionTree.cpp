// Implementation of the Decision Tree fraud detection class
#include "DecisionTree.h"

// Function prototypes for decision routines based on each attribute
bool decide_vendorType(transaction t, Customer c);
bool decide_location(transaction t, Customer c);
bool decide_volumeThreshold(transaction t, Customer c);
bool decide_volumeDistance(transaction t, Customer c);
bool decide_frequencyThreshold(transaction t, Customer c);
bool decide_frequencyDistance(transaction t, Customer c);
bool decide_onlineThreshold(transaction t, Customer c);
bool decide_onlineChange(transaction t, Customer c);

// Create a new decision tree node
DecisionTree::DecisionTree(int nID, nodeTypeID tID) {
    nodeID = nID;
    typeID = tID;
}

// Add a new child to a decision tree node either on the left or on the right
void DecisionTree::addChild(bool left, DecisionTree * c) {
    if(left) {
        children[0] = c;
    } else {
        children[1] = c;
    }
}

// Make the classification - will either involve calling the function recursively on one of the children or returning the classification if this node is a leaf
bool DecisionTree::classify(transaction t, Customer c) {
    bool ret;
    bool choose_child;
    switch(typeID) {
        case VENDOR_TYPE:
            choose_child = decide_vendorType(t, c);
            ret = classify_child(choose_child, t, c);
            break;
        case LOCATION:
            choose_child = decide_location(t, c);
            ret = classify_child(choose_child, t, c);
            break;
        case VOLUME_THRESHOLD:
            choose_child = decide_volumeThreshold(t, c);
            ret = classify_child(choose_child, t, c);
            break;
        case VOLUME_DISTANCE:
            choose_child = decide_volumeDistance(t, c);
            ret = classify_child(choose_child, t, c);
            break;
        case FREQUENCY_THRESHOLD:
            choose_child = decide_frequencyThreshold(t, c);
            ret = classify_child(choose_child, t, c);
            break;
        case FREQUENCY_DISTANCE:
            choose_child = decide_frequencyDistance(t, c);
            ret = classify_child(choose_child, t, c);
            break;
        case ONLINE_THRESHOLD:
            choose_child = decide_onlineThreshold(t, c);
            ret = classify_child(choose_child, t, c);
            break;
        case ONLINE_CHANGE:
            choose_child = decide_onlineChange(t, c);
            ret = classify_child(choose_child, t, c);
            break;
        case LEAF_FRAUD:
            ret = true;
            break;
        case LEAF_NOT_FRAUD:
            ret = false;
            break;
    }
    return ret;
}

// Given a boolean indicating whether we need to choose the left or right child, call classify recursively
bool DecisionTree::classify_child(bool left, transaction t, Customer c) {
    bool ret;
    ret = left ? children[0]->classify(t, c) : children[1]->classify(t, c);
    return ret;
}

// Choose left child or right child based on vendor type (in list, not in list)
bool decide_vendorType(transaction t, Customer c) {
    return false;
}

// Choose left child or right child based on location (in list, not in list)
bool decide_location(transaction t, Customer c) {
    return false;
}

// Choose left child or right child based on volume threshold (under, over)
bool decide_volumeThreshold(transaction t, Customer c) {
    return false;
}

// Choose left child or right child based on volume distance (near, far)
bool decide_volumeDistance(transaction t, Customer c) {
    return false;
}

// Choose left child or right child based on frequency threshold (under, over)
bool decide_frequencyThreshold(transaction t, Customer c) {
    return false;    
}

// Choose left child or right child based on frequency distance (near, far)
bool decide_frequencyDistance(transaction t, Customer c) {
    return false;
}

// Choose left child or right child based on online threshold (under, over)
bool decide_onlineThreshold(transaction t, Customer c) {
    return false;
}

// Choose left child or right child based on online change (increase, decrease)
bool decide_onlineChange(transaction t, Customer c) {
    return false;
}
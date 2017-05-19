// Implementation of the Decision Tree fraud detection class
#include "DecisionTree.h"

// For readability
#define LEFT true
#define RIGHT false
#define FRAUD true
#define NOT_FRAUD false
#define CHILDREN_CONNECTED 2
#define INDICATE_WHEN_DECIDING 0

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
    leftChild = NULL;
    rightChild = NULL;
}

// Add a new child to a decision tree node either on the left or on the right
void DecisionTree::addChild(bool left, DecisionTree * c) {
    if(left) {
        leftChild = c;
    } else {
        rightChild = c;
    }
}

// Sanity check method for making sure tree has been constructed correctly
void DecisionTree::showTree() {
    sayHi();
    //cout << "Hi \n";
    if((typeID != LEAF_FRAUD) && (typeID != LEAF_NOT_FRAUD)) {
        if(leftChild && rightChild) {
            leftChild->showTree();
            rightChild->showTree();
        }     
    }
}

// Make the classification - will either involve calling the function recursively on one of the children or returning the classification if this node is a leaf
bool DecisionTree::classify(transaction t, Customer c) {
    bool ret;
    bool choose_child;

    #if INDICATE_WHEN_DECIDING == 1
    cout << "Node " << to_string(nodeID) << " deciding!\n";
    #endif

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
            ret = FRAUD;
            break;
        case LEAF_NOT_FRAUD:
            ret = NOT_FRAUD;
            break;
    }
    return ret;
}

// Given a boolean indicating whether we need to choose the left or right child, call classify recursively
bool DecisionTree::classify_child(bool left, transaction t, Customer c) {
    bool ret;
    ret = left ? leftChild->classify(t, c) : rightChild->classify(t, c);
    return ret;
}

// Choose left child or right child based on vendor type (in list, not in list)
bool decide_vendorType(transaction t, Customer c) {
    CustomerProfile * profile = c.getProfile();
    vendorType v = t.vendor;
    bool inList;

    inList = profile->check_vendor_in_list(v);

    if(inList) {
        return LEFT;
    } else {
        return RIGHT;
    }
}

// Choose left child or right child based on location (in list, not in list)
bool decide_location(transaction t, Customer c) {
    CustomerProfile * profile = c.getProfile();
    int location = t.postcode;
    bool inList;

    inList = profile->check_location_in_list(location);

    if(inList) {
        return LEFT;
    } else {
        return RIGHT;
    }
}

// Choose left child or right child based on volume threshold (under, over)
bool decide_volumeThreshold(transaction t, Customer c) {
    CustomerProfile * profile = c.getProfile();
    float volume = (float) t.value;
    bool isUnder;

    isUnder = profile->check_volume_threshold(volume);

    if(isUnder) {
        return LEFT;
    } else {
        return RIGHT;
    }
}

// Choose left child or right child based on volume distance (near, far)
bool decide_volumeDistance(transaction t, Customer c) {
    CustomerProfile * profile = c.getProfile();
    float volume = (float) t.value;
    bool isNear;

    isNear = profile->check_volume_distance(volume);

    if(isNear) {
        return LEFT;
    } else {
        return RIGHT;
    }
}

// Choose left child or right child based on frequency threshold (under, over)
bool decide_frequencyThreshold(transaction t, Customer c) {
    CustomerProfile * profile = c.getProfile();
    int day = t.day.day;
    int lastDay = c.getLastDay();
    int timeDifference = day - lastDay;
    bool isUnder;

    if(timeDifference < 0) {
        timeDifference = timeDifference + 365;
    }

    isUnder = profile->check_frequency_threshold(timeDifference);

    if(isUnder) {
        return RIGHT;
    } else {
        return LEFT;
    }
}

// Choose left child or right child based on frequency distance (near, far)
bool decide_frequencyDistance(transaction t, Customer c) {
    CustomerProfile * profile = c.getProfile();
    int day = t.day.day;
    int lastDay = c.getLastDay();
    int timeDifference = day - lastDay;
    bool isNear;

    if(timeDifference < 0) {
        timeDifference = timeDifference + 365;
    }

    isNear = profile->check_frequency_distance(timeDifference);

    if(isNear) {
        return LEFT;
    } else {
        return RIGHT;
    }
}

// Choose left child or right child based on online threshold (under, over)
bool decide_onlineThreshold(transaction t, Customer c) {
    // How this is done: we take the n most recent transactions in the user's history, and comapre this with the user's overall online purchase percentage
    CustomerProfile * profile = c.getProfile();
    TransactionHistory * h = c.getHistory();
    bool isUnder = profile->check_recent_online_purchase_percentage(t, h);

    if(isUnder) {
        return RIGHT;
    } else {
        return LEFT;
    }
}

// Choose left child or right child based on online change (increase, decrease)
bool decide_onlineChange(transaction t, Customer c) {
    CustomerProfile * profile = c.getProfile();
    float currentPercentage = profile->getOnlinePercentage();
    int currentNumTransactions = c.getNumTransactions();
    int numOnline = c.getNumOnlineTransactions();

    // If this transaction was made online, add one to the current number of online transactions for the customer
    if(t.online) {
        numOnline++;
    }

    // Account for new transaction
    currentNumTransactions++;

    // Calculate new percentage of transactions made online, accounting for newly received transaction
    float newPercentage = (float) numOnline / (float) currentNumTransactions;

    // Decide which child we need to choose
    if(newPercentage <= currentPercentage) {
        return RIGHT;
    } else {
        return LEFT;
    }
}
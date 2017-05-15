// Implementation of the Fraud Detector class
#include "FraudDetector.h"

// Fraud Detector initialisation method - create a new fraud detector with specified type
FraudDetector::FraudDetector(detectorTypeID i) {
    typeID = i;
}

// Set the Fraud Detector's decision tree - the one it will use to make classifications
void FraudDetector::setTree(DecisionTree * t) {
    tree = t;
}
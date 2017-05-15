// Implementation of the Fraud Detector class
#include "FraudDetector.h"

// Fraud Detector initialisation method - create a new fraud detector with specified type
FraudDetector::FraudDetector(detectorTypeID i) {
    typeID = i;
    tree = new DecisionTree();
}
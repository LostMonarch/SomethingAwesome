// Fraud Detector class declaraction - the fraud detector is the instruments which performs the fraud analysis itself, using either a decision tree or logistic regression
#ifndef FRAUD_DETECTOR_H_
#define FRAUD_DETECTOR_H_

#include "DecisionTree.h"

using namespace std;

typedef enum detectors {
    DECISION_TREE,
    LOGISTIC_REGRESSION
} detectorTypeID;

class FraudDetector {
    public:
        FraudDetector(detectorTypeID i);
        void setTree(DecisionTree * t);
        void constructTree(vector<DecisionTree> &nodes);
        void showTree();
        bool detect(transaction t, Customer c);
    private:
        DecisionTree * tree;
        detectorTypeID typeID;
};

#endif
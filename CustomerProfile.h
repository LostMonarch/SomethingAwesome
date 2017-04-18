#include <string>
#include <iostream>
#include <vector>

#include "transaction.h"

// CustomerProfile class declaration
using namespace std;

#ifndef CUSTOMER_PROFILE_H_
#define CUSTOMER_PROFILE_H_

class CustomerProfile {
    public:
        void update(transaction t);
    private:
        int postcode;
        float averageSpend;
        float averageFrequency;
        float onlinePurchasePercentage;
        vector<vendorType> vendors;
};

#endif
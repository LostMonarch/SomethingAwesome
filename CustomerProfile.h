#include <string>
#include <iostream>
#include <vector>

#include "transaction.h"
#include "transactionHistory.h"

// CustomerProfile class declaration
using namespace std;

#ifndef CUSTOMER_PROFILE_H_
#define CUSTOMER_PROFILE_H_

class CustomerProfile {
    public:
        CustomerProfile(int p);
        int getPostcode() { return postCode; };
        float getOnlinePercentage() { return onlinePurchasePercentage; };
        void update(transaction t);
        void fill(float spendAverage, float freqAverage, float onlinePercentage, vector<vendorType> &vendorList, vector<int> &codeList);
        bool check_vendor_in_list(vendorType v);
        bool check_location_in_list(int p);
        bool check_volume_threshold(float v);
        bool check_volume_distance(float v);
        bool check_frequency_threshold(int dt);
        bool check_frequency_distance(int dt);
        bool check_recent_online_purchase_percentage(transaction t, TransactionHistory * h);
    private:
        int postCode;
        float averageSpend;
        float averageFrequency;
        float onlinePurchasePercentage;
        vector<vendorType> vendors;
        vector<int> postcodes;
        int getlastDay();
};

#endif
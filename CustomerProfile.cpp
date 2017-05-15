// CustomerProfile class implementation
#include "CustomerProfile.h"

// Initialise a new customer profile with default values for each parameter
CustomerProfile::CustomerProfile(int p) {
    postCode = p;
    averageSpend = 0;
    averageFrequency = 0;
    onlinePurchasePercentage = 0;
}

// Fill a customer profile with values for each parameter calculated during the customer profiling phase
void CustomerProfile::fill(float spendAverage, float freqAverage, float onlinePercentage, vector<vendorType> &vendorList, vector<int> &codeList) {
    averageSpend = spendAverage;
    averageFrequency = freqAverage;
    onlinePurchasePercentage = onlinePercentage;
    vendors = vendorList;
    postcodes = codeList;
}

// Check whether or not a given vendor type is in this customer's list of frequently visited vendor types
bool CustomerProfile::check_vendor_in_list(vendorType v) {
    if(find(vendors.begin(), vendors.end(), v) != vendors.end()){
        return true;
    } else {
        return false;
    }
}

// Check whether or not a given location is in this customer's list of frequently visited locations
bool CustomerProfile::check_location_in_list(int p) {
    if(find(postcodes.begin(), postcodes.end(), p) != postcodes.end()){
        return true;
    } else {
        return false;
    }
}

// Check whether a given transaction volume is under or over the customer's average spend per transaction
bool CustomerProfile::check_volume_threshold(float v) {
    if(v < averageSpend) {
        // The transaction volume is under the customer's average
        return false;
    } else if(v == averageSpend) {
        // The transaction volume is equal to the customer's average
        return false;
    } else {
        // The transaction volume is over the customer's average
        return true;
    }
}
// CustomerProfile class implementation
#include "CustomerProfile.h"
#include <math.h>

// For readability
#define VOLUME_DISTANCE_THRESHOLD_PERCENTAGE 40 // Somewhat arbitrary value, could be optimised further

#define IN_LIST true
#define NOT_IN_LIST false
#define UNDER true
#define OVER false
#define NEAR true
#define FAR false

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
        return IN_LIST;
    } else {
        return NOT_IN_LIST;
    }
}

// Check whether or not a given location is in this customer's list of frequently visited locations
bool CustomerProfile::check_location_in_list(int p) {
    if(find(postcodes.begin(), postcodes.end(), p) != postcodes.end()){
        return IN_LIST;
    } else {
        return NOT_IN_LIST;
    }
}

// Check whether a given transaction volume is under or over the customer's average spend per transaction
bool CustomerProfile::check_volume_threshold(float v) {
    if(v < averageSpend) {
        // The transaction volume is under the customer's average
        return UNDER;
    } else if(v == averageSpend) {
        // The transaction volume is equal to the customer's average
        return UNDER;
    } else {
        // The transaction volume is over the customer's average
        return OVER;
    }
}

// Check whether a given transaction volume is 'near' the customer's average or 'far' from the customer's average
bool CustomerProfile::check_volume_distance(float v) {
    float difference = fabs(v - averageSpend);
    float distance_percentage = (difference / averageSpend) * 100;

    if(distance_percentage <= VOLUME_DISTANCE_THRESHOLD_PERCENTAGE) {
        // The transaction volume is 'near' the customer's average if it is within 40% of the average itself
        return NEAR;
    } else {
        // The transaction volume is 'far' from the customer's average if it is more than 40% greater than or less than the average itself
        return FAR;
    }
}
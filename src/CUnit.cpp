#pragma once
#include "../includes/CUnit.h"

using namespace std;

/** Constructor **/
CUnit::CUnit() {}

/** Destructor **/
CUnit::~CUnit() {}

/** Calculate the residence time(tested) **/
double CUnit::calculate_residence(double *feed_new) {
    double phi = 0.1;
    double volume = 10;
    double rho = 3000;
    double sum_feed = feed_new[0] + feed_new[1];
    return phi * volume / (sum_feed / rho);
}

/** Calculate the recovery of gormanium(tasted) **/
double CUnit::calculate_recovery_g(double residence_time) {
    double k_g = 0.005;
    return k_g * residence_time / (1 + k_g * residence_time);
}

/** Calculate the recovery of waste(tasted) **/
double CUnit::calculate_recovery_w(double residence_time) {
    double k_w = 0.0005;
    return k_w * residence_time / (1 + k_w * residence_time);
}

/** Calculate the concentration and tailing stream **/
void CUnit::calculate_stream() {
//    cout << this->feed_new[0] << " " << this->feed_new[1] << endl;
    double residence_time = calculate_residence(this->feed_new);
    double R_g = calculate_recovery_g(residence_time);
    double R_w = calculate_recovery_w(residence_time);

    // Calculate the gormanium out from the concentration
    conc_out[0] = feed_new[0] * R_g;
    // Calculate the waste out from the concentration
    conc_out[1] = feed_new[1] * R_w;

    // Calculate the gormanium out from the tailing
    tail_out[0] = feed_new[0] - conc_out[0];
    // Calculate the watse out from the tailing
    tail_out[1] = feed_new[1] - conc_out[1];
}

/** Update the feed stream **/
void CUnit::update_feed() {
    for (int i = 0; i < 2; ++i) {
        feed_old[i] = feed_new[i];
    }
}

/** Initialize the feed stream for the next generation **/
void CUnit::zero_feed() {
    for (int i = 0; i < 2; ++i) {
        feed_new[i] = 0;
    }
}
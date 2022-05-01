#pragma once

class CUnit {
public:
    int conc_num = -1;   // index of the unit to which this unit’s concentrate stream is connected
    int tails_num = -1;  // index of the unit to which this unit’s concentrate stream is connected
    bool mark = false;  // A Boolean that is changed to true if the unit has been seen

    double feed_new[2] = {0}; // the current feed of the unit, 0 for gormanium and 1 for waste
    double feed_old[2] = {0}; // the old/previous feed of the unit, 0 for gormanium and 1 for waste

    double conc_out[2] = {0}; // the concentrate output from the unit(both the gormanium and the waste)
    double tail_out[2] = {0}; // the tail output from this unit(both the gormanium and the waste)


    /** Constructor **/
    CUnit();

    /** Destructor **/
    ~CUnit();

    /** Calculate the residence time **/
    double calculate_residence(double *feed_new);

    /** Calculate the recovery of gormanium **/
    double calculate_recovery_g(double residence_time);

    /** Calculate the recovery of waste **/
    double calculate_recovery_w(double residence_time);

    /** Calculate the concentrate and tailing stream out from the unit **/
    void calculate_stream();

    /** Update feed stream **/
    void update_feed();

    /** Initialize the feed stream for the next generation **/
    void zero_feed();

};


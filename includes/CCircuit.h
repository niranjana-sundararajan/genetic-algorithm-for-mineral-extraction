#pragma once

#include "CUnit.h"
#include <vector>

using namespace std;
// We temporarily set the number of units to 10(can be changed)
const int num_units = 10;

class CCircuit {
public:
    int num_units = 10;   // the number of units in the circuit
    double pay = 100; //  the pay for gormanium per kg
    double penalty = 500; // the penalty for waste peer kg
    double gormanium_in = 10;
    double waste_in = 100;
    CUnit *units = nullptr; // the array for units in circuit

    int outlet_conc = -1;    // the id of the last unit of the conc
    int outlet_tail = -1;    // the id of the last unit of the tail

    double purity;
    double recovery;

    /** Constructor **/
    CCircuit();

    CCircuit(int num_units);

    CCircuit(int num_units, double g_in, double w_in, double pay, double penalty);

    /** Destructor **/
    ~CCircuit();

    /** Mark the units using recursion **/
    void mark_units(int unit_num);

    /** Reset all marks to false before each validity test **/
    void mark_false();

    /** Initialize the current circuit **/
    void Initialize(int *circuit_vector);

    /** Calculate the fitness value **/
    double Evaluate_Circuit(int *circuit_vector, double tolerance, int max_iterations);

    /** Calculate the difference **/
    double calculate_difference(int i);

    /** Check whether the circuit is valid or not **/
    bool Check_Validity(int *circuit_vector);
};


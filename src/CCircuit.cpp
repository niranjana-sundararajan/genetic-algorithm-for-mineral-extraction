#pragma once

#include <vector>
#include <iostream>
#include "../includes/CUnit.h"
#include "../includes/CCircuit.h"

using namespace std;

/** Constructor **/
CCircuit::CCircuit() {
    int total_num_units = this->num_units + 2;
    this->outlet_tail = this->num_units + 1;
    this->outlet_conc = this->num_units;
    units = new CUnit[total_num_units];
}

CCircuit::CCircuit(int num_units) {
    this->num_units = num_units;
    int total_num_units = num_units + 2;
    this->outlet_tail = num_units + 1;
    this->outlet_conc = num_units;
    units = new CUnit[total_num_units];
}

CCircuit::CCircuit(int num_units, double g_in, double w_in, double pay, double penalty) {
    this->num_units = num_units;
    this->gormanium_in = g_in;
    this->waste_in = w_in;
    this->pay = pay;
    this->penalty = penalty;
    int total_num_units = num_units + 2;
    this->outlet_tail = num_units + 1;
    this->outlet_conc = num_units;
    units = new CUnit[total_num_units];
}

/** Destructor **/
CCircuit::~CCircuit() {
    delete[] units;
}

// Set the vector of objects(units)
vector<CUnit> units(num_units);

/** Give an initial guess for the feed rate of both components to
 * every cell in the circuit(beyond the last two units)
 * **/
void CCircuit::Initialize(int *circuit_vector) {
    int total_num_units = this->num_units + 2;
    for (int i = 0; i < total_num_units; ++i) {
        if (i >= this->num_units) {
            units[i].conc_num = -1;
            units[i].tails_num = -1;
        } else {
            // Calculate the index of the destination of concentrate
            units[i].conc_num = circuit_vector[2 * i + 1];
            // Calculate the index of the destination of tailing
            units[i].tails_num = circuit_vector[2 * (i + 1)];

            // Initial feed for each unit
            units[i].feed_new[0] = this->gormanium_in;
            units[i].feed_new[1] = this->waste_in;
            units[i].mark = false;
        }
    }
}

void CCircuit::mark_units(int unit_num) {
    // Exit if we have seen this unit already
    if (units[unit_num].mark)
        return;
    // Mark that we have now seen the unit
    units[unit_num].mark = true;

    // If conc_num does not point at a circuit outlet, recursively call the function for the concentrate unit
    if (units[unit_num].conc_num < num_units)
        mark_units(units[unit_num].conc_num);
        // The conc_num point at a circuit outlet, the unit doesn't have the conc_num
        // We only need to mark the unit
    else
        units[units[unit_num].conc_num].mark = true;

    // If tails_num does not point at a circuit outlet, recursively call the function for the tailing unit
    if (units[unit_num].tails_num < num_units)
        mark_units(units[unit_num].tails_num);
        // The tails_num point at a circuit outlet, the unit doesn't have the tails_num
        // We only need to mark the unit
    else
        units[units[unit_num].tails_num].mark = true;
}

/** Reset all marks to false before each validity test **/
void CCircuit::mark_false() {
    for (int i = 0; i < this->num_units + 2; i++) {
        this->units[i].mark = false;
    }
}

double CCircuit::Evaluate_Circuit(int *circuit_vector, double tolerance, int max_iterations) {
//    print_array(circuit_vector);
    // Initialize
    Initialize(circuit_vector);

    //do iteration
    int iter = 0;
    // the flag to check whether it is convergent
    bool is_converged = false;

    double max_rel_diff = 0;

    // When the number of iteration smaller than the max number of iteration
    // and the difference is bigger than the tolerance, we should do the iteration
    while (iter < max_iterations && is_converged == false) {
        /** Update the old table and the new table **/
        for (int i = 0; i < this->num_units; i++) {
            units[i].calculate_stream();    // Calculate the stream out of each unit(both the gormanium and the waste)
            units[i].update_feed(); // Update the feed array to the old table,
            // we will use the old table and the new table to calculate the difference,
            // and then use the difference to check whether it is convergent.
            units[i].zero_feed();   // Update the feed array to the new table(set them to zero)
        }

        /** Update the feed of the last two units to zero**/
        units[num_units].zero_feed();   // the concentrate final unit
        units[num_units + 1].zero_feed();   // the tailing final unit

        /** Add the mass of feed out of the circuit(both gormanium and waste, only unit0) **/
        units[circuit_vector[0]].feed_new[0] = this->gormanium_in;  // set the feed rate of gormanium = 10kg/s
        units[circuit_vector[0]].feed_new[1] = this->waste_in;  // set the feed rate of waste = 100kg/s

        /** Update the mass of feed(both gormanium and waste) **/
        for (int i = 0; i < num_units; i++) {
            for (int j = 0; j < 2; j++) {
                // feed_g = C_g + T_g and feed_w = C_w + T_w
                units[units[i].conc_num].feed_new[j] += units[i].conc_out[j];
                units[units[i].tails_num].feed_new[j] += units[i].tail_out[j];
            }
        }

        /** Calculate the difference and check whether it is convergent **/
        // Calculate the difference of each unit and find the max difference
        max_rel_diff = calculate_difference(0);
        for (int i = 0; i < num_units; i++) {
            max_rel_diff = max(max_rel_diff, calculate_difference(i));
        }
        // Check whether it is convergent by comparing the max difference to the tolerance
        if (max_rel_diff < tolerance) {
            is_converged = true;
        }
        iter++;
    }

    /** Calculate the fitness value **/
    double fitness_value = 0;
    if (!is_converged) {
        fitness_value = this->penalty * (-waste_in);
    }
        // it is convergent, so we need to calculate the fitness value and return it to the GA method
    else {
        fitness_value = units[num_units].feed_new[0] * this->pay - units[num_units].feed_new[1] * this->penalty;
        this->purity = units[num_units].feed_new[0] / (units[num_units].feed_new[0] + units[num_units].feed_new[1]);
        this->recovery = units[num_units].feed_new[0] / this->gormanium_in;
    }
    return fitness_value;
}

double CCircuit::calculate_difference(int i) {
    double rel_diff_g = abs((units[i].feed_new[0]) - (units[i].feed_old[0])) / abs((units[i].feed_old[0]));
    double rel_diff_w = abs((units[i].feed_new[1]) - (units[i].feed_old[1])) / abs((units[i].feed_old[1]));
    return max(rel_diff_g, rel_diff_w);
}

bool CCircuit::Check_Validity(int *circuit_vector) {
    bool validity = true;

    // Set the unit with inital values
    Initialize(circuit_vector);

    // Start Search Unit
    int start_search = circuit_vector[0];

    //--------------------------------------------------------------
    // CONDITION 1 : Check whether all units are accessible from feed
    mark_units(start_search);
    for (int i = 0; i < this->num_units; i++) {
        if (units[i].mark == false) {

            validity = false;   // The unit is invalid
        }
    }

    //--------------------------------------------------------------
    // CONDITION 2 : Check whether all units have a route forward to both outlet streams
    // This check recursively marks concentrate and tails in each iteration
    for (int i = 0; i < this->num_units; i++) {
        // Rest marks to false
        mark_false();

        // Mark concentrate and tails of the current unit
        mark_units(i);
        // Forward to Outlet test
        if (units[this->outlet_conc].mark == false || units[this->outlet_tail].mark == false) {
            validity = false;   // The unit is invalid
        }
    }

    //--------------------------------------------------------------
    // CONDITION 3 : There should be no self-recycle
    for (int i = 0; i < this->num_units; i++) {
        // Self Recycle Test
        if (units[i].conc_num == i || units[i].tails_num == i) {
            validity = false;   // The unit is invalid
        }
    }
    //--------------------------------------------------------------
    // CONDITION 4 : Destination for both products must not be same
    for (int i = 0; i < this->num_units; i++) {
        // Check destination of cuurent unit
        if (units[i].tails_num == units[i].conc_num) {
            validity = false;   // The unit is invalid
        }
    }

    return validity;

}

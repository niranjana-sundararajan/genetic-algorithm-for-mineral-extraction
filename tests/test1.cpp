#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"

using namespace std;

int main(int argc, char *argv[]) {
    int num_units = -1;
    cout << "---------------------------------" << endl;
    cout << "Test : Calculate Fitness Value Function" << endl;
    cout << "---------------------------------" << endl;
    int test_vector1[11] = {4, 5, 1, 2, 4, 0, 1, 1, 6, 1, 3};
    num_units = (sizeof(test_vector1) / sizeof(test_vector1[0]) - 1) / 2;
    CCircuit cCircuit_1 = CCircuit(num_units);
    cout << "Calculate_fitness({4, 5, 1, 2, 4, 0, 1, 1, 6, 1, 3}):" << endl;
    cout << "The fitness value calculated is: " << cCircuit_1.Evaluate_Circuit(test_vector1, 1e-6, 100)
         << " and the value should be: " << 107.204 << endl;
    cout << "---------------------------------" << endl;

    int test_vector2[21] = {0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
                            10, 11, 10, 11, 10, 11, 10, 11};
    num_units = (sizeof(test_vector2) / sizeof(test_vector2[0]) - 1) / 2;
    CCircuit cCircuit_2 = CCircuit(num_units);
    cout << "Calculate_fitness({0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9, 10, 11, 10, 11, 10, 11, 10, 11}):" << endl;
    cout << "The fitness value calculated is: " << cCircuit_2.Evaluate_Circuit(test_vector2, 1e-6, 100) << endl;
    cout << "---------------------------------" << endl;

    int test_vector3[21] = {0, 1, 11, 2, 11, 3, 11, 4, 11, 5, 11, 6, 11,
                            7, 11, 8, 11, 9, 11, 10, 11};
    num_units = (sizeof(test_vector3) / sizeof(test_vector3[0]) - 1) / 2;
    CCircuit cCircuit_3 = CCircuit(num_units);
    cout << "Calculate_fitness({0, 1, 11, 2, 11, 3, 11, 4, 11, 5, 11, 6, 11, 7, 11, 8, 11, 9, 11, 10, 11}):" << endl;
    cout << "The fitness value calculated is: " << cCircuit_3.Evaluate_Circuit(test_vector3, 1e-6, 100) << endl;
    cout << "---------------------------------" << endl;

    int test_vector4[21] = {7, 8, 2, 4, 8, 3, 9, 0, 5, 2, 7, 3, 7, 9, 0, 2, 3, 9, 7, 0, 3};
    num_units = (sizeof(test_vector3) / sizeof(test_vector3[0]) - 1) / 2;
    CCircuit cCircuit_4 = CCircuit(num_units);
    cout << "Calculate_fitness({7, 8, 2, 4, 8, 3, 9, 0, 5, 2, 7, 3, 7, 9, 0, 2, 3, 9, 7, 0, 3}):" << endl;
    cout << "The fitness value calculated is: " << cCircuit_4.Evaluate_Circuit(test_vector4, 1e-6, 100) << endl;
    cout << "---------------------------------" << endl;

    cout << endl << endl;
    cout << "---------------------------------" << endl;
    cout << "Test : Check Validity Function" << endl;
    cout << "---------------------------------" << endl;

    int valid[3] = {0, 1, 2};
    int invalid[3] = {0, 2, 2};
    int test_circuit[] = {4, 5, 1, 2, 4, 0, 1, 1, 6, 1, 3};


    cout << "Check_Validity({0,1,2}):" << endl;
    CCircuit tmp_ccircuit1 = CCircuit(1, 10, 100, 100, 500);
    if (tmp_ccircuit1.Check_Validity(valid))
        cout << "Validity test has passed!" << endl;
    else
        cout << "VALIDITY TEST HAS FAILED!" << endl;
    cout << "---------------------------------" << endl;

    cout << "Check_Validity({0,2,2}):" << endl;
    CCircuit tmp_ccircuit2 = CCircuit(1, 10, 100, 100, 500);
    if (tmp_ccircuit2.Check_Validity(invalid))
        cout << "Validity test has passed!" << endl;
    else
        cout << "VALIDITY TEST HAS FAILED!" << endl;
    cout << "---------------------------------" << endl;

    cout << "Check_Validity({4, 5, 1, 2, 4, 0, 1, 1, 6, 1, 3}):" << endl;
    num_units = (sizeof(test_circuit) / sizeof(test_circuit[0]) - 1) / 2;
    CCircuit tmp_ccircuit3 = CCircuit(num_units, 10, 100, 100, 500);
    if (tmp_ccircuit3.Check_Validity(test_circuit))
        cout << "Validity test has passed!" << endl;
    else
        cout << "VALIDITY TEST HAS FAILED!" << endl;
    cout << "---------------------------------" << endl;
}

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "CUnit.cpp"
#include "CCircuit.cpp"
#include "Genetic_Algorithm.cpp"
#include <random>
#include <chrono>

using namespace std;

void plot_purity(int *vec){
    CCircuit tem = CCircuit(num_units);
    double fitness_val = tem.Evaluate_Circuit(vec, 1e-7, 1000);
    cout << "The num_untis :   " << num_units << endl;
    cout << "The F_g is :      " << tem.gormanium_in << endl;
    cout << "The F_w is :      " << tem.waste_in << endl;
    cout << "The C_g is :      " << tem.recovery * tem.gormanium_in << endl;
    cout << "The C_w is :      " << tem.recovery * tem.gormanium_in/tem.purity - tem.recovery * tem.gormanium_in << endl;
    cout << "The recovery is : " << tem.recovery << endl;
    cout << "The purity is :   " << tem.purity << endl;

}

int main(int argc, char* argv[]) {
    srand(time(0));
    int best_sol[2 * num_units + 1];

    // int num_omp = 4;

    // for (int i=0;i<argc - 1;i++)
    // {
    //     if (strcmp(argv[i], "-num_omp") == 0)
    //         num_omp = stoi(argv[i+1]);
    // }

    // omp_set_num_threads(num_omp);
    solution sol = solution();
    // int cnt = 0;
    // for (int i = 0; i < 10; i++)
    // {
    //     sol.Genetic_algorithm(best_sol, num_units);
    //     cout << sol.fitness_value << endl;
    //     if(abs(sol.fitness_value-375.497) < 0.1) cnt++;//375.497
    // }
    // cout << "The final count is " << cnt << endl;
    
    auto t1 = chrono::high_resolution_clock::now();
    sol.Genetic_algorithm(best_sol, num_units);
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(t2 - t1);
    cout << "The total time is " << duration.count() << " seconds "<< endl;
    // plot_purity(best_sol);

    // omp_set_num_threads(4);
    // #pragma omp parallel for 
    //     for (int i = 0; i < 10; i++)
    //     {
    //         cout << i << endl;
    //     }
    
    // double a = 0.986513;
    // double b = 0.403047;
    // cout << "The C_g is :      " << b * 10 << endl;
    // cout << "The C_w is :      " << b * 10/a - b * 10 << endl;
    // cout << 100 * b * 10 - 500 * (b * 10/a - b * 10);
    return 0;
}

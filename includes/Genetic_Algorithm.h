#pragma once

#include <vector>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <iostream>

// The number of circuits vectors in the set
const int NUM_VEC = 100;
// The rate of cross over.
const double CROSSOVER_RATE = 0.95;
// The rate of mutation.
const double MUTATION_RATE = 0.01;
// The maximum number of iteration
const int MAX_ITERATION = 10000;

// Solution class, store the vector and fitness value
class solution {
public:
    int *circuits_vector;
    double fitness_value;

    /** Constructor **/
    solution();

    /** Destructor **/
    ~solution();

    void initial_allocation(solution *pop, int num_units);

    void free_memory(solution *pop);

    double random_01();

    int select(solution *pop);

    void cross_over(solution *circuits_set, solution &child_1, solution &child_2);

    void mutation(solution &circuits_set);

    void Genetic_algorithm(int *sol, int num_units);

    void copy_solution(solution &sol1, solution &sol2);

    void buble_sort(solution *circuits_set);

    void write_file(int *res_vec, double res_val);

};
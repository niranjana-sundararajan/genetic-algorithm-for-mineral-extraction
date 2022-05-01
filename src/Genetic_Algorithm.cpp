#pragma once

#include "../includes/Genetic_Algorithm.h"
#include "../includes/CUnit.h"
#include "../includes/CCircuit.h"
#include <fstream>
#include <omp.h>
// #include <stdio.h>


using namespace std;

const int gen_tol = 350;

solution::solution() {}

solution::~solution() {}

// Randomly generate double value from 0 to 1
double solution::random_01() {
    return (double) rand() / RAND_MAX;
}

// Free the memory
void solution::free_memory(solution *circuits_set) {
    for (int i = 0; i < NUM_VEC; i++) {
        delete[] circuits_set[i].circuits_vector;
    }
}

// generate the first set of parent vectors
void solution::initial_allocation(solution *circuits_set, int num_units) {
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < NUM_VEC; i++) {
        circuits_set[i].circuits_vector = new int[2 * num_units + 1];
        bool flag = true;
        double fitness;
        do {
            // set them in range(0,num_units)
            circuits_set[i].circuits_vector[0] = rand() % num_units;
            for (int j = 0; j < num_units; j++) {
                while ((circuits_set[i].circuits_vector[2 * j + 1] = rand() % num_units) == j);

                while ((circuits_set[i].circuits_vector[2 * j + 2] = rand() % num_units) == j || \
                circuits_set[i].circuits_vector[2 * j + 2] == circuits_set[i].circuits_vector[2 * j + 1]);
            }

            // then we chose two of cells to be the concentrate and the tailing accordingly
            int conc = rand() % num_units;
            int tail = rand() % num_units;

            circuits_set[i].circuits_vector[2 * conc + 1] = num_units;
            circuits_set[i].circuits_vector[2 * tail + 2] = num_units + 1;

            // check the validity and compute the fitness value
            CCircuit tem = CCircuit(num_units);

            flag = tem.Check_Validity(circuits_set[i].circuits_vector);

            fitness = tem.Evaluate_Circuit(circuits_set[i].circuits_vector, 1e-7, 1000);


            if (fitness == -tem.waste_in * tem.penalty) flag = false;

        } while (!flag);
        circuits_set[i].fitness_value = fitness;
    }

}

// copy data in the object
void solution::copy_solution(solution &sol1, solution &sol2) {
    for (int i = 0; i < 2 * num_units + 1; i++)
        sol2.circuits_vector[i] = sol1.circuits_vector[i];

    sol2.fitness_value = sol1.fitness_value;
}


// bubble sort the population with ascending order of performance
void solution::buble_sort(solution *circuits_set) {
    solution temp;
    temp.circuits_vector = new int[2 * num_units + 1];
    // Sort the population
    for (int i = 0; i < NUM_VEC - 1; i++) {
        for (int j = 0; j < NUM_VEC - 1 - i; j++) {
            if (circuits_set[j].fitness_value > circuits_set[j + 1].fitness_value) {
                for (int k = 0; k < 2 * num_units + 1; k++)
                    swap(circuits_set[j].circuits_vector[k], circuits_set[j + 1].circuits_vector[k]);
                swap(circuits_set[j].fitness_value, circuits_set[j + 1].fitness_value);
            }
        }
    }
    delete[] temp.circuits_vector;
}


// select the parent vector linearly
int solution::select(solution *circuits_set) {
    double p_min = 0.05;
    double p_max = 0.95;
    double *prob = new double[NUM_VEC];
    double p_sum = 0;


    // Give every solution a selected posibility so that we can assign linear distribution to the parent vector set
    for (int i = 0; i < NUM_VEC; i++) {
        prob[i] = p_min + (p_max - p_min) * (i / (NUM_VEC - 1));
        p_sum += prob[i];
    }

    // Randomly select one solution as parent, following the linear distribution here
    double p = 0;
    double tem = random_01();
    for (int i = 0; i < NUM_VEC; i++) {
        p += prob[i] / p_sum;
        if (p > tem) {
            delete[] prob;
            return i;
        }
    }
    delete[] prob;
    // if none of the set is selected, then we select the one with the largest fitness value
    return NUM_VEC - 1;
}

// do the cross over
void solution::cross_over(solution *parents_set, solution &child_1, solution &child_2) {
    int vector_size = 2 * num_units + 1;

    double cross_rate = (double) rand() / RAND_MAX;

    // select two different vectors
    int par1_index = select(parents_set);
    int par2_index;
    while ((par2_index = select(parents_set)) == par1_index);


    solution par1 = parents_set[par1_index];
    solution par2 = parents_set[par2_index];


    // one-point cross over
    if (cross_rate < CROSSOVER_RATE) {

        int cross_point = 1 + rand() % (vector_size - 2);

        for (int j = 0; j < cross_point; j++) {
            child_1.circuits_vector[j] = par2.circuits_vector[j];
            child_2.circuits_vector[j] = par1.circuits_vector[j];
        }

        for (int j = cross_point; j < vector_size; j++) {
            child_1.circuits_vector[j] = par1.circuits_vector[j];
            child_2.circuits_vector[j] = par2.circuits_vector[j];
        }
    } else {
        // do not change the vectors here
        for (int j = 0; j < vector_size; j++) {
            child_1.circuits_vector[j] = par1.circuits_vector[j];
            child_2.circuits_vector[j] = par2.circuits_vector[j];
        }
    }
}


// Mutate the solution
void solution::mutation(solution &curt_sol) {
    // Randomly mutated, but not equal to itself
    double mutation_rate = random_01();
    // mutate the starting cell
    if (mutation_rate < MUTATION_RATE) {
        int tem = curt_sol.circuits_vector[0];
        while ((curt_sol.circuits_vector[0] = rand() % (num_units)) == tem);
    }
    for (int i = 1; i < 2 * num_units + 1; i++) {
        mutation_rate = random_01();
        // mutate the rest cells
        if (mutation_rate < MUTATION_RATE) {
            int tem = curt_sol.circuits_vector[i];
            while ((curt_sol.circuits_vector[i] = rand() % (num_units + 2)) == tem);
        }
    }
}


void solution::write_file(int *res_vec, double res_val) {
    ofstream output_file;
    output_file.open("Visualisation/tex_res.txt", ofstream::app);
    if (output_file.is_open()) {
        for (int j = 0; j < num_units * 2 + 1; j++)
            output_file << res_vec[j] << " ";
        output_file << " - " << res_val << endl;
        output_file.close();
    } else { cout << "Unable to open file" << endl; }
}

void solution::Genetic_algorithm(int *sol, int num_units) {
    solution *parents_set = new solution[NUM_VEC];
    solution *children_set = new solution[NUM_VEC];

    // initialize_set(parents_set, num_units);
    initial_allocation(parents_set, num_units);
    buble_sort(parents_set);

    // allocate space 
    for (int i = 0; i < NUM_VEC; i++) {
        children_set[i].circuits_vector = new int[2 * num_units + 1];
    }

    int gen = 0;    //generation count
    double best_fitness = 0;
    int num_stable_gen = 0;
    int best_gen = 0;

    ofstream output_tem;
    output_tem.open("../../Visualisation/tex_res.txt", ofstream::out | ofstream::trunc);
    output_tem.close();

    while (gen < MAX_ITERATION && num_stable_gen < gen_tol) {
        // cout << gen << endl;
        double pre_best = parents_set[NUM_VEC - 1].fitness_value;
        // copy the best into child population
        copy_solution(parents_set[NUM_VEC - 1], children_set[0]);
        int child_count = 1;

        // {
        while (child_count < NUM_VEC) {
#pragma omp parallel shared(child_count)
            {
                // Initialize two children vector
                solution child_1;
                solution child_2;
                child_1.circuits_vector = new int[2 * num_units + 1];
                child_2.circuits_vector = new int[2 * num_units + 1];

                // Cross over between two parents
                cross_over(parents_set, child_1, child_2);

                // Mutate two children
                mutation(child_1);
                mutation(child_2);

                // Check whether two children are valid
                bool val1, val2;

                CCircuit tmp_circuit = CCircuit(num_units);

                // Check the validity of two children

                val1 = tmp_circuit.Check_Validity(child_1.circuits_vector);
                val2 = tmp_circuit.Check_Validity(child_2.circuits_vector);



                // Evaluate the score of two children
                double fitness_child1 = tmp_circuit.Evaluate_Circuit(child_1.circuits_vector, 1e-7, 1000);
                double fitness_child2 = tmp_circuit.Evaluate_Circuit(child_2.circuits_vector, 1e-7, 1000);


                // If score doesn't converge, it's invalid
#pragma omp critical
                {
                    if (val1 && fitness_child1 != -tmp_circuit.waste_in * tmp_circuit.penalty &&
                        child_count < NUM_VEC) {
                        child_1.fitness_value = fitness_child1;
                        copy_solution(child_1, children_set[child_count]);
                        child_count++;
                    }


                    if (val2 && fitness_child1 != -tmp_circuit.waste_in * tmp_circuit.penalty &&
                        child_count < NUM_VEC) {
                        child_2.fitness_value = fitness_child2;
                        copy_solution(child_2, children_set[child_count]);
                        child_count++;
                    }
                }


                delete[] child_1.circuits_vector;
                delete[] child_2.circuits_vector;
            }
        }
        // Update current population
        for (int i = 0; i < NUM_VEC; i++) copy_solution(children_set[i], parents_set[i]);

        // Sort the current population
        buble_sort(parents_set);
        best_fitness = parents_set[NUM_VEC - 1].fitness_value;

        if (best_fitness != pre_best) {
            cout << "Value updated: " << best_fitness << " at generation: " << gen << endl;
            best_gen = gen;
            num_stable_gen = 0;
            write_file(parents_set[NUM_VEC - 1].circuits_vector, best_fitness);
        } else {
            num_stable_gen++;
        }
        gen++;
    }

    // Print out the result
    cout << "The best vector is: " << endl;
    for (int i = 0; i < 2 * num_units + 1; i++) {
        cout << parents_set[NUM_VEC - 1].circuits_vector[i] << " ";
    }
    cout << "The best fitness value is: " << best_fitness << endl;


    for (int i = 0; i < 2 * num_units + 1; i++)
        sol[i] = parents_set[NUM_VEC - 1].circuits_vector[i];

    this->fitness_value = best_fitness;
    // Free memory
    free_memory(parents_set);
    free_memory(children_set);
    delete[] parents_set;
    delete[] children_set;
}

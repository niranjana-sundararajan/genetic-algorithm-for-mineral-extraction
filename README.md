# Gormanium Rush Processing Using C++

![image](https://user-images.githubusercontent.com/88569855/160098247-060e3168-5eac-4311-ae42-03fbddd5d053.png)

[![MIT License](https://img.shields.io/static/v1?label=license&message=MIT&color=orange)](https://opensource.org/licenses/mit-license.php)
[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

This is a C++ software that optimises Gormanium rush processing using Genetic Algorithm, with Python postprocessing codes. 

## Table of Contents

- [Background](#background)
- [Install](#install)
- [Usage](#usage)
  - [Scenario](#scenario)
  - [Simulation](#simulation)
  - [Visualisation](#visualisation)
  - [Documentation](#documentation)
  - [Improvement](#improvement)
- [Badge](#badge)
- [Maintainers](#maintainers)
- [Contributing](#contributing)
- [License](#license)

## Background

Material separation is widely used in factories through flexible arrangement of various processing units as a circuit. How to find the best circuit subject to existing number of units and economic factors has been a key issue in modern industry. This software implementation generates optimum circuit configuration  for given number of units. The mass balance calculator will tell the user the total conrantration of gormanium and waste in the concentrate, and consequently the purity and recovery of the optimum solution based on the given input feeds of gormanium and waste.
An economic analysiscan be carried out to find the optimum values of recovery and waste depending on the given economic parameters.
The code has four main parts:

- The Genetic Algorithm 
- The Mass Balance Solver
- The Circuit Validity Checking, and finally
- Post-Process and visualizations


## Install

To get the repository on your device run

```sh
git clone https://github.com/ese-msc-2021/acs-gormanium-rush-ilmenite.git 
```

to ensure the python visualisation code works please also download the graphviz package

```sh
pip install graphviz python-graphviz
```

## Usage

To modelling the mineral processing run

```sh
cmake .
```

To visualise the results and perform analysis run
```sh
cmake tests
```

### Scenario

To determine the optimum circuit configuration and performance for a circuit that
contains 10 units, having a total circuit feed of 10 kg/s of gormanium, the valuable material,
and 100 kg/s of the waste material. The payment is £100 per kg of gormanium in the product and the penalty is 
 £500 per kg of the waste material. \
 
<img width="893" alt="base case" src="https://user-images.githubusercontent.com/88569855/160146772-183d60ca-2a74-4ae4-a417-6f21ea56202f.png">


Parameters initialized for running an example include:

``num_units(number of units) :`` \
`` profit(payment for recovery of concentrate) :`` \
`` cost(penalty for recovery of concentrate) :`` \
`` circuit_tolerance :`` \
`` number of iterations :`` \
`` crossing probability :`` \
`` mutation probability :`` \
`` Mutate Step :`` \
`` Number of offsprings :`` \
`` Genetic Algo Iterations :`` \
`` Genetic Algo Tolerance :`` \
`` Feed Gormanium : `` \
`` Feed Waste : `` \

These inital parameters can be changed with discretion to obtain different optmal values for circuit configurations.

The tests can be run either directly through the testing file or by checking the git workflows which directy run the required tests

### Simulation

To simulate the gormanium rush processing (part 1 ~ 3 C++ code) run

```sh
g++-11 -fopenmp src/main.cpp -std=c++20
```

to test the programme run
```sh
python3 run test tests
```

### Visualisation

The post-processing part involves a Jupiter notebook. The programme generates a graph of circuit with specific configuration information. Moreover, it is expanded to be able to animate the convergence path towards the optimum circuit. The (animated) graph demonstrates the optimal circuit which the resulting vector and optimal fitness value.

### Documentation
The code structure and documentations can be automatically generated using git actions using  a generated doxyfile.
To generate the Doxyfile use
`` doxygen -g Illmenite-Documentation ``
To find the current version of documentation generated using Doxygen in html,pdf and docbook format, check the documentations folder [here](documentation)

### Improvement

We have an optional improvement for the Genetic Algorithm (part 1). 

In cross-over part of genetic algorithm, we can use a loop to enumerate all possibilities of cross-over after picking the parents. Then, we choose the vector of the best fitness and put it into the child list. Thus, for each time we choose parents, there is at most 1 vector which is put into the child list. In this method, we can ensure that the child we choose is the best one when picking parents. Besides, the generation will have all good vectors. Compared with the standard genetic algorithm, it will have less iteration and time consuming, but take more memory space for calculating. However, it can be optimized a lot with the help of parallel computation. 

## Badge

This readme.md follows the Github Standard-Readme scheme

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

## Maintainers

[Zonghui Liu](https://github.com/acse-zl1021)

## Contributing

All issues and PRs are warmly welcomed.

### Contributors

This software show respect to all group members who contribute

[Haoran Cheng](https://github.com/acse-hc221),  [Hansong Xiao](https://github.com/acse-hx221),  [Zonghui Liu](https://github.com/Liuzonghui128),  [Xu Ma](https://github.com/acse-xm221),  [Can Dai](https://github.com/acse-cd321),  [Niranjana Sundararajan](https://github.com/acse-ns1321),  [Likai Wei](https://github.com/acse-lw521),  [Yiyu Lin](https://github.com/acse-yl421).

## License

This software uses the MIT Open Source License

[![MIT License](https://img.shields.io/static/v1?label=license&message=MIT&color=orange)](https://opensource.org/licenses/mit-license.php)

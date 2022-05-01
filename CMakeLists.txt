cmake_minimum_required(VERSION 3.10)

# set the project name
project(Genetic_Algorithm)

# add a static library for the main code

add_library(geneticAlgorithm src/CCircuit.cpp src/Genetic_Algorithm.cpp src/CUnit.cpp)
target_include_directories(geneticAlgorithm PUBLIC includes)
set_target_properties( geneticAlgorithm
    PROPERTIES
    CXX_STANDARD 14
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# add the main executable
add_executable(Genetic_Algorithm src/main.cpp)
target_link_libraries(Genetic_Algorithm geneticAlgorithm)
target_include_directories(Genetic_Algorithm PRIVATE includes)
set_target_properties( Genetic_Algorithm
    PROPERTIES
    CXX_STANDARD 14
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

include(CTest)
# add tests

list(APPEND Tests test1 test2)

foreach(Test IN LISTS Tests)
    add_executable(${Test} tests/test1.cpp)
    target_link_libraries(${Test} geneticAlgorithm)
    target_include_directories(${Test} PRIVATE includes)
    set_target_properties(${Test} PROPERTIES
        CXX_STANDARD 14
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/bin")
    add_test(${Test} ${Test})
endforeach()



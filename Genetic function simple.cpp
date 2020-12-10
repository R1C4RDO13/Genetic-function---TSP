// Genetic funtion simple.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//function to test  x + 3 – sin(x)


//for the generic algorithm we need to encode our number into bits
//we need to convert the floating points into bits
//Than we select a range (low - max) (0 , 4)
//the search space needs to be bounded, we cannot look in a infinite number of solutions

//we set a number of bits that we will use (ex: 8 bits), number of chromosomes
//we need to calculate the precision, (high - low) / (2^n - 1)
                            // n = 8bits (0 - 255)

//decode (i is from 0 to the number of bits)
    //SUM( bit_value_i * 2^i) * precision + low

//the decode process is parsing the bits to a decimal value

#include "solution.h"
#include "GeneticAlgorithm.h"
#include "Point.h"


//params
int populationSize = 2000;
int bits = 128; //(8 bits) x (8 bits) y
//int low = 0, high = 4;
int generations = 50; //não vale a pena muitas gerações
int GroupsSizeForTournament = 3; //quanto mais pequeno até melhor
double CrossoverProbability = 0.7;
double MutationProbability = 0.01;
int main()
{
    Point low;
    Point high;

    low.X = -3;
    low.Y = -3.5;
    high.X = 3.5;
    high.Y = 4;

    std::cout << "Hello World!\n";
    GeneticAlgorithm ga(populationSize , generations ,  
        GroupsSizeForTournament , CrossoverProbability , MutationProbability);

    solution bestSolution = ga.run(bits, low, high);

    std::cout << "\nBest Solution - " << bestSolution.toString() << "\n" ;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

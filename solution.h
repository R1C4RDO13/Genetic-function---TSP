#pragma once

#include <vector>
#include <string>
#include "Point.h"
//the solution class will wrap around the bits
class solution
{
public:
	solution(int numberBits , Point low , Point high);
	solution(int numberBits, Point low, Point high , std::vector<int> bits );
	std::string toString() const;
	double fitness() const;
	std::vector<solution> MultiPointCrossover(solution Other, double CrossoverProbability);
	void Mutate(double mutationProbability);

private:
	Point bitsToDouble() const ;
	int nNumberOfBits;
	Point nLow, nHigh;
	std::vector<int> nBits; //chromosomes
	bool IsMaximum = false;



};




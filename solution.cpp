#include "solution.h"
#include <sstream>
#include "Utils.h"
#include <iostream>


solution::solution(int _numberOfBits, Point low, Point high) : nNumberOfBits(_numberOfBits), nLow(low), nHigh(high) //this initializes automatically the values
{
	nBits.reserve(_numberOfBits); // we do this to avoid relocate the vector
	for (size_t i = 0; i < _numberOfBits; i++)
	{
		nBits.push_back(rand() % 2); //random number from 0 -1 
	}

}

solution::solution(int _numberOfBits, Point low, Point high, std::vector<int> bits) : nNumberOfBits(_numberOfBits), nLow(low), nHigh(high),
nBits(bits)
//this initializes automatically the values
{

}

//to return the solution decoded /to print the solution 
std::string solution::toString() const
{
	std::ostringstream stream;
	stream << "[";
	for (int bit : nBits)
	{
		stream << bit << " ";
	}
	stream << "] double = " << bitsToDouble().ToString()
		<< " fitness = " << fitness();
	return stream.str();
}


//In short, Himmelblau's function is this:

//z = f(x, y) = (x ^ 2 + y - 11) ^ 2 + (x + y ^ 2 - 7) ^ 2

// f(x,y) = (x^2 + y - 11)^2 + (x+y^2-7)^3 solution to minimize
double solution::fitness() const
{
	Point p = bitsToDouble();
	double fitness = 
		pow((pow(p.X , 2) + p.Y - 11), 2 ) + pow((p.X + pow(p.Y , 2) - 7) , 2);
	if (!this->IsMaximum)
	{
		fitness = -fitness;
	}

	return fitness;

}



//00110001 => double?

Point solution::bitsToDouble() const
{

	double PrecX = precision(nLow.X, nHigh.X, nNumberOfBits /2);
	double PrecY = precision(nLow.Y, nHigh.Y, nNumberOfBits /2);

	//		x		   |	y
	//( 0 0 1 1 0 0 1 0| 1 1 1 0 0 1 0 1)

	double Xtemp  = 0;
	
	for (int i = 0; i < nNumberOfBits / 2; i++)	//conversion of X
	{
		Xtemp = Xtemp + pow(2, i) * nBits[i];		//conversion from base 2 to base 10
	}

	double Ytemp = 0;

	for (int i = nNumberOfBits / 2; i < nNumberOfBits ; i++) //conversion of Y
	{
		Ytemp = Ytemp + pow(2, i - nNumberOfBits / 2) * nBits[i];		//conversion from base 2 to base 10
	}

	Xtemp = Xtemp * PrecX + nLow.X;
	Ytemp = Ytemp * PrecY + nLow.Y;
	Point p;
	p.X = Xtemp;
	p.Y = Ytemp;

	return p;
}

std::vector<solution> solution::MultiPointCrossover (solution Other, double CrossoverProbability)
{

	bool cross = randomProbability(CrossoverProbability);
	//std::cout << "Crossed ? -> " << cross;
	if (cross)
	{
		/*int crossPoint = rand() % nNumberOfBits;

		std::vector<int> bits1;
		std::vector<int> bits2;

		std::copy(this->nBits.begin(), this->nBits.begin() + crossPoint,
			std::back_inserter(bits1));
		std::copy(Other.nBits.begin() + crossPoint, Other.nBits.end(),
			std::back_inserter(bits1));

		std::copy(Other.nBits.begin(), Other.nBits.begin() + crossPoint,
			std::back_inserter(bits2));
		std::copy(this->nBits.begin() + crossPoint, this->nBits.end(),
			std::back_inserter(bits2));


		solution child1{ nNumberOfBits , nLow , nHigh , bits1 };

		solution child2{ nNumberOfBits , nLow , nHigh , bits2 };


		return { child1 , child2 };*/
		int half = (int)nNumberOfBits / 2;
		int crossPoint1 = rand() % half;
		int crossPoint2 = (rand() % half) + half;


		std::vector<int> bits1;
		std::vector<int> bits2;

		//1 Point X
		std::copy(this->nBits.begin(), this->nBits.begin() + crossPoint1,
			std::back_inserter(bits1));

		std::copy(Other.nBits.begin() + crossPoint1, Other.nBits.begin() + half,
			std::back_inserter(bits1));


		//1 point Y
		std::copy(this->nBits.begin() + half, this->nBits.begin() + crossPoint2,
			std::back_inserter(bits1));

		std::copy(Other.nBits.begin() + crossPoint2, Other.nBits.end(),
			std::back_inserter(bits1));



		//2 Point X
		std::copy(Other.nBits.begin(), Other.nBits.begin() + crossPoint1,
			std::back_inserter(bits2));

		std::copy(this->nBits.begin() + crossPoint1, this->nBits.begin() + half,
			std::back_inserter(bits2));


		//2 point Y
		std::copy(Other.nBits.begin() + half, Other.nBits.begin() + crossPoint2,
			std::back_inserter(bits2));

		std::copy(this->nBits.begin() + crossPoint2, this->nBits.end(),
			std::back_inserter(bits2));


		solution child1{ nNumberOfBits , nLow , nHigh , bits1 };

		solution child2{ nNumberOfBits , nLow , nHigh , bits2 };


		return {child1 , child2};
	}
	else
	{
		return { *this , Other };
	}

}

//performs mutations to the chromosomes
void solution::Mutate(double mutationProbability)
{
	//std::cout << "\nBefore mutation " << this->toString() << "\n";
	for (int i = 0; i < nNumberOfBits; i++) {
		bool mutateBool = randomProbability(mutationProbability);
		if (mutateBool)
		{
			nBits[i] = 1 - nBits[i]; //flips
			//std::cout << "[Mutated]\n";
		}
	}

	//std::cout << "After mutation " << this->toString() << "\n";
}


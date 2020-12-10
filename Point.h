#pragma once
#include <sstream>

class Point
{
public:
	double X;
	double Y;
	std::string ToString() {
		std::ostringstream stream;
		stream << "(X: " << X << ", Y " << Y << ")";
		return stream.str();
	}
};


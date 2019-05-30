#pragma once
#include <Vector>

#include "Triangle.h"
#include "Trapezoid.h"
#include "Cliff.h"

#ifndef FUZZIFIER_H
#define FUZZIFIER_H

/*
 *Fuzziffier
 *Class to handle the fuzzy sets for a given input. One fuzziffier handles one input sensor, and contains all the fuzzy sets relevant to that input
 *
 */
class Fuzziffier {

public:
	//Constructors
	Fuzziffier();
	Fuzziffier(Cliff OA, Cliff EF);
	Fuzziffier(Cliff low, Triangle med, Cliff high);

	void addCliff(Cliff c);

	void addTriangle(Triangle t);

	void addTrapezoid(Trapezoid Tr);

	Cliff getCliff(int i);

	Triangle getTriangle(int i);

	Trapezoid getTrapezoid(int i);

	//Finds membership values for each fuzzy set. If the sensor input is not in the range of the fuzzy set,
	//its membership is set to 0 indicating this fuzzy set is not needed for this value of input.
	void fuzzify(int sensorDistance);

	double returnMembership(int i);

	std::vector <Cliff> cliffs;
	std::vector <Triangle> triangles;
	std::vector <Trapezoid> trapezoids;
	

};

#endif // !FUZZIFIER_H

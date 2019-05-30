#pragma once

#include <String>
#include <Vector>


#ifndef TRAPEZOID_H
#define TRAPEZOID_H

/*
Class to define a fuzzy set with 4 points (Trapezoid)
*/
class Trapezoid{

public:
	//Constructors
	Trapezoid();
	Trapezoid(int x1, int x2, int x3, int x4);

	//Getter and setter functions to access coordinates and membership private variables
	int getPoint(int i);
	void setPoint(int i, int x);
	double getMembership();
	void setMembership(double membership);

	//Given a distance, calculates the membership for this fuzzy set.
	void calculateMembership(int distance);

private:

	int coordinates[4];
	double membership;


};


#endif 

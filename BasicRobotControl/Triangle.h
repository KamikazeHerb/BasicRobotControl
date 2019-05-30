#pragma once

#ifndef Triangle_H
#define Triangle_H

/*
* Class to define a fuzzy set with 3 points (Triangle)
*
*/
class Triangle{

public:
	//Constructors
	Triangle();
	Triangle(int x1, int x2, int x3);

	//Getter and setter methods for coordinates and membership private variables
	int getPoint(int i);
	void setPoint(int i, int x);
	double getMembership();
	void setMembership(double membership);

	//Given a distance, calculates the membership value for this fuzzy set
	void calculateMembership(int distance);

	int coordinates [3];
	double membership;
	

};


#endif // !3POINTFUNCTION_H

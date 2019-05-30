#pragma once


#ifndef CLIFF_H
#define CLIFF_H

/*
 *Defines a cliff fuzzy set, either ascending or descending
 *
 */
class Cliff
{
public:
	Cliff();
	Cliff(int x1, int x2, char direction);

	//Getter and setter methods for coordinates, membership and direction private variables
	int getPoint(int i);
	void setPoint(int i, int x);
	double getMembership();
	void setMembership(double m);
	char getDirection();
	void setDirection(char d);

	//Given a distance, calculates the membership value for this fuzzy set
	void calculateMembership(int distance);

//private:

	char direction;
	int coordinates[2];
	double membership;
};


#endif

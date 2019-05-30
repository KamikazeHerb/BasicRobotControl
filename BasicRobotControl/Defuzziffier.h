#pragma once

#ifndef DEFUZZIFFIER_H
#define DEFFUZZIFIER_H

/*
 *Defines a defuzziffier, using centre of sets defuzziffication. Contains three linguistic output values, used to calculate crisp outputs
 *
 */
class Defuzziffier
{
public:
	//Constructors
	Defuzziffier();
	Defuzziffier(int x1, int x2, int x3);

	//Add a center of gravity value to the array 
	void addCOG(int i, int x);

	//Returns center of gravity found at index i of array centreOfGravity
	int getCOG(int i);

private:
	int centreOfGravity[3];


};

#endif

#pragma once
#include <vector>

#include "Fuzziffier.h"
#include "Defuzziffier.h"

#ifndef RULEBASE_H
#define RULEBASE_H

class Rulebase
{
public:
	//Constructors
	Rulebase();
	Rulebase(Fuzziffier s2, Fuzziffier s34, Fuzziffier s5, Defuzziffier LMS, Defuzziffier RMS);
	Rulebase(Fuzziffier s6, Fuzziffier s7, Defuzziffier LMS, Defuzziffier RMS);

	//Calculates firing strengths, using either AND minimum or AND product. Stores firing strengths in private array "firingStrengths"
	void calcFS(char operation, char behaviour);

	//Calculates output values for left and right motor speeds. Uses centre of sets defuzziffication.
	void calculateOutputs(char behaviour);

	void setLMSOutput(double l);
	void setRMSOutput(double r);

	double getLMSOutput();
	double getRMSOutput();

	//Accessor functions for vectors containing Fuzziffiers and Defuzzifiers
	Fuzziffier getFuzziffier(int s);
	Defuzziffier getDefuzziffier(int i);
	void addFuzziffier(Fuzziffier f);
	void addDefuzziffier(Defuzziffier d);

	double getEFFiringStrength(int i);
	double getOAFiringStrength(int i);

//private:
	//Vectors containing the fuzziffiers and defuzziffiers
	std::vector <Fuzziffier> Fuzziffiers;
	std::vector <Defuzziffier> Defuzziffiers;


	//Output motor speeds
	double LMSOutput;
	double RMSOutput;

	//Rulesbase for right edge following
	int rightEdgeFollowRules[9][4] = { 
							{ 0,0,0,2 },
							{ 0,1,0,2 },
							{ 0,2,0,2 },
							{ 1,0,1,0 },
							{ 1,1,1,1 },
							{ 1,2,0,1 },
							{ 2,0,1,0 },
							{ 2,1,1,0 },
							{ 2,2,2,1 } };

	//Rulebase for obstacle avoidance
	int obstacleAvoidanceRules[27][5] = {
							{0,0,0,0,2},
							{0,0,1,1,0},
							{0,0,2,2,0},
							{0,1,0,1,1},
							{0,1,1,1,0},
							{0,1,2,2,1},
							{0,2,0,1,1},
							{0,2,1,2,1},
							{0,2,2,2,0},
							{1,0,0,0,1},
							{1,0,1,0,2},
							{1,0,2,0,2},
							{1,1,0,0,1},
							{1,1,1,1,1},
							{1,1,2,1,1},
							{1,2,0,0,1},
							{1,2,1,1,1},
							{1,2,2,1,1},
							{2,0,0,0,2},
							{2,0,1,0,2},
							{2,0,2,0,2},
							{2,1,0,0,1},
							{2,1,1,0,1},
							{2,1,2,1,2},
							{2,2,0,1,2},
							{2,2,1,1,1},
							{2,2,2,1,1} };

	//Array to store the firing strengths for the fuzzy input
	double EFFiringStrengths[9] = {0,0,0,0,0,0,0,0,0};
	double OAFiringStrengths[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

};

#endif

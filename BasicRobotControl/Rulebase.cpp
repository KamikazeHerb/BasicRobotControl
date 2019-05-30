#include "Rulebase.h"
#include <algorithm>
#include <iostream>

Rulebase::Rulebase()
{
}

Rulebase::Rulebase(Fuzziffier s2, Fuzziffier s34, Fuzziffier s5, Defuzziffier LMS, Defuzziffier RMS)
{
	addFuzziffier(s2);
	addFuzziffier(s34);
	addFuzziffier(s5);
	addDefuzziffier(LMS);
	addDefuzziffier(RMS);
}

Rulebase::Rulebase( Fuzziffier s6, Fuzziffier s7, Defuzziffier LMS, Defuzziffier RMS)
{
	addFuzziffier(s6);
	addFuzziffier(s7);
	addDefuzziffier(LMS);
	addDefuzziffier(RMS);
}

//Accessor functions for vectors containing Fuzziffiers and Defuzzifiers
Fuzziffier Rulebase::getFuzziffier(int s)
{
	return Fuzziffiers[s];
}
Defuzziffier Rulebase::getDefuzziffier(int i)
{
	return Defuzziffiers[i];
}
void Rulebase::addFuzziffier(Fuzziffier f)
{
	Fuzziffiers.push_back(f);
}
void Rulebase::addDefuzziffier(Defuzziffier d)
{
	Defuzziffiers.push_back(d);
}

double Rulebase::getEFFiringStrength(int i)
{
	return EFFiringStrengths[i];
}

double Rulebase::getOAFiringStrength(int i)
{
	return OAFiringStrengths[i];
}


//Calculates firing strengths
void Rulebase::calcFS(char operation, char behaviour)
{
	if (behaviour == 'e') {
		if (operation == 'm')
		{
			//Iterates through the rule lines in the rule base
			//Compares the membership values from the two fuzzy sets in the current rule, chooses the minimum of the two.
			for (int i = 0; i < 9; i++)
			{	
				EFFiringStrengths[i] = (std::min(Fuzziffiers[0].returnMembership(rightEdgeFollowRules[i][0]), Fuzziffiers[1].returnMembership(rightEdgeFollowRules[i][1])));
			}
		
		}
		else if (operation == 'p')
		{
			//Iterates through the rule lines in the rule base
			for (int i = 0; i < 9; i++)
			{
				//Multiplies the membership values from the two fuzzy sets in the current rule
				EFFiringStrengths[i] = (Fuzziffiers[0].returnMembership(rightEdgeFollowRules[i][0]) * Fuzziffiers[1].returnMembership(rightEdgeFollowRules[i][1]));
			}
		}
	}
	else if (behaviour == 'o') {
		if (operation == 'm')
		{
			//Iterates through the rule lines in the rule base
			for (int i = 0; i < 27; i++)
			{
				//Compares the membership values from the three fuzzy sets in the current rule, chooses the minimum.
				OAFiringStrengths[i] = (std::min(Fuzziffiers[0].returnMembership(obstacleAvoidanceRules[i][0]), std::min(Fuzziffiers[1].returnMembership(obstacleAvoidanceRules[i][1]), Fuzziffiers[2].returnMembership(obstacleAvoidanceRules[i][2]))));
			}
		}
		else if (operation == 'p')
		{
			//Iterates through the rule lines in the rule base
			for (int i = 0; i < 27; i++)
			{
				//Multiplies the membership values from the three fuzzy sets in the current rule
				OAFiringStrengths[i] = (Fuzziffiers[1].returnMembership(obstacleAvoidanceRules[i][0]) * Fuzziffiers[1].returnMembership(obstacleAvoidanceRules[i][1]) * Fuzziffiers[1].returnMembership(obstacleAvoidanceRules[i][2]));
			}
		}
	}

}
//Needs fixing 
void Rulebase::calculateOutputs(char behaviour)
{
	double numerator = 0;
	double denominator = 0;


	if(behaviour == 'e')
	{
		//Edge following behaviour has 9 rules
		for (int i = 0; i < 9; i++)
		{
			//
			numerator += (EFFiringStrengths[i] * Defuzziffiers[0].getCOG(rightEdgeFollowRules[i][2]));
			denominator += EFFiringStrengths[i];
		}
		setLMSOutput(numerator / denominator);
		numerator = 0, denominator = 0;
		for (int i = 0; i < 9; i++)
		{
			numerator += (EFFiringStrengths[i] * Defuzziffiers[1].getCOG(rightEdgeFollowRules[i][3]));
			denominator += EFFiringStrengths[i];
		}
		setRMSOutput(numerator / denominator);
	}
	else if(behaviour == 'o')
	{
		//Object avoidance behaviour has 27 rules to cycle through
		for (int i = 0; i < 27; i++)
		{
			numerator += (OAFiringStrengths[i] * Defuzziffiers[0].getCOG(obstacleAvoidanceRules[i][3]));
			denominator += OAFiringStrengths[i];
		}
		setLMSOutput(numerator / denominator);
		numerator = 0, denominator = 0;
		for (int i = 0; i < 27; i++)
		{
			numerator += (OAFiringStrengths[i] * Defuzziffiers[1].getCOG(obstacleAvoidanceRules[i][4]));
			denominator += OAFiringStrengths[i];
		}
	}
	setRMSOutput(numerator / denominator);
}

void Rulebase::setLMSOutput(double l)
{
	LMSOutput = l;
}

void Rulebase::setRMSOutput(double r)
{
	RMSOutput = r;
}

double Rulebase::getLMSOutput()
{
	return this->LMSOutput;
}

double Rulebase::getRMSOutput()
{
	return this->RMSOutput;
}


#include "Defuzziffier.h"

Defuzziffier::Defuzziffier()
{
	
}

Defuzziffier::Defuzziffier(int x1, int x2, int x3)
{
	addCOG(0, x1);
	addCOG(1, x2);
	addCOG(2, x3);
}

int Defuzziffier::getCOG(int i)
{
	return centreOfGravity[i];
}

void Defuzziffier::addCOG(int i, int x)
{
	centreOfGravity[i] = x;
}
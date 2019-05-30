#include "Fuzziffier.h"
#include "Cliff.h"
#include "Triangle.h"
#include <vector>

Fuzziffier::Fuzziffier()
{

}
Fuzziffier::Fuzziffier(Cliff OA, Cliff EF)
{
	addCliff(OA);
	addCliff(EF);
}

Fuzziffier::Fuzziffier(Cliff low, Triangle med, Cliff high)
{
	addCliff(low);
	addTriangle(med);
	addCliff(high);
	
}

void Fuzziffier::addCliff(Cliff c)
{
	cliffs.push_back(c);
}

void Fuzziffier::addTriangle(Triangle t)
{
	triangles.push_back(t);
}

void Fuzziffier::addTrapezoid(Trapezoid Tr)
{
	trapezoids.push_back(Tr);
}

Cliff Fuzziffier::getCliff(int i) {
	return cliffs[i];
}

Triangle Fuzziffier::getTriangle(int i) {
	return triangles[i];
}

Trapezoid Fuzziffier::getTrapezoid(int i) {
	return trapezoids[i];
}

void Fuzziffier::fuzzify(int sensorDistance)
{
	for(int i = 0; i < 3; i++)
	{
		this->cliffs[0].calculateMembership(sensorDistance);
		this->triangles[0].calculateMembership(sensorDistance);
		this->cliffs[1].calculateMembership(sensorDistance);
	}
}

double Fuzziffier::returnMembership(int i) {
	switch (i) {
	case 0: return this->cliffs[0].membership;
		break;
	case 1: return this->triangles[0].membership;
		break;
	case 2: return this->cliffs[1].membership;
		break;
	}
}


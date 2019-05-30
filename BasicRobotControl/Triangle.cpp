#include "Triangle.h"
#include <iostream>
Triangle::Triangle()
{
}

Triangle::Triangle(int x1, int x2, int x3)
{
	int coord[3] = { x1, x2, x3 };

	for (int i = 0; i < 3; i++)
	{
		setPoint(i, coord[i]);
	}
}

double Triangle::getMembership()
{
	return membership;
}

void Triangle::setMembership(double m)
{
	membership = m;
}

int Triangle::getPoint(int i)
{
	return coordinates[i];
}

void Triangle::setPoint(int i, int x)
{
	coordinates[i] = x;
}

//Something weird going on in this function
void Triangle::calculateMembership(int distance)
{
	int x1 = getPoint(0);
	int x2 = getPoint(1);
	int x3 = getPoint(2);

	double m;

		if (distance <= x2)
		{
			double n1 = distance - x1;
			double d1 = x2 - x1;
			m = n1 / d1;
		}
		else if (distance > x2)
		{
			double n2 = x3 - distance;
			double d2 = x3 - x2;
			m = n2 / d2;
		}
		if (m < 0) {
			m = 0;
		}
		else if(m > 1) {
			m = 1;
		}
	setMembership(m);
}
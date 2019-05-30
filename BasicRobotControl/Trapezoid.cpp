#include "Trapezoid.h"

Trapezoid::Trapezoid()
{
}

Trapezoid::Trapezoid(int x1, int x2, int x3, int x4)
{
	int coordinates[4] = {x1, x2, x3, x4};

	for (int i = 0; i < 4; i++)
	{
		setPoint(i, coordinates[i]);
	}
}

int Trapezoid::getPoint(int i)
{
	return coordinates[i];
}

void Trapezoid::setPoint(int i, int x)
{
	coordinates[i] = x;
}

double Trapezoid::getMembership()
{
	return membership;
}

void Trapezoid::setMembership(double m)
{
	membership = m;
}

void Trapezoid::calculateMembership(int distance)
{
	int x1 = this->getPoint(0);
	int x2 = this->getPoint(1);
	int x3 = this->getPoint(2);
	int x4 = this->getPoint(3);
	double membership = 0;
	if( distance < x1 || distance > x4)
	{
		membership = 0;
	}
	else if(x2 <= distance <= x3)
	{
		membership = 1;
	}
	else
	{
		if(x1 <=distance <=x2)
		{
			membership = (distance - x1) / (x2 - x1);
		}
		else if(x3 <= distance <= x4)
		{
			membership = (x4 - distance) / (x4 - x3);
		}
	}
	if (membership < 0)
	{
		membership = 0;
	}
	setMembership(membership);
}

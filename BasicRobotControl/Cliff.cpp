#include "Cliff.h"
#include <iostream>

using namespace std;

Cliff::Cliff()
{
}

Cliff::Cliff(int x1, int x2, char direction)
{
	membership = 0;
	int coordinates[2] = { x1, x2 };

	for (int i = 0; i < 2; i++)
	{
		setPoint(i, coordinates[i]);
	}

	setDirection(direction);
}

int Cliff::getPoint(int i)
{
	return coordinates[i];
}

void Cliff::setPoint(int i, int x)
{
	coordinates[i] = x;
}

double Cliff::getMembership()
{
	return this->membership;
}

void Cliff::setMembership(double m)
{
	this->membership = m;
}

char Cliff::getDirection()
{
	return direction;
}

void Cliff::setDirection(char d)
{
	direction = d;
}

void Cliff::calculateMembership(int distance)
{

	double x1 = getPoint(0);
	double x2 = getPoint(1);
	double membership = 0;

	if(getDirection() == 'a' || getDirection() == 'A')
	{
		if(distance > x2)
		{
			membership = 1;
		}
		else if(x1 <= distance <= x2)
		{
			double n1 = distance - x1;
			double d1 = x2 - x1;
			membership = n1 / d1;
		}
		else
		{
			membership = 0;
		}
	}
	else if(getDirection() == 'd' || getDirection() == 'D')
	{
		if(distance < x1)
		{
			membership = 1;
		}
		else if(x1 <= distance <= x2)
		{
			double n2 = x2 - distance;
			double d2 = x2 - x1;
			membership = n2 / d2;
		}
		else
		{
			membership = 0;
		}
		
	}
	if(membership < 0)
	{
		membership = 0;
	}
	if (membership > 1) {
		membership = 1;
	}
	setMembership(membership);
}

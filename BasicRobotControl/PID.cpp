#include "PID.h"
#include "Aria.h"
using namespace std;

PID::PID(double kp, double ki, double kd):
ei(0),
eprev(0),
counter(0),
kp(kp),
ki(ki),
kd(kd)
{
	

}


double PID::calculate(int dd, int cd)
{
	//Calculates error between desired distance and current distance
	double error = dd - cd;
	setError(error);

	//Praportional
	double P = kp * error;

	//Integral
	ei += error;
	double I = (ki * ei)/0.05;

	//Derivative
	double deriv = (error - eprev)/0.05;
	double D = kd * deriv;

	//Sum to get output
	double output = P + I + D;

	//Update previous error
	eprev = error;
	if (this->counter == 10) {
		cout << counter*50 << " : " << error << endl;
	}
	this->counter++;
	return output;
}

double PID::rightEdgeFollow(int avDis)
{

	const int dd = 500;
	const int wheelDis = 230;
	
	int s6 = 0, s7 = 0;

	//Use pid to calculate speed modifier
	double w = calculate(dd, avDis);

	return w;
}

int PID::getError() {
	return this->e;
}

void PID::setError(int error) {
	this->e = error;
}

PID::~PID()
{
	
}

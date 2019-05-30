#pragma once

#include "Aria.h"

#ifndef PID_H
#define PID_H
/*
 *
 * PID
 * PID controller class which handles right edge following
 *
 */
class PID
{
public:
	/*
	 * kp = praportional gain
	 * ki = integral gain
	 * kd = derivative gain
	 */
	PID(double kp, double ki, double kd);

	//Destructor
	~PID();

	/*
	 *
	 *Calculate function uses desired distance from wall and current distance from wall
	 *to find the error (difference between desired and current wall distance). This error 
	 *is used to return a value that will vary the wheel speed.
	 *
	 */
	double calculate(int dd, int cd);

	/*
	 * Takes a current distance and calculates wheel speed modifier
	 *
	 */
	double PID::rightEdgeFollow(int avDis);

	/*
	*Returns the current error 
	*
	*/
	int getError();

	/*
	sets the error field
	*/
	void setError(int error);
private:

	//Error and gain variables
	int e;
	int ei;
	int eprev;
	int counter;
	double kp;
	double ki;
	double kd;
};

#endif

#include "Aria.h"
#include "PID.h"
#include "Cliff.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include "Fuzziffier.h"
#include "Defuzziffier.h"
#include "Rulebase.h"
#include <iostream>
#include <fstream>


using namespace std;

int main(int argc, char **argv) {
	//Allow the user to choose either PID or fuzzy logic behaviour
	char mode;
	cout << "Please specify a behaviour mode f/p" << endl;
	cin >> mode;

	//PID variables
	int error = 0;
	int counter = 0;
	int bv = 150;
	int lv = bv;
	int rv = bv;
	const double kp = 0.7;
	const double ki = 0.00001;
	const double kd = 0.4;

	//Create Instances
	Aria::init();
	ArRobot robot;
	ArPose pose;
	PID pid = PID(kp, ki, kd);

	/*
	 * Fuzzy Logic controller instances
	 *
	 * A fuzzy set object calculates and stores within it a membership value as a private field when 
	 * a distance is passed to it. As such separate instances of fuzzy sets must be used for separate behaviours.
	 */
	//Fuzzy sets for edge following behaviour. Paramters 'a' and 'd' represent ascending or descending for a cliff fuzzy set.
	Cliff eLow = Cliff(400, 800, 'd');
	Triangle eMedium = Triangle(400, 800, 1200);
	Cliff eHigh = Cliff(800, 1200, 'a');

	//Fuzzy sets for obstacle avoidance behaviour, needs calculating properly
	Cliff Olow = Cliff(500,900,'d');
	Triangle Omedium = Triangle(500,900,1300);
	Cliff Ohigh = Cliff(900,1300,'a');

	//Fuzzy sets used for context based blending
	Cliff DOA = Cliff(400,1000,'d');
	Cliff DEF = Cliff(0,5000,'d');

	//Fuzziffier created for each sensor. Sensors 2, 34 and 5 used for obstacle avoidance while 6 and 7 are used for right edge following
	Fuzziffier s2 = Fuzziffier(Olow, Omedium, Ohigh);
	Fuzziffier s34 = Fuzziffier(Olow, Omedium, Ohigh);
	Fuzziffier s5 = Fuzziffier(Olow, Omedium, Ohigh);
	Fuzziffier s6 = Fuzziffier(eLow, eMedium, eHigh);
	Fuzziffier s7 = Fuzziffier(eLow, eMedium, eHigh);
	Defuzziffier LMS = Defuzziffier(10, 150, 250);
	Defuzziffier RMS = Defuzziffier(10, 150, 250);
	Rulebase rightEdgeFollow = Rulebase(s6,s7, LMS, RMS);
	Rulebase obstacleAvoidance = Rulebase(s2, s34, s5, LMS, RMS);


	//Parse command line arguments
	ArArgumentParser argParser(&argc, argv);
	argParser.loadDefaultArguments();
	argParser.addDefaultArgument("-connectLaser");


	//Connect to robot
	ArRobotConnector robotConnector(&argParser, &robot);
	if (robotConnector.connectRobot())
		std::cout << "Robot connected!" << std::endl;
	robot.runAsync(false);

	robot.lock();
	robot.enableMotors();
	robot.unlock();

	ofstream fs;
	fs.open("errorData.csv");


	//Run loop. Limited to a set run time so that csv file can be closed
	while (counter < 1200) {
		//Robot movement variables
		ArSensorReading *sonarSensor[8];

		//Sets up sonar sensors
		int sonarRange[8];

		//Counters to count how many PID sonar readings are used in the average, needed as readings of 5000 will be discarded
		//So as not to confuse PID controller
		int PIDs5c = 0;
		int PIDs6c = 0;
		int PIDs7c = 0;

		//Sensor variables for PID and Fuzzy Logic
		int Sensor2 = 0;
		int Sensor3 = 0;
		int Sensor4 = 0;
		int Sensor5 = 0;
		int Sensor6 = 0;
		int Sensor7 = 0;

		//Loop takes distance of sonar sensors 5 times and averages them, leaving a 10ms gap between readings and discarding distance readings of 5000 (maximum range of the sensor)
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				sonarSensor[j] = robot.getSonarReading(j);
				sonarRange[j] = sonarSensor[j]->getRange();
			}
			Sensor2 += sonarRange[2];
			Sensor3 += sonarRange[3];
			Sensor4 += sonarRange[4];
			Sensor5 += sonarRange[5];
			Sensor6 += sonarRange[6];
			Sensor7 += sonarRange[7];
			ArUtil::sleep(10);
		}
		//Get average readings for sensors
		Sensor2 = Sensor2 / 5;
		Sensor3 = Sensor3 / 5;
		Sensor4 = Sensor4 / 5;
		Sensor5 = Sensor5 / 5;
		Sensor6 = Sensor6 / 5;
		Sensor7 = Sensor7 / 5;

		
		//No exactly middle front sensor on robot, so use the minimum of the distances measured by the two front middle sensors 3 and 4.
		int Sensor34 = min(Sensor3, Sensor4);
	
		//PID Behaviour
		if (mode == 'p' || mode == 'P')
		{
			if (Sensor6 > 1000) {
				Sensor6 = 1000;
			}
			if (Sensor7 > 1000) {
				Sensor7 = 1000;
			}
			//Calculates a weighted average, with sensor7 having a higher weighting as it 
			int avDis = (Sensor6 * ArMath::cos(40));
			avDis += Sensor7;
			avDis = avDis / 2;

			//Calculate wheel speed modifier
			double w = pid.rightEdgeFollow(avDis);
			error = pid.getError();
			rv = bv + w;
			lv = bv;

			
			if (counter%10 == 0) {
				
				double time = counter * 0.05;
				fs << time << "," << error << ",\n";
			}
			counter++;
		}
		//Fuzzy Logic Behaviour
		else if(mode == 'f' || mode == 'F')
		{
			//Calculate firing strengths for each fuzzy set, for the distance from the front sensor and back sensor
			rightEdgeFollow.Fuzziffiers[0].fuzzify(Sensor6);
			rightEdgeFollow.Fuzziffiers[1].fuzzify(Sensor7);
			rightEdgeFollow.calcFS('p', 'e');
			rightEdgeFollow.calculateOutputs('e');
			obstacleAvoidance.Fuzziffiers[0].fuzzify(Sensor2);
			obstacleAvoidance.Fuzziffiers[1].fuzzify(Sensor34);
			obstacleAvoidance.Fuzziffiers[2].fuzzify(Sensor5);
			obstacleAvoidance.calcFS('p', 'o');
			obstacleAvoidance.calculateOutputs('o');

			//Context based blending membership calculation
			DOA.calculateMembership(min(Sensor2, min(Sensor34, Sensor5)));
			DEF.calculateMembership(min(Sensor6, Sensor7));
			double mDOA = DOA.getMembership() * 1.8;
			double mDEF = DEF.getMembership() * 0.2;

			//Fix for obstacle avoidance
			int tempr = obstacleAvoidance.getLMSOutput();
			int templ = obstacleAvoidance.getRMSOutput();
			obstacleAvoidance.setLMSOutput(templ);
			obstacleAvoidance.setRMSOutput(tempr);

			//Wheel speeds calculated using context based blending
			rv = ((mDOA*obstacleAvoidance.getRMSOutput()) + (mDEF*rightEdgeFollow.getRMSOutput())) / (mDOA + mDEF);
			lv = (mDOA*obstacleAvoidance.getLMSOutput() + (mDEF * rightEdgeFollow.getLMSOutput())) / (mDOA + mDEF);
		}
		else
		{
			//End program if either p or f is not entered
			return 0;
		}

		//Safeguards to keep wheel speeds within safe speed range, protects from unexpected speed calculation problems
		if (rv > 500)
		{
			rv = 500;
		}
		else if (rv < 0)
		{
			rv = 0;
		}
		if (lv > 500)
		{
			lv = 500;
		}
		else if (lv < 0)
		{
			lv = 0;
		}

		//Sets wheel movement speeds and output them to the console, along with the distance from the wall to help with testing
		robot.setVel2(lv, rv);
		
	}
	fs.close();
	// stop the robot
	robot.lock();
	robot.stop();
	robot.unlock();

	// terminate all threads and exit
	Aria::exit();

}
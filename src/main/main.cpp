#include <iostream>
#include <memory> 
#include <iomanip>

#include "engines/EngineBase.h"
#include "engines/ICE/InternalCombustionEngine.h"

using namespace std;

int main()
{
	double inertia = 0.1;
	std::vector<std::pair<double, double>> torqueCurve = { {0, 20}, {75, 75}, {150, 100}, {200, 105}, {250, 75}, {300, 0} };
	double T_overheat = 110;
	double HM = 0.01;
	double HV = 0.0001;
	double C = 0.1;
	double ambientTemperature = 25.0;

	InternalCombustionEngine* engine = new InternalCombustionEngine(inertia, torqueCurve, T_overheat, HM, HV, C, ambientTemperature);

	double timeStep = 0.01;
	double timer = 0.0;

	while (engine->getTemperature() < 110) {
		engine->run(timeStep);
		timer += timeStep;

		if ((timer - floor(timer)) < timeStep || timer < 1)
		{
			cout << "Time: " << timer << " ";
			cout << "Temperature: " << engine->getTemperature() << " ";
			cout << "Angular Velocity: " << engine->getAngularVelocity() << std::endl;
		}	
	}

	delete engine;

	return 0;
}
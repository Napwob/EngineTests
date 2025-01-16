#include <iostream>
#include <memory> 
#include <iomanip>

#include "engines/EngineBase.h"
#include "stand/TestStand.h"
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

	unique_ptr<EngineBase> engine = make_unique<InternalCombustionEngine>(inertia, torqueCurve, HM, HV, C, ambientTemperature);

	TestStand testStand(move(engine));

	double timeStep = 0.01;
	double timeToOverheat = testStand.runTest(timeStep, T_overheat);

	std::cout << "Test completed. Time to overheat: " << timeToOverheat << " seconds.\n";

	return 0;
}
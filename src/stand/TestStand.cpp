#include "TestStand.h"
#include <iostream>

TestStand::TestStand(std::unique_ptr<EngineBase> engine) : engine(std::move(engine)) {}

double TestStand::runTest(double timeStep, double T_overheat) {
	double timeElapsed = 0.0;

	while (engine->getTemperature() < T_overheat) {
		engine->run(timeStep);
		timeElapsed += timeStep;
	}

	return timeElapsed;
}
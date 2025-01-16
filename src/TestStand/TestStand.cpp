#include "TestStand.h"
#include <iostream>

TestStand::TestStand(std::unique_ptr<EngineBase> engine) : engine(std::move(engine)) {}

double TestStand::runTest(double timeStep, double T_overheat) {
	double timeElapsed = 0.0;

	double previousTemperature = -1;

	while (engine->getTemperature() < T_overheat) {
		previousTemperature = engine->getTemperature();
		engine->run(timeStep);
		timeElapsed += timeStep;

		if (previousTemperature >= engine->getTemperature())
		{
			std::cout << "The ambient temperature does not allow the engine to overheat.\n";
			return timeElapsed;
		}
	}
	std::cout << "The engine overheated.\n";
	return timeElapsed;
}

EngineBase* TestStand::getEngine() const {
	return engine.get();
}
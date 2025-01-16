#include "TestStand.h"
#include <iostream>

TestStand::TestStand(std::unique_ptr<EngineBase> engine) : engine(std::move(engine)) {}

double TestStand::runTest(double timeStep, double T_overheat) {
	double timeElapsed = 0.0;

	double previousTemperature = -1;

	while (true) {
		previousTemperature = engine->getTemperature();
		engine->run(timeStep);
		timeElapsed += timeStep;

		if (engine->getTemperature() >= T_overheat)
		{
			std::cout << "The engine overheated.\n";
			break;
		}

		if (previousTemperature >= engine->getTemperature() && previousTemperature < T_overheat && engine->getTemperature() < T_overheat)
		{
			std::cout << "The ambient temperature does not allow the engine to overheat.\n";
			std::cout << "Stable temperature: " << engine->getTemperature() <<"\n";
			break;
		}
	}
	return timeElapsed;
}

EngineBase* TestStand::getEngine() const {
	return engine.get();
}
#include <iostream>
#include <memory> 
#include <iomanip>

#include "ConfigLoader/ConfigLoader.h"
#include "Engines/EngineBase.h"
#include "TestStand/TestStand.h"
#include "Engines/ICE/InternalCombustionEngine.h"

int main()
{
	std::string filepath;
	std::cout << "Enter configuration filepath: ";
	std::cin >> filepath;

	try
	{
		EngineConfig config = loadConfig(filepath);

		std::unique_ptr<EngineBase> engine;
		if (config.engineType == "ICE")
			engine = std::make_unique<InternalCombustionEngine>(config.inertia, config.torqueCurve, config.HM, config.HV, config.C, config.ambientTemperature);
		else
			throw std::runtime_error("Unsupported engine type: " + config.engineType);

		TestStand testStand(std::move(engine));

		double timeStep = 0.01;
		double timeToOverheat = testStand.runTest(timeStep, config.T_overheat);

		std::cout << "Test completed. Time to overheat: " << timeToOverheat << " seconds.\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}

	return 0;
}
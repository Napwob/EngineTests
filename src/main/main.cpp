#include <iostream>
#include <memory> 
#include <iomanip>

#include "ConfigLoader/ConfigLoader.h"
#include "Engines/EngineBase.h"
#include "TestStand/TestStand.h"
#include "Engines/ICE/InternalCombustionEngine.h"

int main()
{
	std::string filepath; // "EngineTests\EngineConfigs\ICE_Engine.txt";
	std::cout << "Enter configuration filepath: ";
	std::cin >> filepath;

	try
	{
		EngineConfig config = loadConfig(filepath);

		std::unique_ptr<EngineBase> engine;
		if (config.engineType == "ICE")
			engine = std::make_unique<InternalCombustionEngine>(config.inertia, config.torqueCurve, config.HM, config.HV, config.C, 0);
		else
			throw std::runtime_error("Unsupported engine type: " + config.engineType);

		TestStand testStand(std::move(engine));

		while (true) {
			double ambientTemperature;
			std::cout << "Enter ambient temperature (or type 'exit' to quit): ";
			std::string input;
			std::cin >> input;

			if (input == "exit") {
				std::cout << "Exiting the program.\n";
				break;
			}

			try {
				ambientTemperature = std::stod(input);
			}
			catch (const std::invalid_argument&) {
				std::cerr << "Invalid input. Please enter a valid number or 'exit'.\n";
				continue;
			}

			testStand.getEngine()->setAmbientTemperature(ambientTemperature);

			double timeStep = 0.01;
			double testTime = testStand.runTest(timeStep, config.T_overheat);

			std::cout << "Test completed in " << testTime << " seconds.\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}

	return 0;
}
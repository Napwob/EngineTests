#include "configloader/ConfigLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

EngineConfig loadConfig(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open configuration file.");
	}

	EngineConfig config;
	std::string line;

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string key;
		if (std::getline(iss, key, '=')) {
			std::string value;
			if (std::getline(iss, value)) {
				if (key == "engineType") {
					config.engineType = value;
				}
				else if (key == "inertia") {
					config.inertia = std::stod(value);
				}
				else if (key == "T_overheat") {
					config.T_overheat = std::stod(value);
				}
				else if (key == "HM") {
					config.HM = std::stod(value);
				}
				else if (key == "HV") {
					config.HV = std::stod(value);
				}
				else if (key == "C") {
					config.C = std::stod(value);
				}
				else if (key.rfind("torque", 0) == 0) {
					size_t index = std::stoul(key.substr(key.find('[') + 1));
					if (config.torqueCurve.size() <= index) {
						config.torqueCurve.resize(index + 1);
					}
					double speed, torque;
					std::istringstream valStream(value);
					valStream >> speed >> torque;
					config.torqueCurve[index] = { speed, torque };
				}
				else if (key == "ambientTemperature") {
					config.ambientTemperature = std::stod(value);
				}
			}
		}
	}

	if (config.torqueCurve.empty()) {
		throw std::runtime_error("Torque curve not defined in configuration file.");
	}

	return config;
}
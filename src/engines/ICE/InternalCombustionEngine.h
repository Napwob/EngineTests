#ifndef INTERNAL_COMBUSTION_ENGINE_H
#define INTERNAL_COMBUSTION_ENGINE_H

#include "engines/EngineBase.h"
#include <vector>
#include <utility>

class InternalCombustionEngine : public EngineBase {
public:
	InternalCombustionEngine(double I,
		const std::vector<std::pair<double, double>>& torqueCurve,
		double T_overheat,
		double HM,
		double HV,
		double C);

	double simulateOverheatTime(double ambientTemperature) override;

private:
	double inertia;
	std::vector<std::pair<double, double>> torqueCurve;
	double T_overheat;
	double HM;
	double HV;
	double C;

	double temperature;
	double angularVelocity;

	double calculateTorque(double velocity) const;
};

#endif // INTERNAL_COMBUSTION_ENGINE_H
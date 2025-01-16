#include "InternalCombustionEngine.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

InternalCombustionEngine::InternalCombustionEngine(double I,
	const std::vector<std::pair<double, double>>& torqueCurve,
	double HM,
	double HV,
	double C,
	double ambientTemperature)
	: inertia(I),
	torqueCurve(torqueCurve),
	HM(HM),
	HV(HV),
	C(C),
	ambientTemperature(0),
	temperature(ambientTemperature),
	angularVelocity(0),
	torque(0) {
}

double InternalCombustionEngine::getTemperature() const {
	return temperature;
}

double InternalCombustionEngine::getAngularVelocity() const {
	return angularVelocity;
}

void InternalCombustionEngine::setAmbientTemperature(double AmbientTemperature) {
	ambientTemperature = AmbientTemperature;
	temperature = ambientTemperature;
}

void InternalCombustionEngine::run(double timeStep) {
	torque = calculateTorque(angularVelocity);

	updateTemperature(timeStep);
	updateAngularVelocity(timeStep);
}

double InternalCombustionEngine::calculateTorque(double velocity) const {
	if (velocity <= torqueCurve.front().first) {
		return torqueCurve.front().second;
	}
	if (velocity >= torqueCurve.back().first) {
		return torqueCurve.back().second;
	}

	for (size_t i = 1; i < torqueCurve.size(); ++i) {
		if (velocity < torqueCurve[i].first) {
			double x1 = torqueCurve[i - 1].first;
			double y1 = torqueCurve[i - 1].second;
			double x2 = torqueCurve[i].first;
			double y2 = torqueCurve[i].second;

			return y1 + (y2 - y1) * (velocity - x1) / (x2 - x1);
		}
	}

	throw std::runtime_error("calculateTorque error");
}

void InternalCombustionEngine::updateTemperature(double timeStep) {
	double heatingRate = torque * HM + std::pow(angularVelocity, 2) * HV;
	double coolingRate = C * (ambientTemperature - temperature);

	temperature += (heatingRate + coolingRate) * timeStep;
}

void InternalCombustionEngine::updateAngularVelocity(double timeStep) {
	double acceleration = torque / inertia;
	angularVelocity += acceleration * timeStep;
}

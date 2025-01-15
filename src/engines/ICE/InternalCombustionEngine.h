#ifndef INTERNAL_COMBUSTION_ENGINE_H
#define INTERNAL_COMBUSTION_ENGINE_H

#include "engines/EngineBase.h"
#include <vector>
#include <utility>

class InternalCombustionEngine : public EngineBase {
public:
	InternalCombustionEngine(double inertia,
		const std::vector<std::pair<double, double>>& torqueCurve,
		double T_overheat,
		double HM,
		double HV,
		double C,
		double ambientTemperature);

	double getTemperature() const override;
	double getAngularVelocity() const override;

	void run(double timeStep) override;

private:                                                // TODO: Remove after works
	double inertia;                                     // Момент инерции двигателя
	std::vector<std::pair<double, double>> torqueCurve; // Кусочно-линейная зависимость крутящего момента
	double T_overheat;                                  // Температура перегрева
	double HM;                                          // Коэффициент нагрева от крутящего момента
	double HV;                                          // Коэффициент нагрева от скорости вращения
	double C;                                           // Коэффициент охлаждения
	double ambientTemperature;                          // Температура окружающей среды

	double temperature;                                 // Текущая температура двигателя
	double angularVelocity;                             // Текущая скорость вращения коленвала

	double calculateTorque(double velocity) const;      // Вычисляет крутящий момент
	void updateTemperature(double timeStep);
	void updateAngularVelocity(double timeStep);
};

#endif // INTERNAL_COMBUSTION_ENGINE_H

#ifndef INTERNAL_COMBUSTION_ENGINE_H
#define INTERNAL_COMBUSTION_ENGINE_H

#include "engines/EngineBase.h"
#include <vector>
#include <utility>

class InternalCombustionEngine : public EngineBase {
public:
	InternalCombustionEngine(double inertia,
		const std::vector<std::pair<double, double>>& torqueCurve,
		double HM,
		double HV,
		double C,
		double ambientTemperature);

	double getTemperature() const override;
	double getAngularVelocity() const override;

	// Симулирует работу двигателя в течение одного промежутка времени
	void run(double timeStep) override;

private:
	double inertia;                                     // Момент инерции двигателя
	std::vector<std::pair<double, double>> torqueCurve; // Кусочно-линейная зависимость от скорости
	double HM;                                          // Коэффициент нагрева от крутящего момента
	double HV;                                          // Коэффициент нагрева от скорости вращения
	double C;                                           // Коэффициент охлаждения
	double ambientTemperature;                          // Температура окружающей среды

	double temperature;                                 // Текущая температура двигателя
	double angularVelocity;                             // Текущая скорость вращения коленвала
	double torque;                                      // Крутящий момент (рассчитывается один раз за шаг)

	double calculateTorque(double velocity) const;      // Вычисляет крутящий момент
	void updateTemperature(double timeStep);            // Обновляет температуру
	void updateAngularVelocity(double timeStep);        // Обновляет скорость вращения
};

#endif // INTERNAL_COMBUSTION_ENGINE_H
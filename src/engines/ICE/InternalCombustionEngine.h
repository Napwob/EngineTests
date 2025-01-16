#ifndef INTERNAL_COMBUSTION_ENGINE_H
#define INTERNAL_COMBUSTION_ENGINE_H

#include "Engines/EngineBase.h"
#include <vector>
#include <utility>

/// <summary>
/// Двигатель внутреннего сгорания
/// </summary>
class InternalCombustionEngine : public EngineBase {
public:
	InternalCombustionEngine(double inertia,
		const std::vector<std::pair<double, double>>& torqueCurve,
		double HM,
		double HV,
		double C,
		double ambientTemperature);

	// Получить текущее значение температуры
	double getTemperature() const override;
	// Получить текущее значение скорости вращения
	double getAngularVelocity() const override;

	// Симулирует работу двигателя в течение временного шага
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

	// Вычисляет крутящий момент
	double calculateTorque(double velocity) const;
	// Обновляет температуру
	void updateTemperature(double timeStep);    
	// Обновляет скорость вращения
	void updateAngularVelocity(double timeStep);     
};

#endif // INTERNAL_COMBUSTION_ENGINE_H
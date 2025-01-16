#ifndef TEST_STAND_H
#define TEST_STAND_H

#include "engines/EngineBase.h"
#include <memory>

// Тестовый Стенд
class TestStand {
public:
	explicit TestStand(std::unique_ptr<EngineBase> engine);

	/// <summary>
	/// Провести тестирование двигателя
	/// </summary>
	/// <param name="timeStep">Временной шаг</param>
	/// <param name="T_overheat">Температура перегрева</param>
	/// <returns>Время достижения температуры перегрева</returns>
	double runTest(double timeStep, double T_overheat);

	/// <summary>
	/// Получить указатель на объект двигателя
	/// </summary>
	/// <returns>Указатель на объект EngineBase</returns>
	EngineBase* getEngine() const;

private:
	std::unique_ptr<EngineBase> engine;
};

#endif // TEST_STAND_H
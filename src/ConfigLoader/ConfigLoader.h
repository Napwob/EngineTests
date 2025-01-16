#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>
#include <vector>
#include <utility>

struct EngineConfig {
	std::string engineType;                             // Тип двигателя
	double inertia;                                     // Момент инерции двигателя
	std::vector<std::pair<double, double>> torqueCurve; // Кусочно-линейная зависимость от скорости
	double T_overheat;                                  // Температура перегрева
	double HM;                                          // Коэффициент нагрева от крутящего момента
	double HV;                                          // Коэффициент нагрева от скорости вращения
	double C;                                           // Коэффициент охлаждения
};

// Загрузка конфигурации двигателя из указанного файла
EngineConfig loadConfig(const std::string& filepath);

#endif // CONFIG_LOADER_H
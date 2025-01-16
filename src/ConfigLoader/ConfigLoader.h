#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>
#include <vector>
#include <utility>

struct EngineConfig {
	std::string engineType;                             // ��� ���������
	double inertia;                                     // ������ ������� ���������
	std::vector<std::pair<double, double>> torqueCurve; // �������-�������� ����������� �� ��������
	double T_overheat;                                  // ����������� ���������
	double HM;                                          // ����������� ������� �� ��������� �������
	double HV;                                          // ����������� ������� �� �������� ��������
	double C;                                           // ����������� ����������
};

// �������� ������������ ��������� �� ���������� �����
EngineConfig loadConfig(const std::string& filepath);

#endif // CONFIG_LOADER_H
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

	// ���������� ������ ��������� � ������� ������ ���������� �������
	void run(double timeStep) override;

private:
	double inertia;                                     // ������ ������� ���������
	std::vector<std::pair<double, double>> torqueCurve; // �������-�������� ����������� �� ��������
	double HM;                                          // ����������� ������� �� ��������� �������
	double HV;                                          // ����������� ������� �� �������� ��������
	double C;                                           // ����������� ����������
	double ambientTemperature;                          // ����������� ���������� �����

	double temperature;                                 // ������� ����������� ���������
	double angularVelocity;                             // ������� �������� �������� ���������
	double torque;                                      // �������� ������ (�������������� ���� ��� �� ���)

	double calculateTorque(double velocity) const;      // ��������� �������� ������
	void updateTemperature(double timeStep);            // ��������� �����������
	void updateAngularVelocity(double timeStep);        // ��������� �������� ��������
};

#endif // INTERNAL_COMBUSTION_ENGINE_H
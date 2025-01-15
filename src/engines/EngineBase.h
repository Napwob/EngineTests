#ifndef ENGINE_BASE_H
#define ENGINE_BASE_H

class EngineBase {
public:
	virtual ~EngineBase() = default;
	virtual double simulateOverheatTime(double ambientTemperature) = 0;
};

#endif // ENGINE_BASE_H
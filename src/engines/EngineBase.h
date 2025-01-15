#ifndef ENGINE_BASE_H
#define ENGINE_BASE_H

class EngineBase {
public:
	virtual ~EngineBase() = default;

	virtual double getTemperature() const = 0;

	virtual double getAngularVelocity() const = 0;

	virtual void run(double timeStep) = 0;
};

#endif // ENGINE_BASE_H
#pragma once
#include "Model.h"

// models a simple pendulum with quadratic drag
class PendulumModel : public Model {
public:
	PendulumModel();

	void Process(float t, const float dt) override;

	void SetParam(const int index, const std::string& valueString) override;
	void SetInput(const int index, const std::string& valueString) override;
	std::string GetParam(const int index) const override;
	std::string GetInput(const int index) const override;
	std::string GetOutput(const int index) const override;

private:
	// hardcoded const params
	const float g = 9.81f;
	const float c = 3.0f;
	// params
	float m;
	float l;
	float theta0;
	float thetaDot0;
	// outputs
	float theta;
	// internal variables
	float thetaDot;
	float thetaDotDot;
};
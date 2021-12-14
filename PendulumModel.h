#pragma once
#include "Model.h"

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
	const float g = 9.81;
	const float c = 3;
	// params
	float m;
	float l;
	float theta0;
	float thetaDot0;
	// output and feedback variables, all feedback variables must be initialized with params in process
	float theta;
	float thetaDot;
	float thetaDotDot;
	// internal variables
};
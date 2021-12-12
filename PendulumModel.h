#pragma once
#include "Model.h"

class PendulumModel : public Model {
private:
	// params
	float theta0;
	float thetaDot0;
	// inputs
	float stick1;
	float stick2;
	// output and feedback variables, all feedback variables must be initialized with params in process
	float theta;
	float thetaDot;
	// internal variables
	float actuatorCmd1;
	float actuatorCmd2;
public:
	PendulumModel();

	void Process(float t);

	void SetParam(int index, std::string valueString);
	void SetInput(int index, std::string valueString);
	std::string GetOutput(int index);
};
#pragma once
#include "Model.h"

class Claw : public Node {
private:
	// inputs
	float stick1 = 0;
	float stick2 = 0;
	float theta = 0;
	float thetaDot = 0;
	// outputs
	float actuator1Cmd = 0;
	float actuator2Cmd = 0;
public:
	void SetInputs(float _stick1, float _stick2, float _theta, float _thetaDot) {
		stick1 = _stick1;
		stick2 = _stick2;
		theta = _theta;
		thetaDot = _thetaDot;
	}

	float GetActuator1Cmd() { return actuator1Cmd; }
	float GetActuator2Cmd() { return actuator2Cmd; }

	void Process(float t) {
	}
};

class Plant : public Node {
private:
	// inputs
	float actuator1Cmd = 0;
	float actuator2Cmd = 0;
	// outputs
	float theta = 0;
	float thetaDot = 0;
public:
	void SetInputs(float _actuator1Cmd, float _actuator2Cmd) {
		actuator1Cmd = _actuator1Cmd;
		actuator2Cmd = _actuator2Cmd;
	}

	float GetTheta() { return theta; }
	float GetThetaDot() { return thetaDot; }

	void Process(float t) {
	}
};

class PendulumModel : public Model {
private:
	// parameters
	float theta0;
	float thetaDot0;
	// inputs
	float stick1;
	float stick2;
	// output and feedback variables, all feedback variables must be initialized with parameters in process
	float theta;
	float thetaDot;
	// child blocks
	Claw claw = Claw();
	Plant plant = Plant();
public:
	PendulumModel() {
		parameterNames = {"theta0", "thetaDot0"};
		inputNames = {"stick1", "stick2"};
		outputNames = {"theta", "thetaDot"};
	}

	void SetParameter(int index, std::string valueString) {
		switch (index) {
		case 0:
			theta0 = std::stof(valueString);
			break;
		case 1:
			thetaDot0 = std::stof(valueString);
			break;
		default:
			std::cerr << "Given parameter index out of bounds! Possible mismatch between parameter file and model.\n";
			exit(1);
		}
	}

	void SetInput(int index, std::string valueString) {
		switch (index) {
		case 0:
			stick1 = std::stof(valueString);
			break;
		case 1:
			stick2 = std::stof(valueString);
			break;
		default:
			std::cerr << "Given input index out of bounds! Possible mismatch between input file and model.\n";
			exit(1);
		}
	}

	std::string GetOutput(int index) {
		switch (index) {
		case 0:
			return std::to_string(theta);
		case 1:
			return std::to_string(thetaDot);
		default:
			std::cerr << "Requested output index out of bounds! Possible mismatch between output file and model.\n";
			exit(1);
		}
	}

	void Process(float t) {
		if (t == 0) {
			theta = theta0;
			thetaDot = thetaDot0;
		}
		claw.SetInputs(stick1, stick2, theta, thetaDot);
		claw.Process(t);
		plant.SetInputs(claw.GetActuator1Cmd(), claw.GetActuator2Cmd());
		plant.Process(t);
		theta = plant.GetTheta();
		thetaDot = plant.GetThetaDot();
	}
};
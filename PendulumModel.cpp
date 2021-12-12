#include "PendulumModel.h"
#include <iostream>

PendulumModel::PendulumModel() {
	paramNames = {"theta0", "thetaDot0"};
	inputNames = {"stick1", "stick2"};
	outputNames = {"theta", "thetaDot"};
}

void PendulumModel::Process(float t) {
	if (t == 0) {
		theta = theta0;
		thetaDot = thetaDot0;
	}
	actuatorCmd1 = .1 * stick1;
	actuatorCmd2 = .1 * stick2;
	theta = actuatorCmd1 + actuatorCmd2;
	thetaDot = theta / 3;
}

void PendulumModel::SetParam(int index, std::string valueString) {
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

void PendulumModel::SetInput(int index, std::string valueString) {
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

std::string PendulumModel::GetOutput(int index) {
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
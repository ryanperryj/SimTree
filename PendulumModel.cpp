#include "PendulumModel.h"
#include "SignalMath.h"
#include <iostream>

PendulumModel::PendulumModel()
	: Model({"m", "l", "theta0", "thetaDot0"}, {}, {"theta"}) {}

void PendulumModel::Process(float t, const float dt) {
	if (t == 0) {
		theta = theta0;
		thetaDot = thetaDot0;
	}
	else {
		static Integrator thetaDotInt(thetaDot0, dt);
		thetaDot = thetaDotInt.Calculate(thetaDotDot);

		static Integrator thetaInt(theta0, dt);
		theta = thetaInt.Calculate(thetaDot);
	}
	thetaDotDot = -g / l * sin(theta) - c / l * copysignf(powf(thetaDot, 2), thetaDot);
}

void PendulumModel::SetParam(const int index, const std::string& valueString) {
	switch (index) {
	case 0:
		m = std::stof(valueString);
		break;
	case 1:
		l = std::stof(valueString);
		break;
	case 2:
		theta0 = std::stof(valueString);
		break;
	case 3:
		thetaDot0 = std::stof(valueString);
		break;
	default:
		std::cerr << "Given parameter index out of bounds! Possible mismatch between parameter file and model.\n";
		exit(1);
	}
}

void PendulumModel::SetInput(const int index, const std::string& valueString) {
	switch (index) {
	default:
		std::cerr << "Given input index out of bounds! Possible mismatch between input file and model.\n";
		exit(1);
	}
}

std::string PendulumModel::GetParam(const int index) const {
	switch (index) {
	case 0:
		return std::to_string(m);
	case 1:
		return std::to_string(l);
	case 2:
		return std::to_string(theta0);
	case 3:
		return std::to_string(thetaDot0);
	default:
		std::cerr << "Given parameter index out of bounds! Possible mismatch between parameter file and model.\n";
		exit(1);
	}
}

std::string PendulumModel::GetInput(const int index) const {
	switch (index) {
	default:
		std::cerr << "Given output index out of bounds! Possible mismatch between output file and model.\n";
		exit(1);
	}
}

std::string PendulumModel::GetOutput(const int index) const {
	switch (index) {
	case 0:
		return std::to_string(theta);
	default:
		std::cerr << "Requested output index out of bounds! Possible mismatch between output file and model.\n";
		exit(1);
	}
}
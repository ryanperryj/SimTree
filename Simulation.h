#pragma once
#include "Model.h"

class Simulation {
private:
	Model* model;
	std::string paramFileName;
	std::string inputFileName;
	std::string outputFileName;
public:
	Simulation(Model* _model, std::string _paramFileName, std::string _inputFileName, std::string _outputFileName);

	void Simulate(const float tFinal) { Simulate(tFinal, 0.1f);	};
	void Simulate(const float tFinal, const float dt);

	void ReadParamFile();
	float ReadInputFile();
	void WriteOutputFile(float t);
};
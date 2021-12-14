#pragma once
#include "Model.h"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem.hpp"

namespace bfs = boost::filesystem;

class Simulation {
public:
	Simulation(Model& _model, const bfs::path& _paramFilePath, const bfs::path& _inputFilePath, const bfs::path& _outputFilePath);

	void Simulate(const float tFinal) { Simulate(tFinal, 0.1f); };
	void Simulate(const float tFinal, const float dt);

	// reads from paramFilePath and initializes the model data with the appropriate parameters
	void ReadParamFile();
	// reads from inputFilePath for the given time, and updates the model data with the appropriate inputs using a Zero-Order-Hold approach
	void ReadInputFile(float t);
	// writes to outputFilePath for the given time, including a header on the first call
	void WriteOutputFile(float t);

private:
	Model& model;
	const bfs::path& paramFilePath;
	const bfs::path& inputFilePath;
	const bfs::path& outputFilePath;
};
#include "Simulation.h"
#include <fstream>

Simulation::Simulation(Model* _model, std::string _parameterFileName, std::string _inputFileName, std::string _outputFileName)
	: model(_model),
	parameterFileName(_parameterFileName), 
	inputFileName(_inputFileName), 
	outputFileName(_outputFileName) {}

void Simulation::Simulate(const float tFinal, const float dt) {

	ReadParameterFile();

	float tNextInput = ReadInputFile();

	const int nSteps = int(tFinal / dt) + 1;
	for (int i = 0; i < nSteps; i++) {
		float t = i * dt;

		// update inputs
		if (t == tNextInput) {
			std::cout << "t: " << t << "\n";
			tNextInput = ReadInputFile();
		}
		//model->Process();
		WriteOutputFile(t);
	}
}

void Simulation::ReadParameterFile() {
	std::ifstream parameterFile(parameterFileName);
	if (!parameterFile) {
		std::cerr << parameterFileName << " could not be opened!\n";
		exit(1);
	}

	// skip the header
	char c;
	do {
		parameterFile.get(c);
	}
	while (c != '\n');

	static int column = 0;
	std::string s = "";
	do {
		parameterFile.get(c);
		if (c != ',' && c != '\n')
			s += c;
		else {
			if (s != "")
				model->SetParameter(column, s); 
			else {
				std::cerr << "Must give a value for a parameter!\n";
				exit(1);
			}
			column++;
			s = "";
		}
	}
	while (c != '\n' && !parameterFile.eof());
}

 float Simulation::ReadInputFile() {
	static std::ifstream inputFile(inputFileName);
	if (!inputFile) {
		std::cerr << inputFileName << " could not be opened!\n";
		exit(1);
	}

	// skip the header on the first call
	static bool first = true;
	char c;
	if (first) {
		do {
			inputFile.get(c);
		}
		while (c != '\n');
	}

	float tInput = -1;
	static int column = 0;
	bool reachedLineEnd = false;
	std::string s = "";
	do {
		inputFile.get(c);
		if (c != ',' && c != '\n')
			s += c;
		else {
			if (s != "") {
				if (column == 0) { // time of the input (tInput) is always in column 0
					tInput = std::stof(s);
					std::cout << "tInput: " << tInput << "\n";
				}
				else
					model->SetInput(column - 1, s); // SetInput calls for an index of the input starting at 0, but time is not included, hence the - 1
			}

			if (c == '\n') {
				column = 0;
				reachedLineEnd = true;
			}
			else
				column++;
			s = "";
		}
	}
	while ((!reachedLineEnd || column != 1) && !inputFile.eof()); // read the tInput of the next line and then stop

	first = false;
	return tInput;
}

 void Simulation::WriteOutputFile(float t) {
	 static std::ofstream outputFile(outputFileName);

	 auto outputNames = model->GetOutputNames();

	 static bool first = true;
	 if (first) {
		 outputFile << "t";
		 for (auto i = outputNames.begin(); i != outputNames.end(); i++) {
			 outputFile << "," << *i;
		 }
		 outputFile << "\n";
	 }

	 outputFile << t;
	 for (int i = 0; i < outputNames.size(); i++) {
		 outputFile << "," << model->GetOutput(i);
	 }
	 outputFile << "\n";

	 first = false;
 }
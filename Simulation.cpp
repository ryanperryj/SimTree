#include "Simulation.h"

Simulation::Simulation(Model& _model, const bfs::path& _paramFilePath, const bfs::path& _inputFilePath, const bfs::path& _outputFilePath)
	: model(_model),
	paramFilePath(_paramFilePath), 
	inputFilePath(_inputFilePath), 
	outputFilePath(_outputFilePath) {}

void Simulation::Simulate(const float tFinal, const float dt) {
	ConfirmFiles();
	ReadParamFile();

	const int nSteps = int(tFinal / dt) + 1;
	for (int i = 0; i < nSteps; i++) {
		float t = i * dt;

		if (model.HasInputs())
			ReadInputFile(t);

		model.Process(t, dt);
		WriteOutputFile(t);
	}
}

void Simulation::ConfirmFiles() {
	int choice;
	if (bfs::exists(outputFilePath)) {
		std::cout << "\nAre you sure you want to overwrite " << outputFilePath << "? Enter 1 for yes, 2 for no: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			break;
		case 2:
			exit(1);
		default:
			std::cerr << "Not an option!\n";
			exit(1);
		}
	}
	if (!bfs::exists(paramFilePath) || (!bfs::exists(inputFilePath) && model.HasInputs())) {
		if (!bfs::exists(paramFilePath))
			CreateTemplateParamFile();
		if (!bfs::exists(inputFilePath) && model.HasInputs())
			CreateTemplateInputFile();

		std::cout << "\nEdit, save, and close new template files, then enter 1: ";
		std::cin >> choice;
	}
}

void Simulation::ReadParamFile() {
	bfs::ifstream paramFile(paramFilePath);
	if (!paramFile) {
		std::cerr << paramFilePath << " could not be opened!\n";
		exit(1);
	}

	// skip the header
	char c;
	do {
		paramFile.get(c);
	}
	while (c != '\n');

	static int column = 0;
	std::string s = "";
	do {
		paramFile.get(c);
		if (c != ',' && c != '\n')
			s += c;
		else {
			if (s != "")
				model.SetParam(column, s); 
			else {
				std::cerr << "Must give a value for a param!\n";
				exit(1);
			}
			column++;
			s = "";
		}
	}
	while (c != '\n' && !paramFile.eof());
}

void Simulation::ReadInputFile(float t) {

	// only read inputs when it is the right time
	static float tNextInput = 0;
	if (t != tNextInput)
		return;
	
	// open file
	static bfs::ifstream inputFile(inputFilePath);
	if (!inputFile) {
		std::cerr << inputFilePath << " could not be opened!\n";
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

	static int column = 0;
	bool reachedLineEnd = false;
	std::string s = "";
	do {
		inputFile.get(c);
		if (c != ',' && c != '\n')
			s += c;
		else {
			if (s != "") {
				if (column == 0) // time of the input (tInput) is always in column 0
					tNextInput = std::stof(s);
				else
					model.SetInput(column - 1, s); // SetInput calls for an index of the input starting at 0, but time is not included, hence the - 1
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
}

void Simulation::WriteOutputFile(float t) {
	static bool first = true;
	if (first && !bfs::exists(outputFilePath))
		std::cout << "\nCreated " << outputFilePath << ".\n";

	static bfs::ofstream outputFile(outputFilePath);

	auto paramNames = model.GetParamNames();
	auto inputNames = model.GetInputNames();
	auto outputNames = model.GetOutputNames();

	if (first) {
		for (auto i = paramNames.begin(); i != paramNames.end(); i++)
			outputFile << *i << ",";
		outputFile << "t";
		for (auto i = inputNames.begin(); i != inputNames.end(); i++)
			outputFile << "," << *i;
		for (auto i = outputNames.begin(); i != outputNames.end(); i++)
			outputFile << "," << *i;
		outputFile << "\n";
	}

	for (unsigned int i = 0; i < paramNames.size(); i++) {
		if (first)
			outputFile << model.GetParam(i);
		outputFile << ",";
	}
	outputFile << t;
	for (unsigned int i = 0; i < inputNames.size(); i++)
		outputFile << "," << model.GetInput(i);
	for (unsigned int i = 0; i < outputNames.size(); i++)
		outputFile << "," << model.GetOutput(i);
	outputFile << "\n";

	first = false;
 }

void Simulation::CreateTemplateParamFile() {
	bfs::ofstream paramFile(paramFilePath);

	auto paramNames = model.GetParamNames();
	for (auto i = paramNames.begin(); i != paramNames.end(); i++) {
		if (i != paramNames.begin())
			paramFile << ",";
		paramFile << *i;
	}
	paramFile << "\n";
	for (auto i = paramNames.begin(); i != paramNames.end(); i++) {
		if (i != paramNames.begin())
			paramFile << ",";
		paramFile << "-";
	}
	paramFile << "\n";
	
	std::cout << "Created " << paramFilePath << " as a template.\n";
}

void Simulation::CreateTemplateInputFile() {
	bfs::ofstream inputFile(inputFilePath);

	auto inputNames = model.GetInputNames();
	inputFile << "t";
	for (auto i = inputNames.begin(); i != inputNames.end(); i++)
		inputFile << "," << *i;
	inputFile << "\n";
	inputFile << "0";
	for (auto i = inputNames.begin(); i != inputNames.end(); i++)
		inputFile << "," << "-";
	inputFile << "\n";

	std::cout << "Created " << inputFilePath << " as a template.\n";
}
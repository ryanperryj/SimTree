#include "Blocks.h"
#include <fstream>

struct InputStruct {
	float tKey;
	int simRootInput;
	float plantInput;
};

void ReadInputFile(InputStruct& inputStruct, std::string inputFileName);

int main() {
	std::string inputFileName = "InputFile1.csv";



	SimRoot simRoot("SimRoot", 0);
	Claw claw("Claw", &simRoot);
	Plant plant("Plant", &simRoot, &claw);
	std::vector<Node*> allNodes{&simRoot, &claw, &plant};

	const float dt = .1;
	const float tFinal = 10;
	const int nSteps = tFinal / dt + 1;
	InputStruct inputStruct;
	ReadInputFile(inputStruct, inputFileName);
	for (int i = 0; i < nSteps; i++) {
		float t = i * dt;

		// update inputs
		if (t == inputStruct.tKey) {
			simRoot.SetInputs(inputStruct.simRootInput);
			plant.SetInputs(inputStruct.plantInput);
			ReadInputFile(inputStruct, inputFileName);
		}


		simRoot.Propagate();
	}


	std::cin.get();

	return 0;
}

void ReadInputFile(InputStruct& inputStruct, std::string inputFileName) {
	// assigns the values of inputStruct to the next line in the given csv file each time it is called
	static bool first = true;
	static std::ifstream inputFile(inputFileName);

	if (inputFile.eof())
		return;
	
	if (!inputFile) {
		std::cerr << inputFileName << " could not be opened!\n";
		exit(1);
	}

	// skip the header on the first function call
	char c;
	if (first) {
		do {
			inputFile.get(c);
		}
		while (c != '\n');
	}

	// loop through line and set each struct value if there is one
	int column = 1;
	std::string s = "";
	do {
		inputFile.get(c);
		if (c != ',' && c != '\n' && int(c) >= 0)
			s += c;
		else {
			if (s != "") {
				switch (column) {
				case 1:
					inputStruct.tKey = std::stof(s);
					break;
				case 2:
					inputStruct.simRootInput = std::stoi(s);
					break;
				case 3:
					inputStruct.plantInput = std::stof(s);
					break;
				}
			}
			column++;
			s = "";
		}
	}
	while (c != '\n' && !inputFile.eof());

	first = false;
	return;
}
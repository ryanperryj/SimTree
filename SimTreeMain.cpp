#include "Simulation.h"
#include "PendulumModel.h"
#include "ExampleModel.h"

#include "SignalMath.h"

void printWithPrefix(bfs::path dir, std::string prefix);

int main() {
	int choice;
	/*std::cout << "1: Load simulation recipe\n2: Manually setup simulation\nEnter choice: ";
	std::cin >> choice;

	Simulation* sim;
	switch (choice) {
	case 1:
		sim = new Simulation();
		break;
	case 2:
		break;*/

	std::cout << "1: Pendulum\n2: Example\nEnter model number choice: ";
	std::cin >> choice;

	// Choose model
	Model* model;
	bfs::path modelDir;
	switch (choice) {
	case 1:
		model = new PendulumModel();
		modelDir = "Pendulum";
		break;
	case 2:
		model = new ExampleModel();
		modelDir = "Example";
		break;
	default:
		std::cerr << "Not an option!\n";
		exit(1);
	}

	// Choose param file
	printWithPrefix(modelDir, "ParamFile");
	std::cout << "Enter parameter file number choice: ";
	std::cin >> choice;
	bfs::path paramFilePath = modelDir / ("ParamFile" + std::to_string(choice) + ".csv");
	if (!bfs::exists(paramFilePath)) {
		std::cerr << paramFilePath << " does not exist!\n";
		exit(1);
	}

	// Choose input file if model has inputs
	bfs::path inputFilePath;
	if (model->HasInputs()) {
		printWithPrefix(modelDir, "InputFile");
		std::cout << "Enter input file number choice: ";
		std::cin >> choice;
		inputFilePath = modelDir / ("InputFile" + std::to_string(choice) + ".csv");
		if (!bfs::exists(inputFilePath)) {
			std::cerr << inputFilePath << " does not exist!\n";
			exit(1);
		}
	}

	// Choose output file
	printWithPrefix(modelDir, "OutputFile");
	std::cout << "Enter output file number choice, or a new number to create a new file: ";
	std::cin >> choice;
	bfs::path outputFilePath = modelDir / ("OutputFile" + std::to_string(choice) + ".csv");
	if (bfs::exists(outputFilePath)) {
		std::cout << "Are you sure you want to overwrite " << outputFilePath << "? Enter 1 for yes, 2 for no: ";
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

	// Choose simulation time
	float tFinal;
	std::cout << "Enter simulation time: ";
	std::cin >> tFinal;

	Simulation sim(*model, paramFilePath, inputFilePath, outputFilePath);
	sim.Simulate(tFinal);

	delete model;
	return 0;
}

void printWithPrefix(bfs::path dir, std::string prefix) {
	int i = 1;
	bfs::path path = dir / (prefix + std::to_string(i) + ".csv");
	while (bfs::exists(path)) {
		std::cout << i << ": " << prefix + std::to_string(i) + ".csv" << "\n";
		i++;
		path = dir / (prefix + std::to_string(i) + ".csv");
	}
}
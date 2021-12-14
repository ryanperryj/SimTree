#include "Simulation.h"
#include "PendulumModel.h"
#include "ExampleModel.h"

#include "SignalMath.h"

void printWithPrefix(bfs::path dir, std::string prefix);

int main() {
	int choice;
	std::cout << "1: Example\n2: Pendulum\nEnter model number choice: ";
	std::cin >> choice;

	// Choose model
	Model* model;
	bfs::path modelDir;
	switch (choice) {
	case 1:
		model = new ExampleModel();
		modelDir = "Example";
		break;
	case 2:
		model = new PendulumModel();
		modelDir = "Pendulum";
		break;
	default:
		std::cerr << "Not an option!\n";
		exit(1);
	}
	if (!bfs::exists(modelDir))
		bfs::create_directory(modelDir);

	// Choose param file
	std::cout << "\n";
	printWithPrefix(modelDir, "ParamFile");
	std::cout << "Enter parameter file number choice, or a new number to create a template file: ";
	std::cin >> choice;
	bfs::path paramFilePath = modelDir / ("ParamFile" + std::to_string(choice) + ".csv");

	// Choose input file if model has inputs
	bfs::path inputFilePath;
	if (model->HasInputs()) {
		std::cout << "\n";
		printWithPrefix(modelDir, "InputFile");
		std::cout << "Enter input file number choice, or a new number to create a template file: ";
		std::cin >> choice;
		inputFilePath = modelDir / ("InputFile" + std::to_string(choice) + ".csv");
	}

	// Choose output file
	std::cout << "\n";
	printWithPrefix(modelDir, "OutputFile");
	std::cout << "Enter output file number choice, or a new number to create a new file: ";
	std::cin >> choice;
	bfs::path outputFilePath = modelDir / ("OutputFile" + std::to_string(choice) + ".csv");


	// Choose simulation time
	float tFinal;
	std::cout << "\nEnter simulation time: ";
	std::cin >> tFinal;

	Simulation sim(*model, paramFilePath, inputFilePath, outputFilePath);
	sim.Simulate(tFinal);

	delete model;

	std::cout << "\nSimulation complete, press any key to continue.";
	std::cin.get();
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
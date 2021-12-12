#include <fstream>
#include "Blocks.h"
#include "Simulation.h"

int main() {
	Model* pendulumModel = new PendulumModel();
	Simulation sim(pendulumModel, "ParameterFile1.csv", "InputFile2.csv", "OutputFile2.csv");
	sim.Simulate(8);

	std::cin.get();
	return 0;
}
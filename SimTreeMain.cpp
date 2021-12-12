#include "Simulation.h"
#include "PendulumModel.h"

int main() {
	Model* pendulumModel = new PendulumModel();
	Simulation sim(pendulumModel, "ParamFile1.csv", "InputFile1.csv", "OutputFile2.csv");
	sim.Simulate(8);

	return 0;
}
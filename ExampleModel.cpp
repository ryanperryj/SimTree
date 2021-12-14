#include "ExampleModel.h"
#include "StringConversions.h"

ExampleModel::ExampleModel()
	: Model({"iParam", "fParam"}, {"sInput", "vfInput"}, {"viOutput", "bOutput"}) {}

void ExampleModel::Process(float t, const float dt) {
	if (t == 0) {
		bOutput = false;
		viOutput = {1, 4, -3};
	}
	else {
		viOutput = {9, 8, -10};
	}
	if (t == 3)
		bOutput = true;
}

void ExampleModel::SetParam(const int index, const std::string& valueString) {
	switch (index) {
	case 0:
		iParam = FromString<int>(valueString);
		break;
	case 1:
		fParam = FromString<float>(valueString);
		break;
	default:
		std::cerr << "Given parameter index out of bounds! Possible mismatch between parameter file and model.\n";
		exit(1);
	}
}

void ExampleModel::SetInput(const int index, const std::string& valueString) {
	switch (index) {
	case 0:
		sInput = valueString;
		break;
	case 1:
		vfInput = VectorFromString<float>(valueString);
		break;
	default:
		std::cerr << "Given input index out of bounds! Possible mismatch between input file and model.\n";
		exit(1);
	}
}

std::string ExampleModel::GetParam(const int index) const {
	switch (index) {
	case 0:
		return std::to_string(iParam);
	case 1:
		return std::to_string(fParam);
	default:
		std::cerr << "Given parameter index out of bounds! Possible mismatch between parameter file and model.\n";
		exit(1);
	}
}

std::string ExampleModel::GetInput(const int index) const {
	switch (index) {
	case 0:
		return sInput;
	case 1:
		return VectorToString<float>(vfInput);
	default:
		std::cerr << "Given output index out of bounds! Possible mismatch between output file and model.\n";
		exit(1);
	}
}

std::string ExampleModel::GetOutput(const int index) const {
	switch (index) {
	case 0:
		return VectorToString<int>(viOutput);
	case 1:
		return std::to_string(bOutput);
	default:
		std::cerr << "Requested output index out of bounds! Possible mismatch between output file and model.\n";
		exit(1);
	}
}
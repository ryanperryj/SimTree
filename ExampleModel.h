#pragma once
#include "Model.h"

class ExampleModel : public Model {
public:
	ExampleModel();

	void Process(float t, const float dt) override;

	void SetParam(const int index, const std::string& valueString) override;
	void SetInput(const int index, const std::string& valueString) override;
	std::string GetParam(const int index) const override;
	std::string GetInput(const int index) const override;
	std::string GetOutput(const int index) const override;

private:
	// params
	int iParam;
	float fParam;
	// inputs
	std::string sInput;
	std::vector<float> vfInput;
	// outputs
	std::vector<int> viOutput;
	bool bOutput;
};
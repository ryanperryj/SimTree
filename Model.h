#pragma once
#include <vector>
#include <string>
#include <iostream>

class Model {
public:
	Model(const std::vector<std::string> _paramNames, const std::vector<std::string> _inputNames, const std::vector<std::string> _outputNames)
		: paramNames(_paramNames),
		inputNames(_inputNames),
		outputNames(_outputNames),
		hasInputs(!inputNames.empty()) {}

	const bool HasInputs() const { return hasInputs; }

	const std::vector<std::string>& GetParamNames() const { return paramNames; }
	const std::vector<std::string>& GetInputNames() const { return inputNames; }
	const std::vector<std::string>& GetOutputNames() const { return outputNames; }

	// called every time step when simulating
	virtual void Process(float t, const float dt) = 0;

	// sets parameter based off file data that the simulation is reading
	virtual void SetParam(const int index, const std::string& valueString) = 0;
	// sets input based off file data that the simulation is reading
	virtual void SetInput(const int index, const std::string& valueString) = 0;
	// returns string for file output when given a parameters index
	virtual std::string GetParam(const int index) const = 0;
	// returns string for file output when given an inputs index
	virtual std::string GetInput(const int index) const = 0;
	// returns string for file output when given an outputs index
	virtual std::string GetOutput(const int index) const = 0;

protected:
	const std::vector<std::string> paramNames;
	const std::vector<std::string> inputNames;
	const std::vector<std::string> outputNames;
private:
	const bool hasInputs;
};
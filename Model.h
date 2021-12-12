#pragma once
#include <vector>
#include <string>
#include <iostream>

class Model {
protected:
	std::vector<std::string> paramNames;
	std::vector<std::string> inputNames;
	std::vector<std::string> outputNames;
public:
	virtual void Process(float t) = 0;

	virtual void SetParam(int index, std::string valueString) = 0;
	virtual void SetInput(int index, std::string valueString) = 0;
	virtual std::string GetOutput(int index) = 0;

	std::vector<std::string> GetParamNames() { return paramNames; }
	std::vector<std::string> GetInputNames() { return inputNames; }
	std::vector<std::string> GetOutputNames() { return outputNames; }
};
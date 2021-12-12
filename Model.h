#pragma once
#include "Node.h"

class Model : public Node {
protected:
	std::vector<std::string> parameterNames;
	std::vector<std::string> inputNames;
	std::vector<std::string> outputNames;
public:
	virtual void SetParameter(int index, std::string valueString) = 0;
	virtual void SetInput(int index, std::string valueString) = 0;
	virtual std::string GetOutput(int index) = 0;

	std::vector<std::string> GetParameterNames() { return parameterNames; }
	std::vector<std::string> GetInputNames() { return inputNames; }
	std::vector<std::string> GetOutputNames() { return outputNames; }
};
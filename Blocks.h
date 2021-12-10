#pragma once
#include "Node.h"

class SimRoot : public Node {
private:
	int simRootInput;
public:
	using Node::Node;

	void SetInputs(int _simRootInput) {
		simRootInput = _simRootInput;
	}

	void Process() {
		std::cout << label << " processed.\n";
	}
};

class Claw : public Node {
public:
	using Node::Node;

	void SetInputs() {}

	virtual void Process() {
		std::cout << label << " processed.\n";
	}
};

class Plant : public Node {
private:
	float plantInput;
public:
	using Node::Node;

	void SetInputs(float _plantInput) {
		plantInput = _plantInput;
	}

	virtual void Process() {
		std::cout << label << " processed.\n";
	}
};

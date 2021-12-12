#pragma once
#include <vector>
#include <string>
#include <iostream>

class Node {
protected:
	const std::string label;
	std::vector<Node*> childNodes;
public:
	virtual void Process(float t) = 0;
	void AddChildNode(Node* _childNode);
};
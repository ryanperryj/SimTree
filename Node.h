#pragma once
#include <vector>

class Node {
	// 
protected:
	std::vector<Node*> children;
	Node* parent;
public:
	Node(Node* _parent);
	void AddChild(Node* _child);
	void Process();
};
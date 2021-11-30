#include "Node.h"
#include <iostream>

Node::Node(Node* _parent) 
	: parent(_parent) 
{
	if (parent)
		parent->AddChild(this);
}

void Node::AddChild(Node* _child) {
	children.push_back(_child);
}

void Node::Process() {
	for (std::vector<Node*>::iterator i = children.begin(); i != children.end(); i++) {
		(*i)->Process();
	}
	std::cout << this << " processed.\n";
}
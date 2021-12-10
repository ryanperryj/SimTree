#pragma once
#include <vector>
#include <string>
#include <iostream>

class Node {
protected:
	bool processedThisFrame = false;
	const std::string label;

	// !!! downstreamNodes and parentNode are possibly useless, and perhaps shouldn't exist. Tree nodes often don't have knowledge of their parents !!!

	std::vector<Node*> downstreamNodes; // parents in the dependency tree
	std::vector<Node*> upstreamNodes; // children in the dependency tree
	std::vector<Node*> subTreeHeadNodes; // each block can be a subsystem with it's own dependency tree inside, where the heads are the most downstream nodes
	Node* parentNode;
public:
	Node(std::string _label, Node* _parentNode);
	Node(std::string _label, Node* _parentNode, Node* _downstreamNode);
	Node(std::string _label, Node* _parentNode, std::vector<Node*> _downstreamNodes);

	void Propagate();
	virtual void Process() = 0;

	void AddUpstreamNode(Node* _upstreamNode);
	void AddUpstreamNodes(std::vector<Node*> _upstreamNodes);

	void AddSubTreeHeadNode(Node* _subTreeHeadNode);
	void AddSubTreeHeadNodes(std::vector<Node*> _subTreeHeadNodes);
};
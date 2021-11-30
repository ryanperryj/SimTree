#pragma once
#include <vector>
#include <string>
#include <iostream>

class Node {
	// 
protected:
	bool processedThisFrame = false;
	const std::string label;



	std::vector<Node*> upstreamNodes; // children
	std::vector<Node*> downstreamNodes; // parents
	std::vector<Node*> subTreeHeadNodes; // each block can be a subsystem with it's own diagram inside, where the heads are the most downstream nodes
	Node* subTreeParentNode;
public:
	Node(std::string _label);
	Node(std::string _label, Node* _downstreamNode);
	Node(std::string _label, std::vector<Node*> _downstreamNodes);

	void Process();

	void AddUpstreamNode(Node* _upstreamNode);
	void AddUpstreamNodes(std::vector<Node*> _upstreamNodes);

	void AddSubTreeHeadNode(Node* _subTreeHeadNode);
	void AddSubTreeHeadNodes(std::vector<Node*> _subTreeHeadNodes);
};
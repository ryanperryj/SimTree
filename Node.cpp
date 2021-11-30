#include "Node.h"

Node::Node(std::string _label)
	: label(_label) {}

Node::Node(std::string _label, Node* _downstreamNode)
	: Node(_label, std::vector<Node*>(1, _downstreamNode)) {}

Node::Node(std::string _label, std::vector<Node*> _downstreamNodes)
	: label(_label), downstreamNodes(_downstreamNodes) {

	for (std::vector<Node*>::iterator i = downstreamNodes.begin(); i != downstreamNodes.end(); i++)
		(*i)->AddUpstreamNode(this);
}

void Node::Process() {
	if (processedThisFrame)
		return;
	processedThisFrame = true;

	for (std::vector<Node*>::iterator i = upstreamNodes.begin(); i != upstreamNodes.end(); i++)
		(*i)->Process();
	for (std::vector<Node*>::iterator i = subTreeHeadNodes.begin(); i != subTreeHeadNodes.end(); i++)
		(*i)->Process();

	std::cout << label << " processed.\n";
}

void Node::AddUpstreamNode(Node* _node) {
	upstreamNodes.push_back(_node);
}
void Node::AddUpstreamNodes(std::vector<Node*> _nodes) {
	upstreamNodes.insert(upstreamNodes.end(), _nodes.begin(), _nodes.end());
}
void Node::AddSubTreeHeadNode(Node* _node) {
	subTreeHeadNodes.push_back(_node);
}
void Node::AddSubTreeHeadNodes(std::vector<Node*> _nodes) {
	subTreeHeadNodes.insert(subTreeHeadNodes.end(), _nodes.begin(), _nodes.end());
}
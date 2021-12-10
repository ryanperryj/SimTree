#include "Node.h"

Node::Node(std::string _label, Node* _parentNode)
	: Node(_label, _parentNode, std::vector<Node*>()) {}

Node::Node(std::string _label, Node* _parentNode, Node* _downstreamNode)
	: Node(_label, _parentNode, std::vector<Node*>(1, _downstreamNode)) {}

Node::Node(std::string _label, Node* _parentNode, std::vector<Node*> _downstreamNodes)
	: label(_label), 
	parentNode(_parentNode), 
	downstreamNodes(_downstreamNodes) {

	std::cout << "Node " << label << " constructed.\n";

	// if there are no downstream nodes and it isn't the outermost tree, then this is a head of the sub tree
	if (downstreamNodes.empty() && parentNode)
		parentNode->AddSubTreeHeadNode(this);

	for (std::vector<Node*>::iterator i = downstreamNodes.begin(); i != downstreamNodes.end(); i++)
		(*i)->AddUpstreamNode(this);
}

void Node::Propagate() {
	if (processedThisFrame)
		return;
	processedThisFrame = true;

	//std::cout << "Node " << label << " propagated.\n";
	for (std::vector<Node*>::iterator i = upstreamNodes.begin(); i != upstreamNodes.end(); i++)
		(*i)->Propagate();
	for (std::vector<Node*>::iterator i = subTreeHeadNodes.begin(); i != subTreeHeadNodes.end(); i++)
		(*i)->Propagate();

	this->Process();
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
#include "Node.h"

Node::Node(const std::string& value) :
	m_value(value)
{};

void Node::reverseTree()
{
	std::reverse(m_childs.begin(), m_childs.end());
	for (auto& child : m_childs)
		child->reverseTree();
}

void Node::addChild(std::string& value)
{
	m_childs.push_back(std::make_unique<Node>(value));
	m_childs.back()->setParent(this);
}

#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include "Grammar.h"

class Node
{
public:
	Node(const std::string& value);
	std::string value() const;
	Node* child(int index) const;
	Node* backChild();
	void addChild(std::string& value);
	void setParent(Node* parent);
	Node* parent() const;
	void setValue(const std::string& value);
	void printTree(int level);
	void reverseTree();
	int childsSize() const;
	void collectTokens();
	void calcExpression();
	double calculatedValue();
	std::string expression();
	void clear();

private:
	std::string m_value;
	Node* m_parent{nullptr};
	std::vector<std::unique_ptr<Node>> m_childs;
	double m_calculatedValue{ 0 };
	std::vector<std::pair<std::string, bool>> m_tokens;
	std::vector<std::pair<std::string, bool>> m_postfixTokens;
	std::string m_expression{""};
};

inline Node* Node::parent() const
{
	return m_parent;
}

inline void Node::setParent(Node* parent)
{
	m_parent = parent;
}

inline double Node::calculatedValue()
{
	return m_calculatedValue;
}

inline std::string Node::expression()
{
	return m_expression;
}

inline int Node::childsSize() const
{
	return m_childs.size();
}

inline Node* Node::backChild()
{
	return m_childs.back().get();
}

inline void Node::setValue(const std::string& value)
{
	m_value = value;
}

inline std::string Node::value() const
{
	return m_value;
}

inline Node* Node::child(int index) const
{
	return m_childs[index].get();
}

#endif // NODE_H

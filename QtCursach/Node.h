#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Node
{
public:
    Node(Node* parent, string& value);
    string value() const;
    Node* parent() const;
    Node* child(int inx) const;
    Node* backChild();
    void addChild(string& value);
    void setParent(Node* parent);
    void setValue(string& value);
    void printTree(int level);
    void reverseTree();
    int childsSize();
    void collectTokens();
    void calcExpression();
    double calcValue();
    string expression();

private:
    string m_value;
    Node* m_parent;
    vector<unique_ptr<Node>> m_childs;
    double m_calcValue{ 0 };
    vector<pair<string, bool>> m_tokens;
    vector<pair<string, bool>> m_postfixTokens;
    string m_expression{ "" };
};

inline double Node::calcValue()
{
    return m_calcValue;
}

#endif // NODE_H

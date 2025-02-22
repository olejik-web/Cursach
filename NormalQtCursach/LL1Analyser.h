#ifndef LL1ANALYSER_H
#define LL1ANALYSER_H

#include <map>
#include <set>
#include <string>
#include <stack>
#include <vector>
#include <QDebug>
#include <QString>
#include "Grammar.h"
#include "Node.h"

class LL1Analyser
{
public:
	explicit LL1Analyser(Grammar* grammar = nullptr, bool* isLL = nullptr);
	std::set<std::string> fromTokensFirst(
		const std::vector<std::string>& tokens);
	void printFirst() const;
	void printFollow() const;
	void printSyntaxAnalyseTable() const;
	std::set<std::string> intersectonOfSets(std::set<std::string> a,
		std::set<std::string> b) const;
	Node* parseTree();
	void initialiseFirst();
	void initialiseFollow();
	void initialiseSyntaxAnalyseTable();
	bool grammarCanParse();
	bool analyseExpression(std::string expression);

private:
	std::unique_ptr<Node> m_parseTree;
	Grammar* m_grammar;
	std::map<std::string, std::set<std::string>> m_first;
	std::map<std::string, std::set<std::string>> m_follow;
	std::map<std::string, std::map<std::string, std::vector<
	std::pair<std::string, std::vector<std::string>>>>> m_syntaxAnalyseTable;
};

inline Node* LL1Analyser::parseTree()
{
	return m_parseTree.get();
}

#endif // LL1ANALYSER_H

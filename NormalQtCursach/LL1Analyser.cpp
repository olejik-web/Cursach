#include "LL1Analyser.h"

LL1Analyser::LL1Analyser(Grammar* grammar, bool* isLL) :
	m_grammar(grammar)
{
	initialiseFirst();
	initialiseFollow();
	if (isLL)
		*isLL = grammarCanParse();
	if (*isLL)
		initialiseSyntaxAnalyseTable();

}

void LL1Analyser::printFollow() const
{
	for (auto p : m_follow)
	{
		QDebug info = qInfo();
		info << QString::fromStdString(p.first) << ": {";
		if (p.second.size() > 0)
		{
			for (std::set<std::string> ::iterator it = p.second.begin();
				it != --p.second.end(); it++)
			{
				if ((*it).empty())
					info << "eps";
				else
					info << QString::fromStdString(*it);
				info << ", ";
			}
			if ((*(--p.second.end())).empty())
				info << "eps";
			else
				info << QString::fromStdString(*(--p.second.end()));
		}
		info << "}";
	}
}


void LL1Analyser::printFirst() const
{
	for (auto p : m_first)
	{
		QDebug info = qInfo();
		info << QString::fromStdString(p.first) << ": {";
		if (p.second.size() > 0)
		{
			for (std::set<std::string> ::iterator it = p.second.begin();
				 it != --p.second.end(); it++)
			{
				if ((*it).empty())
					info << "eps";
				else
					info << QString::fromStdString(*it);
				info << ", ";
			}
			if ((*(--p.second.end())).empty())
				info << "eps";
			else
				info << QString::fromStdString(*(--p.second.end()));
		}
		info << "}";
	}
}

std::set<std::string> LL1Analyser::intersectonOfSets(
	std::set<std::string> a, std::set<std::string> b) const
{
	std::set<std::string>intersectionSet;
	while (!a.empty() && !b.empty())
	{
		if (*a.begin() < *b.begin())
			a.erase(a.begin());
		else if (*a.begin() > *b.begin())
			b.erase(b.begin());
		else
		{
			intersectionSet.insert(*a.begin());
			a.erase(a.begin());
			b.erase(b.begin());
		}
	}
	return intersectionSet;
}

bool LL1Analyser::analyseExpression(std::string expression)
{
	m_parseTree = std::make_unique<Node>(m_grammar->startNotTerminal());
	expression += "$";
	// qInfo() << QString::fromStdString(expression);
	std::stack<Node*> expressionStack;
	std::string endSymbol = "$";
	std::unique_ptr<Node> endNode =
		std::make_unique<Node>(endSymbol);
	expressionStack.push(endNode.get());
	expressionStack.push(m_parseTree.get());
	int ip = 0;
	std::string currentString = "";
	while (expressionStack.top()->value() != "$")
	{
		Node* parentNode = expressionStack.top();
		std::string X = expressionStack.top()->value();
		if (currentString.empty())
		{
			for (auto terminal : *m_grammar->terminals())
			{
				if (expression.substr(ip, terminal.size()) == terminal)
				{
					currentString = terminal;
					break;
				}
			}
			if (expression.substr(ip) == "$")
				currentString = "$";
		}
		if (X == currentString)
		{
			// cout << "equality: " << X << "\n";
			expressionStack.pop();
			ip += currentString.size();
			currentString = "";
		}
		else {
			bool flag = false;
			for (auto notTerminal : *m_grammar->notTerminals())
			{
				if (X == notTerminal)
				{
					if (m_syntaxAnalyseTable[X][currentString].empty())
						return false;
					else
					{
						flag = true;
						std::pair<std::string, std::vector<std::string>>
							porno = m_syntaxAnalyseTable[X][
							currentString][0];
						// cout << p.first << "-->";
						// for (auto c : p.second)
						//   cout << c;
						// cout << "\n";
						expressionStack.pop();
						std::vector<std::string>tmp = porno.second;
						std::reverse(tmp.begin(), tmp.end());
						for (auto chegivara : tmp)
						{
							if (!chegivara.empty())
							{
								parentNode->addChild(chegivara);
								expressionStack.push(
									parentNode->backChild());
							}
						}
						break;
					}
				}
			}
			if (!flag)
				return false;
		}
	}
	m_parseTree->reverseTree();
	return true && expression[ip] == '$';
}

void LL1Analyser::initialiseFirst()
{
	for (auto s : *m_grammar->terminals())
		m_first[s].insert(s);
	m_first[""].insert("");
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (auto notTerminal : *m_grammar->notTerminals())
		{
			int startCount = m_first[notTerminal].size();
			for (auto tokens : (*m_grammar->tokensStructure())[notTerminal])
			{
				bool haveEpsilon;
				for (int i = 0; i < tokens.size(); i++)
				{
					haveEpsilon = true;
					for (int j = 0; j < i && haveEpsilon; j++)
						haveEpsilon = m_first[tokens[j]].find("")
							!= m_first[tokens[j]].end();
					if (haveEpsilon)
					{
						for (auto a : m_first[tokens[i]])
							m_first[notTerminal].insert(a);
					}
				}
				haveEpsilon = true;
				for (int i = 0; i < tokens.size() && haveEpsilon; i++)
					haveEpsilon = m_first[tokens[i]].find("")
						!= m_first[tokens[i]].end();
				if (haveEpsilon)
					m_first[notTerminal].insert("");
			}
			flag = flag || startCount < m_first[notTerminal].size();
		}
	}
}

void LL1Analyser::initialiseFollow()
{
	m_follow[m_grammar->startNotTerminal()].insert("$");
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (auto notTerminal : *m_grammar->notTerminals())
		{
			for (auto tokens : (*m_grammar->tokensStructure())[notTerminal])
			{
				std::vector<std::string>afterTokens = tokens;
				std::reverse(afterTokens.begin(), afterTokens.end());
				for (std::size_t i = 0; i < tokens.size(); i++)
				{
					afterTokens.pop_back();
					if (m_grammar->tokensStructure()->find(tokens[i])
							!= m_grammar->tokensStructure()->end())
					{
						std::reverse(afterTokens.begin(),
							afterTokens.end());
						std::set<std::string> gettedFirst =
							fromTokensFirst(afterTokens);
						std::reverse(afterTokens.begin(),
							afterTokens.end());
						int startCount = m_follow[tokens[i]].size();
						for (auto s : gettedFirst)
						{
							if (!s.empty())
								m_follow[tokens[i]].insert(s);
						}
						if (gettedFirst.find("") != gettedFirst.end())
						{
							for (auto s : m_follow[notTerminal])
								m_follow[tokens[i]].insert(s);
						}
						flag = flag ||
							startCount < static_cast<int>(
							m_follow[tokens[i]].size());
					}
				}
			}
		}
	}
}

bool LL1Analyser::grammarCanParse()
{
	bool isLL = true;
	for (auto token : *m_grammar->tokensStructure())
	{
		for (std::size_t i = 0; i < token.second.size(); i++)
		{
			std::set<std::string>alphaFirst =
				fromTokensFirst(token.second[i]);
			for (std::size_t j = i + 1; j < token.second.size(); j++)
			{
				std::set<std::string>bettaFirst =
					fromTokensFirst(token.second[j]);
				std::set<std::string>intersectionResult =
					intersectonOfSets(alphaFirst, bettaFirst);
				isLL = isLL && intersectionResult.empty();
				if (alphaFirst.find("") != alphaFirst.end())
				{
					intersectionResult = intersectonOfSets(bettaFirst,
						m_follow[token.first]);
					isLL = isLL && intersectionResult.empty();
				}
			}
		}
	}
	return isLL;
}

void LL1Analyser::printSyntaxAnalyseTable() const
{
	for (auto firstElement : m_syntaxAnalyseTable) // p
	{
		for (auto secondElement : firstElement.second) // v
		{
			QDebug info = qInfo();
			info << "(" << QString::fromStdString(firstElement.first)
				<< ", " << QString::fromStdString(secondElement.first)
				<< "): ";
			for (auto thirdElement : secondElement.second) // q
			{
				info << QString::fromStdString(thirdElement.first) << "-->";
				for (auto fourthElement : thirdElement.second) // c
					info << QString::fromStdString(fourthElement) << " ";
				info << "|";
			}
			info << "size: " << secondElement.second.size();
		}
	}
}

void LL1Analyser::initialiseSyntaxAnalyseTable()
{
	// m_grammar->tokensStructure();
	// m_grammar->terminals();
	// m_grammar->notTerminals();
	std::map<std::string, std::vector<std::pair<std::string,
		std::vector<std::string>>>> terminalsMap;
	for (auto terminal : *m_grammar->terminals())
		terminalsMap[terminal] = std::vector<std::pair<std::string,
			std::vector<std::string>>>();
	terminalsMap["$"] = std::vector<std::pair<std::string,
		std::vector<std::string>>>();
	for (auto notTerminal : *m_grammar->notTerminals())
		m_syntaxAnalyseTable[notTerminal] = terminalsMap;
	for (auto grammarToken : *m_grammar->tokensStructure()) // p
	{
		for (auto tokens : grammarToken.second)
		{
			std::set<std::string> first = fromTokensFirst(tokens);
			for (auto firstElement : first) // a
			{
				if (firstElement.empty())
				{
					for (auto followElement : m_follow[grammarToken.first]) // b
					{
						for (auto terminal : *m_grammar->terminals()) // q
						{
							if (followElement == terminal)
							{
								m_syntaxAnalyseTable[grammarToken.first][
									followElement].push_back(
									{ grammarToken.first, tokens });
								break;
							}
						}
						if (followElement == "$")
							m_syntaxAnalyseTable[grammarToken.first][
								followElement].push_back({
								grammarToken.first, tokens });
					}
				}
				for (auto terminal : *m_grammar->terminals()) // q
				{
					if (terminal == firstElement)
					{
						m_syntaxAnalyseTable[grammarToken.first][
							firstElement].push_back({
							grammarToken.first, tokens });
						break;
					}
				}
			}
		}
	}
}

std::set<std::string> LL1Analyser::fromTokensFirst(
	const std::vector<std::string>& tokens)
{
	std::set<std::string> first;
	bool haveEpsilon = true;
	for (int i = 0; i < static_cast<int>(tokens.size())
		&& haveEpsilon; i++)
	{
		haveEpsilon = false;
		for (auto s : m_first[tokens[i]])
		{
			haveEpsilon = haveEpsilon || s.empty();
			if (!s.empty())
				first.insert(s);
		}
	}
	if (haveEpsilon)
		first.insert("");
	return first;
}

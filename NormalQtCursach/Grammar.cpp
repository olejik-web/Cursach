#include "Grammar.h"

Grammar::Grammar()
{
	initialiseStructure();
	initialiseStructureVariables();
	std::sort(m_terminals.begin(), m_terminals.end(), comparator);
	std::sort(m_usedWords.begin(), m_usedWords.end(), comparator);
	std::reverse(m_terminals.begin(), m_terminals.end());
	std::reverse(m_usedWords.begin(), m_usedWords.end());
	clearLeftRecursion();
	leftFactorisation();
	m_structure["G"].pop_back();
	m_structure["L"].erase(m_structure["L"].begin());
	m_structure["D"].push_back("*FD");
	m_structure["C"].push_back("pi");
	m_structure["F"].push_back("pi");
	m_structure["T"].push_back("piD");
	initialiseTokensStructure();
}

void Grammar::deleteDirectRecursion(const std::string& recursionVariable)
{
	std::vector<std::string>afterVar(0);
	std::vector<std::string>beforeVar(0);
	for (auto elem : m_structure[recursionVariable])
	{
		if (elem.empty())
		{
			beforeVar.push_back(elem);
			continue;
		}
		bool flag = true;
		for (int inx = 0; inx < static_cast<int>(std::min(elem.size(),
				recursionVariable.size())) && flag; inx++)
			flag = elem[inx] == recursionVariable[inx];
		if (!flag)
			beforeVar.push_back(elem);
		else
			afterVar.push_back(elem.substr(std::min(elem.size(),
				recursionVariable.size())));
	}
	if (afterVar.empty())
		return;
	for (auto var : m_structureVariables)
	{
		if (m_structure.find(var) == m_structure.end())
		{
			for (std::size_t i = 0; i < beforeVar.size(); i++)
				beforeVar[i] += var;
			for (std::size_t i = 0; i < afterVar.size(); i++)
				afterVar[i] = afterVar[i] + var;
			afterVar.push_back("");
			if (beforeVar.empty())
				beforeVar.push_back(var);
			m_structure[recursionVariable] = beforeVar;
			m_structure[var] = afterVar;
			return;
		}
	}
}

void Grammar::clearLeftRecursion()
{
	std::vector<std::string> variables(0);
	for (auto p : m_structure)
		variables.push_back(p.first);
	for (std::size_t i = 0; i < variables.size(); i++)
	{
		for (std::size_t j = 0; j < i; j++)
		{
			std::vector<std::string> newGrammarVector(0);
			for (int k = 0; k < static_cast<int>(
				m_structure[variables[i]].size()); k++)
			{
				std::string elem = m_structure[variables[i]][k];
				if (elem.empty())
				{
					newGrammarVector.push_back(m_structure[variables[i]][k]);
					continue;
				}
				bool flag = true;
				for (int inx = 0; inx < static_cast<int>(std::min(elem.size(),
					variables[j].size())) && flag; inx++)
					flag = elem[inx] == variables[j][inx];
				if (flag)
				{
					std::string rightPart = elem.substr(std::min(elem.size(),
						variables[j].size()));
					for (auto q : m_structure[variables[j]])
					{
						std::string s = q + rightPart;
						newGrammarVector.push_back(s);
					}
				}
				else
					newGrammarVector.push_back(m_structure[variables[i]][k]);
			}
			m_structure[variables[i]] = newGrammarVector;
		}
		deleteDirectRecursion(variables[i]);
	}
}

void Grammar::initialiseStructure()
{
	m_structure["F"] = { "C", "N", "(E)", "-F", "sqrt(E)",
		"sin(E)", "cos(E)", "tg(E)", "ctg(E)", "-F", "ln(E)", "exp(E)" };
	m_structure["T"] = { "F", "TF", "T/F" };
	m_structure["E"] = { "T", "E+T", "E-T", "E^T" };
	m_structure["C"] = { "NC", "x", "t" };
	m_structure["N"] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	for (char i = '0'; i <= '9'; i++)
	{
		std::string s = "N";
		s += i;
		m_structure["N"].push_back(s);
	}
}

void Grammar::initialiseStructureVariables()
{
	for (char i = 'A'; i <= 'Z'; i++)
	{
		if (i == 'O') continue;
		std::string s = "";
		s += i;
		m_structureVariables.push_back(s);
	}
	for (char i = 'A'; i <= 'Z'; i++)
	{
		if (i == 'O') continue;
		std::string s = "1";
		s = i + s;
		m_structureVariables.push_back(s);
	}
}

void Grammar::leftFactorisation()
{
	for (std::map<std::string, std::vector<std::string>> ::iterator it
		= m_structure.begin(); it != m_structure.end(); it++)
	{
		int count = 1e9;
		while (count > 1)
		{
			count = 1;
			std::string prefix = "";
			std::map<std::string, int> prefixCountMap;
			for (std::size_t i = 0; i < it->second.size(); i++)
			{
				std::string s = "";
				for (std::size_t j = 0; j < it->second[i].size(); j++)
				{
					s += it->second[i][j];
					prefixCountMap[s]++;
				}
			}
			for (auto p : prefixCountMap)
			{
				if (p.second > 1 && p.first.size() > prefix.size())
				{
					count = p.second;
					prefix = p.first;
				}
			}
			if (count > 1)
			{
				std::string currentVariable = it->first;
				replaceProduction(currentVariable, prefix);
			}
		}
	}
}

void Grammar::replaceProduction(const std::string& variable,
	const std::string& prefix)
{
	std::string newVar;
	for (auto var : m_structureVariables)
	{
		if (m_structure.find(var) == m_structure.end())
		{
			newVar = var;
			break;
		}
	}
	std::vector<std::string> newGrammarVector(0);
	std::vector<std::string> newVarGrammarVector(0);
	for (std::size_t i = 0; i < m_structure[variable].size(); i++)
	{
		bool flag = m_structure[variable][i].size() >= prefix.size();
		for (std::size_t j = 0; j < prefix.size() && flag; j++)
			flag = prefix[j] == m_structure[variable][i][j];
		if (flag)
			newVarGrammarVector.push_back(
				m_structure[variable][i].substr(prefix.size()));
		else
			newGrammarVector.push_back(m_structure[variable][i]);
	}
	for (auto p : m_structure)
	{
		if (p.second == newVarGrammarVector)
		{
			newGrammarVector.push_back(prefix + p.first);
			m_structure[variable] = newGrammarVector;
			return;
		}
	}
	newGrammarVector.push_back(prefix + newVar);
	m_structure[newVar] = newVarGrammarVector;
	m_structure[variable] = newGrammarVector;
}

void Grammar::initialiseTokensStructure()
{
	for (auto notTerminal : m_notTerminals)
	{
		for (auto production : m_structure[notTerminal])
		{
			std::vector<std::string> tokens;
			int index = 0;
			if (production.empty())
				tokens.push_back("");
			else
			{
				while (index < static_cast<int>(production.size()))
				{
					std::string choosenTerminal = "";
					std::string choosenNotTerminal = "";
					for (auto terminal : m_terminals)
					{
						if (index + terminal.size() <= production.size()
							&& production.substr(index,
							terminal.size()) == terminal
							&& terminal.size() > choosenTerminal.size())
							choosenTerminal = terminal;
					}
					if (!choosenTerminal.empty())
					{
						tokens.push_back(choosenTerminal);
						index += choosenTerminal.size();
					}
					for (auto notTerminal : m_notTerminals)
					{
						if (index + notTerminal.size() <= production.size()
							&& production.substr(index,
							notTerminal.size()) == notTerminal)
							choosenNotTerminal = notTerminal;
					}
					if (!choosenNotTerminal.empty())
					{
						tokens.push_back(choosenNotTerminal);
						index += choosenNotTerminal.size();
					}
				}
			}
			m_tokensStructure[notTerminal].push_back(tokens);
		}
	}
}

bool Grammar::isConstant(const std::string& value) const
{
	bool flag = false;
	for (auto myConst : m_constants)
		flag |= value == myConst;
	return flag;
}

bool Grammar::isMathVariable(const std::string& value) const
{
	bool flag = false;
	for (auto mathVar : m_mathVariables)
		flag |= value == mathVar;
	return flag;
}

bool Grammar::isDigit(const std::string& value) const
{
	bool flag = false;
	for (auto digit : m_digits)
		flag |= value == digit;
	return flag;
}

bool Grammar::isFunction(const std::string& value) const
{
	bool flag = false;
	for (auto function : m_functions)
		flag |= value == function;
	return flag;
}

bool Grammar::isOperator(const std::string& value) const
{
	bool flag = false;
	for (auto op : m_operators)
		flag |= value == op;
	return flag;
}

void Grammar::printStructure() const
{
	for (auto elem : m_structure)
	{
		QDebug info = qInfo();
		info << QString::fromStdString(elem.first) << "-->";
		for (int i = 0; i < elem.second.size() - 1; i++)
			info << QString::fromStdString(elem.second[i]) << "|";
		info << QString::fromStdString(elem.second.back());
	}
}

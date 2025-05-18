#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>
#include <map>
#include <memory>
#include <string>
#include <QString>
#include <QDebug>

class Grammar
{
public:
	Grammar();
	void printStructure() const;
	void initialiseStructure();
	void initialiseTokensStructure();
	void initialiseStructureVariables();
	void deleteDirectRecursion(const std::string& recursionVariable);
	void clearLeftRecursion();
	void leftFactorisation();
	void replaceProduction(const std::string& variable,
		const std::string& prefix);
	static bool comparator(const std::string& a, const std::string& b);
	bool isConstant(const std::string& value) const;
	bool isMathVariable(const std::string& value) const;
	bool isDigit(const std::string& value) const;
	bool isFunction(const std::string& value) const;
	bool isOperator(const std::string& value) const;
	std::string startNotTerminal();
	std::map<std::string, std::vector<std::vector<std::string>>>*
		tokensStructure();
	std::vector<std::string>* terminals();
	std::vector<std::string>* notTerminals();
	std::vector<std::string>* usedWords();
	std::vector<std::string>* operators();
private:
	std::map<std::string, std::vector<std::vector<std::string>>>
		m_tokensStructure;
	std::map<std::string, std::vector<std::string> > m_structure;
	std::vector<std::string> m_digits{
		{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}
	};
	std::vector<std::string> m_structureVariables{};
	std::vector<std::string> m_mathVariables{"x", "t"};
	std::vector<std::string> m_constants{"pi"};
	std::vector<std::string >m_terminals{
		{
			"+", "-", "^", "*", "0", "1", "2", "3", "4", "5", "6", "7", "8",
			"9", "x", "t", "/", "ln(", "(", ")", "c", "s", "os(", "qrt(",
			"in(", "g(", "exp(", "pi"
		}
	};
	std::vector<std::string> m_usedWords{
		{
			"+", "-", "^", "*", "/", "0", "1", "2", "3", "4", "5", "6", "7",
			"8", "9", "pi", "x", "t", "cos", "sin", "tg", "ctg", "sqrt",
			"exp", "ln", "(", ")"
		}
	};
	std::vector<std::string> m_operators{
		{ "+", "-", "^", "*", "/", "(", ")" }
	};
	std::vector<std::string> m_functions{
		{"cos", "sin", "tg", "ctg", "sqrt", "exp", "ln"}
	};
	std::vector<std::string> m_notTerminals{
		{
			"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
			"M", "N", "P", "Q", "T"
		}
	};
	std::string m_startNotTerminal = "E";
};

inline std::vector<std::string>* Grammar::usedWords()
{
	return &m_usedWords;
}

inline std::string Grammar::startNotTerminal()
{
	return m_startNotTerminal;
}

inline std::map<std::string, std::vector<std::vector<std::string>>>*
	Grammar::tokensStructure()
{
	return &m_tokensStructure;
}

inline std::vector<std::string>* Grammar::notTerminals()
{
	return &m_notTerminals;
}

inline std::vector<std::string>* Grammar::terminals()
{
	return &m_terminals;
}

inline std::vector<std::string>* Grammar::operators()
{
	return &m_operators;
}

inline bool Grammar::comparator(const std::string& a, const std::string& b)
{
	return a.size() < b.size();
}

#endif // GRAMMAR_H

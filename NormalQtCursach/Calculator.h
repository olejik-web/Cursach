#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <map>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <QDebug>
#include "Grammar.h"
#include "Node.h"

class Calculator
{
public:
	enum WorkStatus {
		Success,
		BracketsError,
		DivisionOnZeroError,
		LogarithmNegativeValueError,
		SqrtNegativeValueError,
		TgValueError,
		CtgValueError,
	};
	Calculator(Grammar* grammar);
	double calculateValue(std::string& currentExpression,
		const Node* currentNode, double xValue, double tValue,
		WorkStatus& workStatus);
	void collectTokens(const std::string expression,
		std::vector<std::pair<std::string, bool>>& tokens) const;
	void transferToPostfixTokens(const
		std::vector<std::pair<std::string, bool>>& tokens,
		std::vector<std::pair<std::string, bool>>& postfixTokens,
		WorkStatus& workStatus);
	double calculatePostfixTokensExpression(
		const std::vector<std::pair<std::string, bool>>& postfixTokens,
		double xValue, double tValue, WorkStatus& workStatus);
	static int mathSign(double value);
	static constexpr double PI_VALUE{3.14159265358979323846};
	static constexpr double EPSILON_VALUE{1e-10};
private:
	std::map<std::string, double> m_calculatedValuesMap;
	Grammar* m_grammar;
};

#endif // CALCULATOR_H

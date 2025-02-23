#include "Calculator.h"

Calculator::Calculator(Grammar* grammar) :
	m_grammar(grammar)
{}

void Calculator::collectTokens(const std::string expression,
	std::vector<std::pair<std::string, bool>>& tokens) const
{
	int ip = 0;
	bool haveMinus = false;
	bool minusFlag = false;
	std::vector<std::pair<std::string, bool>> tmp;
	while (ip < expression.size())
	{
		std::string calcValueCode = "$";
		if (expression[ip] == '$')
		{
			ip++;
			while (expression[ip] != '$')
			{
				calcValueCode += expression[ip];
				ip++;
			}
			calcValueCode += '$';
			ip++;
		}
		if (calcValueCode.size() > 1 && minusFlag) // here
		{
			if (tmp.empty() || (tmp.back().first == "-"
				|| tmp.back().first == "+" || tmp.back().first == "*"
				|| tmp.back().first == "/" || tmp.back().first == "(" ||
				tmp.back().first == "^"))
				tmp.push_back({ calcValueCode, haveMinus });
			else
			{
				if (haveMinus)
					tmp.push_back({ "-", false });
				else
					tmp.push_back({ "+", false });
				tmp.push_back({ calcValueCode, false });
			}
			haveMinus = false;
			minusFlag = false;
		}
		else if (calcValueCode.size() > 1)
			tmp.push_back({ calcValueCode, false });
		for (auto word : *m_grammar->usedWords())
		{
			bool flag = false;
			if (ip + word.size() <= expression.size() &&
				expression.substr(ip, word.size()) == word)
			{
				if (word == "-")
				{
					haveMinus ^= true;
					minusFlag = true;
				}
				else if (minusFlag)
				{
					if (tmp.empty() || (tmp.back().first == "-" ||
						tmp.back().first == "+" || tmp.back().first == "*" ||
						tmp.back().first == "/" || tmp.back().first == "(" ||
						tmp.back().first == "^"))
						tmp.push_back({ word, haveMinus });
					else
					{
						if (haveMinus)
							tmp.push_back({ "-", false });
						else
							tmp.push_back({ "+", false });
						tmp.push_back({ word, false });
					}
					haveMinus = false;
					minusFlag = false;
				}
				else
					tmp.push_back({ word, false });
				ip += word.size();
				break;
			}
		}
	}
	for (auto p : tmp)
	{
		if (m_grammar->isDigit(p.first))
		{
			if (!tokens.empty() && tokens.back().first.back() >= '0'
				&& tokens.back().first.back() <= '9')
			{
				tokens.back().first += p.first;
				tokens.back().second ^= p.second;
			}
			else if (!tokens.empty() &&
				(!m_grammar->isOperator(tokens.back().first) ||
				 tokens.back().first == ")"))
			{
				tokens.push_back({ "*", false });
				tokens.push_back(p);
			}
			else
				tokens.push_back(p);
		}
		else if (m_grammar->isMathVariable(p.first) ||
			m_grammar->isFunction(p.first) || m_grammar->isConstant(p.first))
		{
			if (!tokens.empty() && (!m_grammar->isOperator(tokens.back().first)
				|| tokens.back().first == ")"))
				tokens.push_back({ "*", false });
			tokens.push_back(p);
		}
		else if (p.first == "(")
		{
			if (!tokens.empty() && (!m_grammar->isOperator(tokens.back().first)
				&& !m_grammar->isFunction(tokens.back().first) ||
				tokens.back().first == ")"))
				tokens.push_back({ "*", false });
			tokens.push_back(p);
		}
		else
			tokens.push_back(p);
	}
}

void Calculator::transferToPostfixTokens(const
	std::vector<std::pair<std::string, bool>>& tokens,
	std::vector<std::pair<std::string, bool>>& postfixTokens,
	WorkStatus& workStatus)
{
	std::map<std::string, int> operatorsPriority =
	{ {"(", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3} };
	std::stack<std::pair<std::string, bool>> algoStack;
	int minusCount = 0;
	for (auto token : tokens)
	{
		if (token.first == "(" && token.second)
			minusCount++;
		else if (!m_grammar->isOperator(token.first))
			token.second ^= static_cast<bool>(minusCount % 2);
		if (!m_grammar->isOperator(token.first)
			&& !m_grammar->isFunction(token.first))
			postfixTokens.push_back(token);
		else if (m_grammar->isFunction(token.first))
			algoStack.push(token);
		else if (m_grammar->isOperator(token.first) &&
			token.first != "(" && token.first != ")")
		{
			while (!algoStack.empty()
				&& operatorsPriority[algoStack.top().first] >=
				operatorsPriority[token.first])
			{
				postfixTokens.push_back(algoStack.top());
				algoStack.pop();
			}
			algoStack.push(token);
		}
		else if (token.first == "(")
			algoStack.push(token);
		else if (token.first == ")")
		{
			while (!algoStack.empty() && algoStack.top().first != "(")
			{
				postfixTokens.push_back(algoStack.top());
				algoStack.pop();
			}
			if (algoStack.empty())
			{
				workStatus = WorkStatus::BracketsError;
				return;
			}
			if (algoStack.top().second)
				minusCount--;
			algoStack.pop();
			if (!algoStack.empty() &&
				m_grammar->isFunction(algoStack.top().first))
			{
				postfixTokens.push_back(algoStack.top());
				algoStack.pop();
			}
		}
	}
	while (!algoStack.empty() && algoStack.top().first != "(")
	{
		postfixTokens.push_back(algoStack.top());
		algoStack.pop();
	}
	if (!algoStack.empty())
	{
		workStatus = WorkStatus::BracketsError;
		return;
	}
}

double Calculator::calculatePostfixTokensExpression(
	const std::vector<std::pair<std::string, bool>>& postfixTokens,
	double xValue, double tValue, WorkStatus& workStatus)
{
	std::stack<double> calculateStack;
	for (auto pt : postfixTokens)
	{
		if (!m_grammar->isOperator(pt.first)
			&& !m_grammar->isFunction(pt.first))
		{
			double ans = 1;
			int ip = 0;
			int num = -1;
			while (ip < pt.first.size())
			{
				bool flag = false;
				if (pt.first[ip] == '$')
				{
					std::string valueCode = "$";
					ip++;
					while (pt.first[ip] != '$')
					{
						valueCode += pt.first[ip];
						ip++;
					}
					valueCode += '$';
					ans *= m_calculatedValuesMap[valueCode];
					flag = true;
					ip++;
				}
				else if (pt.first[ip] == 'x')
				{
					ans *= xValue;
					ip++;
					flag = true;
				}
				else if (pt.first[ip] == 't')
				{
					ans *= tValue;
					ip++;
					flag = true;
				}
				else if (ip + 2 <= pt.first.size()
					&& pt.first.substr(ip, 2) == "pi")
				{
					ans *= PI_VALUE;
					ip += 2;
					flag = true;
				}
				else
				{
					if (num < 0)
						num = pt.first[ip] - '0';
					else
						num = num * 10 + pt.first[ip] - '0';
					ip++;
				}
				if (flag && num > -1)
				{
					ans *= num;
					num = -1;
				}
			}
			if (num > -1)
			{
				ans *= num;
				num = -1;
			}
			if (pt.second)
				ans *= -1;
			calculateStack.push(ans);
		}
		else if (m_grammar->isOperator(pt.first))
		{
			double first = calculateStack.top();
			calculateStack.pop();
			double second = calculateStack.top();
			calculateStack.pop();
			if (pt.first == "+")
				calculateStack.push(second + first);
			if (pt.first == "-")
				calculateStack.push(second - first);
			if (pt.first == "*")
				calculateStack.push(first * second);
			if (pt.first == "/")
			{
				if (abs(first) < EPSILON_VALUE)
				{
					workStatus = WorkStatus::DivisionOnZeroError;
					return 1;
				}
				calculateStack.push(second / first);
			}
			if (pt.first == "^")
				calculateStack.push(std::pow(second, first));
		}
		else {
			double value = calculateStack.top();
			calculateStack.pop();
			if (pt.first == "cos")
			{
				if (pt.second)
					calculateStack.push(-cos(value));
				else
					calculateStack.push(cos(value));
			}
			if (pt.first == "sin")
			{
				if (pt.second)
					calculateStack.push(-sin(value));
				else
					calculateStack.push(sin(value));
			}
			if (pt.first == "tg")
			{
				if (abs(cos(value)) < EPSILON_VALUE)
				{
					workStatus = WorkStatus::TgValueError;
					return 1;
				}
				if (pt.second)
					calculateStack.push(-tan(value));
				else
					calculateStack.push(tan(value));
			}
			if (pt.first == "ctg")
			{
				if (abs(sin(value)) < EPSILON_VALUE)
				{
					workStatus = WorkStatus::CtgValueError;
					return 1;
				}
				if (pt.second)
					calculateStack.push(-tan(PI_VALUE / 2 - value));
				else
					calculateStack.push(tan(PI_VALUE / 2 - value));
			}
			if (pt.first == "ln")
			{
				if (abs(value) < EPSILON_VALUE)
				{
					workStatus = WorkStatus::LogarithmNegativeValueError;
					return 1;
				}
				else
				{
					if (pt.second)
						calculateStack.push(-log(value));
					else
						calculateStack.push(log(value));
				}
			}
			if (pt.first == "sqrt")
			{
				if (value < -EPSILON_VALUE)
				{
					workStatus = WorkStatus::SqrtNegativeValueError;
					return 1;
				}
				else
				{
					if (pt.second)
						calculateStack.push(-sqrt(value));
					else
						calculateStack.push(sqrt(value));
				}
			}
			if (pt.first == "exp")
				calculateStack.push(exp(value));
		}
	}
	return calculateStack.top();
}

int Calculator::mathSign(double value)
{
	if (value < -EPSILON_VALUE)
		return -1;
	if (value > EPSILON_VALUE)
		return 1;
	return 0;
}

double Calculator::calculateValue(std::string& currentExpression,
	const Node* currentNode, double xValue, double tValue,
	WorkStatus& workStatus)
{
	if (!currentNode->parent())
		workStatus = WorkStatus::Success;
	if (workStatus != WorkStatus::Success)
		return 1;
	for (int i = 0; i < currentNode->childsSize(); i++)
	{
		std::string childExpression;
		calculateValue(childExpression, currentNode->child(i), xValue,
			tValue, workStatus);
		if (workStatus != WorkStatus::Success)
			return 1;
		currentExpression += childExpression;
	}
	double calculatedValue = 0;
	for (auto terminal : *m_grammar->terminals())
		if (currentNode->value() == terminal)
			currentExpression = terminal;
	if (currentNode->value() == "E")
	{
		std::vector<std::pair<std::string, bool>> tokens;
		std::vector<std::pair<std::string, bool>> postfixTokens;
		collectTokens(currentExpression, tokens);
		transferToPostfixTokens(tokens, postfixTokens, workStatus);
		if (workStatus != WorkStatus::Success)
			return 1;
		calculatedValue = calculatePostfixTokensExpression(
			postfixTokens, xValue, tValue, workStatus);
		if (workStatus != WorkStatus::Success)
			return 1;
		currentExpression = "$" + std::to_string(
			m_calculatedValuesMap.size()) + "$";
		m_calculatedValuesMap[currentExpression] = calculatedValue;
	}
	if (!currentNode->parent())
		m_calculatedValuesMap.clear();
	return calculatedValue;
}

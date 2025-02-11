#ifndef TESTER_H
#define TESTER_H

#include <map>
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include "Calculator.h"
#include "LL1Analyser.h"
#include <QDebug>

class Tester
{
public:
	Tester(Grammar* grammar, LL1Analyser* analyser);
	bool testing();
	void addTest(const std::string& expression, double(*executeExpression)(
		double, double), std::vector<std::pair<double, double>>
		mathVariablesValues = {});
	void addMathVariablesValuesForTest(const std::string& testExpression,
		double x, double t);
	static double executeExpression1(double x, double t);
	static double executeExpression2(double x, double t);
	static double executeExpression3(double x, double t);
	static double executeExpression4(double x, double t);
	static double executeExpression5(double x, double t);
	static double executeExpression6(double x, double t);
	static double executeExpression7(double x, double t);
	static double executeExpression8(double x, double t);
	static double executeExpression9(double x, double t);
	static double executeExpression10(double x, double t);
	static double executeExpression11(double x, double t);
	static double executeExpression12(double x, double t);
	static double executeExpression13(double x, double t);
	static double executeExpression14(double x, double t);
	static double executeExpression15(double x, double t);
	static double executeExpression16(double x, double t);
	static double executeExpression17(double x, double t);
	static double executeExpression18(double x, double t);
	static double executeExpression19(double x, double t);
	static double executeExpression20(double x, double t);
	static double executeExpression21(double x, double t);
private:
	Grammar* m_grammar;
	LL1Analyser* m_analyser;
	std::map<std::string, double(*)(double, double)> m_tests;
	// first -> x
	// second -> t
	std::map<std::string, std::vector<std::pair<double, double>>>
		m_mathVariablesValues;
};

// sin(x^3)cos(t^(x/15))2/tx+2t^3
inline double Tester::executeExpression1(double x, double t)
{
	return sin(pow(x, 3)) * cos(pow(t, (x / 15)))
		* 2 / t * x + 2 * pow(t, 3);
}

// 2xt
inline double Tester::executeExpression2(double x, double t)
{
	return 2 * x * t;
}

// t^(x/15)
inline double Tester::executeExpression3(double x, double t)
{
	return pow(t, (x / 15));
}

// 15/(7-(1+1))3-(2+(1+1))15/(7-(200+1))3-(2+(1+1))(15/(7-(1+1))
// 3-(2+(1+1))+15/(7-(1+1))3-(2+(1+1)))
// ответ посчитан на питоне -30.072164948453608
inline double Tester::executeExpression4(double x, double t)
{
	return -30.072164948453608;
}

// x+t^(sin(5xt)cos(x^x^6))
inline double Tester::executeExpression5(double x, double t)
{
	return x + pow(t, sin(5*x*t) * cos(pow(pow(x, x), 6)));
}

// 1-txpi*cos(pit)
inline double Tester::executeExpression6(double x, double t)
{
	return 1 - t * x * Calculator::PI_VALUE * cos(Calculator::PI_VALUE * t);
}

// 1+---sqrt(2)x
inline double Tester::executeExpression7(double x, double t)
{
	return 1 + -(-(-sqrt(2))) * x;
}

// -(-x--t+--(-2-5x))
inline double Tester::executeExpression8(double x, double t)
{
	return -(-x - (-t) + -(-(-2 - 5 * x)));
}

// (1+t)+-(-x+-4t)
inline double Tester::executeExpression9(double x, double t)
{
	return (1 + t) + -(-x + -4 * t);
}

// pi/3xt^1/2x
inline double Tester::executeExpression10(double x, double t)
{
	return Calculator::PI_VALUE / 3 * x * t / 2 * x;
}

// ---ln(x)+-cos(x)--sin(x)
inline double Tester::executeExpression11(double x, double t)
{
	return -(-(-log(x))) + -cos(x) - (-sin(x));
}

// (((x)pi/(3xt)^1/2x))
inline double Tester::executeExpression12(double x, double t)
{
	return ((x) * Calculator::PI_VALUE / (3 * x * t) / 2 * x);
}

// -(---x--3*---2t)
inline double Tester::executeExpression13(double x, double t)
{
	return -(-(-(-x)) - -3*-(-(-2*t)));
}

// -cos(-2x)sin(-2x)-(---4-7)xtx
inline double Tester::executeExpression14(double x, double t)
{
	return -cos(-2 * x) * sin(-2 * x) - (-(-(-4)) - 7) * x * t * x;
}

// -2tln(exp(1))-(-cos(25xt)888+-sin(1111)+13exp(6))
inline double Tester::executeExpression15(double x, double t)
{
	return -2 * t * log(exp(1)) - (-cos(25 * x * t) * 888 +
		-sin(1111) + 13 * exp(6));
}

// ln(18)/ln(2)/pi*sqrt((11/100)^(-3)*100/2)
inline double Tester::executeExpression16(double x, double t)
{
	return log(18) / log(2) / Calculator::PI_VALUE *
		sqrt(pow((11.0 / 100.0), -3) * 100 / 2);
}

// (-x27)(--x/5)(---t)
inline double Tester::executeExpression17(double x, double t)
{
	return (-x*27)*(-(-x)/5)*-(-(-t));
}

// 200t^3
inline double Tester::executeExpression18(double x, double t)
{
	return 200*pow(t, 3);
}

// 200t^-3
inline double Tester::executeExpression19(double x, double t)
{
	return 200 * pow(t, -3);
}

// 1/-9
inline double Tester::executeExpression20(double x, double t)
{
	return 1.0/-9.0;
}

// 2xt^--(--x^-3+5/-9t)
inline double Tester::executeExpression21(double x, double t)
{
	return 2 * x * pow(t, -(-(-(-pow(x, -3)) + 5.0 / -9.0 * t)));
}

inline void Tester::addMathVariablesValuesForTest(
	const std::string& testExpression, double x, double t)
{
	if (m_mathVariablesValues.find(testExpression)
		!= m_mathVariablesValues.end())
		m_mathVariablesValues[testExpression].push_back({ x, t });
}

#endif // TESTER_H

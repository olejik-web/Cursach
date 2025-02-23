#include "Tester.h"

Tester::Tester(Grammar* grammar, LL1Analyser* analyser) :
	m_grammar(grammar),
	m_analyser(analyser)
{
	addTest("2xt", executeExpression2, {{1, 0}, {-2, 7}, {33, -11}});
	addTest("sin(x^3)cos(t^(x/15))2/tx+2t^3", executeExpression1,
		{ {Calculator::PI_VALUE / 2, Calculator::PI_VALUE / 8},
		{-20 * Calculator::PI_VALUE / 2, Calculator::PI_VALUE + 10 / 8},
		{35, 26}, { 7, 23 } });
	addTest("t^(x/15)", executeExpression3, { {7, 23} });
	addTest("15/(7-(1+1))3-(2+(1+1))15/(7-(200+1))3-(2+(1+1))(15/(7-(1+1))3"
		"-(2+(1+1))+15/(7-(1+1))3-(2+(1+1)))",
		executeExpression4, { {1, 1}, {-2, -3} });
	addTest("x+t^(sin(5xt)cos(x^x^6))",
		executeExpression5, { {(Calculator::PI_VALUE + 236) / 321.0,
		Calculator::PI_VALUE * Calculator::PI_VALUE *
		Calculator::PI_VALUE / 25.0}, {25, 0},
		{11, 3 * Calculator::PI_VALUE} });
	addTest("1-txpi*cos(pit)", executeExpression6,
		{{(Calculator::PI_VALUE + 236) / 321.0,
		Calculator::PI_VALUE * Calculator::PI_VALUE *
		Calculator::PI_VALUE / 25.0}, {17, -10},
		{-11, -3 * Calculator::PI_VALUE}});
	addTest("1+---sqrt(2)x", executeExpression7, {{-62.354, 727.734},
		{-733.311, -966.223}, {-126.504, 213.409}});
	addTest("-(-x--t+--(-2-5x))", executeExpression8, {{530.9, -87.564},
		{-171.098, 560.32}, {32.736, -351.14}});
	addTest("(1+t)+-(-x+-4t)", executeExpression9, {{828.457, 488.669},
		{56.466, -983.201}, {-350.11, 271.453}});
	addTest("pi/3xt^1/2x", executeExpression10, {{386.617, 156.115},
		{319.497, 387.655}, {-897.75, 871.51}});
	addTest("---ln(x)+-cos(x)--sin(x)", executeExpression11,
		{{771.174, 670.509}, {225.049, -818.449}, {368.900, -797.374}});
	addTest("(((x)pi/(3xt)^1/2x))", executeExpression12, {{771.174, 670.509},
		{225.049, -818.449}, {368.900, -797.374}});
	addTest("-(---x--3*---2t)", executeExpression13, {{771.174, 670.509},
		{225.049, -818.449}, {368.900, -797.374}});
	addTest("-cos(-2x)sin(-2x)-(---4-7)xtx", executeExpression14,
		{{771.174, 670.509}, {225.049, -818.449}, {368.900, -797.374}});
	addTest("-2tln(exp(1))-(-cos(25xt)888+-sin(1111)+13exp(6))",
		executeExpression15, {{771.174, 670.509}, {225.049, -818.449},
		{368.900, -797.374}});
	addTest("ln(18)/ln(2)/pi*sqrt((11/100)^(-3)*100/2)",
		executeExpression16, {{0, 0}});
	addTest("(-x27)(--x/5)(---t)", executeExpression17, {{771.174, 670.509},
		{225.049, -818.449}, {368.900, -797.374}});
	addTest("200t^3", executeExpression18, {{2.392, 7.013},
		{1.725, 9.846}, {12.003, -11.334}});
	addTest("200t^-3", executeExpression19, {{2.392, 7.013},
		{1.725, 9.846}, {12.003, -11.334}});
	addTest("1/-9", executeExpression20, {{2.392, 7.013},
		{1.725, 9.846}, {12.003, -11.334}});
	addTest("2xt^--(--x^-3+5/-9t)", executeExpression21, {{2.392, 7.013},
		{1.725, 9.846}, {12, 11}});
}

void Tester::addTest(const std::string& expression, double(*executeExpression)(
	double, double), std::vector<std::pair<double, double>>
	mathVariablesValues)
{
	m_tests[expression] = executeExpression;
	m_mathVariablesValues[expression] = {};
	for (auto values : mathVariablesValues)
		addMathVariablesValuesForTest(expression, values.first,
			values.second);
}

bool Tester::testing()
{
	int testNumber = 0;
	bool testingResult = true;
	Calculator calculator(m_grammar);
	for (auto test : m_tests)
	{
		std::vector<std::pair<double, double>> testResults;
		if (m_analyser->analyseExpression(test.first))
		{
			for (auto data : m_mathVariablesValues[test.first])
			{
				Calculator::WorkStatus workStatus =
					Calculator::WorkStatus::Success;
				std::string expression;
				double myCalculatorAnswer = calculator.calculateValue(
					expression, m_analyser->parseTree(), data.first,
					data.second, workStatus);
				double compilerAnswer = test.second(data.first, data.second);
				testResults.push_back({compilerAnswer, myCalculatorAnswer});
			}
			int dataNumber = 0;
			int acceptedTestsCount = 0;
			bool flag = true;
			for (auto data : m_mathVariablesValues[test.first])
			{
				if (abs(testResults[dataNumber].first -
					testResults[dataNumber].second)
					< Calculator::EPSILON_VALUE)
					acceptedTestsCount++;
				else
				{
					if (flag)
					{
						qInfo() <<
							"----------------------------------------------"
							"------------";
						qInfo() << "Test" << testNumber << ":";
						qInfo() << "expression: " <<
							QString::fromStdString(test.first) << "\n";
						flag = false;
					}
					qInfo() << "\nx=" << data.first << " t=" << data.second;
					qInfo() << "compilerAnswer: " <<
						testResults[dataNumber].first;
					qInfo() << "myCalculatorAnswer: " <<
						testResults[dataNumber].second;
					qInfo() << "Verdict: Failed";
				}
				dataNumber++;
			}
			if (acceptedTestsCount < m_mathVariablesValues[test.first].size())
			{
				testingResult = false;
				qInfo() << "\nResult of testing: " << acceptedTestsCount
					<< "/" << m_mathVariablesValues[test.first].size();
				qInfo() << "CommonVerdict: ";
				if (acceptedTestsCount ==
					m_mathVariablesValues[test.first].size())
					qInfo() << "Accepted";
				else
					qInfo() << "Failed";
				qInfo() << "\n";
				qInfo() << "----------------------------------"
					"------------------------";
			}
		}
		else
		{
			testingResult = false;
			qInfo() << "-----------------------------"
				"-----------------------------";
			qInfo() << "Test" << testNumber << ":";
			qInfo() << "expression: " << QString::fromStdString(test.first);
			qInfo() << "Данное выражение невозможно посчитать,";
			qInfo() <<"так как в нем нарушены правила записи "
				"математических выраженией";
			qInfo() << "----------------------------"
				"------------------------------";
		}
		testNumber++;
	}
	return testingResult;
}

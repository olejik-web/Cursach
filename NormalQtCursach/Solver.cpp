#include "Solver.h"

Solver::Solver(Grammar* grammar, LL1Analyser* analyser) :
	m_grammar(grammar),
	m_analyser(analyser)
{}

double Solver::calculateExampleDifferentialEquation(
	int exampleDifferentionalEquationIndex, double xValue, double tValue)
{
	switch(exampleDifferentionalEquationIndex)
	{
	case 1:
		return exampleDifferentialEquation1(xValue, tValue);
	case 2:
		return exampleDifferentialEquation2(xValue, tValue);
	case 3:
		return exampleDifferentialEquation3(xValue, tValue);
	case 4:
		return exampleDifferentialEquation4(xValue, tValue);
	case 5:
		return exampleDifferentialEquation5(xValue, tValue);
	case 6:
		return exampleDifferentialEquation6(xValue, tValue);
	case 7:
		return exampleDifferentialEquation7(xValue, tValue);
	case 8:
		return exampleDifferentialEquation8(xValue, tValue);
	case 9:
		return exampleDifferentialEquation9(xValue, tValue);
	default:
		return 0;
	}
}

void Solver::fillCalculatedSolveDataParts(double startX, double startT,
	double stepLength, int pointsCount, QVector<QPair<QVector<double>,
	QVector<double>>>& calculatedSolveDataParts,
	bool& haveHandsFindedSolve, int exampleDifferentionalEquationIndex)
{
	switch(exampleDifferentionalEquationIndex)
	{
	case 1:
	{
		if (abs(startX - EXAMPLE_DIFFERENTIAL_EQUATION_1_START_X)
			< Calculator::EPSILON_VALUE && abs(
			startT - EXAMPLE_DIFFERENTIAL_EQUATION_1_START_T) <
			Calculator::EPSILON_VALUE)
		{
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve1(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			haveHandsFindedSolve = true;
			return;
		}
		break;
	}
	case 2:
	{
		if (abs(startX - EXAMPLE_DIFFERENTIAL_EQUATION_2_START_X)
			< Calculator::EPSILON_VALUE && abs(
			startT - EXAMPLE_DIFFERENTIAL_EQUATION_2_START_T) <
			Calculator::EPSILON_VALUE)
		{
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve2(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			haveHandsFindedSolve = true;
			return;
		}
		break;
	}
	}
	haveHandsFindedSolve = false;
}

void Solver::calculateHandsFindedSolve(const
	std::string& differentionalEquation, double startX, double startT,
	double stepLength, int pointsCount, QVector<QPair<QVector<double>,
	QVector<double>>>& calculatedSolveDataParts, bool& haveHandsFindedSolve)
{
	int exampleDifferentionalEquationIndex =
		isExampleDifferentionalEquation(differentionalEquation);
	if (exampleDifferentionalEquationIndex ==
		INVALID_EXAMPLE_DIFFERENTIONAL_EQUATION_NUMBER)
	{
		haveHandsFindedSolve = false;
		return;
	}
	fillCalculatedSolveDataParts(startX, startT, stepLength, pointsCount,
		calculatedSolveDataParts, haveHandsFindedSolve,
		exampleDifferentionalEquationIndex);
}

void Solver::calculatorSolveRungeCutta(double startX, double startT,
	double stepLength, int pointsCount, QVector<double>& xValues,
	QVector<double>& tValues, QString& statusBarMessage)
{
	double x = startX;
	double t = startT;
	double h = stepLength;
	Calculator calculator(m_grammar);
	xValues.push_back(x);
	tValues.push_back(t);
	Calculator::WorkStatus workStatus = Calculator::WorkStatus::Success;
	int successCalculatedPointsCount = 0;
	for (int i=0; i < pointsCount; i++)
	{
		std::string expression;
		double k1 = calculator.calculateValue(expression,
			m_analyser->parseTree(), x, t, workStatus);
		if (workStatus != Calculator::WorkStatus::Success)
			break;
		expression = "";
		double k2 = calculator.calculateValue(expression,
			m_analyser->parseTree(), x + h / 2.0 * k1, t + h / 2.0, workStatus);
		if (workStatus != Calculator::WorkStatus::Success)
			break;
		expression = "";
		double k3 = calculator.calculateValue(expression,
			m_analyser->parseTree(), x + h / 2.0 * k2, t + h / 2.0, workStatus);
		if (workStatus != Calculator::WorkStatus::Success)
			break;
		expression = "";
		double k4 = calculator.calculateValue(expression,
			m_analyser->parseTree(), x + h * k3, t + h, workStatus);
		if (workStatus != Calculator::WorkStatus::Success)
			break;
		x += h / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
		t += h;
		xValues.push_back(x);
		tValues.push_back(t);
		successCalculatedPointsCount++;
		// qInfo() << k1 << k2 << k3 << k4;
		// qInfo() << "--" << x << t;
	}
	switch (workStatus)
	{
	case Calculator::WorkStatus::Success:
		statusBarMessage =
			QString("Все %1 точек были успешно посчитаны "
			"и отрисованы!").arg(pointsCount);
		return;
	case Calculator::WorkStatus::BracketsError:
		statusBarMessage = QString("В выражении не соблюден баланс скобок! "
			"Приведите его к правильному виду!");
		return;
	case Calculator::WorkStatus::DivisionOnZeroError:
		statusBarMessage =
			QString("При вычислении значения в точке %1 "
			"произошло деление на ноль, поэтому были "
			"посчитаны успешно только %2 точек").arg(t + h).arg(
			successCalculatedPointsCount);
		return;
	case Calculator::WorkStatus::LogarithmNegativeValueError:
		statusBarMessage =
			QString("При вычислении значения в точке %1 "
			"под логарифмом соказалось не положительное число, поэтому были "
			"посчитаны успешно только %2 точек").arg(t + h).arg(
			successCalculatedPointsCount);
		return;
	case Calculator::WorkStatus::SqrtNegativeValueError:
		statusBarMessage =
			QString("При вычислении значения в точке %1 "
			"под корнем оказалось отрицательное число, поэтому были "
			"посчитаны успешно только %2 точек").arg(t + h).arg(
			successCalculatedPointsCount);
		return;
	case Calculator::WorkStatus::TgValueError:
		statusBarMessage =
			QString("При вычислении значения в точке %1 "
			"под тангенсом оказалось число, которое не входит в область "
			"определения данной функции, поэтому были посчитаны успешно "
			"только %2 точек").arg(t + h).arg(successCalculatedPointsCount);
		return;
	case Calculator::WorkStatus::CtgValueError:
		statusBarMessage =
			QString("При вычислении значения в точке %1 "
			"под котангенсом оказалось число, которое не входит в область "
			"определения данной функции, поэтому были посчитаны успешно "
			"только %2 точек").arg(t + h).arg(successCalculatedPointsCount);
		return;
	}
}

void Solver::compilerSolveRungeCutta(const std::string& differentialEquation,
	double startX, double startT, double stepLength, int pointsCount,
	QVector<double>& xValues, QVector<double>& tValues,
	bool& findExampleDifferentionalEquation)
{
	// qInfo() << exampleDifferentialEquation1(startX, startT);
	int exampleDifferentionalEquationIndex =
		isExampleDifferentionalEquation(differentialEquation);
	if (exampleDifferentionalEquationIndex ==
		INVALID_EXAMPLE_DIFFERENTIONAL_EQUATION_NUMBER)
	{
		findExampleDifferentionalEquation = false;
		return;
	}
	findExampleDifferentionalEquation = true;
	double x = startX;
	double t = startT;
	double h = stepLength;
	xValues.push_back(x);
	tValues.push_back(t);
	for (int i=0; i < pointsCount; i++)
	{
		double k1 = calculateExampleDifferentialEquation(
			exampleDifferentionalEquationIndex, x, t);
		double k2 = calculateExampleDifferentialEquation(
			exampleDifferentionalEquationIndex, x + h / 2.0 * k1, t + h / 2.0);
		double k3 = calculateExampleDifferentialEquation(
			exampleDifferentionalEquationIndex, x + h / 2.0 * k2, t + h / 2.0);
		double k4 = calculateExampleDifferentialEquation(
			exampleDifferentionalEquationIndex, x + h * k3, t + h);
		x += h / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
		t += h;
		// qInfo() << k1 << k2 << k3 << k4;
		// qInfo() << x << t;
		xValues.push_back(x);
		tValues.push_back(t);
	}
}

int Solver::isExampleDifferentionalEquation(
	const std::string& differentialEquation) const
{
	for (size_t i = 0; i < m_exampleDifferentionalEquations.size(); i++)
		if (m_exampleDifferentionalEquations[i] == differentialEquation)
			return i + 1;
	return INVALID_EXAMPLE_DIFFERENTIONAL_EQUATION_NUMBER;
}

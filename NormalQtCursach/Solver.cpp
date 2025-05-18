#include "Solver.h"

Solver::Solver(Grammar* grammar, LL1Analyser* analyser, QObject* parent) :
	QObject(parent),
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
	case 3:
	{
		if (abs(startX - EXAMPLE_DIFFERENTIAL_EQUATION_3_START_X)
			< Calculator::EPSILON_VALUE && abs(
			startT - EXAMPLE_DIFFERENTIAL_EQUATION_3_START_T) <
			Calculator::EPSILON_VALUE)
		{
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve31(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			startX *= -1.0;
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve32(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			haveHandsFindedSolve = true;
			return;
		}
		break;
	}
	case 4:
	{
		if (abs(startX - EXAMPLE_DIFFERENTIAL_EQUATION_4_START_X)
			< Calculator::EPSILON_VALUE && abs(
			startT - EXAMPLE_DIFFERENTIAL_EQUATION_4_START_T) <
			Calculator::EPSILON_VALUE)
		{
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double x = startX + stepLength * i;
				double t = exampleHandsFindedDifferentionalEquationSolve4(x);
				if (t <= 0)
				{
					calculatedSolveDataParts.back().first.push_back(x);
					calculatedSolveDataParts.back().second.push_back(t);
				}
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double x = startX - stepLength * i;
				double t = exampleHandsFindedDifferentionalEquationSolve4(x);
				if (t >= 0)
				{
					calculatedSolveDataParts.back().first.push_back(x);
					calculatedSolveDataParts.back().second.push_back(t);
				}
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount
				&& -3.315 + stepLength * i < -0.01; i++)
			{
				double x = -3.315 + stepLength * i;
				double t = exampleHandsFindedDifferentionalEquationSolve4(x);
				if (t <= 0)
				{
					calculatedSolveDataParts.back().first.push_back(x);
					calculatedSolveDataParts.back().second.push_back(t);
				}
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double x = -3.315 - stepLength * i;
				double t = exampleHandsFindedDifferentionalEquationSolve4(x);
				if (t <= 0)
				{
					calculatedSolveDataParts.back().first.push_back(x);
					calculatedSolveDataParts.back().second.push_back(t);
				}
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double x = 3.315 + stepLength * i;
				double t = exampleHandsFindedDifferentionalEquationSolve4(x);
				if (t >= 0)
				{
					calculatedSolveDataParts.back().first.push_back(x);
					calculatedSolveDataParts.back().second.push_back(t);
				}
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount
				&& 3.315 - stepLength * i > 0.01; i++)
			{
				double x = 3.315 - stepLength * i;
				double t = exampleHandsFindedDifferentionalEquationSolve4(x);
				if (t >= 0)
				{
					calculatedSolveDataParts.back().first.push_back(x);
					calculatedSolveDataParts.back().second.push_back(t);
				}
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < 100; i++)
			{
				double x = startX + stepLength * i;
				double t = exampleHandsFindedDifferentionalEquationSolve4(x);
				if (t >= 0)
				{
					calculatedSolveDataParts.back().first.push_back(x);
					calculatedSolveDataParts.back().second.push_back(t);
				}
			}
			haveHandsFindedSolve = true;
			return;
		}
		break;
	}
	case 5:
	{
		if (abs(startX - EXAMPLE_DIFFERENTIAL_EQUATION_5_START_X)
			< Calculator::EPSILON_VALUE && abs(
			startT - EXAMPLE_DIFFERENTIAL_EQUATION_5_START_T) <
			Calculator::EPSILON_VALUE)
		{
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve5(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			startT *= -1.0;
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve5(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			haveHandsFindedSolve = true;
			return;
		}
		break;
	}
	case 6:
	{
		if (abs(startX - EXAMPLE_DIFFERENTIAL_EQUATION_6_START_X)
			< Calculator::EPSILON_VALUE && abs(
			startT - EXAMPLE_DIFFERENTIAL_EQUATION_6_START_T) <
			Calculator::EPSILON_VALUE)
		{
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve61(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve62(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			haveHandsFindedSolve = true;
			return;
		}
		break;
	}
	case 7:
	{
		if (abs(startX - EXAMPLE_DIFFERENTIAL_EQUATION_7_START_X)
			< Calculator::EPSILON_VALUE && abs(
			startT - EXAMPLE_DIFFERENTIAL_EQUATION_7_START_T) <
			Calculator::EPSILON_VALUE)
		{
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve7(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			haveHandsFindedSolve = true;
			return;
		}
		break;
	}
	case 8:
	{
		if (abs(startX - EXAMPLE_DIFFERENTIAL_EQUATION_8_START_X)
			< Calculator::EPSILON_VALUE && abs(
			startT - EXAMPLE_DIFFERENTIAL_EQUATION_8_START_T) <
			Calculator::EPSILON_VALUE)
		{
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve81(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve82(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve83(t);
				calculatedSolveDataParts.back().first.push_back(x);
				calculatedSolveDataParts.back().second.push_back(t);
			}
			haveHandsFindedSolve = true;
			return;
		}
		break;
	}
	case 9:
	{
		if (abs(startX - EXAMPLE_DIFFERENTIAL_EQUATION_9_START_X)
			< Calculator::EPSILON_VALUE && abs(
			startT - EXAMPLE_DIFFERENTIAL_EQUATION_9_START_T) <
			Calculator::EPSILON_VALUE)
		{
			calculatedSolveDataParts.push_back(QPair<QVector<double>,
				QVector<double>>());
			for (int i = 0; i < pointsCount; i++)
			{
				double multiplier = i - pointsCount / 2.0;
				double t = startT + stepLength * multiplier;
				double x = exampleHandsFindedDifferentionalEquationSolve9(t);
				if (t >= 0)
					break;
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
	double stepLength, int pointsCount, bool* canCalculate,
	bool* pauseCalculate)
{
	double x = startX;
	double t = startT;
	double h = stepLength;
	Calculator calculator(m_grammar);
	emit calculatePoint(t, x);
	Calculator::WorkStatus workStatus = Calculator::WorkStatus::Success;
	int successCalculatedPointsCount = 0;
	for (int i=0; i < pointsCount; i++)
	{
		while (*pauseCalculate && *canCalculate);
		if (!*canCalculate)
			return;
		std::string expression;
		double k1 = calculator.calculateValue(expression,
			m_analyser->parseTree(), x, t, workStatus);
		if (workStatus != Calculator::WorkStatus::Success)
			break;
		expression = "";
		double k2 = calculator.calculateValue(expression,
			m_analyser->parseTree(), x + h / 2.0 * k1,
			t + h / 2.0, workStatus);
		if (workStatus != Calculator::WorkStatus::Success)
			break;
		expression = "";
		double k3 = calculator.calculateValue(expression,
			m_analyser->parseTree(), x + h / 2.0 * k2,
			t + h / 2.0, workStatus);
		if (workStatus != Calculator::WorkStatus::Success)
			break;
		expression = "";
		double k4 = calculator.calculateValue(expression,
			m_analyser->parseTree(), x + h * k3, t + h, workStatus);
		if (workStatus != Calculator::WorkStatus::Success)
			break;
		x += h / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
		t += h;
		successCalculatedPointsCount++;
		emit updateStatusBar(
			QString("Вычислено значение решения в %1 из %2 точек").arg(
			successCalculatedPointsCount).arg(pointsCount));
		emit calculatePoint(t, x);
	}
	switch (workStatus)
	{
	case Calculator::WorkStatus::Success:
		emit updateStatusBar(QString("Все %1 точек были успешно посчитаны "
			"и отрисованы!").arg(pointsCount));
		return;
	case Calculator::WorkStatus::BracketsError:
		emit updateStatusBar(
			QString("В выражении не соблюден баланс скобок! "
			"Приведите его к правильному виду!"));
		return;
	case Calculator::WorkStatus::DivisionOnZeroError:
		emit updateStatusBar(QString("При вычислении значения в точке %1 "
			"произошло деление на ноль, поэтому были "
			"посчитаны успешно только %2 точек").arg(t + h).arg(
			successCalculatedPointsCount));
		return;
	case Calculator::WorkStatus::LogarithmNegativeValueError:
		emit updateStatusBar(QString("При вычислении значения в точке %1 "
			"под логарифмом оказалось не положительное число, поэтому были "
			"посчитаны успешно только %2 точек").arg(t + h).arg(
			successCalculatedPointsCount));
		return;
	case Calculator::WorkStatus::SqrtNegativeValueError:
		emit updateStatusBar(QString("При вычислении значения в точке %1 "
			"под корнем оказалось отрицательное число, поэтому были "
			"посчитаны успешно только %2 точек").arg(t + h).arg(
			successCalculatedPointsCount));
		return;
	case Calculator::WorkStatus::TgValueError:
		emit updateStatusBar(QString("При вычислении значения в точке %1 "
			"под тангенсом оказалось число, которое не входит в область "
			"определения данной функции, поэтому были посчитаны успешно "
			"только %2 точек").arg(t + h).arg(successCalculatedPointsCount));
		return;
	case Calculator::WorkStatus::CtgValueError:
		emit updateStatusBar(QString("При вычислении значения в точке %1 "
			"под котангенсом оказалось число, которое не входит в область "
			"определения данной функции, поэтому были посчитаны успешно "
			"только %2 точек").arg(t + h).arg(successCalculatedPointsCount));
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

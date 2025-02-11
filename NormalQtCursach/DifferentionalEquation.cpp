#include "DifferentionalEquation.h"

/* DifferentionalEquation::DifferentionalEquation(double startX, double startT,
	double hStepLength, const std::string& stringEquation) :
	m_stringEquation(stringEquation),
	m_startX(startX),
	m_startT(startT),
	m_hStepLength(hStepLength)
{}*/

/* void DifferentionalEquation4::compilerSolvePart1(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=0; i<graphPointsCount; i++)
	{
		double x = startX() + hStepLength() * i;
		double t = knownEquationSolve(x);
		if (t <= 0)
		{
			addCompilerValueX(x);
			addCompilerValueT(t);
		}
	}
}

void DifferentionalEquation4::compilerSolvePart2(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=0; i<graphPointsCount; i++)
	{
		double x = startX() - hStepLength() * i;
		double t = knownEquationSolve(x);
		if (t >= 0)
		{
			addCompilerValueX(x);
			addCompilerValueT(t);
		}
	}
}

void DifferentionalEquation4::compilerSolvePart3(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=0; i<100; i++)
	{
		double x = startX() + hStepLength() * i;
		double t = knownEquationSolve(x);
		// qInfo() << x << " " << t;
		if (t >= 0)
		{
			addCompilerValueX(x);
			addCompilerValueT(t);
		}
	}
}

void DifferentionalEquation4::compilerSolvePart4(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=0; i<graphPointsCount
		&& -3.315 + hStepLength() * i < -0.01; i++)
	{
		double x = -3.315 + hStepLength() * i;
		double t = knownEquationSolve(x);
		// qInfo() << x << " " << t;
		if (t <= 0)
		{
			addCompilerValueX(x);
			addCompilerValueT(t);
		}
	}
}

void DifferentionalEquation4::compilerSolvePart5(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=0; i<graphPointsCount; i++)
	{
		double x = -3.315 - hStepLength() * i;
		double t = knownEquationSolve(x);
		// qInfo() << x << " " << t;
		if (t <= 0)
		{
			addCompilerValueX(x);
			addCompilerValueT(t);
		}
	}
}

void DifferentionalEquation4::compilerSolvePart6(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=0; i<graphPointsCount; i++)
	{
		double x = 3.315 + hStepLength() * i;
		double t = knownEquationSolve(x);
		if (t >= 0)
		{
			addCompilerValueX(x);
			addCompilerValueT(t);
		}
	}
}

void DifferentionalEquation4::compilerSolvePart7(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=0; i<graphPointsCount
		&& 3.315 - hStepLength() * i > 0.01; i++)
	{
		double x = 3.315 - hStepLength() * i;
		double t = knownEquationSolve(x);
		if (t >= 0)
		{
			addCompilerValueX(x);
			addCompilerValueT(t);
		}
	}
}

void DifferentionalEquation7::compilerSolve(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=1; i<graphPointsCount; i++)
	{
		double multiplier = i;
		double t = 6 + hStepLength() * multiplier;
		double x = knownEquationSolve(t);
		addCompilerValueX(x);
		addCompilerValueT(t);
	}
}

void DifferentionalEquation81::compilerSolve(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=0; i<graphPointsCount; i++)
	{
		double multiplier = i - graphPointsCount / 2;
		double t = startT() + hStepLength() * multiplier;
		if (t <= 0)
			continue;
		double x = knownEquationSolve(t);
		addCompilerValueX(x);
		addCompilerValueT(t);
	}
}

void DifferentionalEquation::compilerSolve(int graphPointsCount)
{
	m_compilerXValues.clear();
	m_compilerTValues.clear();
	for (int i=0; i<graphPointsCount; i++)
	{
		double multiplier = i - graphPointsCount / 2;
		double t = m_startT + m_hStepLength * multiplier;
		double x = knownEquationSolve(t);
		m_compilerXValues.push_back(x);
		m_compilerTValues.push_back(t);
	}
}

void DifferentionalEquation9::compilerSolve(int graphPointsCount)
{
	clearCompilerXValues();
	clearCompilerTValues();
	for (int i=0; i<graphPointsCount; i++)
	{
		double multiplier = i - graphPointsCount / 2;
		double t = startT() + hStepLength() * multiplier;
		if (t >= 0)
			continue;
		double x = knownEquationSolve(t);
		addCompilerValueX(x);
		addCompilerValueT(t);
	}
}

int DifferentionalEquation9::mathSign(double value) const
{
	if (value < -1e-6)
		return -1;
	if (value > 1e-6)
		return 1;
	return 0;
}*/

/* void DifferentionalEquation::drawCompilerGraph(QCustomPlot* plot,
	int rangeWidth, int rangeHeight) const
{
	plot->addGraph();
	QPen pen(m_compilerSolveGraphColor);
	pen.setWidth(3);
	plot->graph()->setPen(pen);
	plot->graph()->setData(m_compilerTValues, m_compilerXValues);
	plot->xAxis->setRange(m_startT - rangeWidth / 2,
		m_startT + rangeWidth / 2);
	plot->yAxis->setRange(m_startX - rangeHeight / 2,
		m_startX + rangeHeight / 2);
}*/

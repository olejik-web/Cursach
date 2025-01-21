#include "DifferentionalEquation.h"

DifferentionalEquation::DifferentionalEquation(double startX, double startT,
	double hStepLength, const std::string& stringEquation) :
	m_stringEquation(stringEquation),
	m_startX(startX),
	m_startT(startT),
	m_hStepLength(hStepLength)
{}

double DifferentionalEquation::compilerEquation(double t) const
{}

void DifferentionalEquation::compilerSolve(int graphPointsCount)
{
	m_compilerXValues.clear();
	m_compilerTValues.clear();
	for (int i=0; i<graphPointsCount; i++)
	{
		double multiplier = i - graphPointsCount / 2;
		double t = m_startT + m_hStepLength * multiplier;
		double x = compilerEquation(t);
		m_compilerXValues.push_back(x);
		m_compilerTValues.push_back(t);
	}
}

void DifferentionalEquation::drawCompilerGraph(QCustomPlot* plot,
	int rangeWidth, int rangeHeight, const QColor& color) const
{
	plot->addGraph();
	plot->graph()->setPen(QPen(color));
	plot->graph()->setData(m_compilerTValues, m_compilerXValues);
	plot->xAxis->setRange(m_startT - rangeWidth / 2,
		m_startT + rangeWidth / 2);
	plot->yAxis->setRange(m_startX - rangeHeight / 2,
		m_startX + rangeHeight / 2);
	plot->replot();
}

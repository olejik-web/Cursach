#include "GraphDrawer.h"

GraphDrawer::GraphDrawer(QCustomPlot* plot, Grammar* grammar,
	LL1Analyser* analyser) :
	m_plot(plot),
	m_grammar(grammar),
	m_analyser(analyser)
{}

void GraphDrawer::drawGraph(const std::string& differentionalEquation,
	double startX, double startT, double stepLength, int pointsCount,
	GraphDrawer::GraphType graphType, QString& statusBarMessage)
{
	QPen pen;
	Solver solver(m_grammar, m_analyser);
	switch (graphType)
	{
	case GraphDrawer::HandsFindedSolveGraph:
	{
		pen = QPen(HANDS_FINDED_SOLVE_GRAPH_COLOR);
		pen.setWidth(3);
		QVector<QPair<QVector<double>, QVector<double>>> graphParts;
		bool haveHandsFindedSolve;
		solver.calculateHandsFindedSolve(differentionalEquation, startX,
			startT, stepLength, pointsCount, graphParts, haveHandsFindedSolve);
		if (!haveHandsFindedSolve)
			break;
		for (auto graphPart : graphParts)
		{
			m_plot->addGraph();
			m_plot->graph()->setPen(pen);
			m_plot->graph()->setData(graphPart.second, graphPart.first);
		}
		break;
	}
	case GraphDrawer::CompilerRungeKuttaSolveGraph:
	{
		pen = QPen(COMPILER_RUNGE_KUTTA_SOLVE_GRAPH_COLOR);
		pen.setWidth(3);
		QVector<double> xValues;
		QVector<double> tValues;
		bool findExampleDifferentionalEquation;
		solver.compilerSolveRungeCutta(differentionalEquation, startX,
			startT, stepLength, pointsCount, xValues, tValues,
			findExampleDifferentionalEquation);
		m_plot->addGraph();
		m_plot->graph()->setPen(pen);
		m_plot->graph()->setData(tValues, xValues);
		break;
	}
	case GraphDrawer::CalculatorRungeKuttaSolveGraph:
	{
		pen = QPen(CALCULATOR_RUNGE_KUTTA_SOLVE_GRAPH_COLOR);
		pen.setWidth(3);
		QVector<double> xValues;
		QVector<double> tValues;
		solver.calculatorSolveRungeCutta(startX, startT, stepLength,
			pointsCount, xValues, tValues, statusBarMessage);
		m_plot->addGraph();
		m_plot->graph()->setPen(pen);
		m_plot->graph()->setData(tValues, xValues);
		break;
	}
	}
	m_plot->replot();
}

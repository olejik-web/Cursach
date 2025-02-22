#include "GraphDrawer.h"

GraphDrawer::GraphDrawer(QCustomPlot* plot, Grammar* grammar,
	LL1Analyser* analyser, QObject* parent) :
	QObject(parent),
	m_plot(plot),
	m_grammar(grammar),
	m_analyser(analyser)
{
	clearPlot();
}

GraphDrawer::~GraphDrawer()
{
	if (m_calculateRungeKuttaThread)
	{
		m_calculateRungeKuttaThread->quit();
		m_calculateRungeKuttaThread->stop();
		m_calculateRungeKuttaThread->wait();
	}
}

void GraphDrawer::drawNextPointCalculateRungeKuttaSolveGraph(
	double t, double x)
{
	calculatorRungeKuttaSolvePlotGraph->addData(t, x);
	m_plot->replot();
}

void GraphDrawer::drawGraph(const std::string& differentionalEquation,
	double startX, double startT, double stepLength, int pointsCount,
	GraphDrawer::GraphType graphType, QStatusBar* statusBar)
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
		if (!findExampleDifferentionalEquation)
			break;
		m_plot->addGraph();
		m_plot->graph()->setPen(pen);
		m_plot->graph()->setData(tValues, xValues);
		break;
	}
	case GraphDrawer::CalculatorRungeKuttaSolveGraph:
	{
		pen = QPen(CALCULATOR_RUNGE_KUTTA_SOLVE_GRAPH_COLOR);
		pen.setWidth(3);
		m_plot->addGraph();
		m_plot->graph()->setPen(pen);
		calculatorRungeKuttaSolvePlotGraph = m_plot->graph();
		m_calculateRungeKuttaThread = std::make_unique<CalculateThread>(
			m_grammar, m_analyser, differentionalEquation, startX, startT,
			stepLength, pointsCount, statusBar);
		/* connect(m_calculateRungeKuttaThread.get(),
			&CalculateThread::calculatePoint, this,
			&GraphDrawer::drawNextPointCalculateRungeKuttaSolveGraph);*/
		connect(m_calculateRungeKuttaThread.get(),
			&CalculateThread::finished, this,
			&GraphDrawer::drawCalculatorRungeKuttaSolveFullGraph);
		m_calculateRungeKuttaThread->start();
		break;
	}
	}
	m_plot->replot();
	m_plot->xAxis->setRange(startT - m_plot->width() / 2,
		startT + m_plot->width() / 2);
	m_plot->yAxis->setRange(startX - m_plot->height() / 2,
		startX + m_plot->height() / 2);
}

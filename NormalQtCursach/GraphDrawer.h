#ifndef GRAPHDRAWER_H
#define GRAPHDRAWER_H

#include <QVector>
#include <QTimer>
#include <QPair>
#include <QObject>
#include "qcustomplot.h"
#include "Grammar.h"
#include "LL1Analyser.h"
#include "Solver.h"
#include "CalculateThread.h"

class GraphDrawer : public QObject
{
	Q_OBJECT
public:
	const QColor HANDS_FINDED_SOLVE_GRAPH_COLOR{Qt::blue};
	const QColor COMPILER_RUNGE_KUTTA_SOLVE_GRAPH_COLOR{Qt::green};
	const QColor CALCULATOR_RUNGE_KUTTA_SOLVE_GRAPH_COLOR{Qt::red};
	enum GraphType
	{
		HandsFindedSolveGraph,
		CompilerRungeKuttaSolveGraph,
		CalculatorRungeKuttaSolveGraph
	};
	GraphDrawer(QCustomPlot* plot = nullptr, Grammar* grammar = nullptr,
		LL1Analyser* analyser = nullptr, QObject* parent = nullptr);
	~GraphDrawer();
	void drawGraph(const std::string& differentionalEquation, double startX,
		double startT, double stepLength, int pointsCount,
		GraphDrawer::GraphType graphType, QStatusBar* statusBar);
	void drawNextPointCalculateRungeKuttaSolveGraph(double t, double x);
	void drawCalculatorRungeKuttaSolveFullGraph();
	void clearPlot();
	void updatePlot();
	void stop();
	void pauseDrawing();
	void continueDrawing();
signals:
	void drawedCalculatorRungeKuttaSolveFullGraph();
private:
	QCustomPlot* m_plot;
	Grammar* m_grammar;
	LL1Analyser* m_analyser;
	QCPGraph* calculatorRungeKuttaSolvePlotGraph;
	std::unique_ptr<CalculateThread> m_calculateRungeKuttaThread;
	QTimer m_timer;
};

inline void GraphDrawer::pauseDrawing()
{
	m_calculateRungeKuttaThread->pause();
}

inline void GraphDrawer::continueDrawing()
{
	m_calculateRungeKuttaThread->continueCalculate();
}

inline void GraphDrawer::drawNextPointCalculateRungeKuttaSolveGraph(
	double t, double x)
{
	if (m_plot->graphCount())
		calculatorRungeKuttaSolvePlotGraph->addData(t, x);
}

inline void GraphDrawer::updatePlot()
{
	m_plot->replot();
}

inline void GraphDrawer::drawCalculatorRungeKuttaSolveFullGraph()
{
	emit drawedCalculatorRungeKuttaSolveFullGraph();
}

inline void GraphDrawer::clearPlot()
{
	m_plot->clearGraphs();
}

#endif // GRAPHDRAWER_H

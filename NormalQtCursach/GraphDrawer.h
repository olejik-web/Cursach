#ifndef GRAPHDRAWER_H
#define GRAPHDRAWER_H

#include <QVector>
#include <QPair>
#include "qcustomplot.h"
#include "Grammar.h"
#include "LL1Analyser.h"
#include "Solver.h"

class GraphDrawer
{
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
	GraphDrawer(QCustomPlot* plot, Grammar* grammar, LL1Analyser* analyser);
	void drawGraph(const std::string& differentionalEquation, double startX,
		double startT, double stepLength, int pointsCount,
		GraphDrawer::GraphType graphType, QString& statusBarMessage);
	void clearPlot();
private:
	QCustomPlot* m_plot;
	Grammar* m_grammar;
	LL1Analyser* m_analyser;
};

inline void GraphDrawer::clearPlot()
{
	m_plot->clearGraphs();
}

#endif // GRAPHDRAWER_H

#include "CalculateThread.h"

CalculateThread::CalculateThread(Grammar* grammar,
	LL1Analyser* analyser, const std::string& differentionalEquation,
	double startX, double startT, double stepLength, int pointsCount,
	QStatusBar* statusBar, QObject* parent) :
	QThread(parent),
	m_solver(Solver(grammar, analyser)),
	m_startX(startX),
	m_startT(startT),
	m_stepLength(stepLength),
	m_pointsCount(pointsCount),
	m_statusBar(statusBar)
{
	connect(&m_solver, &Solver::updateStatusBar,
		this, &CalculateThread::updateStatusBar);
	connect(&m_solver, &Solver::calculatePoint,
		this, &CalculateThread::calculatePoint);
}

void CalculateThread::run()
{
	m_started = true;
	m_solver.calculatorSolveRungeCutta(m_startX, m_startT, m_stepLength,
		m_pointsCount, &m_started, &m_paused);
}

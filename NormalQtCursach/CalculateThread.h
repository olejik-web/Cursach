#ifndef CALCULATETHREAD_H
#define CALCULATETHREAD_H

#include <QThread>
#include <QVector>
#include "Solver.h"

class CalculateThread : public QThread
{
	Q_OBJECT
public:
	CalculateThread(Grammar* grammar, LL1Analyser* analyser,
		const std::string& differentionalEquation, double startX,
		double startT, double stepLength, int pointsCount,
		QStatusBar* statusBar, QObject* parent = nullptr);
	void run() override;
	void updateStatusBar(const QString& message, int timeout = 0);
	void stop();
signals:
	void calculatePoint(double t, double x);
private:
	Solver m_solver;
	std::string m_differentionalEquation;
	double m_startX;
	double m_startT;
	double m_stepLength;
	int m_pointsCount;
	QStatusBar* m_statusBar;
	bool m_started{false};
};

inline void CalculateThread::stop()
{
	m_started = false;
}

inline void CalculateThread::updateStatusBar(
	const QString& message, int timeout)
{
	m_statusBar->showMessage(message);
}

#endif // CALCULATETHREAD_H

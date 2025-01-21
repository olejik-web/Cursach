#ifndef DIFFERENTIONALEQUATION_H
#define DIFFERENTIONALEQUATION_H

#include <QVector>
#include <math.h>
#include "qcustomplot.h"

class DifferentionalEquation
{
public:
	DifferentionalEquation(double startX=0, double startT=0,
		double hStepLength=0.5, const std::string& stringEquation="");
	void rungeKuttaSolve(int graphPointsCount);
	void drawCompilerGraph(QCustomPlot* plot, int rangeWidth, int rangeHeight,
		const QColor& color) const;
	void compilerSolve(int graphPointsCount);
	virtual double compilerEquation(double t) const;
private:
	double m_startX;
	double m_startT;
	double m_hStepLength;
	QVector<double> m_compilerXValues;
	QVector<double> m_compilerTValues;
	QVector<double> m_rungeKuttaXValues;
	QVector<double> m_rungeKuttaTValues;
	std::string m_stringEquation;
};

class DifferentionalEquation1 : public DifferentionalEquation
{
public:
	DifferentionalEquation1(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	virtual double compilerEquation(double t) const;
};

inline double DifferentionalEquation1::compilerEquation(double t) const
{
	return -t*log(log(t*exp(exp(-7.0/5.0))/5.0));
}

#endif // DIFFERENTIONALEQUATION_H

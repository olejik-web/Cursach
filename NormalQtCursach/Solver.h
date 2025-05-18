#ifndef SOLVER_H
#define SOLVER_H

#include <math.h>
#include <string>
#include <QVector>
#include <QMap>
#include <QPair>
#include "Calculator.h"
#include "LL1Analyser.h"
#include <QStatusBar>
#include <QObject>

class Solver : public QObject
{
	Q_OBJECT
public:
	Solver(Grammar* grammar, LL1Analyser* analyser,
		QObject* parent = nullptr);
	void calculatorSolveRungeCutta(double startX, double startT,
		double stepLength, int pointsCount, bool* canCalculate,
		bool* pauseCalculate);
	void compilerSolveRungeCutta(const std::string& differentialEquation,
		double startX, double startT, double stepLength, int pointsCount,
		QVector<double>& xValues, QVector<double>& tValues,
		bool& findExampleDifferentionalEquation);
	void fillCalculatedSolveDataParts(double startX, double startT,
		double stepLength, int pointsCount, QVector<QPair<QVector<double>,
		QVector<double>>>& calculatedSolveDataParts,
		bool& haveHandsFindedSolve, int exampleDifferentionalEquationIndex);
	void calculateHandsFindedSolve(const std::string& differentionalEquation,
		double startX, double startT, double stepLength, int pointsCount,
		QVector<QPair<QVector<double>, QVector<double>>>&
		calculatedSolveDataParts, bool& haveHandsFindedSolve);
	double calculateExampleDifferentialEquation(int
		exampleDifferentionalEquationIndex, double xValue, double tValue);
	double calculateExampleDifferentialEquationSolve(int
		exampleDifferentionalEquationIndex, double xValue, double tValue);
	double exampleHandsFindedDifferentionalEquationSolve1(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve2(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve31(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve32(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve4(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve5(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve61(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve62(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve7(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve81(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve82(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve83(double t) const;
	double exampleHandsFindedDifferentionalEquationSolve9(double t) const;
	double exampleDifferentialEquation1(double x, double t) const;
	double exampleDifferentialEquation2(double x, double t) const;
	double exampleDifferentialEquation3(double x, double t) const;
	double exampleDifferentialEquation4(double x, double t) const;
	double exampleDifferentialEquation5(double x, double t) const;
	double exampleDifferentialEquation6(double x, double t) const;
	double exampleDifferentialEquation7(double x, double t) const;
	double exampleDifferentialEquation8(double x, double t) const;
	double exampleDifferentialEquation9(double x, double t) const;
	int isExampleDifferentionalEquation(
		const std::string& differentialEquation) const;

signals:
	void updateStatusBar(const QString& message, int timeout = 0);
	void calculatePoint(double t, double x);

private:
	const int INVALID_EXAMPLE_DIFFERENTIONAL_EQUATION_NUMBER{-1};

	const double EXAMPLE_DIFFERENTIAL_EQUATION_1_START_X{7.0};
	const double EXAMPLE_DIFFERENTIAL_EQUATION_1_START_T{5.0};

	const double EXAMPLE_DIFFERENTIAL_EQUATION_2_START_X{0.26179};
	const double EXAMPLE_DIFFERENTIAL_EQUATION_2_START_T{0.5};

	const double EXAMPLE_DIFFERENTIAL_EQUATION_3_START_X{15.0};
	const double EXAMPLE_DIFFERENTIAL_EQUATION_3_START_T{8.0};

	const double EXAMPLE_DIFFERENTIAL_EQUATION_4_START_X{-1.0};
	const double EXAMPLE_DIFFERENTIAL_EQUATION_4_START_T{5.0};

	const double EXAMPLE_DIFFERENTIAL_EQUATION_5_START_X{0};
	const double EXAMPLE_DIFFERENTIAL_EQUATION_5_START_T{0.53551};

	const double EXAMPLE_DIFFERENTIAL_EQUATION_6_START_X{3.0};
	const double EXAMPLE_DIFFERENTIAL_EQUATION_6_START_T{12.0};

	const double EXAMPLE_DIFFERENTIAL_EQUATION_7_START_X{25.0};
	const double EXAMPLE_DIFFERENTIAL_EQUATION_7_START_T{15.0};

	const double EXAMPLE_DIFFERENTIAL_EQUATION_8_START_X{1.0};
	const double EXAMPLE_DIFFERENTIAL_EQUATION_8_START_T{1.0};

	const double EXAMPLE_DIFFERENTIAL_EQUATION_9_START_X{-4.0};
	const double EXAMPLE_DIFFERENTIAL_EQUATION_9_START_T{-1.0};

	Grammar* m_grammar;
	LL1Analyser* m_analyser;
	QVector<std::string> m_exampleDifferentionalEquations
	{
		{
			QString("x/t-exp(x/t)").toStdString(),
			QString("x/t+tg(x/t)").toStdString(),
			QString("-(x/(x+t))").toStdString(),
			QString("-(x^2)/(t^2-tx)").toStdString(),
			QString("(5t^2-tx+x^2)/t^2").toStdString(),
			QString("x^2/(4t^2)+(5/2)(x/t)+5/4").toStdString(),
			QString("(x^2-2tx)/-(t^2)").toStdString(),
			QString("(2/t)sqrt(3t^2+x^2)+x/t").toStdString(),
			QString("(x-2sqrt(tx))/t").toStdString(),
		}
	};
};

inline double Solver::exampleHandsFindedDifferentionalEquationSolve1(
	double t) const
{
	return -t * log(log(abs(t) * exp(exp(-7.0 / 5.0)) / 5.0));
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve2(
	double t) const
{
	return t * asin(t);
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve31(
	double t) const
{
	return -t + sqrt(t * t + 465);
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve32(
	double t) const
{
	return -t - sqrt(t * t - 15);
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve4(
	double t) const
{
	return t / (-1.0 / 5.0 + log(abs(t)));
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve5(
	double t) const
{
	return 2.0 * t * tan(Calculator::PI_VALUE / 4.0 + 2.0 * log(abs(t))) + t;
}


inline double Solver::exampleHandsFindedDifferentionalEquationSolve61(
	double t) const
{
	return (25.0 * t * t / 252.0 - t) / (1.0 - 5.0 * t / 252.0);
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve62(
	double t) const
{
	return -5.0 * t;
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve7(
	double t) const
{
	return t * t / (t - 6);
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve81(
	double t) const
{
	return (1 - 3 * t * t * t * t) / (-2 * t);
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve82(
	double t) const
{
	return t;
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve83(
	double t) const
{
	return 0;
}

inline double Solver::exampleHandsFindedDifferentionalEquationSolve9(
	double t) const
{
	return ((-2 - log(abs(t))) / Calculator::mathSign(t))
		* ((-2 - log(abs(t))) / Calculator::mathSign(t)) * t;
}

inline double Solver::exampleDifferentialEquation1(double x, double t) const
{
	return x / t - exp(x / t);
}

inline double Solver::exampleDifferentialEquation2(double x, double t) const
{
	return x / t + tan(x/t);
}

inline double Solver::exampleDifferentialEquation3(double x, double t) const
{
	return -(x / (x + t));
}

inline double Solver::exampleDifferentialEquation4(double x, double t) const
{
	return -x * x / ((t * t) - t * x);
}

inline double Solver::exampleDifferentialEquation5(double x, double t) const
{
	return (5.0 * t * t - t * x + x * x) / (t * t);
}

inline double Solver::exampleDifferentialEquation6(double x, double t) const
{
	return x * x / (4.0 * t * t) + 5.0 / 2.0 * x / t + 5.0 / 4.0;
}

inline double Solver::exampleDifferentialEquation7(double x, double t) const
{
	return (x * x - 2.0 * t * x) / (-t * t);
}

inline double Solver::exampleDifferentialEquation8(double x, double t) const
{
	return (2.0 / t) * sqrt(3.0 * t * t + x * x) + x / t;
}

inline double Solver::exampleDifferentialEquation9(double x, double t) const
{
	return (x - 2 * sqrt(t * x)) / t;
}

#endif // SOLVER_H

#ifndef DIFFERENTIONALEQUATION_H
#define DIFFERENTIONALEQUATION_H

#include <QVector>
#include <math.h>
#include <QColor>
#include "qcustomplot.h"

/* class DifferentionalEquation
{
public:
	DifferentionalEquation(double startX=0, double startT=0,
		double hStepLength=0.5, const std::string& stringEquation="");
	void compilerSolve(int graphPointsCount);
	virtual double knownEquationSolve(double t) const;
	void clearCompilerTValues();
	void clearCompilerXValues();
	bool compilerTValuesIsEmpty();
	double compilerTValuesBack();
	double startX();
	double startT();
	double hStepLength();

private:
	double m_startX;
	double m_startT;
	double m_hStepLength;
	QVector<double> m_compilerXValues;
	QVector<double> m_compilerTValues;
	std::string m_stringEquation;
};*/

/* inline bool DifferentionalEquation::compilerTValuesIsEmpty()
{
	return m_compilerTValues.isEmpty();
}

inline double DifferentionalEquation::compilerTValuesBack()
{
	return m_compilerTValues.back();
}

inline void DifferentionalEquation::addCompilerValueX(double x)
{
	m_compilerXValues.push_back(x);
}

inline void DifferentionalEquation::addCompilerValueT(double x)
{
	m_compilerTValues.push_back(x);
}

inline void DifferentionalEquation::clearCompilerTValues()
{
	m_compilerTValues.clear();
}

inline void DifferentionalEquation::clearCompilerXValues()
{
	m_compilerXValues.clear();
}

inline double DifferentionalEquation::startX()
{
	return m_startX;
}

inline double DifferentionalEquation::startT()
{
	return m_startT;
}

inline double DifferentionalEquation::hStepLength()
{
	return m_hStepLength;
}

inline double DifferentionalEquation::knownEquationSolve(double t) const
{};

class DifferentionalEquation1 : public DifferentionalEquation
{
public:
	DifferentionalEquation1(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
};

inline double DifferentionalEquation1::knownEquationSolve(double t) const
{
	return -t*log(log(abs(t)*exp(exp(-7.0/5.0))/5.0));
}

class DifferentionalEquation2 : public DifferentionalEquation
{
public:
	DifferentionalEquation2(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
};

inline double DifferentionalEquation2::knownEquationSolve(double t) const
{
	return t * asin(t);
}

class DifferentionalEquation31 : public DifferentionalEquation
{
public:
	DifferentionalEquation31(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
};

inline double DifferentionalEquation31::knownEquationSolve(double t) const
{
	return -t + sqrt(t*t+465);
}

class DifferentionalEquation32 : public DifferentionalEquation
{
public:
	DifferentionalEquation32(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
};

inline double DifferentionalEquation32::knownEquationSolve(double t) const
{
	return -t - sqrt(t*t-15);
}

class DifferentionalEquation4 : public DifferentionalEquation
{
public:
	DifferentionalEquation4(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
	void compilerSolvePart1(int graphPointsCount);
	void compilerSolvePart2(int graphPointsCount);
	void compilerSolvePart3(int graphPointsCount);
	void compilerSolvePart4(int graphPointsCount);
	void compilerSolvePart5(int graphPointsCount);
	void compilerSolvePart6(int graphPointsCount);
	void compilerSolvePart7(int graphPointsCount);
};

inline double DifferentionalEquation4::knownEquationSolve(double t) const
{
	return t / (-1.0/5.0 + log(abs(t)));
}

class DifferentionalEquation5 : public DifferentionalEquation
{
public:
	DifferentionalEquation5(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
};

inline double DifferentionalEquation5::knownEquationSolve(double t) const
{
	return 2.0 * t * tan(M_PI / 4.0 + 2.0 * log(abs(t))) + t;
}

class DifferentionalEquation61 : public DifferentionalEquation
{
public:
	DifferentionalEquation61(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
};

inline double DifferentionalEquation61::knownEquationSolve(double t) const
{
	return (25.0 * t * t / 252.0 - t) / (1.0 - 5.0 * t / 252.0);
}

class DifferentionalEquation62 : public DifferentionalEquation
{
public:
	DifferentionalEquation62(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
};

inline double DifferentionalEquation62::knownEquationSolve(double t) const
{
	return -5 * t;
}

class DifferentionalEquation7 : public DifferentionalEquation
{
public:
	DifferentionalEquation7(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
	void compilerSolve(int graphPointsCount);
};

inline double DifferentionalEquation7::knownEquationSolve(double t) const
{
	return t * t / (t - 6);
}

class DifferentionalEquation81 : public DifferentionalEquation
{
public:
	DifferentionalEquation81(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
	void compilerSolve(int graphPointsCount);
};

inline double DifferentionalEquation81::knownEquationSolve(double t) const
{
	return (1 - 3 * t * t * t * t) / (-2 * t);
}

class DifferentionalEquation82 : public DifferentionalEquation
{
public:
	DifferentionalEquation82(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
};

inline double DifferentionalEquation82::knownEquationSolve(double t) const
{
	return 0;
}

class DifferentionalEquation83 : public DifferentionalEquation
{
public:
	DifferentionalEquation83(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
};

inline double DifferentionalEquation83::knownEquationSolve(double t) const
{
	return t;
}

class DifferentionalEquation9 : public DifferentionalEquation
{
public:
	DifferentionalEquation9(double startX, double startT,
		double hStepLength, const std::string& stringEquation) :
		DifferentionalEquation(startX, startT, hStepLength, stringEquation)
		{};
	double knownEquationSolve(double t) const override;
	void compilerSolve(int graphPointsCount);
	int mathSign(double value) const;
};

inline double DifferentionalEquation9::knownEquationSolve(double t) const
{
	return ((-2 - log(abs(t))) / mathSign(t))
		* ((-2 - log(abs(t))) / mathSign(t)) * t;
}*/

#endif // DIFFERENTIONALEQUATION_H

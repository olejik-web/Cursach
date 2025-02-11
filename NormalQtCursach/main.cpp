#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <set>
#include <algorithm>
#include <stack>
#include <memory>
#include <iomanip>
#include <complex>
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include <qmath.h>
#include "Grammar.h"
#define M_PI 3.14159265358979323846
#define BRACKETS_ERROR -1
#define LOG_ERROR -2
#define SQRT_ERROR -3
#define DIVISION_ZERO_ERROR -4

// Неправильно считаются случаи вида -...^...
// Нужно исправить путем добавления "1*" после минуса
// Вроде как это фиксит данную проблему
// Нет, не фиксит

// ВАЖНОЕ
// Компилятор не умеет брать корни из отрицательных чисел, когда они получаются не комплексные
// Ну, пиздец это как бы
// Надо исправлять каким-то образом
// pow(-27, 1.0 / 3.0) --> -nan(ind), а нужно -3
// pow(-8, 1.0 / 3.0) --> -nan(ind), а нужно -2
// pow(-32, 0.2) --> -nan(ind), а нужно -2
// pow(-23, 7.0/15.0) --> -nan(ind), а нужно -4.31989300289223
// "pow(-27.0, 1.0 / 3.0)=" << pow(-27.0, 1.0 / 3.0) << ", а правильный ответ -3\n";
// "pow(-8.0, 1.0 / 3.0)=" << pow(-8.0, 1.0 / 3.0) << ", а правильный ответ -2\n";
// "pow(-32.0, 0.2)=" << pow(-32.0, 0.2) << ", а правильный ответ -2\n";
// "pow(-23.0, 7.0 / 15.0)=" << pow(-23.0, 7.0 / 15.0) << ", а правильный ответ -4.31989300289223\n";
// "pow(-8.0, 5.0 / 3.0)=" << pow(-8.0, 5.0 / 3.0) << ", а правильный ответ -32\n";
// "pow(-32.0, 3.0 / 5.0)=" << pow(-32.0, 3.0 / 5.0) << ", а правильный ответ -8\n";


using namespace std;

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	/* int exitCode = 0;
	initGrammar();
	initVariables();
	sort(Terminals.begin(), Terminals.end(), comp);
	sort(UsedWords.begin(), UsedWords.end(), comp);
	reverse(Terminals.begin(), Terminals.end());
	reverse(UsedWords.begin(), UsedWords.end());
	if (!getLLFromMyGrammar())
	{
		qInfo() << "Не удалось преобразовать "
			"заданную грамматику в LL1-грамматику";
	}*/
	return a.exec();
	/* fillTable(Grammar, Terminals, NotTerminals);
	Tester tester;
	bool testingResult = tester.testing();
	if (testingResult)
	{
		std::unique_ptr<Node> parseTree =
			make_unique<Node>(nullptr, StartNotTerminal);
		// "x/t-exp(x/t)"
		// "x/t+tg(x/t)"
		// "-(x/(x+t))"
		// "cos(t)"
		// "-(x^2)/(t^2-tx)"
		// "(5t^2-tx+x^2)/t^2"
		// "x^2/(4t^2)+(5/2)(x/t)+5/4"
		// "(x^2-2tx)/-(t^2)"
		// "(2/t)sqrt(3t^2+x^2)+x/t"
		// "(x-2sqrt(tx))/t"
		bool resultOfAnalyseExpression = analyseExpression(
			"-x^2", StartNotTerminal, Terminals,
			NotTerminals, parseTree);
		parseTree->reverseTree();
		xVALUE = 5;
		parseTree->calcExpression();
		qInfo() << parseTree->calcValue();
		int graphPointsCount = 1000;
		QVector<double>tValues;
		QVector<double>xValues;
		double x0 = -4;
		double t0 = -1;
		double h = 0.001;
		if (resultOfAnalyseExpression)
		{
			parseTree->reverseTree();
			calcRungeKuttaSolve(tValues, xValues, t0, x0, h, 2000,
				parseTree);
		}
		else
		{
			qInfo() << "Выражение записано неверно!";
			return -1;
		}
		qInfo() << resultOfAnalyseExpression;
		// parseTree->calcExpression();
		// qInfo() << parseTree->calcValue();
		QApplication a(argc, argv);
		MainWindow w;
		w.drawGraph(tValues, xValues, Qt::red);
		xValues.clear();
		tValues.clear();
		// t0 *= -1;
		calcCompilerSolve(tValues, xValues, t0, x0, h, 400, diffur9);
		w.drawGraph(tValues, xValues, Qt::green);
		w.show();
		exitCode = a.exec();
	}
	else
		return -1;
	return exitCode;*/
	// return 0;
}

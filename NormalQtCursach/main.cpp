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
#include "MainWindow.h"
#include <qmath.h>
#include "Grammar.h"
#define M_PI 3.14159265358979323846
#define BRACKETS_ERROR -1
#define LOG_ERROR -2
#define SQRT_ERROR -3
#define DIVISION_ZERO_ERROR -4

using namespace std;

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

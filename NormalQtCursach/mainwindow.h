#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <iostream>
#include <QMainWindow>
#include <QValidator>
#include <QMessageBox>
#include <QRect>
#include "DifferentionalEquation.h"
#include "Grammar.h"
#include "LL1Analyser.h"
#include "Calculator.h"
#include "Tester.h"
#include "Solver.h"
#include "GraphDrawer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	void drawGraph(QVector<double>& x,
		QVector<double>& y, const QColor& color);
	void drawInputDataGraph();
	void moveParametersWidget(QRect currentPlotRect);
	~MainWindow();
private:
	Ui::MainWindow* ui;
	QDoubleValidator m_doubleValidator;
};
#endif // MAINWINDOW_H

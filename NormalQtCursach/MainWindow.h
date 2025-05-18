#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <memory>
#include <iostream>
#include <QMainWindow>
#include <QValidator>
#include <QMessageBox>
#include <QRect>
#include "Grammar.h"
#include "LL1Analyser.h"
#include "Calculator.h"
#include "Tester.h"
#include "Solver.h"
#include "GraphDrawer.h"
#include "CalculateThread.h"
#include "EditParametersDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void drawGraph(QVector<double>& x,
		QVector<double>& y, const QColor& color);
	void drawInputDataGraph();
	void moveParametersWidget(QRect currentPlotRect);
	void allowEdit();
	void clearGraph();
	void process();
	void setParametersValues(std::string& diffur);
private:
	enum Status
	{
		NotWork,
		Work,
		Pause
	};
	Status m_status{NotWork};
	Ui::MainWindow* ui;
	QDoubleValidator m_doubleValidator;
	Grammar m_grammar;
	LL1Analyser m_analyser;
	std::unique_ptr<GraphDrawer> m_graphDrawer;
	EditParametersDialog m_editParametersDialog;
};
#endif // MAINWINDOW_H

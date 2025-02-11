#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	Grammar grammar;
	bool isLLGrammar;
	LL1Analyser analyser(&grammar, &isLLGrammar);
	Tester tester(&grammar, &analyser);
	if (!tester.testing())
	{
		qInfo() << "Not worked on tests";
		return;
	}
	std::string diffur;
	QString statusBarMessage;
	/* if (!analyser.analyseExpression(diffur))
	{
		qInfo() << "error in analyse";
		return;
	}*/
	// Все графики диффура 1
	/* diffur = "x/t-exp(x/t)";
	analyser.analyseExpression("x/t-exp(x/t)");
	GraphDrawer graphDrawer(ui->plotWidget, &grammar, &analyser);
	graphDrawer.drawGraph(diffur, 7.0, 5.0, 0.01, 20000,
		GraphDrawer::GraphType::HandsFindedSolveGraph, statusBarMessage);
	graphDrawer.drawGraph(diffur, 7.0, 5.0, 0.01, 8000,
		GraphDrawer::GraphType::CalculatorRungeKuttaSolveGraph,
		statusBarMessage);
	graphDrawer.drawGraph(diffur, 7.0, 5.0, 0.01, 4000,
		GraphDrawer::GraphType::CompilerRungeKuttaSolveGraph,
		statusBarMessage);
	qInfo() << statusBarMessage;*/
	// Все графики диффура 2
	diffur = "x/t+tg(x/t)";
	analyser.analyseExpression("x/t+tg(x/t)");
	GraphDrawer graphDrawer(ui->plotWidget, &grammar, &analyser);
	graphDrawer.drawGraph(diffur, Calculator::PI_VALUE / 12.0, 1.0 / 2.0,
		0.01, 5000, GraphDrawer::GraphType::HandsFindedSolveGraph,
		statusBarMessage);
	graphDrawer.drawGraph(diffur, Calculator::PI_VALUE / 12.0, -1.0 / 2.0,
		0.001, 5000, GraphDrawer::GraphType::CalculatorRungeKuttaSolveGraph,
		statusBarMessage);
	graphDrawer.drawGraph(diffur, Calculator::PI_VALUE / 12.0, 1.0 / 2.0,
		0.0001, 500, GraphDrawer::GraphType::CompilerRungeKuttaSolveGraph,
		statusBarMessage);
	qInfo() << statusBarMessage;
	// Solver solver(&grammar, &analyser);
	// QVector<double> xValues;
	// QVector<double> tValues;
	/* bool findEquation;
	solver.compilerSolveRungeCutta("-(x/(x+t))", 15.0, 8.0, 0.01, 5,
		xValues, tValues, findEquation);
	if (findEquation)
		for (int i = 0; i < tValues.size(); i++)
			qInfo() << tValues[i] << xValues[i];
	else
		qInfo() << "Not found example equation";
	qInfo() << "-------------------------------";
	xValues.clear();
	tValues.clear();
	solver.calculatorSolveRungeCutta(15.0, 8.0, 0.01, 5, xValues, tValues);
	for (int i = 0; i < tValues.size(); i++)
		qInfo() << tValues[i] << xValues[i];*/
	// qInfo() << calculator.calculateValue()
	// analyser.printFollow();
	// qInfo() << analyser.analyseExpression("x^2");
	// grammar.printStructure();
	/* ui->plotWidget->addGraph();
	ui->plotWidget->addGraph();
	ui->plotWidget->graph(0)->setPen(QPen(Qt::blue));
	ui->plotWidget->graph(1)->setPen(QPen(Qt::red));*/
	/* ui->startValueXLineEdit->setValidator(&m_doubleValidator);
	ui->startValueTLineEdit->setValidator(&m_doubleValidator);
	ui->hStepLengthLineEdit->setValidator(&m_doubleValidator);*/
	ui->plotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	ui->plotWidget->xAxis->setLabel("t");
	ui->plotWidget->yAxis->setLabel("x");
	connect(ui->plotWidget, &QCustomPlot::resized,
		this, &MainWindow::moveParametersWidget);
	connect(ui->drawGraphButton, &QPushButton::clicked,
		this, &MainWindow::drawInputDataGraph);
	// drawInputDataGraph();
}

void MainWindow::moveParametersWidget(QRect currentPlotRect)
{
	ui->parametersWidget->move(
		currentPlotRect.width() - ui->parametersWidget->width(),
		ui->parametersWidget->y());
}

void MainWindow::drawInputDataGraph()
{
	/* if (!ui->differentiaonalEquationLineEdit->text().size() ||
		!ui->hStepLengthLineEdit->text().size() ||
		!ui->startValueXLineEdit->text().size() ||
		!ui->startValueTLineEdit->text().size() ||
		!ui->solveEquationLineEdit->text().size())
	{
		QMessageBox::information(this, "Сообщение об ошибке!",
			"Одно из полей на форме не заполнено!");
		return;
	}
	std::string solveEquation =
		ui->solveEquationLineEdit->text().toStdString();
	double startX = ui->startValueXLineEdit->text().toDouble();
	double startT = ui->startValueTLineEdit->text().toDouble();
	double hStepLength = ui->hStepLengthLineEdit->text().toDouble();*/
	// std::string differentionalEquation = "x/t-exp(x/t)";
	// DifferentionalEquation1 diffur1(7, 5,
		// 0.01, "x/t-exp(x/t)"); // "-tln(ln(texp(exp(-7/5))))"
	// DifferentionalEquation2 diffur2(M_PI / 12.0, 1.0/2.0,
		// 0.01, "x/t+tg(x/t)");
	// DifferentionalEquation31 diffur31(15, 8, 0.01, "-(x/(x+t))");
	// DifferentionalEquation32 diffur32(-15, 8, 0.01, "-(x/(x+t))");
	// DifferentionalEquation4 diffur4(-1, 5, 0.01, "-x^2/(t^2-tx)");
	/* diffur4.compilerSolvePart1(400);
	diffur4.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	diffur4.compilerSolvePart2(400);
	diffur4.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	diffur4.compilerSolvePart3(400);
	diffur4.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	diffur4.compilerSolvePart4(400);
	diffur4.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	diffur4.compilerSolvePart5(10000);
	diffur4.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	diffur4.compilerSolvePart6(10000);
	diffur4.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	diffur4.compilerSolvePart7(400);
	diffur4.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();*/
	/* DifferentionalEquation5 diffur5Positive(0,
		exp(0.5*atan2(-1.0, 2.0) - M_PI / 8.0), 0.0001,
		"(5t^2-tx+x^2)/t^2");
	diffur5Positive.compilerSolve(4500);
	diffur5Positive.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	DifferentionalEquation5 diffur5Negative(0,
		-exp(0.5*atan2(-1.0, 2.0) - M_PI / 8.0), 0.0001,
		"(5t^2-tx+x^2)/t^2");
	diffur5Negative.compilerSolve(4500);
	diffur5Negative.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();*/
	/* DifferentionalEquation61 diffur61(3, 12, 0.01,
		"x^2/(4t^2)+(5/2)(x/t)+5/4");
	diffur61.compilerSolve(6000);
	diffur61.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	DifferentionalEquation62 diffur62(3, 12, 0.01,
		"x^2/(4t^2)+(5/2)(x/t)+5/4");
	diffur62.compilerSolve(12000);
	diffur62.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();*/
	/* DifferentionalEquation7 diffur7(25, 15, 0.01, "(x^2-2tx)/-(t^2)");
	diffur7.compilerSolve(16000);
	diffur7.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();*/
	/* DifferentionalEquation81 diffur81(1, 1, 0.001, "(2/t)sqrt(3t^2+x^2)+x/t");
	diffur81.compilerSolve(30000);
	diffur81.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	DifferentionalEquation82 diffur82(1, 1, 0.001, "(2/t)sqrt(3t^2+x^2)+x/t");
	diffur82.compilerSolve(50000);
	diffur82.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();
	DifferentionalEquation83 diffur83(1, 1, 0.001, "(2/t)sqrt(3t^2+x^2)+x/t");
	diffur83.compilerSolve(50000);
	diffur83.drawCompilerGraph(ui->plotWidget, 50, 25);
	ui->plotWidget->replot();*/
	// DifferentionalEquation9 diffur9(-4, -1, 0.001, "(x-2sqrt(tx))/t");
	// diffur9.compilerSolve(10000);
	// diffur9.drawCompilerGraph(ui->plotWidget, 50, 25);
	// ui->plotWidget->replot();
	// qInfo() << exp(0.5*atan2(-1.0, 2.0) - M_PI / 8.0);
	// qInfo() << diffur5.knownEquationSolve();
	// ui->plotWidget->replot();
	// ui->plotWidget->clearGraphs();
	// diffur31.compilerSolve(80000);
	// diffur31.drawCompilerGraph(ui->plotWidget, 50, 25);
	// ui->plotWidget->replot();
	// diffur32.compilerSolve(80000);
	// diffur32.drawCompilerGraph(ui->plotWidget, 50, 25);
	// ui->plotWidget->replot();
	// std::cout << startX << " " << startT << " " << hStepLength << "\n";
	// std::cout << differentionalEquation << "\n";
	// std::cout << solveEquation << "\n";
}



void MainWindow::drawGraph(QVector<double>& x,
	QVector<double>& y, const QColor& color)
{
	ui->plotWidget->addGraph();
	QPen pen(color);
	pen.setWidth(3);
	ui->plotWidget->graph()->setPen(pen);
	ui->plotWidget->graph()->setData(x, y);
	ui->plotWidget->replot();
}

MainWindow::~MainWindow()
{
	delete ui;
}

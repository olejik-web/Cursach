#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	/* ui->plotWidget->addGraph();
	ui->plotWidget->addGraph();
	ui->plotWidget->graph(0)->setPen(QPen(Qt::blue));
	ui->plotWidget->graph(1)->setPen(QPen(Qt::red));*/
	ui->startValueXLineEdit->setValidator(&m_doubleValidator);
	ui->startValueTLineEdit->setValidator(&m_doubleValidator);
	ui->hStepLengthLineEdit->setValidator(&m_doubleValidator);
	ui->plotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	// ui->plotWidget->xAxis->setLabel("t");
	// ui->plotWidget->yAxis->setLabel("x");
	connect(ui->drawGraphButton, &QPushButton::clicked,
		this, &MainWindow::drawInputDataGraph);
}

void MainWindow::drawInputDataGraph()
{
	if (!ui->differentiaonalEquationLineEdit->text().size() ||
		!ui->hStepLengthLineEdit->text().size() ||
		!ui->startValueXLineEdit->text().size() ||
		!ui->startValueTLineEdit->text().size() ||
		!ui->solveEquationLineEdit->text().size())
	{
		QMessageBox::information(this, "Сообщение об ошибке!",
			"Одно из полей на форме не заполнено!");
		return;
	}
	std::string differentionalEquation =
		ui->differentiaonalEquationLineEdit->text().toStdString();
	std::string solveEquation =
		ui->solveEquationLineEdit->text().toStdString();
	double startX = ui->startValueXLineEdit->text().toDouble();
	double startT = ui->startValueTLineEdit->text().toDouble();
	double hStepLength = ui->hStepLengthLineEdit->text().toDouble();
	DifferentionalEquation1 diffur1(startX, startT,
		hStepLength, differentionalEquation); // "-tln(ln(texp(exp(-7/5))))"
	ui->plotWidget->clearGraphs();
	diffur1.compilerSolve(20000);
	diffur1.drawCompilerGraph(ui->plotWidget, 50, 25, Qt::blue);
	// std::cout << startX << " " << startT << " " << hStepLength << "\n";
	// std::cout << differentionalEquation << "\n";
	// std::cout << solveEquation << "\n";
}

void MainWindow::drawGraph(QVector<double>& x,
	QVector<double>& y, const QColor& color)
{
	ui->plotWidget->addGraph();
	ui->plotWidget->graph()->setPen(QPen(color));
	ui->plotWidget->graph()->setData(x, y);
}

MainWindow::~MainWindow()
{
	delete ui;
}


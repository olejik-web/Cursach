#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	bool isLLGrammar;
	m_analyser = LL1Analyser(&m_grammar, &isLLGrammar);
	if (!isLLGrammar)
	{
		qInfo() << "Grammar doesn't analyse LL1";
		return;
	}
	Tester tester(&m_grammar, &m_analyser);
	if (!tester.testing())
	{
		qInfo() << "Not works on tests";
		return;
	}
	ui->plotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	ui->plotWidget->xAxis->setLabel("t");
	ui->plotWidget->yAxis->setLabel("x");
	m_graphDrawer = std::make_unique<GraphDrawer>(
		ui->plotWidget, &m_grammar, &m_analyser);
	connect(ui->plotWidget, &QCustomPlot::resized,
		this, &MainWindow::moveParametersWidget);
	connect(ui->drawGraphButton, &QPushButton::clicked,
		this, &MainWindow::drawInputDataGraph);
	connect(m_graphDrawer.get(),
		&GraphDrawer::drawedCalculatorRungeKuttaSolveFullGraph,
		ui->drawGraphButton, &QPushButton::setEnabled);
}

void MainWindow::moveParametersWidget(QRect currentPlotRect)
{
	ui->parametersWidget->move(
		currentPlotRect.width() - ui->parametersWidget->width(),
		ui->parametersWidget->y());
}

void MainWindow::drawInputDataGraph()
{
	double startX = ui->x0SpinBox->value();
	double startT = ui->t0SpinBox->value();
	double h = ui->hSpinBox->value();
	int n = ui->nSpinBox->value();
	std::string diffur =
		ui->differentionalEquationLineEdit->text().toStdString();
	if (!m_analyser.analyseExpression(diffur))
	{
		QMessageBox::information(this, "Сообщение об ошибке!",
			"Введенное выражение содержит ошибку в записи!");
		return;
	}
	else
	{
		ui->drawGraphButton->setEnabled(false);
		m_graphDrawer->clearPlot();
		m_graphDrawer->drawGraph(diffur, startX, startT, h, n,
			GraphDrawer::GraphType::HandsFindedSolveGraph, ui->statusBar);
		m_graphDrawer->drawGraph(diffur, startX, startT, h, n,
			GraphDrawer::GraphType::CalculatorRungeKuttaSolveGraph,
			ui->statusBar);
		m_graphDrawer->drawGraph(diffur, startX, startT, h, n / 2,
			GraphDrawer::GraphType::CompilerRungeKuttaSolveGraph,
			ui->statusBar);
	}
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

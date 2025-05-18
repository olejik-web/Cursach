#include "MainWindow.h"
#include "ui_MainWindow.h"

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
	connect(ui->plotWidget, &QCustomPlot::resized,
		this, &MainWindow::moveParametersWidget);
	connect(ui->drawGraphButton, &QPushButton::clicked,
		this, &MainWindow::process);
	connect(ui->clearGraphButton, &QPushButton::clicked,
		this, &MainWindow::clearGraph);
	m_graphDrawer = std::make_unique<GraphDrawer>(ui->plotWidget,
		&m_grammar, &m_analyser);
	connect(m_graphDrawer.get(),
		&GraphDrawer::drawedCalculatorRungeKuttaSolveFullGraph,
		this, &MainWindow::allowEdit);
	connect(ui->editParametersButton, &QPushButton::clicked,
		&m_editParametersDialog, &EditParametersDialog::show);
	ui->plotWidget->axisRect()->insetLayout()->setInsetAlignment(
		0, Qt::AlignLeft|Qt::AlignBottom);
}

void MainWindow::allowEdit()
{
	ui->drawGraphButton->setText("Построить график");
	ui->editParametersButton->setEnabled(true);
	ui->differentionalEquationLineEdit->setEnabled(true);
	ui->hSpinBox->setEnabled(true);
	ui->x0SpinBox->setEnabled(true);
	ui->t0SpinBox->setEnabled(true);
	ui->nSpinBox->setEnabled(true);
	m_status = NotWork;
}

void MainWindow::process()
{
	switch(m_status)
	{
	case NotWork:
	{
		std::string diffur =
			ui->differentionalEquationLineEdit->text().toStdString();
		setParametersValues(diffur);
		if (!m_analyser.analyseExpression(diffur))
		{
			QMessageBox::information(this, "Сообщение об ошибке!",
				"Введенное выражение содержит ошибку в записи!");
			return;
		}
		drawInputDataGraph();
		m_status = Work;
		ui->drawGraphButton->setText("Приостановить");
		return;
	}
	case Work:
		m_graphDrawer->pauseDrawing();
		ui->statusBar->showMessage("Процесс построения графика приостановлен");
		ui->drawGraphButton->setText("Продолжить");
		m_status = Pause;
		return;
	case Pause:
		m_graphDrawer->continueDrawing();
		ui->drawGraphButton->setText("Приостановить");
		m_status = Work;
		return;
	}
}

void MainWindow::clearGraph()
{
	m_graphDrawer->stop();
	ui->plotWidget->clearGraphs();
	ui->plotWidget->legend->setVisible(false);
	ui->statusBar->showMessage("График был очищен");
	allowEdit();
}

void MainWindow::moveParametersWidget(QRect currentPlotRect)
{
	ui->parametersWidget->move(
		currentPlotRect.width() - ui->parametersWidget->width() - 20,
		ui->parametersWidget->y());
}

void MainWindow::setParametersValues(std::string& diffur)
{
	size_t diffurIndex = 0;
	std::string formatedDiffur;
	while(diffurIndex < diffur.size())
	{
		bool isNotOperator = true;
		std::string diffurChar(1, diffur[diffurIndex]);
		for (auto grammarOperator : *m_grammar.operators())
			isNotOperator = isNotOperator && (diffurChar != grammarOperator);
		std::string parameterName;
		while (diffurIndex < diffur.size() && isNotOperator)
		{
			parameterName += diffurChar;
			diffurIndex++;
			diffurChar[0] = diffur[diffurIndex];
			for (auto grammarOperator : *m_grammar.operators())
				isNotOperator = isNotOperator &&
				(diffurChar != grammarOperator);
		}
		if (parameterName.size())
		{
			bool findValue;
			double parameterValue = m_editParametersDialog.parameterValue(
				QString::fromStdString(parameterName), findValue);
			if (findValue)
			{
				formatedDiffur += "(" + std::to_string(
					static_cast<int>(parameterValue * 1e6)) + "/" +
					std::to_string(static_cast<int>(1e6)) + ")";
			}
			else
				formatedDiffur += parameterName;
		}
		if (!isNotOperator)
			formatedDiffur += diffurChar;
		diffurIndex++;
	}
	diffur = formatedDiffur;
}

void MainWindow::drawInputDataGraph()
{
	double startX = ui->x0SpinBox->value();
	double startT = ui->t0SpinBox->value();
	double h = ui->hSpinBox->value();
	int n = ui->nSpinBox->value();
	std::string diffur =
		ui->differentionalEquationLineEdit->text().toStdString();
	setParametersValues(diffur);
	ui->editParametersButton->setEnabled(false);
	ui->differentionalEquationLineEdit->setEnabled(false);
	ui->hSpinBox->setEnabled(false);
	ui->x0SpinBox->setEnabled(false);
	ui->t0SpinBox->setEnabled(false);
	ui->nSpinBox->setEnabled(false);
	m_graphDrawer->clearPlot();
	m_graphDrawer->drawGraph(diffur, startX, startT,
		h, n, GraphDrawer::GraphType::HandsFindedSolveGraph,
		ui->statusBar);
	m_graphDrawer->drawGraph(diffur, startX, startT,
		h, n, GraphDrawer::GraphType::CompilerRungeKuttaSolveGraph,
		ui->statusBar);
	m_graphDrawer->drawGraph(diffur, startX, startT,
		h, n, GraphDrawer::GraphType::CalculatorRungeKuttaSolveGraph,
		ui->statusBar);
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

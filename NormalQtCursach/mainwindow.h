#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QValidator>
#include <QMessageBox>
#include <iostream>
#include <DifferentionalEquation.h>

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
	~MainWindow();
private:
	Ui::MainWindow* ui;
	QDoubleValidator m_doubleValidator;
};
#endif // MAINWINDOW_H

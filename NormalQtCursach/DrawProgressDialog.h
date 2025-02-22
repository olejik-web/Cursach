#ifndef DRAWPROGRESSDIALOG_H
#define DRAWPROGRESSDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class DrawProgressDialog;
}

class DrawProgressDialog : public QDialog
{
	Q_OBJECT
public:
	explicit DrawProgressDialog(QWidget *parent = nullptr);
	~DrawProgressDialog();

private:
	Ui::DrawProgressDialog *ui;
};

#endif // DRAWPROGRESSDIALOG_H

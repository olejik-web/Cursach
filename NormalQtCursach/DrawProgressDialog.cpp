#include "DrawProgressDialog.h"
#include "ui_DrawProgressDialog.h"

DrawProgressDialog::DrawProgressDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DrawProgressDialog)
{
	ui->setupUi(this);
}

DrawProgressDialog::~DrawProgressDialog()
{
	qInfo() << "destruction";
	delete ui;
}

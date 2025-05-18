#ifndef EDITPARAMETERSDIALOG_H
#define EDITPARAMETERSDIALOG_H

#include <set>
#include <QDialog>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QMenu>
#include <QMessageBox>
#include "ParametersTableDelegate.h"

namespace Ui {
class EditParametersDialog;
}

class EditParametersDialog : public QDialog
{
	Q_OBJECT

public:
	explicit EditParametersDialog(QWidget *parent = nullptr);
	~EditParametersDialog();
	void onCustomContextMenuRequested(const QPoint& cursorPosition);
	void showContextMenu(const QModelIndex& index,
		const QPoint& globalPosition);
	void showErrorMessage(ParametersTableDelegate::NameError error);
	double parameterValue(const QString& name, bool& findValue);

private:
	Ui::EditParametersDialog *ui;
	QStandardItemModel m_parametersTableModel{QStandardItemModel(0, 2)};
	ParametersTableDelegate m_parametersTableDelegate;
};

#endif // EDITPARAMETERSDIALOG_H

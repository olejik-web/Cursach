#include "EditParametersDialog.h"
#include "ui_EditParametersDialog.h"

EditParametersDialog::EditParametersDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::EditParametersDialog)
{
	ui->setupUi(this);
	setModal(true);
	m_parametersTableModel.setHeaderData(ParametersTableDelegate::Name,
		Qt::Horizontal, "Название");
	m_parametersTableModel.setHeaderData(ParametersTableDelegate::Value,
		Qt::Horizontal, "Значение");
	ui->parametersTable->setModel(&m_parametersTableModel);
	ui->parametersTable->setItemDelegate(&m_parametersTableDelegate);
	ui->parametersTable->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->parametersTable, &QTableView::customContextMenuRequested,
		this, &EditParametersDialog::onCustomContextMenuRequested);
	connect(&m_parametersTableDelegate,
		&ParametersTableDelegate::parameterNameError, this,
		&EditParametersDialog::showErrorMessage);
}

void EditParametersDialog::showErrorMessage(
	ParametersTableDelegate::NameError error)
{
	switch(error)
	{
	case ParametersTableDelegate::NameError::NumInBegin:
		QMessageBox::information(this, "Сообщение об ошибке!",
			"Имя параметра не должно начинаться с цифры!");
		return;
	case ParametersTableDelegate::NameError::GrammarWord:
		QMessageBox::information(this, "Сообщение об ошибке!",
			"Имя параметра не должно совпадать с названиями "
			"математических функций!");
		return;
	}
}

double EditParametersDialog::parameterValue(const QString& name,
	bool& findValue)
{
	for (int row = 0; row < m_parametersTableModel.rowCount(); row++)
	{
		QModelIndex parameterNameIndex = m_parametersTableModel.index(row,
			ParametersTableDelegate::Column::Name);
		QModelIndex parameterValueIndex = m_parametersTableModel.index(row,
			ParametersTableDelegate::Column::Value);
		if (m_parametersTableModel.data(parameterNameIndex,
			Qt::DisplayRole) == name)
		{
			findValue = true;
			return m_parametersTableModel.data(parameterValueIndex,
				Qt::DisplayRole).toDouble();
		}
	}
	findValue = false;
	return 0;
}

void EditParametersDialog::onCustomContextMenuRequested(
	const QPoint& cursorPosition)
{
	QModelIndex index = ui->parametersTable->indexAt(cursorPosition);
	showContextMenu(index, ui->parametersTable->viewport()->mapToGlobal(
		cursorPosition));
}

void EditParametersDialog::showContextMenu(
	const QModelIndex& index, const QPoint& globalPosition)
{
	QMenu contextMenu;
	QAction removeAction("Удалить");
	QAction addAction("Добавить");
	if (!ui->parametersTable->selectionModel()->selectedIndexes().empty())
		contextMenu.addAction(&removeAction);
	else
		contextMenu.addAction(&addAction);
	QAction* contextMenuResult = contextMenu.exec(globalPosition);
	if (contextMenuResult == &addAction)
		m_parametersTableModel.insertRow(m_parametersTableModel.rowCount());
	if (contextMenuResult == &removeAction)
	{
		QModelIndexList selectedIndexesList =
			ui->parametersTable->selectionModel()->selectedIndexes();
		std::set<size_t> selectedRows;
		for (int i = 0; i < selectedIndexesList.size(); i++)
			selectedRows.insert(selectedIndexesList[i].row());
		auto selectedRow = --selectedRows.end();
		while (selectedRow != selectedRows.begin())
		{
			m_parametersTableModel.removeRow(*selectedRow);
			selectedRow--;
		}
		m_parametersTableModel.removeRow(*selectedRow);
	}
}

EditParametersDialog::~EditParametersDialog()
{
	delete ui;
}

#include "ParametersTableDelegate.h"

ParametersTableDelegate::ParametersTableDelegate(QObject* parent) :
	QStyledItemDelegate(parent)
{
}

ParametersTableDelegate::~ParametersTableDelegate()
{

}

ParametersTableDelegate::NameError ParametersTableDelegate::checkName(
	const QString& name) const
{
	if (!name.isEmpty() && name[0] >= '0' && name[0] <= '9')
		return NumInBegin;
	Grammar grammar;
	for (auto word : *grammar.usedWords())
		if (name.toStdString() == word)
			return GrammarWord;
	return NoErrors;
}

QWidget* ParametersTableDelegate::createEditor(QWidget* parent,
	const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	switch(index.column())
	{
	case Name:
	{
		QLineEdit* lineEdit = new QLineEdit(parent);
		lineEdit->setValidator(new QRegularExpressionValidator(
			QRegularExpression("[0-9, a-z, A-Z]*"), lineEdit));
		return lineEdit;
	}
	case Value:
	{
		QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox(parent);
		doubleSpinBox->setDecimals(5);
		doubleSpinBox->setRange(-10000, 10000);
		return doubleSpinBox;
	}
	}
}

void ParametersTableDelegate::paint(QPainter* painter,
	const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	switch(index.column())
	{
	case Value:
	{
		QStyleOptionViewItem editedOption = option;
		initStyleOption(&editedOption, index);
		editedOption.text = editedOption.locale.toString(
			index.data().toDouble(), 'f', 5);
		while (editedOption.text.back() != '.' &&
			editedOption.text.back() == '0')
			editedOption.text.remove(editedOption.text.size() - 1, 1);
		if (editedOption.text.back() == '.')
			editedOption.text.remove(editedOption.text.size() - 1, 1);
		const QWidget* widget = option.widget;
		QStyle* style = widget ? widget->style() : QApplication::style();
		style->drawControl(QStyle::CE_ItemViewItem, &editedOption,
			painter, widget);
		break;
	}
	case Name:
		QStyledItemDelegate::paint(painter, option, index);
		break;
	}
}

void ParametersTableDelegate::setEditorData(QWidget* editor,
	const QModelIndex& index) const
{
	switch(index.column())
	{
	case Name:
		qobject_cast<QLineEdit*>(editor)->setText(index.data().toString());
		break;
	case Value:
		qobject_cast<QDoubleSpinBox*>(editor)->setValue(
			index.data().toDouble());
		break;
	}
}

void ParametersTableDelegate::setModelData(QWidget* editor,
	QAbstractItemModel* model, const QModelIndex& index) const
{
	switch(index.column())
	{
	case Column::Name:
	{
		QString name = qobject_cast<QLineEdit*>(editor)->text();
		NameError nameError = checkName(name);
		if (nameError == NameError::NoErrors)
			model->setData(index, name, Qt::DisplayRole);
		else
			emit parameterNameError(nameError);
		break;
	}
	case Column::Value:
		model->setData(index, qobject_cast<QDoubleSpinBox*>(editor)->value(),
			Qt::DisplayRole);
		break;
	}
}

#ifndef PARAMETERSTABLEDELEGATE_H
#define PARAMETERSTABLEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QLineEdit>

#include "Grammar.h"

class ParametersTableDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	enum NameError {
		NoErrors,
		NumInBegin,
		GrammarWord
	};
	enum Column {
		Name,
		Value
	};
	ParametersTableDelegate(QObject* parent = 0);
	~ParametersTableDelegate();
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;
	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	void setModelData(QWidget* editor, QAbstractItemModel* model,
		const QModelIndex& index) const override;
	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;
	NameError checkName(const QString& name) const;
signals:
	void parameterNameError(NameError error) const;
};

#endif // PARAMETERSTABLEDELEGATE_H

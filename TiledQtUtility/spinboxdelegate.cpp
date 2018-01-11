/*-----------------------------------------------------------------------------------------------------------*/
#include <QSpinBox>
#include "spinboxdelegate.h"
/*-----------------------------------------------------------------------------------------------------------*/
SpinBoxDelegate::SpinBoxDelegate(const QList<std::pair<QString, QVariant>>& properties, QObject* parent) :
	QStyledItemDelegate(parent),
	mProperties(properties)
{
	
}
/*-----------------------------------------------------------------------------------------------------------*/
QWidget* SpinBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	const QModelIndex& index) const 
{
	Q_UNUSED(option);
	Q_UNUSED(index);

	auto editor = new QSpinBox(parent);

	for(decltype(auto) pair : mProperties)
	{
		auto good = editor->setProperty(pair.first.toLatin1(), pair.second);
		Q_ASSERT(good);
	}
	
	return editor;
}
/*-----------------------------------------------------------------------------------------------------------*/
void SpinBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	const auto value = index.model()->data(index, Qt::EditRole).toInt();
	auto spinBox = static_cast<QSpinBox*>(editor);

	spinBox->setValue(value);
}
/*-----------------------------------------------------------------------------------------------------------*/
void SpinBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	auto spinBox = static_cast<QSpinBox*>(editor);
	spinBox->interpretText();

	const auto value = spinBox->value();
	model->setData(index, value, Qt::EditRole);
}
/*-----------------------------------------------------------------------------------------------------------*/
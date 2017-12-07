/*-----------------------------------------------------------------------------------------------------------*/
#include <QLineEdit>
#include "commitonchangeddelegate.h"
/*-----------------------------------------------------------------------------------------------------------*/
CommitOnChangedDelegate::CommitOnChangedDelegate(QObject* parent) :
	QStyledItemDelegate(parent),
	mMapper(new QSignalMapper(this))
{
	connect(mMapper, QOverload<QWidget*>::of(&QSignalMapper::mapped),
		this, &CommitOnChangedDelegate::commitData);
}
/*-----------------------------------------------------------------------------------------------------------*/
QWidget* CommitOnChangedDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	auto editor = QStyledItemDelegate::createEditor(parent, option, index);

	if(auto lineEdit = qobject_cast<QLineEdit*>(editor))
	{
		connect(lineEdit, &QLineEdit::textChanged, 
			mMapper, QOverload<>::of(&QSignalMapper::map));
		mMapper->setMapping(lineEdit, lineEdit);
	}

	return editor;
}
/*-----------------------------------------------------------------------------------------------------------*/
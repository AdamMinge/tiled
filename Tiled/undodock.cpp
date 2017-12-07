/*-----------------------------------------------------------------------------------------------------------*/
#include <QEvent>
#include <QUndoView>
#include <QVBoxLayout>
#include "undodock.h"
/*-----------------------------------------------------------------------------------------------------------*/
UndoDock::UndoDock(QWidget* parent) :
	QDockWidget(parent)
{
	setObjectName(QLatin1String("History"));

	mUndoView = new QUndoView(this);
	mUndoView->setCleanIcon(QIcon(":/MapEditor/images/16x16/drive-harddisk.png"));
	mUndoView->setUniformItemSizes(true);

	auto widget = new QWidget(this);
	auto layout = new QVBoxLayout(widget);
	layout->setMargin(0);
	layout->addWidget(mUndoView);
	widget->setLayout(layout);

	setWidget(widget);
	retranslateUi();
}
/*-----------------------------------------------------------------------------------------------------------*/
void UndoDock::setStack(QUndoStack* stack)
{
	Q_ASSERT(mUndoView);
	mUndoView->setStack(stack);
}
/*-----------------------------------------------------------------------------------------------------------*/
void UndoDock::changeEvent(QEvent* event)
{
	QDockWidget::changeEvent(event);

	switch (event->type())
	{
	case QEvent::LanguageChange:
		retranslateUi();
		break;
	default:
		break;	
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void UndoDock::retranslateUi()
{
	setWindowTitle(tr("History"));
	mUndoView->setEmptyLabel(tr("<empty>"));
}
/*-----------------------------------------------------------------------------------------------------------*/

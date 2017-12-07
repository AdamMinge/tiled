/*-----------------------------------------------------------------------------------------------------------*/
#include <QAction>
#include <QCloseEvent>
#include "dialogwithtoggleview.h"
/*-----------------------------------------------------------------------------------------------------------*/
DialogWithToggleView::DialogWithToggleView(QWidget* parent) :
	QDialog(parent),
	mToggleView(new QAction(this))
{
	mToggleView->setCheckable(true);

	connect(mToggleView, &QAction::toggled, this, &DialogWithToggleView::setVisible);
	connect(this, &DialogWithToggleView::windowTitleChanged, this, &DialogWithToggleView::titleChanged);
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* DialogWithToggleView::toggleViewAction() const
{
	return mToggleView;
}
/*-----------------------------------------------------------------------------------------------------------*/
void DialogWithToggleView::closeEvent(QCloseEvent* event)
{
	QWidget::closeEvent(event);

	if (event->isAccepted()) 
		mToggleView->setChecked(false);
}
/*-----------------------------------------------------------------------------------------------------------*/
void DialogWithToggleView::titleChanged(const QString& title)
{
	mToggleView->setText(title);
}
/*-----------------------------------------------------------------------------------------------------------*/

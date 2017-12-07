/*-----------------------------------------------------------------------------------------------------------*/
#include "ui_noeditorwidget.h"
#include "noeditorwidget.h"
#include "actionmanager.h"
/*-----------------------------------------------------------------------------------------------------------*/
NoEditorWidget::NoEditorWidget(QWidget* parent) :
	QWidget(parent),
	mUi(new Ui::NoEditorWidgetClass)
{
	mUi->setupUi(this);

	connect(mUi->newMapButton, &QPushButton::clicked, this, &NoEditorWidget::newMap);
}
/*-----------------------------------------------------------------------------------------------------------*/
NoEditorWidget::~NoEditorWidget()
{
	delete mUi;
}
/*-----------------------------------------------------------------------------------------------------------*/
void NoEditorWidget::newMap()
{
	ActionManager::instance()->action(QLatin1String("MainWindow-NewMap"))->trigger();
}
/*-----------------------------------------------------------------------------------------------------------*/

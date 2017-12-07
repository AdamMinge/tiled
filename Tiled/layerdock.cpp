/*-----------------------------------------------------------------------------------------------------------*/
#include <QEvent>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QVBoxLayout>
#include <QToolButton>
#include "utils.h"
#include "layerdock.h"
#include "layerview.h"
#include "mapdocumentactionhandler.h"
/*-----------------------------------------------------------------------------------------------------------*/
LayerDock::LayerDock(QWidget* parent) :
	QDockWidget(parent),
	mMapDocument(nullptr),
	mLayerView(new LayerView),
	mToolBar(new QToolBar)
{
	setObjectName(QLatin1String("Layers"));

	auto widget = new QWidget(this);
	auto layout = new QVBoxLayout(widget);
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(mLayerView);
	layout->addWidget(mToolBar);
	widget->setLayout(layout);

	mLayerView->setDragEnabled(true);
	mLayerView->setDragDropMode(QAbstractItemView::InternalMove);

	buildToolBar();
	setWidget(widget);
	retranslateUi();
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerDock::setMapDocument(MapDocument* document)
{
	if (mMapDocument == document) return;

	mMapDocument = document;
	mLayerView->setMapDocument(mMapDocument);
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerDock::changeEvent(QEvent* event)
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
void LayerDock::buildToolBar()
{
	Q_ASSERT(mToolBar);

	mNewLayerMenu = new QMenu(mToolBar);
	mNewLayerMenu->addAction(MapDocumentActionHandler::instance()->actionNewTileLayer());
	mNewLayerMenu->addAction(MapDocumentActionHandler::instance()->actionNewGroupLayer());

	mNewLayerMenu->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-new.png"),
	{ QSize(16,16) }));

	auto mNewLayerButton = new QToolButton;
	mNewLayerButton->setPopupMode(QToolButton::InstantPopup);
	mNewLayerButton->setMenu(mNewLayerMenu);
	mNewLayerButton->setIcon(mNewLayerMenu->icon());

	mToolBar->addWidget(mNewLayerButton);
	mToolBar->addActions({
		MapDocumentActionHandler::instance()->actionRaiseLayer(),
		MapDocumentActionHandler::instance()->actionLowerLayer(),
		MapDocumentActionHandler::instance()->actionDuplicateLayer(),
		MapDocumentActionHandler::instance()->actionRemoveLayer(),
		MapDocumentActionHandler::instance()->actionShowHideAllOtherLayers() });
	mToolBar->setIconSize(iconSize(IconSize::Small));
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerDock::retranslateUi()
{
	setWindowTitle(tr("Layers"));
}
/*-----------------------------------------------------------------------------------------------------------*/

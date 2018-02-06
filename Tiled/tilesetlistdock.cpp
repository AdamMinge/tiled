/*-----------------------------------------------------------------------------------------------------------*/
#include <QEvent>
#include <QToolBar>
#include <QHBoxLayout>
#include "utils.h"
#include "tilesetlistdock.h"
#include "tilesetlistview.h"
#include "mapdocumentactionhandler.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilesetListDock::TilesetListDock(QWidget* parent) :
	QDockWidget(parent),
	mMapDocument(nullptr),
	mTilesetsView(new TilesetListView(this)),
	mToolBar(new QToolBar)
{
	setObjectName(QLatin1String("Tileset List"));

	auto widget = new QWidget(this);

	auto vertical = new QVBoxLayout(widget);
	vertical->setSpacing(0);
	vertical->setMargin(0);
	vertical->addWidget(mTilesetsView);
	vertical->addWidget(mToolBar);
	widget->setLayout(vertical);

	buildToolBar();
	setWidget(widget);
	retranslateUi();
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetListDock::setMapDocument(MapDocument* document)
{
	if (mMapDocument == document) return;

	mMapDocument = document;
	mTilesetsView->setMapDocument(mMapDocument);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetListDock::changeEvent(QEvent* event)
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
void TilesetListDock::buildToolBar()
{
	Q_ASSERT(mToolBar);

	mToolBar->addActions({ MapDocumentActionHandler::instance()->actionNewTileset(),
		MapDocumentActionHandler::instance()->actionTilesetProperties(),
		MapDocumentActionHandler::instance()->actionSelectNextTileset(),
		MapDocumentActionHandler::instance()->actionSelectPreviousTileset(),
		MapDocumentActionHandler::instance()->actionRemoveTileset() });

	mToolBar->setIconSize(iconSize(IconSize::Small));
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetListDock::retranslateUi()
{
	setWindowTitle(tr("Tilesets"));
}
/*-----------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------*/
#include <QEvent>
#include <QToolBar>
#include <QHBoxLayout>
#include "utils.h"
#include "tilesetsdock.h"
#include "tilesetsview.h"
#include "mapdocumentactionhandler.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilesetsDock::TilesetsDock(QWidget* parent) :
	QDockWidget(parent),
	mMapDocument(nullptr),
	mTilesetsView(new TilesetsView(this)),
	mToolBar(new QToolBar)
{
	setObjectName(QLatin1String("Tilesets"));

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
void TilesetsDock::setMapDocument(MapDocument* document)
{
	if (mMapDocument == document) return;

	mMapDocument = document;
	mTilesetsView->setMapDocument(mMapDocument);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetsDock::changeEvent(QEvent* event)
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
void TilesetsDock::buildToolBar()
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
void TilesetsDock::retranslateUi()
{
	setWindowTitle(tr("Tilesets"));
}
/*-----------------------------------------------------------------------------------------------------------*/
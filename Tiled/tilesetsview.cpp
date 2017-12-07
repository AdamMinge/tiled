/*-----------------------------------------------------------------------------------------------------------*/
#include <QContextMenuEvent>
#include <QMenu>
#include "tileset.h"
#include "mapdocument.h"
#include "tilesetsview.h"
#include "tilesetlistmodel.h"
#include "reversingproxymodel.h"
#include "commitonchangeddelegate.h"
#include "mapdocumentactionhandler.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilesetsView::TilesetsView(QWidget* parent) :
	QTreeView(parent),
	mProxyModel(new ReversingProxyModel(this)),
	mMapDocument(nullptr)
{
	QTreeView::setModel(mProxyModel);

	connect(this, &QTreeView::pressed, this, &TilesetsView::indexPressed);

	setItemDelegateForColumn(0, new CommitOnChangedDelegate(this));
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetsView::setMapDocument(MapDocument* mapDocument)
{
	if (mMapDocument == mapDocument) return;

	if (mMapDocument)
	{
		mMapDocument->disconnect(this);
		selectionModel()->disconnect(this);
	}

	mMapDocument = mapDocument;

	if (mMapDocument)
	{
		mProxyModel->setSourceModel(mMapDocument->tilesetsModel());

		connect(mMapDocument, &MapDocument::currentTilesetChanged,
			this, &TilesetsView::currentTilesetChanged);
		connect(selectionModel(), &QItemSelectionModel::currentChanged,
			this, &TilesetsView::currentChanged);

		currentTilesetChanged(mMapDocument->currentTileset());
	}
	else
	{
		mProxyModel->setSourceModel(nullptr);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetsView::contextMenuEvent(QContextMenuEvent* event)
{
	if (!model()) return;

	auto index = indexAt(event->pos());
	QMenu menu;

	menu.addAction(MapDocumentActionHandler::instance()->actionNewTileset());

	if (index.isValid())
	{
		menu.addAction(MapDocumentActionHandler::instance()->actionTilesetProperties());
		menu.addAction(MapDocumentActionHandler::instance()->actionSelectNextTileset());
		menu.addAction(MapDocumentActionHandler::instance()->actionSelectPreviousTileset());
		menu.addAction(MapDocumentActionHandler::instance()->actionRemoveTileset());
	}

	menu.exec(event->globalPos());
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetsView::currentTilesetChanged(Tileset* tileset)
{
	Q_ASSERT(mMapDocument);

	auto sourceIndex = mMapDocument->tilesetsModel()->index(tileset);
	auto index = mProxyModel->mapFromSource(sourceIndex);

	selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetsView::indexPressed(const QModelIndex& index)
{
	auto sourceIndex = mProxyModel->mapToSource(index);

	if (auto tileset = mMapDocument->tilesetsModel()->tileset(sourceIndex))
		mMapDocument->setCurrentObject(tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetsView::currentChanged()
{
	Q_ASSERT(mMapDocument);

	auto index = selectionModel()->currentIndex();
	auto sourceIndex = mProxyModel->mapToSource(index);
	auto tileset = mMapDocument->tilesetsModel()->tileset(sourceIndex);

	mMapDocument->setCurrentTileset(tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
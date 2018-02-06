/*-----------------------------------------------------------------------------------------------------------*/
#include <QMenu>
#include <QHeaderView>
#include <QContextMenuEvent>
#include "tileset.h"
#include "tilesetview.h"
#include "tilesettablemodel.h"
#include "tilesetviewdelegate.h"
#include "preferencesmanager.h"
#include "zoomable.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilesetView::TilesetView(QWidget* parent) :
	QTableView(parent),
	mZoomable(new Zoomable(this)),
	mDrawGrid(true),
	mMarkAnimatedTiles(true)
{
	setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	setItemDelegate(new TilesetViewDelegate(this, this));
	setShowGrid(false);
	setTabKeyNavigation(false);

	auto hHeader = horizontalHeader();
	auto vHeader = verticalHeader();
	hHeader->hide();
	vHeader->hide();
	hHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
	vHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
	hHeader->setMinimumSectionSize(1);
	vHeader->setMinimumSectionSize(1);

	setLayoutDirection(Qt::LeftToRight);

	const auto preferencesManager = PreferencesManager::instance();
	mDrawGrid = preferencesManager->showTilesetGrid();

	connect(preferencesManager, &PreferencesManager::showTilesetGridChanged, this, &TilesetView::setDrawGrid);
	connect(mZoomable, &Zoomable::scaleChanged, this, &TilesetView::adjustScale);
}
/*-----------------------------------------------------------------------------------------------------------*/
int TilesetView::sizeHintForColumn(int column) const 
{
	Q_UNUSED(column);

	const auto tilesetModel = qobject_cast<const TilesetTableModel*>(model());
	if (!tilesetModel) return -1;

	const auto tileWidth = tilesetModel->tileset()->tileSize().width();
	return qRound(tileWidth * scale()) + (mDrawGrid ? 1 : 0);
}
/*-----------------------------------------------------------------------------------------------------------*/
int TilesetView::sizeHintForRow(int row) const 
{
	Q_UNUSED(row)

	const auto tilesetModel = qobject_cast<TilesetTableModel*>(model());
	if (!tilesetModel) return -1;

	const auto tileHeight = tilesetModel->tileset()->tileSize().height();
	return qRound(tileHeight * scale()) + (mDrawGrid ? 1 : 0);;
}
/*-----------------------------------------------------------------------------------------------------------*/
Zoomable* TilesetView::zoomable() const
{
	return mZoomable;
}
/*-----------------------------------------------------------------------------------------------------------*/
qreal TilesetView::scale() const 
{
	Q_ASSERT(mZoomable);
	return mZoomable->scale();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TilesetView::drawGrid() const 
{
	return mDrawGrid;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetView::setModel(QAbstractItemModel* model)
{
	Q_ASSERT(qobject_cast<TilesetTableModel*>(model));
	QTableView::setModel(model);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetView::setMarkAnimatedTiles(bool enabled)
{
	if (mMarkAnimatedTiles == enabled) return;

	mMarkAnimatedTiles = enabled;

	viewport()->update();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TilesetView::markAnimatedTiles() const
{
	return mMarkAnimatedTiles;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetView::wheelEvent(QWheelEvent* event)
{
	if (event->modifiers() & Qt::ControlModifier && 
		event->orientation() == Qt::Vertical)
	{
		Q_ASSERT(mZoomable);
		mZoomable->handleWheelDelta(event->delta());
	}
	else QTableView::wheelEvent(event);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetView::contextMenuEvent(QContextMenuEvent* event)
{
	const auto model = qobject_cast<TilesetTableModel*>(QTableView::model());

	if (!model) return;

	QMenu contextMenu;
	auto showTilesetGrid = contextMenu.addAction(tr("Show Tileset Grid"));
	showTilesetGrid->setCheckable(true);
	showTilesetGrid->setChecked(mDrawGrid);

	connect(showTilesetGrid, &QAction::toggled, 
		PreferencesManager::instance(), &PreferencesManager::setShowTilesetGrid);

	contextMenu.exec(event->globalPos());
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetView::setDrawGrid(bool drawGrid)
{
	if (mDrawGrid == drawGrid) return;

	mDrawGrid = drawGrid;

	if(const auto model = qobject_cast<TilesetTableModel*>(QTableView::model()))
		resetModel(model);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetView::adjustScale()
{
	auto model = qobject_cast<TilesetTableModel*>(QTableView::model());
	Q_ASSERT(model);

	resetModel(model);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetView::resetModel(TilesetTableModel* model)
{
	Q_ASSERT(model);
	model->resetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/


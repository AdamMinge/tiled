/*-----------------------------------------------------------------------------------------------------------*/
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QToolBar>
#include <QEvent>
#include "tile.h"
#include "utils.h"
#include "tileset.h"
#include "tilesetdock.h"
#include "tilesetview.h"
#include "mapdocument.h"
#include "tilesettablemodel.h"
#include "tilesetlistmodel.h"
#include "mapdocumentactionhandler.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilesetDock::TilesetDock(QWidget* parent) :
	QDockWidget(parent),
	mMapDocument(nullptr),
	mTabBar(new QTabBar),
	mToolBar(new QToolBar),
	mViewStack(new QStackedWidget),
	mUpdating(false)
{
	setObjectName(QLatin1String("Tileset"));

	mTabBar->setUsesScrollButtons(true);
	mTabBar->setExpanding(false);

	auto widget = new QWidget(this);
	
	auto horizontal = new QHBoxLayout;
	horizontal->setSpacing(0);
	horizontal->addWidget(mTabBar);

	auto horizontal2 = new QHBoxLayout;
	horizontal2->setSpacing(0);
	horizontal2->addWidget(mToolBar, 1);

	auto vertical = new QVBoxLayout(widget);
	vertical->setSpacing(0);
	vertical->setMargin(0);
	vertical->addLayout(horizontal);
	vertical->addWidget(mViewStack);
	vertical->addLayout(horizontal2);
	widget->setLayout(vertical);

	buildToolBar();
	setWidget(widget);
	retranslateUi();

	connect(mTabBar, &QTabBar::currentChanged, this, &TilesetDock::currentTabChanged);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::setMapDocument(MapDocument* document)
{
	if (mMapDocument == document) return;

	if (mMapDocument)
	{
		const auto tilesetsModel = mMapDocument->tilesetsModel();

		mUpdating = true;
		for (auto i = 0; i < tilesetsModel->rowCount(); i++)
			tilesetRemoved(tilesetsModel->tileset(tilesetsModel->index(i)));
		mUpdating = false;

		mMapDocument->disconnect(this);
	}
		
	mMapDocument = document;
	Q_ASSERT(mTilesets.isEmpty());
	Q_ASSERT(mViewStack->count() == 0);

	if (mMapDocument)
	{
		const auto tilesetsModel = mMapDocument->tilesetsModel();
			
		mUpdating = true;
		for (auto i = 0; i < tilesetsModel->rowCount(); i++)
			tilesetAdded(tilesetsModel->tileset(tilesetsModel->index(i)));
		mUpdating = false;

		currentTilesetChanged(mMapDocument->currentTileset());

		connect(mMapDocument, &MapDocument::tilesetAdded, this, &TilesetDock::tilesetAdded);
		connect(mMapDocument, &MapDocument::tilesetRemoved, this, &TilesetDock::tilesetRemoved);

		connect(mMapDocument, &MapDocument::currentTilesetChanged, this, &TilesetDock::currentTilesetChanged);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::changeEvent(QEvent* event)
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
void TilesetDock::currentTabChanged()
{
	const auto index = mTabBar->currentIndex();
	const auto view = currentTilesetView();

	if (index > -1)
	{
		if (tilesetView(index))
			mViewStack->setCurrentIndex(index);
	}

	if (view && !mUpdating)
	{
		if (const auto selectionModel = view->selectionModel())
			currentTileChanged(selectionModel->currentIndex());

		mMapDocument->setCurrentTileset(currentTileset());
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::currentTilesetChanged(Tileset* tileset)
{
	Q_ASSERT(!tileset || mTilesets.contains(tileset));
	if (currentTileset() == tileset) return;

	mTabBar->setCurrentIndex(mTilesets.indexOf(tileset));
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::selectionTileChanged()
{
	auto view = currentTilesetView();
	Q_ASSERT(view);

	auto selectionModel = view->selectionModel();
	Q_ASSERT(selectionModel);

	auto indexes = selectionModel->selectedIndexes();
	if (indexes.isEmpty()) return;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::currentTileChanged(const QModelIndex& index)
{
	if (!index.isValid()) return;
	
	const auto model = static_cast<TilesetTableModel*>(const_cast<QAbstractItemModel*>(index.model()));
	const auto tile = model->tile(index);

	mMapDocument->setCurrentObject(tile);
	mMapDocument->setCurrentTile(tile);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::buildToolBar()
{
	Q_ASSERT(mToolBar);

	mToolBar->addActions({ MapDocumentActionHandler::instance()->actionNewTileset(), 
		MapDocumentActionHandler::instance()->actionTilesetProperties() ,
		MapDocumentActionHandler::instance()->actionRemoveTileset() });

	mToolBar->setIconSize(iconSize(IconSize::Small));
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::retranslateUi()
{
	setWindowTitle(tr("Tileset"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::tilesetAdded(Tileset* tileset)
{
	const auto view = new TilesetView;
	const auto index = mMapDocument->tilesetsModel()->index(tileset).row();

	mTilesets.insert(index, tileset);

	mViewStack->insertWidget(index, view);
	mTabBar->insertTab(index, tileset->name());

	setupTilesetModel(view, tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::tilesetRemoved(Tileset* tileset)
{
	const auto index = mTilesets.indexOf(tileset);
	const auto view = tilesetView(index);
	
	mTilesets.remove(index);
	delete view;

	mTabBar->removeTab(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDock::setupTilesetModel(TilesetView* view, Tileset* tileset)
{
	view->setModel(new TilesetTableModel(mMapDocument, tileset, view));

	const auto selectionModel = view->selectionModel();

	connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &TilesetDock::selectionTileChanged);
	connect(selectionModel, &QItemSelectionModel::currentChanged, this, &TilesetDock::currentTileChanged);
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* TilesetDock::currentTileset() const
{
	const auto index = mTabBar->currentIndex();

	if (index < 0) return nullptr;
	else return mTilesets.at(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
TilesetView* TilesetDock::currentTilesetView() const
{
	return static_cast<TilesetView*>(mViewStack->currentWidget());
}
/*-----------------------------------------------------------------------------------------------------------*/
TilesetView* TilesetDock::tilesetView(int index) const
{
	return static_cast<TilesetView*>(mViewStack->widget(index));
}
/*-----------------------------------------------------------------------------------------------------------*/
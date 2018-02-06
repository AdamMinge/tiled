/*-----------------------------------------------------------------------------------------------------------*/
#include <QStyle>
#include <QFileInfo>
#include <QApplication>
#include "mapdocumentactionhandler.h"
#include "preferencesmanager.h"
#include "newtilesetdialog.h"
#include "addremovetileset.h"
#include "addremovelayer.h"
#include "layeriterator.h"
#include "groupcommand.h"
#include "mapdocument.h"
#include "grouplayer.h"
#include "movelayer.h"
#include "tilelayer.h"
#include "utils.h"
#include "map.h"
#include "reparentlayer.h"
#include "ChangeLayerProperty.h"
#include "documentmanager.h"
/*-----------------------------------------------------------------------------------------------------------*/
MapDocumentActionHandler* MapDocumentActionHandler::mInstance = nullptr;
/*-----------------------------------------------------------------------------------------------------------*/
MapDocumentActionHandler* MapDocumentActionHandler::instance()
{
	if(!mInstance)
		mInstance = new MapDocumentActionHandler();

	Q_ASSERT(mInstance);
	return mInstance;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::deleteInstance()
{
	Q_ASSERT(mInstance);
	delete mInstance;
	mInstance = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::setMapDocument(MapDocument* mapDocument)
{
	if (mMapDocument == mapDocument) return;

	if(mMapDocument)
	{
		mMapDocument->disconnect(this);
	}

	mMapDocument = mapDocument;
	updateActions();

	if(mMapDocument)
	{
		connect(mMapDocument, &MapDocument::tilesetAdded,
			this, &MapDocumentActionHandler::updateActions);
		connect(mMapDocument, &MapDocument::tilesetRemoved,
			this, &MapDocumentActionHandler::updateActions);
		connect(mMapDocument, &MapDocument::currentTilesetChanged,
			this, &MapDocumentActionHandler::updateActions);

		connect(mMapDocument, &MapDocument::layerAdded,
			this, &MapDocumentActionHandler::updateActions);
		connect(mMapDocument, &MapDocument::layerRemoved,
			this, &MapDocumentActionHandler::updateActions);
		connect(mMapDocument, &MapDocument::currentLayerChanged,
			this, &MapDocumentActionHandler::updateActions);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
MapDocument* MapDocumentActionHandler::mapDocument() const
{
	return mMapDocument;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::retranslateUi()
{
	mNewTileset->setText(tr("New Tileset..."));
	mRemoveTileset->setText(tr("Remove Tileset"));
	mTilesetProperties->setText(tr("Tileset Properties..."));
	mSelectNextTileset->setText(tr("Select Next Tileset"));
	mSelectPreviousTileset->setText(tr("Select Previous Tileset"));

	mCut->setText(tr("Cut"));
	mCopy->setText(tr("Copy"));
	mPaste->setText(tr("Paste"));
	mDelete->setText(tr("Delete"));
	mSelectAll->setText(tr("Select All"));
	mInvertSelection->setText(tr("Invert Selection"));
	mSelectNone->setText(tr("Select None"));

	mResizeMap->setText(tr("Resize Map..."));
	mMapProperties->setText(tr("Map Properties..."));

	mNewTileLayer->setText(tr("Tile Layer"));
	mNewGroupLayer->setText(tr("Group Layer"));
	mGroupLayer->setText(tr("Group Layer"));
	mUngroupLayer->setText(tr("Ungroup Layer"));
	mDuplicateLayer->setText(tr("Duplicate Layer"));
	mMergeLayerDown->setText(tr("Merge Layer Down"));
	mMergeLayerUp->setText(tr("Merge Layer Up"));
	mRemoveLayer->setText(tr("Remove Layer"));
	mSelectNextLayer->setText(tr("Select Next Layer"));
	mSelectPreviousLayer->setText(tr("Select Previous Layer"));
	mRaiseLayer->setText(tr("Raise Layer"));
	mLowerLayer->setText(tr("Lower Layer"));
	mShowHideAllOtherLayers->setText(tr("Show/Hide All Other layers"));
	mLayerProperties->setText(tr("Layer Properties..."));
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionNewTileset()
{
	return mNewTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionRemoveTileset()
{
	return mRemoveTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionTilesetProperties()
{
	return mTilesetProperties;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionSelectNextTileset()
{
	return mSelectNextTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionSelectPreviousTileset()
{
	return mSelectPreviousTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionCut()
{
	return mCut;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionCopy()
{
	return mCopy;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionPaste()
{
	return mPaste;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionDelete()
{
	return mDelete;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionSelectAll()
{
	return mSelectAll;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionInvertSelection()
{
	return mInvertSelection;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionSelectNone()
{
	return mSelectNone;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionResizeMap()
{
	return mResizeMap;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionMapProperties()
{
	return mMapProperties;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionNewTileLayer()
{
	return mNewTileLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionNewGroupLayer()
{
	return mNewGroupLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionGroupLayer()
{
	return mGroupLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionUngroupLayer()
{
	return mUngroupLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionDuplicateLayer()
{
	return mDuplicateLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionMergeLayerDown()
{
	return mMergeLayerDown;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionMergeLayerUp()
{
	return mMergeLayerUp;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionRemoveLayer()
{
	return mRemoveLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionSelectNextLayer()
{
	return mSelectNextLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionSelectPreviousLayer()
{
	return mSelectPreviousLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionRaiseLayer()
{
	return mRaiseLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionLowerLayer()
{
	return mLowerLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionShowHideAllOtherLayers()
{
	return mShowHideAllOtherLayers;
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* MapDocumentActionHandler::actionLayerProperties()
{
	return mLayerProperties;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::newTileset()
{
	Q_ASSERT(mMapDocument);

	const auto startLocation = PreferencesManager::instance()->recentImageDirectory();

	NewTilesetDialog newTilesetDialog;
	newTilesetDialog.setImagePath(startLocation);

	const auto tileset = newTilesetDialog.createTileset();
	if (!tileset) return;

	PreferencesManager::instance()->setRecentImageDirectory(QFileInfo(tileset->imageReference().source()).absolutePath());

	mMapDocument->undoStack()->push(new AddTileset(mMapDocument, tileset));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::removeTileset()
{
	Q_ASSERT(mMapDocument);
	auto mapTilesetIndex = mMapDocument->map()->tilesets().indexOf(mMapDocument->currentTileset());
	Q_ASSERT(mapTilesetIndex != -1);

	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new RemoveTileset(mMapDocument, mapTilesetIndex));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::tilesetProperties()
{
	Q_ASSERT(mMapDocument);

	auto documentManager = DocumentManager::instance();
	documentManager->openTilesetDocument(mMapDocument->currentTileset());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::selectNextTileset()
{
	Q_ASSERT(mMapDocument);
	const auto index = mMapDocument->map()->tilesets().indexOf(mMapDocument->currentTileset());
	const auto nextTileset = mMapDocument->map()->tilesets().at(index + 1);

	mMapDocument->setCurrentTileset(nextTileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::selectPreviousTileset()
{
	Q_ASSERT(mMapDocument);
	const auto index = mMapDocument->map()->tilesets().indexOf(mMapDocument->currentTileset());
	const auto previousTileset = mMapDocument->map()->tilesets().at(index - 1);

	mMapDocument->setCurrentTileset(previousTileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::cut()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::copy()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::paste()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::delete_()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::selectAll()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::invertSelection()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::selectNone()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::resizeMap()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::mapProperties()
{
	Q_ASSERT(mMapDocument);
	mMapDocument->setCurrentObject(mMapDocument->map());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::newTileLayer()
{
	Q_ASSERT(mMapDocument);

	GroupLayer* parentLayer = nullptr;
	auto name = QString("tileLayer");
	auto size = mMapDocument->map()->size();

	if (mMapDocument->currentLayer() == mMapDocument->map()->rootLayer())
		parentLayer = mMapDocument->map()->rootLayer();
	else
		parentLayer = mMapDocument->currentLayer()->parent();

	Q_ASSERT(parentLayer);
	Q_ASSERT(!name.isEmpty());
	Q_ASSERT(!size.isEmpty());

	const auto newLayer = new TileLayer(name, size);

	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new AddLayer(mMapDocument, newLayer, parentLayer));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::newGroupLayer()
{
	Q_ASSERT(mMapDocument);

	GroupLayer* parentLayer = nullptr;
	auto name = QString("groupLayer");

	if (mMapDocument->currentLayer() == mMapDocument->map()->rootLayer())
		parentLayer = mMapDocument->map()->rootLayer();
	else
		parentLayer = mMapDocument->currentLayer()->parent();

	Q_ASSERT(parentLayer);
	Q_ASSERT(!name.isEmpty());

	const auto newLayer = new GroupLayer(name);

	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new AddLayer(mMapDocument, newLayer, parentLayer));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::groupLayer()
{
	Q_ASSERT(mMapDocument);
	auto currentLayer = mMapDocument->currentLayer();
	const auto newGroupLayer = new GroupLayer("groupLayer");
	auto commands = QList<Command*>{};
	
	Q_ASSERT(currentLayer);
	auto parentLayer = currentLayer->parent();
	const auto index = currentLayer->siblingIndex() + 1;

	Q_ASSERT(parentLayer);
	commands.append(new AddLayer(mMapDocument, index, newGroupLayer, parentLayer));
	commands.append(new ReparentLayer(mMapDocument, currentLayer, newGroupLayer, 0));

	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new GroupCommand(tr("Group Layer"), std::move(commands)));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::ungroupLayer()
{
	Q_ASSERT(mMapDocument);
	auto currentLayer = mMapDocument->currentLayer();

	auto commands = QList<Command*>{};
	auto layers = QList<Layer*>{};
	GroupLayer* groupLayer = nullptr;

	Q_ASSERT(currentLayer);
	if(const auto layer = dynamic_cast<GroupLayer*>(currentLayer))
	{
		layers = layer->layers();
		groupLayer = layer;
	}
	else if(currentLayer->parent())
	{
		layers.append(currentLayer);
		groupLayer = currentLayer->parent();
	}
	else { return; }

	Q_ASSERT(groupLayer);
	auto parent = groupLayer->parent();
	const auto index = groupLayer->siblingIndex();
	Q_ASSERT(parent);

	for(auto iter = layers.rbegin(); iter != layers.rend(); ++iter)
		commands.append(new ReparentLayer(mMapDocument, *iter, parent, index + 1));

	if (groupLayer->layerCount() - layers.count() == 0)
		commands.append(new RemoveLayer(mMapDocument, index, parent));

	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new GroupCommand(tr("Ungroup Layer"), std::move(commands)));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::duplicateLayer()
{
	Q_ASSERT(mMapDocument);
	auto currentLayer = mMapDocument->currentLayer();

	Q_ASSERT(currentLayer);
	const auto parent = currentLayer->parent();
	const auto index = currentLayer->siblingIndex();
	const auto newLayer = currentLayer->clone();

	auto undoStack = mMapDocument->undoStack();
	auto command = new AddLayer(mMapDocument, index, newLayer, parent);
	command->setText(tr("Duplicate Layer"));
	
	undoStack->push(command);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::mergeLayerDown()
{
	Q_ASSERT(mMapDocument);
	auto currentLayer = mMapDocument->currentLayer();
	auto index = currentLayer->siblingIndex();
	auto parentLayer = currentLayer->parent();

	Q_ASSERT(index > 0);
	Q_ASSERT(currentLayer);
	Q_ASSERT(parentLayer);
	auto lowerLayer = currentLayer->siblings().at(index - 1);

	Q_ASSERT(lowerLayer);
	Q_ASSERT(lowerLayer->canMergeWith(currentLayer));

	auto mergeLayer = lowerLayer->mergeWith(currentLayer);
	Q_ASSERT(mergeLayer);

	auto undoStack = mMapDocument->undoStack();
	auto commands = QList<Command*>{};

	commands.append(new AddLayer(mMapDocument, index - 1, mergeLayer, parentLayer));
	commands.append(new RemoveLayer(mMapDocument, index, parentLayer));
	commands.append(new RemoveLayer(mMapDocument, index, parentLayer));

	undoStack->push(new GroupCommand(tr("Merge Layer Down"), std::move(commands)));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::mergeLayerUp()
{
	Q_ASSERT(mMapDocument);
	auto currentLayer = mMapDocument->currentLayer();
	auto index = currentLayer->siblingIndex();
	auto parentLayer = currentLayer->parent();

	Q_ASSERT(index + 1 < parentLayer->layerCount());
	Q_ASSERT(currentLayer);
	Q_ASSERT(parentLayer);
	auto higherLayer = currentLayer->siblings().at(index + 1);

	Q_ASSERT(higherLayer);
	Q_ASSERT(higherLayer->canMergeWith(currentLayer));

	auto mergeLayer = higherLayer->mergeWith(currentLayer);
	Q_ASSERT(mergeLayer);

	auto undoStack = mMapDocument->undoStack();
	auto commands = QList<Command*>{};

	commands.append(new RemoveLayer(mMapDocument, index, parentLayer));
	commands.append(new RemoveLayer(mMapDocument, index, parentLayer));
	commands.append(new AddLayer(mMapDocument, index, mergeLayer, parentLayer));

	undoStack->push(new GroupCommand(tr("Merge Layer Up"), std::move(commands)));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::removeLayer()
{
	Q_ASSERT(mMapDocument);

	auto currentLayer = mMapDocument->currentLayer();
	auto parent = currentLayer->parent();

	Q_ASSERT(currentLayer != mMapDocument->map()->rootLayer());
	Q_ASSERT(currentLayer);
	Q_ASSERT(parent);

	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new RemoveLayer(mMapDocument, currentLayer->siblingIndex(), parent));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::selectNextLayer()
{
	Q_ASSERT(mMapDocument);

	auto currentLayer = mMapDocument->currentLayer();
	auto parent = mMapDocument->map()->rootLayer();

	Q_ASSERT(currentLayer);
	Q_ASSERT(parent);

	mMapDocument->setCurrentLayer(LayerIterator<PostOrderLayerIteration>(parent, currentLayer).next());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::selectPreviousLayer()
{
	Q_ASSERT(mMapDocument);

	auto currentLayer = mMapDocument->currentLayer();
	auto parent = mMapDocument->map()->rootLayer();

	Q_ASSERT(currentLayer);
	Q_ASSERT(parent);

	mMapDocument->setCurrentLayer(LayerIterator<PostOrderLayerIteration>(parent, currentLayer).previous());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::raiseLayer()
{
	Q_ASSERT(mMapDocument);

	auto currentLayer = mMapDocument->currentLayer();
	Q_ASSERT(currentLayer != mMapDocument->map()->rootLayer());
	Q_ASSERT(currentLayer);

	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new MoveLayer(mMapDocument, currentLayer, MoveLayer::Move::Raise));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::lowerLayer()
{
	Q_ASSERT(mMapDocument);

	auto currentLayer = mMapDocument->currentLayer();
	Q_ASSERT(currentLayer != mMapDocument->map()->rootLayer());
	Q_ASSERT(currentLayer);

	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new MoveLayer(mMapDocument, currentLayer, MoveLayer::Move::Lower));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::showHideAllOtherLayers()
{
	Q_ASSERT(mMapDocument);

	auto currentLayer = mMapDocument->currentLayer();
	Q_ASSERT(currentLayer != mMapDocument->map()->rootLayer());
	Q_ASSERT(currentLayer);

	auto layers = QList<Layer*>{};	
	while (currentLayer)
	{
		auto siblings = currentLayer->siblings();
		for (decltype(auto) sibling : siblings)
			if (sibling != currentLayer) layers.append(sibling);

		currentLayer = currentLayer->parent();
	}

	auto visibility = true;
	for (decltype(auto) layer : layers)
	{
		if (layer->isVisible())
		{
			visibility = false;
			break;
		}
	}
		
	auto undoStack = mMapDocument->undoStack();
	auto commands = QList<Command*>{};

	for (decltype(auto) layer : layers)
		commands.append(new ChangeLayerProperty(mMapDocument, layer, 
			visibility, ChangeLayerProperty::BoolProperty::Visible));

	undoStack->push(new GroupCommand(visibility ? tr("Show Other Layer") : tr("Hide Other Layers"),
		std::move(commands)));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::layerProperties()
{
	Q_ASSERT(mMapDocument);
	mMapDocument->setCurrentObject(mMapDocument->currentLayer());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocumentActionHandler::updateActions()
{
	auto isCurrentTileset = false;
	auto canSelectNextTileset = false;
	auto canSelectPreviousTileset = false;

	auto isLayer = false;
	auto isNotRootLayer = false;
	auto canUngroupLayer = false;
	auto canSelectNextLayer = false;
	auto canSelectPreviosLayer = false;
	auto canRaiseLayer = false;
	auto canLowerLayer = false;
	auto canMergeLayerDown = false;
	auto canMergeLayerUp = false;

	if(mMapDocument)
	{
		const auto currentTileset = mMapDocument->currentTileset();
		const auto lastTileset = currentTileset ? mMapDocument->map()->tilesets().last() : nullptr;
		const auto firstTileset = currentTileset ? mMapDocument->map()->tilesets().first() : nullptr;

		isCurrentTileset = static_cast<bool>(currentTileset);
		canSelectNextTileset = lastTileset != currentTileset;
		canSelectPreviousTileset = firstTileset != currentTileset;

		const auto currentLayer = mMapDocument->currentLayer();
		const auto currentGroupLayer = dynamic_cast<GroupLayer*>(currentLayer);
		const auto currentLayerParent = currentLayer->parent();
		const auto rootLayer = mMapDocument->map()->rootLayer();
		auto currentLayerIter = LayerIterator<PostOrderLayerIteration>(rootLayer, currentLayer);
		const auto mergeLayerDown = (currentLayer->siblingIndex() > 0) ?
			currentLayer->siblings().at(currentLayer->siblingIndex() - 1) : nullptr;
		const auto mergeLayerUp = (currentLayer->siblingIndex() + 1 < currentLayer->siblings().count()) ?
			currentLayer->siblings().at(currentLayer->siblingIndex() + 1) : nullptr;
		
		isLayer = static_cast<bool>(currentLayer);
		isNotRootLayer = static_cast<bool>(currentLayer) && currentLayer != rootLayer;
		canUngroupLayer = isNotRootLayer && (static_cast<bool>(currentGroupLayer) || currentLayerParent != rootLayer);
		canSelectNextLayer = currentLayerIter.hasNext();
		canSelectPreviosLayer = currentLayerIter.hasPrevious();
		canRaiseLayer = (currentLayerParent && currentLayerParent != rootLayer) || static_cast<bool>(mergeLayerUp);
		canLowerLayer = (currentLayerParent && currentLayerParent != rootLayer) || static_cast<bool>(mergeLayerDown);
		canMergeLayerDown = static_cast<bool>(mergeLayerDown) && currentLayer->canMergeWith(mergeLayerDown);
		canMergeLayerUp = static_cast<bool>(mergeLayerUp) && currentLayer->canMergeWith(mergeLayerUp);
	}

	mRemoveTileset->setEnabled(isCurrentTileset);
	mTilesetProperties->setEnabled(isCurrentTileset);
	mSelectNextTileset->setEnabled(canSelectNextTileset);
	mSelectPreviousTileset->setEnabled(canSelectPreviousTileset);

	mGroupLayer->setEnabled(isNotRootLayer);
	mUngroupLayer->setEnabled(canUngroupLayer);
	mDuplicateLayer->setEnabled(isNotRootLayer);
	mMergeLayerDown->setEnabled(canMergeLayerDown);
	mMergeLayerUp->setEnabled(canMergeLayerUp);
	mRemoveLayer->setEnabled(isNotRootLayer);
	mSelectNextLayer->setEnabled(canSelectNextLayer);
	mSelectPreviousLayer->setEnabled(canSelectPreviosLayer);
	mRaiseLayer->setEnabled(canRaiseLayer);
	mLowerLayer->setEnabled(canLowerLayer);
	mShowHideAllOtherLayers->setEnabled(isNotRootLayer);
	mLayerProperties->setEnabled(isLayer);
}
/*-----------------------------------------------------------------------------------------------------------*/
MapDocumentActionHandler::MapDocumentActionHandler() : 
	mMapDocument(nullptr)
{
	mNewTileset = new QAction(this);
	mRemoveTileset = new QAction(this);
	mTilesetProperties = new QAction(this);
	mSelectNextTileset = new QAction(this);
	mSelectPreviousTileset = new QAction(this);

	mCut = new QAction(this);
	mCopy = new QAction(this);
	mPaste = new QAction(this);
	mDelete = new QAction(this);
	mSelectAll = new QAction(this);
	mInvertSelection = new QAction(this);
	mSelectNone = new QAction(this);

	mResizeMap = new QAction(this);
	mMapProperties = new QAction(this);

	mNewTileLayer = new QAction(this);
	mNewGroupLayer = new QAction(this);
	mGroupLayer = new QAction(this);
	mUngroupLayer = new QAction(this);
	mDuplicateLayer = new QAction(this);
	mMergeLayerDown = new QAction(this);
	mMergeLayerUp = new QAction(this);
	mRemoveLayer = new QAction(this);
	mSelectNextLayer = new QAction(this);
	mSelectPreviousLayer = new QAction(this);
	mRaiseLayer = new QAction(this);
	mLowerLayer = new QAction(this);
	mShowHideAllOtherLayers = new QAction(this);
	mLayerProperties = new QAction(this);

	mNewTileset->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-new.png"), 
	{ QSize(16,16) }));
	mTilesetProperties->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-properties.png"), 
	{ QSize(16,16) }));
	mRemoveTileset->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-delete.png"), 
	{ QSize(16,16) }));
	mSelectNextTileset->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/go-up.png"),
	{ QSize(16,16) }));
	mSelectPreviousTileset->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/go-down.png"),
	{ QSize(16,16) }));

	mCut->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-cut.png"),
	{ QSize(24,24) }));
	mCopy->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-copy.png"),
	{ QSize(24,24) }));
	mPaste->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-paste.png"),
	{ QSize(24,24) }));
	mDelete->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-delete.png"),
	{ QSize(16,16) }));
	mResizeMap->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-page-setup.png"),
	{ QSize(16,16) }));
	mMapProperties->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-properties.png"),
	{ QSize(16,16) }));

	mNewTileLayer->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/layer-tile.png"),
	{ QSize(16,16) }));
	mNewGroupLayer->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon));
	mDuplicateLayer->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/stock-duplicate-16.png"),
	{ QSize(16,16) }));
	mRemoveLayer->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-delete.png"),
	{ QSize(16,16) }));
	mRaiseLayer->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/go-up.png"),
	{ QSize(16,16) }));
	mLowerLayer->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/go-down.png"),
	{ QSize(16,16) }));
	mShowHideAllOtherLayers->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/show_hide_others.png"),
	{ QSize(16,16) }));
	mLayerProperties->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-properties.png"),
	{ QSize(16,16) }));

	connect(mNewTileset, &QAction::triggered, this, &MapDocumentActionHandler::newTileset);
	connect(mRemoveTileset, &QAction::triggered, this, &MapDocumentActionHandler::removeTileset);
	connect(mTilesetProperties, &QAction::triggered, this, &MapDocumentActionHandler::tilesetProperties);
	connect(mSelectNextTileset, &QAction::triggered, this, &MapDocumentActionHandler::selectNextTileset);
	connect(mSelectPreviousTileset, &QAction::triggered, this, &MapDocumentActionHandler::selectPreviousTileset);

	connect(mCut, &QAction::triggered, this, &MapDocumentActionHandler::cut);
	connect(mCopy, &QAction::triggered, this, &MapDocumentActionHandler::copy);
	connect(mPaste, &QAction::triggered, this, &MapDocumentActionHandler::paste);
	connect(mDelete, &QAction::triggered, this, &MapDocumentActionHandler::delete_);
	connect(mSelectAll, &QAction::triggered, this, &MapDocumentActionHandler::selectAll);
	connect(mInvertSelection, &QAction::triggered, this, &MapDocumentActionHandler::invertSelection);
	connect(mSelectNone, &QAction::triggered, this, &MapDocumentActionHandler::selectNone);
	connect(mResizeMap, &QAction::triggered, this, &MapDocumentActionHandler::resizeMap);
	connect(mMapProperties, &QAction::triggered, this, &MapDocumentActionHandler::mapProperties);

	connect(mNewTileLayer, &QAction::triggered, this, &MapDocumentActionHandler::newTileLayer);
	connect(mNewGroupLayer, &QAction::triggered, this, &MapDocumentActionHandler::newGroupLayer);
	connect(mGroupLayer, &QAction::triggered, this, &MapDocumentActionHandler::groupLayer);
	connect(mUngroupLayer, &QAction::triggered, this, &MapDocumentActionHandler::ungroupLayer);
	connect(mDuplicateLayer, &QAction::triggered, this, &MapDocumentActionHandler::duplicateLayer);
	connect(mMergeLayerDown, &QAction::triggered, this, &MapDocumentActionHandler::mergeLayerDown);
	connect(mMergeLayerUp, &QAction::triggered, this, &MapDocumentActionHandler::mergeLayerUp);
	connect(mRemoveLayer, &QAction::triggered, this, &MapDocumentActionHandler::removeLayer);
	connect(mSelectNextLayer, &QAction::triggered, this, &MapDocumentActionHandler::selectNextLayer);
	connect(mSelectPreviousLayer, &QAction::triggered, this, &MapDocumentActionHandler::selectPreviousLayer);
	connect(mRaiseLayer, &QAction::triggered, this, &MapDocumentActionHandler::raiseLayer);
	connect(mLowerLayer, &QAction::triggered, this, &MapDocumentActionHandler::lowerLayer);
	connect(mShowHideAllOtherLayers, &QAction::triggered, this, &MapDocumentActionHandler::showHideAllOtherLayers);
	connect(mLayerProperties, &QAction::triggered, this, &MapDocumentActionHandler::layerProperties);

	retranslateUi();
	updateActions();
}
/*-----------------------------------------------------------------------------------------------------------*/

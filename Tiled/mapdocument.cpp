/*-----------------------------------------------------------------------------------------------------------*/
#include <qfileinfo.h>
#include "map.h"
#include "tile.h"
#include "tileset.h"
#include "grouplayer.h"
#include "mapdocument.h"
#include "layertreemodel.h"
#include "tilesetlistmodel.h"
/*-----------------------------------------------------------------------------------------------------------*/
MapDocument::MapDocument(Map* map, const QString &fileName) :
	Document(fileName, createDisplayName(fileName), DocumentType::MapDocumentType),
	mMap(map),
	mCurrentTile(nullptr),
	mCurrentTileset(nullptr),
	mCurrentLayer(map->rootLayer()),
	mLayerModel(new LayerTreeModel(this, this)),
	mTilesetsModel(new TilesetListModel(this, this))
{
	connect(mLayerModel, &LayerTreeModel::layerAdded, this, &MapDocument::onLayerAdded);
	connect(mLayerModel, &LayerTreeModel::layerRemoved, this, &MapDocument::onLayerRemoved);

	connect(mTilesetsModel, &TilesetListModel::tilesetAdded, this, &MapDocument::onTilesetAdded);
	connect(mTilesetsModel, &TilesetListModel::tilesetRemoved, this, &MapDocument::onTilesetRemoved);
}
/*-----------------------------------------------------------------------------------------------------------*/
MapDocument::~MapDocument()
{
	delete mMap;
}
/*-----------------------------------------------------------------------------------------------------------*/
Map* MapDocument::map() const
{
	return mMap;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocument::setCurrentTile(Tile* tile)
{
	if (mCurrentTile == tile) return;

	mCurrentTile = tile;
	emit currentTileChanged(mCurrentTile);
}
/*-----------------------------------------------------------------------------------------------------------*/
Tile* MapDocument::currentTile() const
{
	return mCurrentTile;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocument::setCurrentTileset(Tileset* tileset)
{
	if (mCurrentTileset == tileset) return;

	mCurrentTileset = tileset;
	emit currentTilesetChanged(mCurrentTileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* MapDocument::currentTileset() const
{
	return mCurrentTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocument::setCurrentLayer(Layer* layer)
{
	if (mCurrentLayer == layer) return;

	mCurrentLayer = layer;
	emit currentLayerChanged(mCurrentLayer);
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* MapDocument::currentLayer() const
{
	return mCurrentLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
LayerTreeModel* MapDocument::layerModel() const
{
	return mLayerModel;
}
/*-----------------------------------------------------------------------------------------------------------*/
TilesetListModel* MapDocument::tilesetsModel() const
{
	return mTilesetsModel;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocument::onLayerAdded(Layer* layer)
{
	emit layerAdded(layer);
	setCurrentLayer(layer);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocument::onLayerRemoved(Layer* layer)
{
	const auto objectAsLayer = dynamic_cast<Layer*>(currentObject());
	const auto cLayer = currentLayer();

	if (objectAsLayer && objectAsLayer == layer)
		setCurrentObject(nullptr);

	if (cLayer && cLayer == layer)
		setCurrentTileset(nullptr);

	emit layerRemoved(layer);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocument::onTilesetAdded(Tileset* tileset)
{
	emit tilesetAdded(tileset);
	setCurrentTileset(tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapDocument::onTilesetRemoved(Tileset* tileset)
{
	const auto objectAsTileset = dynamic_cast<Tileset*>(currentObject());
	const auto objectAsTile = dynamic_cast<Tile*>(currentObject());

	const auto cTile = currentTile();
	const auto cTileset = currentTileset();

	if ((objectAsTileset && objectAsTileset == tileset) || (objectAsTile && objectAsTile->tileset() == tileset))
		setCurrentObject(nullptr);

	if (cTile && cTile->tileset() == tileset)
		setCurrentTile(nullptr);

	if (cTileset && cTileset == tileset)
		setCurrentTileset(nullptr);

	emit tilesetRemoved(tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
QString MapDocument::createDisplayName(const QString& fileName)
{
	auto displayName = QFileInfo(fileName).fileName();

	if (displayName.isEmpty()) return tr("untitled.tm");
	else return displayName;
}
/*-----------------------------------------------------------------------------------------------------------*/

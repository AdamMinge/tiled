﻿/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "document.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Map;
class Tile;
class Layer;
class Tileset;
class GroupLayer;
class LayerTreeModel;
class TilesetListModel;
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocument final : public Document
{
	Q_OBJECT

public:
	enum ChangedPropertyId
	{
		OrientationChangedId = 1 << 0,
		RenderOrderChangedId = 1 << 1,
		TileSizeChangedId = 1 << 2,
		AnimationChangedId = 1 << 3,
		NameChangedId = 1 << 4,
		VisibleChangedId = 1 << 5,
		LockedChangedId = 1 << 6,
		OpacityChangedId = 1 << 7
	};

public:
	explicit MapDocument(Map* map, const QString &fileName = QString());
	~MapDocument() override;

	Map* map() const;

	void setCurrentTile(Tile* tile);
	Tile* currentTile() const;

	void setCurrentTileset(Tileset* tileset);
	Tileset* currentTileset() const;

	void setCurrentLayer(Layer* layer);
	Layer *currentLayer() const;

	LayerTreeModel* layerModel() const;
	TilesetListModel* tilesetsModel() const;

signals:
	void layerAdded(Layer* layer);
	void layerRemoved(Layer* layer);

	void tilesetAdded(Tileset* tileset);
	void tilesetRemoved(Tileset* tileset);

	void currentTileChanged(Tile* tile);
	void currentTilesetChanged(Tileset* tileset);
	void currentLayerChanged(Layer* layer);

	void mapChanged(Map* map, int changedPropertyId);
	void tileChanged(Tile* tile, int changedPropertyId);
	void tilesetChanged(Tileset* tileset, int changedPropertyId);
	void layerChanged(Layer* layer, int changedPropertyId);

private slots:
	void onLayerAdded(Layer* layer);
	void onLayerRemoved(Layer* layer);

	void onTilesetAdded(Tileset* tileset);
	void onTilesetRemoved(Tileset* tileset);

private:
	static QString createDisplayName(const QString& fileName);

private:
	Map* mMap;

	Tile* mCurrentTile;
	Tileset* mCurrentTileset;
	Layer* mCurrentLayer;

	LayerTreeModel* mLayerModel;
	TilesetListModel* mTilesetsModel;
};
/*-----------------------------------------------------------------------------------------------------------*/
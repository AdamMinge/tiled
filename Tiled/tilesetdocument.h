/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "document.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Tileset;
class Tile;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetDocument final : public Document
{
	Q_OBJECT

public:
	explicit TilesetDocument(Tileset* tileset, const QString &fileName = QString());
	~TilesetDocument() override = default;

	Tileset* tileset() const;

	void setCurrentTile(Tile* tile);
	Tile* currentTile() const;

signals:
	void currentTileChanged(Tile* tile);

	void tileChanged(Tile* tile, int changedPropertyId);
	void tilesetChanged(Tileset* tileset, int changedPropertyId);

private:
	static QString createDisplayName(const QString& fileName, Tileset* tileset);

private:
	Tileset* mTileset;

	Tile* mCurrentTile;
};
/*-----------------------------------------------------------------------------------------------------------*/
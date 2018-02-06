/*-----------------------------------------------------------------------------------------------------------*/
#include <QFileInfo>
#include "tileset.h"
#include "tilesetdocument.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilesetDocument::TilesetDocument(Tileset* tileset, const QString& fileName) :
	Document(fileName, createDisplayName(fileName, tileset), DocumentType::TilesetDocumentType),
	mTileset(tileset),
	mCurrentTile(nullptr)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* TilesetDocument::tileset() const
{
	return mTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetDocument::setCurrentTile(Tile* tile)
{
	if (mCurrentTile == tile) return;

	mCurrentTile = tile;
	emit currentTileChanged(mCurrentTile);
}
/*-----------------------------------------------------------------------------------------------------------*/
Tile* TilesetDocument::currentTile() const
{
	return mCurrentTile;
}
/*-----------------------------------------------------------------------------------------------------------*/
QString TilesetDocument::createDisplayName(const QString& fileName, Tileset* tileset)
{
	Q_ASSERT(tileset);

	auto displayName = QFileInfo(fileName).fileName();

	if (displayName.isEmpty()) return tileset->name();
	else return displayName;
}
/*-----------------------------------------------------------------------------------------------------------*/
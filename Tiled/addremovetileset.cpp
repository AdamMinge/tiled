/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "addremovetileset.h"
#include "tilesetlistmodel.h"
#include "mapdocument.h"
#include "tileset.h"
#include "map.h"
/*-----------------------------------------------------------------------------------------------------------*/
AddRemoveTileset::AddRemoveTileset(MapDocument* mapDocument, int index,
	Tileset* tileset, Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mTileset(tileset),
	mIndex(index)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
AddRemoveTileset::~AddRemoveTileset()
{
	if (mTileset) delete mTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddRemoveTileset::addTileset()
{
	mMapDocument->tilesetsModel()->addTileset(mIndex, mTileset);
	mTileset = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddRemoveTileset::removeTileset()
{
	mTileset = mMapDocument->tilesetsModel()->takeTileset(mIndex);
}
/*-----------------------------------------------------------------------------------------------------------*/
AddTileset::AddTileset(MapDocument* mapDocument, Tileset* tileset, Command* parent) :
	AddRemoveTileset(mapDocument, mapDocument->map()->tilesetCount(), tileset, parent)
{
	setText(QCoreApplication::translate("Undo Commands", "Add Tileset"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddTileset::undo()
{
	removeTileset();
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddTileset::redo()
{
	addTileset();
}
/*-----------------------------------------------------------------------------------------------------------*/
RemoveTileset::RemoveTileset(MapDocument* mapDocument, int index, Command* parent) :
	AddRemoveTileset(mapDocument, index, mapDocument->map()->tileset(index), parent)
{
	setText(QCoreApplication::translate("Undo Commands", "Remove Tileset"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void RemoveTileset::undo()
{
	addTileset();
}
/*-----------------------------------------------------------------------------------------------------------*/
void RemoveTileset::redo()
{
	removeTileset();
}
/*-----------------------------------------------------------------------------------------------------------*/
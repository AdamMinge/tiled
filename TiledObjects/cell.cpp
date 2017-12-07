/*-----------------------------------------------------------------------------------------------------------*/
#include "cell.h"
#include "tileset.h"
#include "tile.h"
/*-----------------------------------------------------------------------------------------------------------*/
Cell::Cell(Tile* tile) :
	mTileset((tile) ? tile->tileset() : nullptr),
	mId((tile) ? tile->id() : -1)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
Cell::Cell(Cell&& other) noexcept
{
	mTileset = other.mTileset;
	mId = other.mId;

	other.mTileset = nullptr;
	other.mId = -1;
}
/*-----------------------------------------------------------------------------------------------------------*/
Cell& Cell::operator=(Cell&& other) noexcept
{
	mTileset = other.mTileset;
	mId = other.mId;

	other.mTileset = nullptr;
	other.mId = -1;

	return *this;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Cell::operator==(const Cell& other) const
{
	if (mTileset != other.mTileset || mId != other.mId) return false;
	else return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Cell::operator!=(const Cell& other) const
{
	return !(*this == other);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Cell::isEmpty() const
{
	return !mTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* Cell::tileset() const
{
	return mTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
Tile* Cell::tile() const
{
	if(mTileset) return mTileset->tile(mId);
	else return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Cell::setTile(Tile* tile)
{
	if(tile)
	{
		mTileset = tile->tileset();
		mId = tile->id();
	}
	else
	{
		mTileset = nullptr;
		mId = -1;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
int Cell::tileId() const
{
	return mId;
}
/*-----------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------*/
#include "cell.h"
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
Cell<TILESET,TILE>::Cell(TILE* tile) :
	mTileset((tile) ? tile->tileset() : nullptr),
	mId((tile) ? tile->id() : -1)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
Cell<TILESET, TILE>::Cell(Cell<TILESET, TILE>&& other) noexcept
{
	mTileset = other.mTileset;
	mId = other.mId;

	other.mTileset = nullptr;
	other.mId = -1;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
Cell<TILESET, TILE>& Cell<TILESET, TILE>::operator=(Cell<TILESET, TILE>&& other) noexcept
{
	mTileset = other.mTileset;
	mId = other.mId;

	other.mTileset = nullptr;
	other.mId = -1;

	return *this;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
bool Cell<TILESET, TILE>::operator==(const Cell<TILESET, TILE>& other) const
{
	if (mTileset != other.mTileset || mId != other.mId) return false;
	else return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
bool Cell<TILESET, TILE>::operator!=(const Cell<TILESET, TILE>& other) const
{
	return !(*this == other);
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
bool Cell<TILESET, TILE>::isEmpty() const
{
	return !mTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
TILESET* Cell<TILESET, TILE>::tileset() const
{
	return mTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
TILE* Cell<TILESET, TILE>::tile() const
{
	if(mTileset) return mTileset->tile(mId);
	else return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
void Cell<TILESET, TILE>::setTile(TILE* tile)
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
template<typename TILESET, typename TILE>
int Cell<TILESET, TILE>::tileId() const
{
	return mId;
}
/*-----------------------------------------------------------------------------------------------------------*/
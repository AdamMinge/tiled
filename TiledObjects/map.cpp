/*-----------------------------------------------------------------------------------------------------------*/
#include "map.h"
#include "tileset.h"
#include "grouplayer.h"
/*-----------------------------------------------------------------------------------------------------------*/
Map::Map(Orientation orientation, RenderOrder renderOrder, const QSize& size, const QSize& tileSize) :
	Object(ObjectType::MapType),
	mOrientation(orientation),
	mRenderOrder(renderOrder),
	mSize(size),
	mTileSize(tileSize),
	mRootLayer(new GroupLayer(QLatin1String("root")))
{

}
/*-----------------------------------------------------------------------------------------------------------*/
Map::~Map()
{
	qDeleteAll(mTilesets);
}
/*-----------------------------------------------------------------------------------------------------------*/
Map::Orientation Map::orientation() const
{
	return mOrientation;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Map::setOrientation(Orientation orientation)
{
	mOrientation = orientation;
}
/*-----------------------------------------------------------------------------------------------------------*/
Map::RenderOrder Map::renderOrder() const
{
	return mRenderOrder;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Map::setRenderOrder(RenderOrder renderOrder)
{
	mRenderOrder = renderOrder;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QSize& Map::size() const
{
	return mSize;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Map::setSize(const QSize& size)
{
	mSize = size;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QSize& Map::tileSize() const
{
	return mTileSize;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Map::setTileSize(const QSize& tileSize)
{
	mTileSize = tileSize;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QVector<Tileset*>& Map::tilesets() const
{
	return mTilesets;
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* Map::tileset(int index) const
{
	return mTilesets.at(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
int Map::tilesetCount() const
{
	return mTilesets.count();
}
/*-----------------------------------------------------------------------------------------------------------*/
void Map::addTileset(Tileset* tileset)
{
	Q_ASSERT(!mTilesets.contains(tileset));
	mTilesets.append(tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
void Map::addTileset(Tileset* tileset, int index)
{
	Q_ASSERT(!mTilesets.contains(tileset));
	mTilesets.insert(index, tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
void Map::removeTileset(int index)
{
	auto tileset = mTilesets.takeAt(index);
	delete tileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* Map::takeTileset(int index)
{
	return mTilesets.takeAt(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
GroupLayer* Map::rootLayer() const
{
	return mRootLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
Map* Map::clone() const
{
	auto cloneMap = new Map(mOrientation, mRenderOrder, mSize, mTileSize);
	cloneMap->setProperties(properties());

	for(decltype(auto) iter : mTilesets)
		cloneMap->mTilesets.push_back(iter->clone());

	return cloneMap;
}
/*-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QSize>
#include <QVector>
#include "object.h"
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Tileset;
class GroupLayer;
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT Map final : public Object
{
public:
	enum class Orientation;
	enum class RenderOrder;

public:
	explicit Map(Orientation orientation, RenderOrder renderOrder,
		const QSize& size, const QSize& tileSize);
	~Map() override;

	Map(Map&&) = delete;
	Map(const Map&) = delete;

	Map& operator=(Map&&) = delete;
	Map& operator=(const Map&) = delete;

	Orientation orientation() const;
	void setOrientation(Orientation orientation);

	RenderOrder renderOrder() const;
	void setRenderOrder(RenderOrder renderOrder);

	const QSize& size() const;
	void setSize(const QSize& size);

	const QSize& tileSize() const;
	void setTileSize(const QSize& tileSize);

	const QVector<Tileset*>& tilesets() const;
	Tileset* tileset(int index) const;
	int tilesetCount() const;

	void addTileset(Tileset* tileset);
	void addTileset(Tileset* tileset, int index);

	void removeTileset(int index);
	Tileset* takeTileset(int index);

	GroupLayer* rootLayer() const;

	Map* clone() const;

private:
	Orientation mOrientation;
	RenderOrder mRenderOrder;
	QSize mSize;
	QSize mTileSize;

	QVector<Tileset*> mTilesets;
	GroupLayer* mRootLayer;
};
/*-----------------------------------------------------------------------------------------------------------*/
enum class Map::Orientation
{
	Orthogonal,
	Isometric,
	Hexagonal
};
/*-----------------------------------------------------------------------------------------------------------*/
enum class Map::RenderOrder
{
	RightDown,
	RightUp,
	LeftDown,
	LeftUp
};
/*-----------------------------------------------------------------------------------------------------------*/

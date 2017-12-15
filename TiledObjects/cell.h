/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Tileset;
class Tile;
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT Cell
{
public:
	explicit Cell(Tile* tile = nullptr);
	~Cell() = default;

	Cell(const Cell&) = default;
	Cell(Cell&& other) noexcept;

	Cell& operator=(const Cell&) = default;
	Cell& operator=(Cell&& other) noexcept;

	bool operator==(const Cell& other) const;
	bool operator!=(const Cell& other) const;

	bool isEmpty() const;

	Tileset* tileset() const;

	Tile* tile() const;
	void setTile(Tile* tile);

	int tileId() const;

private:
	Tileset* mTileset;
	int mId;
};
/*-----------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TILESET, typename TILE>
class TILEDOBJECTS_EXPORT Cell final
{
public:
	explicit Cell(TILE* tile = nullptr);
	~Cell() = default;

	Cell(const Cell&) = default;
	Cell(Cell&& other) noexcept;

	Cell& operator=(const Cell&) = default;
	Cell& operator=(Cell&& other) noexcept;

	bool operator==(const Cell& other) const;
	bool operator!=(const Cell& other) const;

	bool isEmpty() const;

	TILESET* tileset() const;

	TILE* tile() const;
	void setTile(TILE* tile);

	int tileId() const;

private:
	TILESET* mTileset;
	int mId;
};
/*-----------------------------------------------------------------------------------------------------------*/
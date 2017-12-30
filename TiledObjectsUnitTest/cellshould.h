/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <gtest/gtest.h>
#include "tilemock.h"
#include "tilesetmock.h"
/*-----------------------------------------------------------------------------------------------------------*/
class CellShould : public testing::Test
{
public:
	CellShould();

protected:
	void SetUp() override;
	void TearDown() override;

protected:
	TilesetMock* mTilesetMock1;
	TilesetMock* mTilesetMock2;

	TileMock* mTileMock1Tileset1;
	TileMock* mTileMock2Tileset1;
	TileMock* mTileMock3Tileset2;
	TileMock* mTileMock4Tileset2;
};
/*-----------------------------------------------------------------------------------------------------------*/
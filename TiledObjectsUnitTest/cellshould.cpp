/*-----------------------------------------------------------------------------------------------------------*/
#include "cellshould.h"
#include "cell.h"
/*-----------------------------------------------------------------------------------------------------------*/
CellShould::CellShould() :
	mTilesetMock1(nullptr),
	mTilesetMock2(nullptr),
	mTileMock1Tileset1(nullptr),
	mTileMock2Tileset1(nullptr),
	mTileMock3Tileset2(nullptr),
	mTileMock4Tileset2(nullptr)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
void CellShould::SetUp()
{
	mTilesetMock1 = new TilesetMock();
	mTilesetMock2 = new TilesetMock();

	mTileMock1Tileset1 = new TileMock();
	mTileMock2Tileset1 = new TileMock();
	mTileMock3Tileset2 = new TileMock();
	mTileMock4Tileset2 = new TileMock();
}
/*-----------------------------------------------------------------------------------------------------------*/
void CellShould::TearDown()
{
	delete mTilesetMock1;
	delete mTilesetMock2;

	delete mTileMock1Tileset1;
	delete mTileMock2Tileset1;
	delete mTileMock3Tileset2;
	delete mTileMock4Tileset2;
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnTrueWhenComperedWithSelf)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	const auto cell1 = Cell<TilesetMock,TileMock>(mTileMock1Tileset1);
	const auto cell2 = Cell<TilesetMock, TileMock>();

	EXPECT_EQ(cell1, cell1);
	EXPECT_EQ(cell2, cell2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnTrueWhenComperedWithCellWithTheSameTile)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(2)
		.WillRepeatedly(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(2)
		.WillRepeatedly(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);
	const auto cell2 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	EXPECT_EQ(cell1, cell2);
	EXPECT_EQ(cell2, cell1);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnFalseWhenComperedWithCellWithOtherTile)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
		EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	EXPECT_CALL(*mTileMock2Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock2Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(2));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);
	const auto cell2 = Cell<TilesetMock, TileMock>(mTileMock2Tileset1);

	EXPECT_NE(cell1, cell2);
	EXPECT_NE(cell2, cell1);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeSameAsOrginalWhenWasCopied)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto cell1CopyOperator = Cell<TilesetMock, TileMock>();

	auto cell1CopyConstructor = cell1;
	cell1CopyOperator = cell1;

	EXPECT_EQ(cell1, cell1CopyConstructor);
	EXPECT_EQ(cell1, cell1CopyOperator);
	EXPECT_EQ(cell1CopyConstructor, cell1CopyOperator);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeEmptyWhenUsedDefaultConstructor)
{
	const auto cell1 = Cell<TilesetMock, TileMock>();

	EXPECT_TRUE(cell1.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeNoEmptyWhenUsedConstructorWithParametr)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	EXPECT_FALSE(cell1.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeNoEmptyWhenCopiedNoEmptyCell)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto cell1CopyOperator = Cell<TilesetMock, TileMock>();

	auto cell1CopyConstructor = cell1;
	cell1CopyOperator = cell1;

	EXPECT_FALSE(cell1CopyConstructor.isEmpty());
	EXPECT_FALSE(cell1CopyOperator.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeEmptyWhenCopiedEmptyCell)
{
	const auto cell1 = Cell<TilesetMock, TileMock>();

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto cell1CopyOperator = Cell<TilesetMock, TileMock>();

	auto cell1CopyConstructor = cell1;
	cell1CopyOperator = cell1;

	EXPECT_TRUE(cell1CopyConstructor.isEmpty());
	EXPECT_TRUE(cell1CopyOperator.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnNullPtrTilesetForEmptyCell)
{
	const auto cell1 = Cell<TilesetMock, TileMock>();

	auto tilesetCell1 = cell1.tileset();

	EXPECT_EQ(tilesetCell1, nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnNoNullPtrTilesetForNoEmptyCell)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	auto tilesetCell1 = cell1.tileset();

	EXPECT_NE(tilesetCell1, nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnSameTilesetForEqualCell)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(2)
		.WillRepeatedly(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(2)
		.WillRepeatedly(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>();
	const auto cell2 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);
	const auto cell3 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	auto tilesetCell1 = cell1.tileset();
	auto tilesetCell2 = cell2.tileset();
	auto tilesetCell3 = cell3.tileset();

	EXPECT_EQ(tilesetCell1, tilesetCell1);
	EXPECT_EQ(tilesetCell2, tilesetCell2);
	EXPECT_EQ(tilesetCell3, tilesetCell3);

	EXPECT_EQ(tilesetCell2, tilesetCell3);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnSameTilesetForCellWithTileWithSameTileset)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	EXPECT_CALL(*mTileMock2Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock2Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(2));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);
	const auto cell2 = Cell<TilesetMock, TileMock>(mTileMock2Tileset1);

	auto tilesetCell1 = cell1.tileset();
	auto tilesetCell2 = cell2.tileset();

	EXPECT_EQ(tilesetCell1, tilesetCell2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnOtherTilesetForCellWithTileWithOtherTileset)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	EXPECT_CALL(*mTileMock3Tileset2, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock2));
	EXPECT_CALL(*mTileMock3Tileset2, id())
		.Times(1)
		.WillOnce(testing::Return(3));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);
	const auto cell2 = Cell<TilesetMock, TileMock>(mTileMock3Tileset2);
	const auto cell3 = Cell<TilesetMock, TileMock>();

	auto tilesetCell1 = cell1.tileset();
	auto tilesetCell2 = cell2.tileset();
	auto tilesetCell3 = cell3.tileset();

	EXPECT_NE(tilesetCell1, tilesetCell2);
	EXPECT_NE(tilesetCell2, tilesetCell3);
	EXPECT_NE(tilesetCell3, tilesetCell1);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnNullPtrTileForEmptyCell)
{
	const auto cell1 = Cell<TilesetMock, TileMock>();

	auto tileCell1 = cell1.tile();

	EXPECT_EQ(tileCell1, nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnNoNullptrTileForNoEmptyCell)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));
	EXPECT_CALL(*mTilesetMock1, tile(testing::Eq(1)))
		.Times(1)
		.WillOnce(testing::Return(mTileMock1Tileset1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	auto tileCell1 = cell1.tile();

	EXPECT_NE(tileCell1, nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnSameTileForEqualCell)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(2)
		.WillRepeatedly(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(2)
		.WillRepeatedly(testing::Return(1));
	EXPECT_CALL(*mTilesetMock1, tile(testing::Eq(1)))
		.Times(2)
		.WillRepeatedly(testing::Return(mTileMock1Tileset1));

	const auto cell1 = Cell<TilesetMock, TileMock>();
	const auto cell2 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);
	const auto cell3 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	auto tileCell1 = cell1.tile();
	auto tileCell2 = cell2.tile();
	auto tileCell3 = cell3.tile();

	EXPECT_EQ(tileCell1, tileCell1);
	EXPECT_EQ(tileCell2, tileCell2);
	EXPECT_EQ(tileCell3, tileCell3);

	EXPECT_EQ(tileCell2, tileCell3);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnOtherTileForNoEqualCell)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	EXPECT_CALL(*mTileMock2Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock2Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(2));

	EXPECT_CALL(*mTilesetMock1, tile(testing::AnyOf(testing::Eq(1), testing::Eq(2))))
		.Times(2)
		.WillOnce(testing::Return(mTileMock1Tileset1))
		.WillOnce(testing::Return(mTileMock2Tileset1));

	const auto cell1 = Cell<TilesetMock, TileMock>();
	const auto cell2 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);
	const auto cell3 = Cell<TilesetMock, TileMock>(mTileMock2Tileset1);

	auto tileCell1 = cell1.tile();
	auto tileCell2 = cell2.tile();
	auto tileCell3 = cell3.tile();

	EXPECT_NE(tileCell2, tileCell3);
	EXPECT_NE(tileCell1, tileCell3);
	EXPECT_NE(tileCell1, tileCell2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeEmptyWhenSetNullptrTile)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	auto cell1 = Cell<TilesetMock, TileMock>();
	auto cell2 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	cell1.setTile(nullptr);
	cell2.setTile(nullptr);

	EXPECT_TRUE(cell1.isEmpty());
	EXPECT_TRUE(cell2.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeNoEmptyWhenSetNoNullptrTile)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	EXPECT_CALL(*mTileMock2Tileset1, tileset())
		.Times(2)
		.WillRepeatedly(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock2Tileset1, id())
		.Times(2)
		.WillRepeatedly(testing::Return(2));

	auto cell1 = Cell<TilesetMock, TileMock>();
	auto cell2 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	cell1.setTile(mTileMock2Tileset1);
	cell2.setTile(mTileMock2Tileset1);

	EXPECT_FALSE(cell1.isEmpty());
	EXPECT_FALSE(cell2.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeStillEmptyWhenHisCopySetNewNoNullptrTile)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(2)
		.WillRepeatedly(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(2)
		.WillRepeatedly(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>();

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto cell1CopyOperator = Cell<TilesetMock, TileMock>();

	auto cell1CopyConstructor = cell1;
	cell1CopyOperator = cell1;

	cell1CopyOperator.setTile(mTileMock1Tileset1);
	cell1CopyConstructor.setTile(mTileMock1Tileset1);

	EXPECT_TRUE(cell1.isEmpty());
	EXPECT_FALSE(cell1CopyOperator.isEmpty());
	EXPECT_FALSE(cell1CopyConstructor.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeStillNoEmptyWhenHisCopySetNewNullptrTile)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto cell1CopyOperator = Cell<TilesetMock, TileMock>();

	auto cell1CopyConstructor = cell1;
	cell1CopyOperator = cell1;

	cell1CopyOperator.setTile(nullptr);
	cell1CopyConstructor.setTile(nullptr);

	EXPECT_FALSE(cell1.isEmpty());
	EXPECT_TRUE(cell1CopyOperator.isEmpty());
	EXPECT_TRUE(cell1CopyConstructor.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnMinusOneIdWhenIsEmpty)
{
	const auto cell1 = Cell<TilesetMock, TileMock>();

	EXPECT_EQ(cell1.tileId(), -1);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, NoReturnMinusOneIdWhenIsNoEmpty)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	EXPECT_NE(cell1.tileId(), -1);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnSameIdAsHisCopy)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto cell1CopyOperator = Cell<TilesetMock, TileMock>();

	auto cell1CopyConstructor = cell1;
	cell1CopyOperator = cell1;

	EXPECT_EQ(cell1.tileId(), cell1CopyOperator.tileId());
	EXPECT_EQ(cell1.tileId(), cell1CopyConstructor.tileId());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnSameIdAsOtherCellWhenCellsAreEqual)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(2)
		.WillRepeatedly(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(2)
		.WillRepeatedly(testing::Return(1));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);
	const auto cell2 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);

	EXPECT_EQ(cell1.tileId(), cell2.tileId());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnOtherIdForTwoCellFromSameTilesetWhenCellsAreNotEqual)
{
	EXPECT_CALL(*mTileMock1Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock1Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(1));

	EXPECT_CALL(*mTileMock2Tileset1, tileset())
		.Times(1)
		.WillOnce(testing::Return(mTilesetMock1));
	EXPECT_CALL(*mTileMock2Tileset1, id())
		.Times(1)
		.WillOnce(testing::Return(2));

	const auto cell1 = Cell<TilesetMock, TileMock>(mTileMock1Tileset1);
	const auto cell2 = Cell<TilesetMock, TileMock>(mTileMock2Tileset1);

	EXPECT_NE(cell1.tileId(), cell2.tileId());
}
/*-----------------------------------------------------------------------------------------------------------*/
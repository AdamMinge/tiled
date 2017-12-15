/*-----------------------------------------------------------------------------------------------------------*/
#include "cellshould.h"
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
	mTilesetMock1 = new TilesetMock(QString(), ImageReference(), QSize(), 0, 0);
	mTilesetMock2 = new TilesetMock(QString(), ImageReference(), QSize(), 0, 0);

	mTileMock1Tileset1 = new TileMock(mTilesetMock1, QPixmap(), 1);
	mTileMock2Tileset1 = new TileMock(mTilesetMock1, QPixmap(), 2);
	mTileMock3Tileset2 = new TileMock(mTilesetMock2, QPixmap(), 1);
	mTileMock4Tileset2 = new TileMock(mTilesetMock2, QPixmap(), 2);
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
	const auto cell1 = Cell(mTileMock1Tileset1);
	const auto cell2 = Cell();

	EXPECT_EQ(cell1, cell1);
	EXPECT_EQ(cell2, cell2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnTrueWhenComperedWithCellWithTheSameTile)
{
	const auto cell1 = Cell(mTileMock1Tileset1);
	const auto cell2 = Cell(mTileMock1Tileset1);

	EXPECT_EQ(cell1, cell2);
	EXPECT_EQ(cell2, cell1);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnFalseWhenComperedWithCellWithOtherTile)
{
	const auto cell1 = Cell(mTileMock1Tileset1);
	const auto cell2 = Cell(mTileMock2Tileset1);

	EXPECT_NE(cell1, cell2);
	EXPECT_NE(cell2, cell1);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeSameAsOrginalWhenWasCopied)
{
	const auto cell1 = Cell(mTileMock1Tileset1);

	auto cell1CopyOperator = Cell();

	auto cell1CopyConstructor = cell1;
	cell1CopyOperator = cell1;

	EXPECT_EQ(cell1, cell1CopyConstructor);
	EXPECT_EQ(cell1, cell1CopyOperator);
	EXPECT_EQ(cell1CopyConstructor, cell1CopyOperator);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeEmptyWhenUsedDefaultConstructor)
{
	const auto cell1 = Cell();

	EXPECT_TRUE(cell1.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeNoEmptyWhenUsedConstructorWithParametr)
{
	const auto cell1 = Cell(mTileMock1Tileset1);

	EXPECT_FALSE(cell1.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeNoEmptyWhenCopiedNoEmptyCell)
{
	const auto cell1 = Cell(mTileMock1Tileset1);

	auto cell1CopyOperator = Cell();

	auto cell1CopyConstructor = cell1;
	cell1CopyOperator = cell1;

	EXPECT_FALSE(cell1CopyConstructor.isEmpty());
	EXPECT_FALSE(cell1CopyOperator.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, BeEmptyWhenCopiedEmptyCell)
{
	const auto cell1 = Cell();

	auto cell1CopyOperator = Cell();

	auto cell1CopyConstructor = cell1;
	cell1CopyOperator = cell1;

	EXPECT_TRUE(cell1CopyConstructor.isEmpty());
	EXPECT_TRUE(cell1CopyOperator.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnNullPtrTilesetForEmptyCell)
{
	const auto cell1 = Cell();

	EXPECT_EQ(cell1.tileset(), nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnNoNullPtrTilesetForNoEmptyCell)
{
	const auto cell1 = Cell(mTileMock1Tileset1);

	EXPECT_NE(cell1.tileset(), nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnSameTilesetForEqualCell)
{
	const auto cell1 = Cell();
	const auto cell2 = Cell(mTileMock1Tileset1);
	const auto cell3 = Cell(mTileMock1Tileset1);

	EXPECT_EQ(cell1.tileset(), cell1.tileset());
	EXPECT_EQ(cell2.tileset(), cell2.tileset());
	EXPECT_EQ(cell3.tileset(), cell3.tileset());

	EXPECT_EQ(cell2.tileset(), cell3.tileset());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnSameTilesetForCellWithTileWithSameTileset)
{
	const auto cell1 = Cell(mTileMock1Tileset1);
	const auto cell2 = Cell(mTileMock2Tileset1);

	EXPECT_EQ(cell1.tileset(), cell2.tileset());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnOtherTilesetForCellWithTileWithOtherTileset)
{
	const auto cell1 = Cell(mTileMock1Tileset1);
	const auto cell2 = Cell(mTileMock3Tileset2);
	const auto cell3 = Cell();

	EXPECT_NE(cell1.tileset(), cell2.tileset());
	EXPECT_NE(cell2.tileset(), cell3.tileset());
	EXPECT_NE(cell3.tileset(), cell1.tileset());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnNullPtrTileForEmptyCell)
{
	const auto cell1 = Cell();

	EXPECT_EQ(cell1.tile(), nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnNoNullptrTileForNoEmptyCell)
{
	const auto cell1 = Cell(mTileMock1Tileset1);

	EXPECT_NE(cell1.tile(), nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnSameTileForEqualCell)
{
	const auto cell1 = Cell();
	const auto cell2 = Cell(mTileMock1Tileset1);
	const auto cell3 = Cell(mTileMock1Tileset1);

	EXPECT_EQ(cell1.tile(), cell1.tile());
	EXPECT_EQ(cell2.tile(), cell2.tile());
	EXPECT_EQ(cell3.tile(), cell3.tile());

	EXPECT_EQ(cell2.tile(), cell3.tile());
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(CellShould, ReturnOtherTileForNoEqualCell)
{
	const auto cell1 = Cell();
	const auto cell2 = Cell(mTileMock1Tileset1);
	const auto cell3 = Cell(mTileMock2Tileset1);

	EXPECT_NE(cell1.tile(), cell2.tile());
	EXPECT_NE(cell2.tile(), cell3.tile());
	EXPECT_NE(cell1.tile(), cell3.tile());
}
/*-----------------------------------------------------------------------------------------------------------*/
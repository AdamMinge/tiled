/*-----------------------------------------------------------------------------------------------------------*/
#include "chunkshould.h"
#include "chunk.h"
#include "tiledutils.h"
/*-----------------------------------------------------------------------------------------------------------*/
ChunkShould::ChunkShould() :
	mCellMock1(nullptr),
	mCellMock2(nullptr),
	mCellMock3(nullptr),
	mCellMock4(nullptr)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
void ChunkShould::SetUp()
{
	mCellMock1 = new CellMock();
	mCellMock2 = new CellMock();
	mCellMock3 = new CellMock();
	mCellMock4 = new CellMock();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChunkShould::TearDown()
{
	delete mCellMock1;
	delete mCellMock2;
	delete mCellMock3;
	delete mCellMock4;
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ReturnTrueWhenComperedEmptyChunks)
{
	auto chunk1 = Chunk<CellMock>();
	auto chunk2 = Chunk<CellMock>();

	EXPECT_EQ(chunk1, chunk1);
	EXPECT_EQ(chunk2, chunk2);
	EXPECT_EQ(chunk1, chunk2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ReturnTrueWhenComparedChunksWithSameCellsInSamePlaces)
{
	auto chunk1 = Chunk<CellMock>();
	auto chunk2 = Chunk<CellMock>();

	chunk1.setCell(QPoint(1, 1), *mCellMock1);
	chunk1.setCell(QPoint(2, 2), *mCellMock2);
	chunk1.setCell(QPoint(3, 3), *mCellMock3);
	chunk1.setCell(QPoint(4, 4), *mCellMock4);

	chunk2.setCell(QPoint(1, 1), *mCellMock1);
	chunk2.setCell(QPoint(2, 2), *mCellMock2);
	chunk2.setCell(QPoint(3, 3), *mCellMock3);
	chunk2.setCell(QPoint(4, 4), *mCellMock4);

	EXPECT_EQ(chunk1, chunk2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ReturnFalseWhenComparedChunksWithCellsInOtherPlaces)
{
	auto chunk1 = Chunk<CellMock>();
	auto chunk2 = Chunk<CellMock>();

	chunk1.setCell(QPoint(1, 1), *mCellMock1);
	chunk1.setCell(QPoint(2, 2), *mCellMock2);
	chunk1.setCell(QPoint(3, 3), *mCellMock3);
	chunk1.setCell(QPoint(4, 4), *mCellMock4);

	chunk2.setCell(QPoint(5, 5), *mCellMock1);
	chunk2.setCell(QPoint(2, 2), *mCellMock2);
	chunk2.setCell(QPoint(3, 3), *mCellMock3);
	chunk2.setCell(QPoint(4, 4), *mCellMock4);

	EXPECT_NE(chunk1, chunk2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ReturnFalseWhenComparedChunksWithOtherCells)
{
	auto chunk1 = Chunk<CellMock>();
	auto chunk2 = Chunk<CellMock>();

	chunk1.setCell(QPoint(1, 1), *mCellMock1);
	chunk1.setCell(QPoint(2, 2), *mCellMock2);
	chunk1.setCell(QPoint(3, 3), *mCellMock3);
	chunk1.setCell(QPoint(4, 4), *mCellMock4);

	chunk2.setCell(QPoint(1, 1), *mCellMock4);
	chunk2.setCell(QPoint(2, 2), *mCellMock2);
	chunk2.setCell(QPoint(3, 3), *mCellMock3);
	chunk2.setCell(QPoint(4, 4), *mCellMock4);

	EXPECT_NE(chunk1, chunk2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ContainsExtremePoints)
{
	auto chunk1 = Chunk<CellMock>();

	EXPECT_TRUE(chunk1.contains(QPoint(0, 0)));
	EXPECT_TRUE(chunk1.contains(QPoint(chunkSize() - 1, chunkSize() - 1)));
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ContainsPointsBetweenExtremePoints)
{
	auto chunk1 = Chunk<CellMock>();

	EXPECT_TRUE(chunk1.contains(QPoint(1, 1)));
	EXPECT_TRUE(chunk1.contains(QPoint(chunkSize() / 2, chunkSize() / 2)));
	EXPECT_TRUE(chunk1.contains(QPoint(chunkSize() - 2, chunkSize() - 2)));
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, NotContainsPointsSmallerThanExtremeLeftPoint)
{
	auto chunk1 = Chunk<CellMock>();

	EXPECT_FALSE(chunk1.contains(QPoint(0, -1)));
	EXPECT_FALSE(chunk1.contains(QPoint(-1, 0)));
	EXPECT_FALSE(chunk1.contains(QPoint(-1, -1)));
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, NotContainsPointsBiggerThanExtremeRightPoint)
{
	auto chunk1 = Chunk<CellMock>();

	EXPECT_FALSE(chunk1.contains(QPoint(0, chunkSize())));
	EXPECT_FALSE(chunk1.contains(QPoint(chunkSize(), chunkSize())));
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, FindCellWhenContainsPoint)
{
	auto chunk1 = Chunk<CellMock>();

	EXPECT_TRUE(chunk1.contains(QPoint(0, 0)));
	EXPECT_NE(chunk1.findCell(QPoint(0, 0)), nullptr);

	EXPECT_TRUE(chunk1.contains(QPoint(chunkSize() - 1, chunkSize() - 1)));
	EXPECT_NE(chunk1.findCell(QPoint(chunkSize() - 1, chunkSize() - 1)), nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, NotFindCellWhenNotContainsPoint)
{
	auto chunk1 = Chunk<CellMock>();

	EXPECT_FALSE(chunk1.contains(QPoint(-1, -1)));
	EXPECT_EQ(chunk1.findCell(QPoint(-1, -1)), nullptr);

	EXPECT_FALSE(chunk1.contains(QPoint(chunkSize(), chunkSize())));
	EXPECT_EQ(chunk1.findCell(QPoint(chunkSize(), chunkSize())), nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, BeEmptyByDefault)
{
	auto chunk1 = Chunk<CellMock>();

	EXPECT_TRUE(chunk1.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
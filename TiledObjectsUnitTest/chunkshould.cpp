/*-----------------------------------------------------------------------------------------------------------*/
#include "chunkshould.h"
#include "tiledutils.h"
#include "chunk.h"
/*-----------------------------------------------------------------------------------------------------------*/
ChunkShould::ChunkShould() :
	mCell1(nullptr),
	mCell2(nullptr),
	mCell3(nullptr),
	mCell4(nullptr)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
void ChunkShould::SetUp()
{
	mCell1 = new Cell();
	mCell2 = new Cell();
	mCell3 = new Cell();
	mCell4 = new Cell();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChunkShould::TearDown()
{
	delete mCell1;
	delete mCell2;
	delete mCell3;
	delete mCell4;
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ReturnTrueWhenComperedEmptyChunks)
{
	auto chunk1 = Chunk();
	auto chunk2 = Chunk();

	EXPECT_EQ(chunk1, chunk1);
	EXPECT_EQ(chunk2, chunk2);
	EXPECT_EQ(chunk1, chunk2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ReturnTrueWhenComparedChunksWithSameCellsInSamePlaces)
{
	auto chunk1 = Chunk();
	auto chunk2 = Chunk();

	chunk1.setCell(QPoint(1, 1), *mCell1);
	chunk1.setCell(QPoint(2, 2), *mCell2);
	chunk1.setCell(QPoint(3, 3), *mCell3);
	chunk1.setCell(QPoint(4, 4), *mCell4);

	chunk2.setCell(QPoint(1, 1), *mCell1);
	chunk2.setCell(QPoint(2, 2), *mCell2);
	chunk2.setCell(QPoint(3, 3), *mCell3);
	chunk2.setCell(QPoint(4, 4), *mCell4);

	EXPECT_EQ(chunk1, chunk2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ReturnFalseWhenComparedChunksWithCellsInOtherPlaces)
{
	auto chunk1 = Chunk();
	auto chunk2 = Chunk();

	chunk1.setCell(QPoint(1, 1), *mCell1);
	chunk1.setCell(QPoint(2, 2), *mCell2);
	chunk1.setCell(QPoint(3, 3), *mCell3);
	chunk1.setCell(QPoint(4, 4), *mCell4);

	chunk2.setCell(QPoint(5, 5), *mCell1);
	chunk2.setCell(QPoint(2, 2), *mCell2);
	chunk2.setCell(QPoint(3, 3), *mCell3);
	chunk2.setCell(QPoint(4, 4), *mCell4);

	EXPECT_NE(chunk1, chunk2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ReturnFalseWhenComparedChunksWithOtherCells)
{
	auto chunk1 = Chunk();
	auto chunk2 = Chunk();

	chunk1.setCell(QPoint(1, 1), *mCell1);
	chunk1.setCell(QPoint(2, 2), *mCell2);
	chunk1.setCell(QPoint(3, 3), *mCell3);
	chunk1.setCell(QPoint(4, 4), *mCell4);

	chunk2.setCell(QPoint(1, 1), *mCell4);
	chunk2.setCell(QPoint(2, 2), *mCell2);
	chunk2.setCell(QPoint(3, 3), *mCell3);
	chunk2.setCell(QPoint(4, 4), *mCell4);

	EXPECT_NE(chunk1, chunk2);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ContainsExtremePoints)
{
	auto chunk1 = Chunk();

	EXPECT_TRUE(chunk1.contains(QPoint(0, 0)));
	EXPECT_TRUE(chunk1.contains(QPoint(chunkSize() - 1, chunkSize() - 1)));
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ContainsPointsBetweenExtremePoints)
{
	auto chunk1 = Chunk();

	EXPECT_TRUE(chunk1.contains(QPoint(1, 1)));
	EXPECT_TRUE(chunk1.contains(QPoint(chunkSize() / 2, chunkSize() / 2)));
	EXPECT_TRUE(chunk1.contains(QPoint(chunkSize() - 2, chunkSize() - 2)));
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, NotContainsPointsSmallerThanExtremeLeftPoint)
{
	auto chunk1 = Chunk();

	EXPECT_FALSE(chunk1.contains(QPoint(0, -1)));
	EXPECT_FALSE(chunk1.contains(QPoint(-1, 0)));
	EXPECT_FALSE(chunk1.contains(QPoint(-1, -1)));
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, NotContainsPointsBiggerThanExtremeRightPoint)
{
	auto chunk1 = Chunk();

	EXPECT_FALSE(chunk1.contains(QPoint(0, chunkSize())));
	EXPECT_FALSE(chunk1.contains(QPoint(chunkSize(), chunkSize())));
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, FindCellWhenContainsPoint)
{
	auto chunk1 = Chunk();

	EXPECT_TRUE(chunk1.contains(QPoint(0, 0)));
	EXPECT_NE(chunk1.findCell(QPoint(0, 0)), nullptr);

	EXPECT_TRUE(chunk1.contains(QPoint(chunkSize() - 1, chunkSize() - 1)));
	EXPECT_NE(chunk1.findCell(QPoint(chunkSize() - 1, chunkSize() - 1)), nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, NotFindCellWhenNotContainsPoint)
{
	auto chunk1 = Chunk();

	EXPECT_FALSE(chunk1.contains(QPoint(-1, -1)));
	EXPECT_EQ(chunk1.findCell(QPoint(-1, -1)), nullptr);

	EXPECT_FALSE(chunk1.contains(QPoint(chunkSize(), chunkSize())));
	EXPECT_EQ(chunk1.findCell(QPoint(chunkSize(), chunkSize())), nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, BeEmptyByDefault)
{
	auto chunk1 = Chunk();

	EXPECT_TRUE(chunk1.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
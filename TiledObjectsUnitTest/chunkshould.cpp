﻿/*-----------------------------------------------------------------------------------------------------------*/
#include "chunkshould.h"
#include "chunk.h"
/*-----------------------------------------------------------------------------------------------------------*/
ChunkShould::ChunkShould()
{

}
/*-----------------------------------------------------------------------------------------------------------*/
void ChunkShould::SetUp()
{

}
/*-----------------------------------------------------------------------------------------------------------*/
void ChunkShould::TearDown()
{

}
/*-----------------------------------------------------------------------------------------------------------*/
TEST_F(ChunkShould, ReturnTrueWhenComperedWithSelf)
{
	auto chunk1 = Chunk<CellMock>();
	auto chunk2 = Chunk<CellMock>();

	EXPECT_EQ(chunk1, chunk1);
	EXPECT_EQ(chunk2, chunk2);
}
/*-----------------------------------------------------------------------------------------------------------*/
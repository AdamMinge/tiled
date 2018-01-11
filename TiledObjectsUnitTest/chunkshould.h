/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <gtest/gtest.h>
#include "cellmock.h"
/*-----------------------------------------------------------------------------------------------------------*/
class ChunkShould : public testing::Test
{
public:
	ChunkShould();
	
protected:
	void SetUp() override;
	void TearDown() override;
	
protected:
	CellMock* mCellMock1;
	CellMock* mCellMock2;
	CellMock* mCellMock3;
	CellMock* mCellMock4;
};
/*-----------------------------------------------------------------------------------------------------------*/
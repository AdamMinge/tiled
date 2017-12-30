/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <gmock/gmock.h>
/*-----------------------------------------------------------------------------------------------------------*/
class CellMock
{
public:
	CellMock() = default;

	CellMock(const CellMock&) {}
	CellMock(CellMock&&) noexcept {}

	CellMock& operator=(const CellMock&) { return *this; }
	CellMock& operator=(CellMock&&) noexcept { return *this; }

	MOCK_CONST_METHOD1(equals, bool(const CellMock&));
	MOCK_CONST_METHOD1(notEquals, bool(const CellMock&));

	MOCK_CONST_METHOD0(isEmpty, bool());

	bool operator==(const CellMock& cell) const { return equals(cell); }
	bool operator!=(const CellMock& cell) const { return notEquals(cell); }

};
/*-----------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <gmock/gmock.h>
/*-----------------------------------------------------------------------------------------------------------*/
class CellMock
{
public:
	explicit CellMock() = default;

	CellMock(const CellMock&) { }
	CellMock(CellMock&&) noexcept { }

	CellMock& operator=(const CellMock&) { return *this; }
	CellMock& operator=(CellMock&&) noexcept { return *this; }

	bool operator==(const CellMock& cell) const { return isEq(cell); }
	bool operator!=(const CellMock& cell) const { return isNotEq(cell); }

	MOCK_CONST_METHOD0(isEmpty, bool());

	MOCK_CONST_METHOD1(isEq, bool(const CellMock&));
	MOCK_CONST_METHOD1(isNotEq, bool(const CellMock&));
};
/*-----------------------------------------------------------------------------------------------------------*/
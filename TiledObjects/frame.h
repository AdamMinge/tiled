/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT Frame final
{
public:
	explicit Frame(int tileId = 0, int duration = 0);
	~Frame() = default;

	Frame(Frame&&) = default;
	Frame(const Frame&) = default;

	Frame& operator=(Frame&&) = default;
	Frame& operator=(const Frame&) = default;

	bool operator==(const Frame& other) const;
	bool operator!=(const Frame& other) const;

	void setTileId(int tileId);
	int tileId() const;

	void setDuration(int duration);
	int duration() const;

private:
	int mTileId;
	int mDuration;
};
/*-----------------------------------------------------------------------------------------------------------*/

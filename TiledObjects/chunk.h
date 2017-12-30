/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QVector>
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
class TILEDOBJECTS_EXPORT Chunk final
{
public:
	explicit Chunk();
	~Chunk() = default;

	Chunk(const Chunk&) = default;
	Chunk(Chunk&&) = default;

	Chunk& operator=(const Chunk&) = default;
	Chunk& operator=(Chunk&&) = default;

	bool contains(const QPoint& point) const;

	const CELL& cell(const QPoint& point) const;
	const CELL* findCell(const QPoint& point) const;

	void setCell(const QPoint& point, const CELL& cell);
	void setCell(const QPoint& point, CELL&& cell);

	bool isEmpty() const;

	bool operator==(const Chunk& chunk) const;
	bool operator!=(const Chunk& chunk) const;

	typename QVector<CELL>::const_iterator begin() const;
	typename QVector<CELL>::iterator begin();

	typename QVector<CELL>::const_iterator end() const;
	typename QVector<CELL>::iterator end();

private:
	QVector<CELL> mGrid;
};
/*-----------------------------------------------------------------------------------------------------------*/
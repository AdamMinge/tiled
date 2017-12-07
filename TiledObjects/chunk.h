/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QVector>
#include "cell.h"
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
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

	const Cell& cell(const QPoint& point) const;
	const Cell* findCell(const QPoint& point) const;

	void setCell(const QPoint& point, const Cell& cell);
	void setCell(const QPoint& point, Cell&& cell);

	bool isEmpty() const;

	QVector<Cell>::const_iterator begin() const;
	QVector<Cell>::iterator begin();

	QVector<Cell>::const_iterator end() const;
	QVector<Cell>::iterator end();

private:
	QVector<Cell> mGrid;
};
/*-----------------------------------------------------------------------------------------------------------*/
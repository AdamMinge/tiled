/*-----------------------------------------------------------------------------------------------------------*/
#include "chunk.h"
#include "cell.h"
#include "tiledutils.h"
/*-----------------------------------------------------------------------------------------------------------*/
Chunk::Chunk() :
	mGrid(chunkSize() * chunkSize())
{
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Chunk::contains(const QPoint& point) const
{
	const auto index = (point.x() + point.y() * chunkSize());
	
	if (index < 0 || index >= mGrid.count()) return false;
	else return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
const Cell& Chunk::cell(const QPoint& point) const
{
	auto cell = findCell(point);
	Q_ASSERT(cell);

	return *cell;
}
/*-----------------------------------------------------------------------------------------------------------*/
const Cell* Chunk::findCell(const QPoint& point) const
{
	if (contains(point)) return &mGrid[(point.x() + point.y() * chunkSize())];
	else return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Chunk::setCell(const QPoint& point, const Cell& cell)
{
	Q_ASSERT(contains(point));
	mGrid[point.x() + point.y() * chunkSize()] = cell;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Chunk::setCell(const QPoint& point, Cell&& cell)
{
	Q_ASSERT(contains(point));
	mGrid[point.x() + point.y() * chunkSize()] = std::move(cell);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Chunk::isEmpty() const
{
	for(auto y = 0; y < chunkSize(); y++)
		for(auto x = 0; x < chunkSize(); x++)
			if (!cell(QPoint(x, y)).isEmpty()) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Chunk::operator==(const Chunk& chunk) const
{
	return mGrid == chunk.mGrid;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Chunk::operator!=(const Chunk& chunk) const
{
	return mGrid != chunk.mGrid;
}
/*-----------------------------------------------------------------------------------------------------------*/
QVector<Cell>::const_iterator Chunk::begin() const
{
	return mGrid.begin();
}
/*-----------------------------------------------------------------------------------------------------------*/
QVector<Cell>::iterator Chunk::begin()
{
	return mGrid.begin();
}
/*-----------------------------------------------------------------------------------------------------------*/
QVector<Cell>::const_iterator Chunk::end() const
{
	return mGrid.end();
}
/*-----------------------------------------------------------------------------------------------------------*/
QVector<Cell>::iterator Chunk::end()
{
	return mGrid.end();
}
/*-----------------------------------------------------------------------------------------------------------*/

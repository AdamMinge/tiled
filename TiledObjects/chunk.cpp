/*-----------------------------------------------------------------------------------------------------------*/
#include "chunk.h"
#include "tiledutils.h"
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
Chunk<CELL>::Chunk() :
	mGrid(chunkSize() * chunkSize())
{
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
bool Chunk<CELL>::contains(const QPoint& point) const
{
	const auto index = (point.x() + point.y() * chunkSize());
	
	if (index < 0 || index >= mGrid.count()) return false;
	else return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
const CELL& Chunk<CELL>::cell(const QPoint& point) const
{
	auto cell = findCell(point);
	Q_ASSERT(cell);

	return *cell;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
const CELL* Chunk<CELL>::findCell(const QPoint& point) const
{
	if (contains(point)) return &mGrid[(point.x() + point.y() * chunkSize())];
	else return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
void Chunk<CELL>::setCell(const QPoint& point, const CELL& cell)
{
	mGrid[point.x() + point.y() * chunkSize()] = cell;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
void Chunk<CELL>::setCell(const QPoint& point, CELL&& cell)
{
	mGrid[point.x() + point.y() * chunkSize()] = std::move(cell);
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
bool Chunk<CELL>::isEmpty() const
{
	for(auto y = 0; y < chunkSize(); y++)
		for(auto x = 0; x < chunkSize(); x++)
			if (!cell(QPoint(x, y)).isEmpty()) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
template <typename CELL>
bool Chunk<CELL>::operator==(const Chunk& chunk) const
{
	return mGrid == chunk.mGrid;
}
/*-----------------------------------------------------------------------------------------------------------*/
template <typename CELL>
bool Chunk<CELL>::operator!=(const Chunk& chunk) const
{
	return mGrid != chunk.mGrid;
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
typename QVector<CELL>::const_iterator Chunk<CELL>::begin() const
{
	return mGrid.begin();
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
typename QVector<CELL>::iterator Chunk<CELL>::begin()
{
	return mGrid.begin();
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
typename QVector<CELL>::const_iterator Chunk<CELL>::end() const
{
	return mGrid.end();
}
/*-----------------------------------------------------------------------------------------------------------*/
template<typename CELL>
typename QVector<CELL>::iterator Chunk<CELL>::end()
{
	return mGrid.end();
}
/*-----------------------------------------------------------------------------------------------------------*/

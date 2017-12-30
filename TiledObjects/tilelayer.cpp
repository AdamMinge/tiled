/*-----------------------------------------------------------------------------------------------------------*/
#include "tilelayer.h"
#include "tiledutils.h"
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::TileLayer(const QString& name, const QSize& size) :
	Layer(LayerType::TileLayerType, name),
	mSize(size)
{
	Q_ASSERT(size.width() > 0 && size.height() > 0);
}
/*-----------------------------------------------------------------------------------------------------------*/
const QSize& TileLayer::size() const
{
	return mSize;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TileLayer::setSize(const QSize& size)
{
	mSize = size;
}
/*-----------------------------------------------------------------------------------------------------------*/
QRect TileLayer::bounds() const
{
	return mBounds;
}
/*-----------------------------------------------------------------------------------------------------------*/
QRect TileLayer::rect() const
{
	return QRect(QPoint(0, 0), mSize);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::contains(const QPoint& point) const
{
	if (point.x() < 0 || point.y() < 0 || 
		point.x() >= mSize.width() || point.y() >= mSize.height())
		return false;
	else 
		return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
const TileLayer::UChunk& TileLayer::chunk(const QPoint& point) const
{
	const auto chunkCoordinates = point / chunkSize();
	auto chunk = findChunk(chunkCoordinates);
	Q_ASSERT(chunk);

	return *chunk;
}
/*-----------------------------------------------------------------------------------------------------------*/
const TileLayer::UChunk* TileLayer::findChunk(const QPoint& point) const
{
	return const_cast<TileLayer*>(this)->findChunk(point);
}
/*-----------------------------------------------------------------------------------------------------------*/
const TileLayer::UCell& TileLayer::cell(const QPoint& point) const
{
	auto cellPtr = findCell(point);
	if (!cellPtr) cellPtr = &mEmptyCell;

	return *cellPtr;
}
/*-----------------------------------------------------------------------------------------------------------*/
const TileLayer::UCell* TileLayer::findCell(const QPoint& point) const
{
	if (const auto chunk = findChunk(point))
		return &chunk->cell(point & chunkMask());
	else
		return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TileLayer::setCell(const QPoint& point, const TileLayer::UCell& cell)
{
	auto chunk = findChunk(point);

	if (!chunk)
	{
		if (cell.isEmpty()) return;
		else
		{
			mBounds = mBounds.united(QRect(
				point.x() - (point.x() & chunkMask()),
				point.y() - (point.y() & chunkMask()),
				chunkSize(),
				chunkSize()));
		}
	}

	auto oldTileset = chunk->cell(point & chunkMask()).tileset();
	const auto newTileset = cell.tileset();

	if(oldTileset != newTileset)
	{
		if (oldTileset)
		{
			mUsedTileset[oldTileset] -= 1;

			if (mUsedTileset[oldTileset] == 0)
				mUsedTileset.remove(oldTileset);
		}
		if (newTileset)
		{
			Q_ASSERT(mUsedTileset[oldTileset] != std::numeric_limits<unsigned>::max());
			mUsedTileset[oldTileset] += 1;
		}
	}

	chunk->setCell(point & chunkMask(), cell);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TileLayer::setCell(const QPoint& point, TileLayer::UCell&& cell)
{
	auto chunk = findChunk(point);

	if (!chunk)
	{
		if (cell.isEmpty()) return;
		else
		{
			mBounds = mBounds.united(QRect(
				point.x() - (point.x() & chunkMask()),
				point.y() - (point.y() & chunkMask()),
				chunkSize(),
				chunkSize()));
		}
	}

	auto oldTileset = chunk->cell(point & chunkMask()).tileset();
	const auto newTileset = cell.tileset();

	if (oldTileset != newTileset)
	{
		if (oldTileset)
		{
			mUsedTileset[oldTileset] -= 1;

			if (mUsedTileset[oldTileset] == 0)
				mUsedTileset.remove(oldTileset);
		}
		if (newTileset)
		{
			Q_ASSERT(mUsedTileset[oldTileset] != std::numeric_limits<unsigned>::max());
			mUsedTileset[oldTileset] += 1;
		}
	}

	chunk->setCell(point & chunkMask(), std::move(cell));
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::isEmpty() const
{
	for(decltype(auto) chunk : mChunks)
		if (!chunk.isEmpty()) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<Tileset*> TileLayer::usedTilesets() const
{
	QList<Tileset*> usedTileset;

	for (decltype(auto) tileset : mUsedTileset.keys())
		usedTileset.append(const_cast<Tileset*>(tileset));

	return usedTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::referencesTileset(const Tileset* tileset) const
{
	auto tilesets = mUsedTileset.keys();
	return tilesets.contains(tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TileLayer::merge(const QPoint& pos, const TileLayer* layer)
{
	auto area = QRect(pos, layer->size());
	area &= QRect(0, 0, size().width(), size().height());

	for(auto y = area.top(); y <= area.bottom(); ++y)
	{
		for(auto x = area.left(); x <= area.right(); ++x)
		{
			auto cell = layer->cell(QPoint(x - pos.x(), y - pos.y()));

			if (!cell.isEmpty())
				setCell(QPoint(x, y), std::move(cell));
		}
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::canMergeWith(Layer* layer) const
{
	return layer->layerType() == layerType();
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* TileLayer::mergeWith(Layer* layer) const
{
	Q_ASSERT(canMergeWith(layer));

	const auto tileLayer = static_cast<TileLayer*>(layer);
	auto merged = clone();

	merged->merge(QPoint(), tileLayer);

	return merged;
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::ConstIterator TileLayer::begin() const
{
	return ConstIterator(mChunks.begin(), mChunks.end());
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::Iterator TileLayer::begin()
{
	return Iterator(mChunks.end(), mChunks.end());
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::ConstIterator TileLayer::end() const
{
	return ConstIterator(mChunks.begin(), mChunks.end());
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::Iterator TileLayer::end()
{
	return Iterator(mChunks.end(), mChunks.end());
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer* TileLayer::clone() const
{
	return initializeClone(new TileLayer(name(), mSize));
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer* TileLayer::initializeClone(TileLayer* clone) const
{
	Layer::initializeClone(clone);
	clone->mChunks = mChunks;
	clone->mUsedTileset = mUsedTileset;

	return clone;
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::UChunk* TileLayer::findChunk(const QPoint& point)
{
	const auto chunkCoordinates = point / chunkSize();
	auto iter = mChunks.find(chunkCoordinates);

	if (iter != mChunks.end()) return &iter.value();
	else return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::Iterator::Iterator(QHash<QPoint, TileLayer::UChunk>::Iterator start,
	QHash<QPoint, TileLayer::UChunk>::Iterator end) :
	mChunkIter(start),
	mChunkEndIter(end),
	mCellIter((mChunkIter != mChunkEndIter) ? start.value().begin() : QVector<TileLayer::UCell>::Iterator())
{

}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::Iterator TileLayer::Iterator::operator++(int)
{
	const auto iter = *this;
	advance();
	return iter;
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::Iterator& TileLayer::Iterator::operator++()
{
	advance();
	return *this;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::Iterator::operator==(const Iterator& other) const
{
	if (mChunkIter == mChunkEndIter || other.mChunkIter == other.mChunkEndIter)
		return mChunkIter == other.mChunkIter;
	else
		return mCellIter == other.mCellIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::UCell& TileLayer::Iterator::operator*() const
{
	return *mCellIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::UCell* TileLayer::Iterator::operator->() const
{
	return mCellIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::UCell& TileLayer::Iterator::value() const
{
	return *mCellIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
QPoint TileLayer::Iterator::key() const
{
	const auto chunkCoordinates = mChunkIter.key() * chunkSize();
	const auto cellIndex = mCellIter - mChunkIter.value().begin();
	const auto cellCoordinates = QPoint(cellIndex & chunkMask(), cellIndex / chunkSize());

	return  chunkCoordinates + cellCoordinates;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::Iterator::hasNext() const
{
	return mChunkIter != mChunkEndIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TileLayer::Iterator::advance()
{
	if(++mCellIter == mChunkIter.value().end())
	{
		++mChunkIter;
		Q_ASSERT(mChunkIter != mChunkEndIter);

		mCellIter = mChunkIter.value().begin();
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::ConstIterator::ConstIterator(QHash<QPoint, TileLayer::UChunk>::ConstIterator start,
	QHash<QPoint, TileLayer::UChunk>::ConstIterator end) :
	mChunkIter(start),
	mChunkEndIter(end),
	mCellIter((mChunkIter != mChunkEndIter) ? start.value().begin() : QVector<TileLayer::UCell>::ConstIterator())
{

}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::ConstIterator TileLayer::ConstIterator::operator++(int)
{
	const auto iter = *this;
	advance();
	return iter;
}
/*-----------------------------------------------------------------------------------------------------------*/
TileLayer::ConstIterator& TileLayer::ConstIterator::operator++()
{
	advance();
	return *this;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::ConstIterator::operator==(const ConstIterator& other) const
{
	if (mChunkIter == mChunkEndIter || other.mChunkIter == other.mChunkEndIter)
		return mChunkIter == other.mChunkIter;
	else
		return mCellIter == other.mCellIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::ConstIterator::operator!=(const ConstIterator& other) const
{
	return !(*this == other);
}
/*-----------------------------------------------------------------------------------------------------------*/
const TileLayer::UCell& TileLayer::ConstIterator::operator*() const
{
	return *mCellIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
const TileLayer::UCell* TileLayer::ConstIterator::operator->() const
{
	return mCellIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
const TileLayer::UCell& TileLayer::ConstIterator::value() const
{
	return *mCellIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
QPoint TileLayer::ConstIterator::key() const
{
	const auto chunkCoordinates = mChunkIter.key() * chunkSize();
	const auto cellIndex = mCellIter - mChunkIter.value().begin();
	const auto cellCoordinates = QPoint(cellIndex & chunkMask(), cellIndex / chunkSize());

	return  chunkCoordinates + cellCoordinates;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TileLayer::ConstIterator::hasNext() const
{
	return mChunkIter != mChunkEndIter;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TileLayer::ConstIterator::advance()
{
	if (++mCellIter == mChunkIter.value().end())
	{
		++mChunkIter;
		Q_ASSERT(mChunkIter != mChunkEndIter);

		mCellIter = mChunkIter.value().begin();
	}
}
/*-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QRect>
#include "layer.h"
#include "chunk.h"
#include "cell.h"
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Tileset;
class Tile;
/*-----------------------------------------------------------------------------------------------------------*/
inline uint TILEDOBJECTS_EXPORT qHash(const QPoint &key, const uint seed = 0) Q_DECL_NOTHROW
{
	const auto h1 = qHash(key.x(), seed);
	const auto h2 = qHash(key.y(), seed);
	return ((h1 << 16) | (h1 >> 16)) ^ h2 ^ seed;
}
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT TileLayer final : public Layer
{
private:
	using UCell = Cell<Tileset, Tile>;
	using UChunk = Chunk<UCell>;

public:
	class Iterator;
	class ConstIterator;

public:
	explicit TileLayer(const QString& name, const QSize& size);
	~TileLayer() override = default;

	const QSize& size() const;
	void setSize(const QSize& size);

	QRect bounds() const;
	QRect rect() const;

	bool contains(const QPoint& point) const;

	const UChunk& chunk(const QPoint& point) const;
	const UChunk* findChunk(const QPoint& point) const;

	const UCell &cell(const QPoint& point) const;
	const UCell* findCell(const QPoint& point) const;

	void setCell(const QPoint& point, const UCell& cell);
	void setCell(const QPoint& point, UCell&& cell);

	bool isEmpty() const override;
	QList<Tileset*> usedTilesets() const override;
	bool referencesTileset(const Tileset *tileset) const override;

	void merge(const QPoint& pos, const TileLayer* layer);
	bool canMergeWith(Layer* layer) const override;
	Layer* mergeWith(Layer* layer) const override;

	ConstIterator begin() const;
	Iterator begin();

	ConstIterator end() const;
	Iterator end();

	TileLayer* clone() const override;

private:
	TileLayer* initializeClone(TileLayer* clone) const;
	UChunk* findChunk(const QPoint& point);

private:
	QSize mSize;
	QRect mBounds;
	UCell mEmptyCell;
	QHash<QPoint, UChunk> mChunks;
	QMap<const Tileset*, unsigned> mUsedTileset;
};
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT TileLayer::Iterator
{
public:
	explicit Iterator(QHash<QPoint, UChunk>::Iterator start, QHash<QPoint, UChunk>::Iterator end);

	Iterator(const Iterator&) = default;
	Iterator(Iterator&&) = default;

	Iterator& operator=(const Iterator&) = default;
	Iterator& operator=(Iterator&&) = default;

	Iterator operator++(int);
	Iterator& operator++();

	bool operator==(const Iterator& other) const;
	bool operator!=(const Iterator& other) const;

	UCell& operator*() const;
	UCell* operator->() const;

	UCell& value() const;
	QPoint key() const;

	bool hasNext() const;

private:
	void advance();

private:
	QHash<QPoint, UChunk>::Iterator mChunkIter;
	QHash<QPoint, UChunk>::Iterator mChunkEndIter;
	QVector<UCell>::Iterator mCellIter;
};
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT TileLayer::ConstIterator
{
public:
	explicit ConstIterator(QHash<QPoint, UChunk>::ConstIterator start, QHash<QPoint, UChunk>::ConstIterator end);

	ConstIterator(const ConstIterator&) = default;
	ConstIterator(ConstIterator&&) = default;

	ConstIterator& operator=(const ConstIterator&) = default;
	ConstIterator& operator=(ConstIterator&&) = default;

	ConstIterator operator++(int);
	ConstIterator& operator++();

	bool operator==(const ConstIterator& other) const;
	bool operator!=(const ConstIterator& other) const;

	const UCell& operator*() const;
	const UCell* operator->() const;

	const UCell& value() const;
	QPoint key() const;

	bool hasNext() const;

private:
	void advance();

private:
	QHash<QPoint, UChunk>::ConstIterator mChunkIter;
	QHash<QPoint, UChunk>::ConstIterator mChunkEndIter;
	QVector<UCell>::ConstIterator mCellIter;
};
/*-----------------------------------------------------------------------------------------------------------*/
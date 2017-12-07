/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Layer;
class GroupLayer;
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT PostOrderLayerIteration
{
public:
	explicit PostOrderLayerIteration(GroupLayer* root, Layer* start = nullptr);
	~PostOrderLayerIteration() = default;

	PostOrderLayerIteration(const PostOrderLayerIteration&) = default;
	PostOrderLayerIteration(PostOrderLayerIteration&& other) noexcept;

	PostOrderLayerIteration& operator=(const PostOrderLayerIteration&) = default;
	PostOrderLayerIteration& operator=(PostOrderLayerIteration&& other) noexcept;

	Layer* currentLayer() const;
	int currentSiblingIndex() const;

	Layer* next();
	Layer* previous();

	bool hasNext() const;
	bool hasPrevious() const;

	bool operator==(const PostOrderLayerIteration& other) const;
	bool operator!=(const PostOrderLayerIteration& other) const;

	void reset();

private:
	static Layer* getFirst(GroupLayer* root);
	static Layer* getLast(GroupLayer* root);

private:
	Layer* mFirst;
	Layer* mLast;
	Layer* mCurrentLayer;
	int mSiblingIndex;
};
/*-----------------------------------------------------------------------------------------------------------*/
template<typename ITERATION = PostOrderLayerIteration>
class TILEDOBJECTS_EXPORT LayerIterator final
{
public:
	explicit LayerIterator(GroupLayer* root, Layer* start = nullptr) : mIterationAlgorithm(root, start) {}
	~LayerIterator() = default;

	LayerIterator(const LayerIterator&) = default;
	LayerIterator(LayerIterator&& other) = default;

	LayerIterator& operator=(const LayerIterator&) = default;
	LayerIterator& operator=(LayerIterator&& other) = default;

	Layer* currentLayer() const { return mIterationAlgorithm.currentLayer(); }
	int currentSiblingIndex() const { return mIterationAlgorithm.currentSiblingIndex(); }

	Layer* next() { return mIterationAlgorithm.next(); }
	Layer* previous() { return mIterationAlgorithm.previous(); }

	bool hasNext() { return mIterationAlgorithm.hasNext(); }
	bool hasPrevious() { return mIterationAlgorithm.hasPrevious(); }

	LayerIterator operator++(int) { auto oldIter = *this; next(); return oldIter; }
	LayerIterator& operator++() { next(); return *this; }

	LayerIterator operator--(int) { auto oldIter = *this; previous(); return oldIter; }
	LayerIterator& operator--() { previous(); return *this; }

	bool operator==(const LayerIterator& other) const { return mIterationAlgorithm == other.mIterationAlgorithm; }
	bool operator!=(const LayerIterator& other) const { return mIterationAlgorithm != other.mIterationAlgorithm; }

	void reset() { mIterationAlgorithm.reset(); }

private:
	ITERATION mIterationAlgorithm;
};
/*-----------------------------------------------------------------------------------------------------------*/
template<typename ITERATION = PostOrderLayerIteration>
class TILEDOBJECTS_EXPORT ConstLayerIterator final
{
public:
	explicit ConstLayerIterator(const GroupLayer* root, const Layer* start = nullptr) : mIterationAlgorithm(const_cast<GroupLayer*>(root), const_cast<Layer*>(start)) {}
	~ConstLayerIterator() = default;

	ConstLayerIterator(const ConstLayerIterator&) = default;
	ConstLayerIterator(ConstLayerIterator&& other) = default;

	ConstLayerIterator& operator=(const ConstLayerIterator&) = default;
	ConstLayerIterator& operator=(ConstLayerIterator&& other) = default;

	const Layer* currentLayer() const { return mIterationAlgorithm.currentLayer(); }
	int currentSiblingIndex() const { return mIterationAlgorithm.currentSiblingIndex(); }

	const Layer* next() { return mIterationAlgorithm.next(); }
	const Layer* previous() { return mIterationAlgorithm.previous(); }

	bool hasNext() { return mIterationAlgorithm.hasNext(); }
	bool hasPrevious() { return mIterationAlgorithm.hasPrevious(); }

	ConstLayerIterator operator++(int) { auto oldIter = *this; next(); return oldIter; }
	ConstLayerIterator& operator++() { next(); return *this; }

	ConstLayerIterator operator--(int) { auto oldIter = *this; previous(); return oldIter; }
	ConstLayerIterator& operator--() { previous(); return *this; }

	bool operator==(const ConstLayerIterator& other) const { return mIterationAlgorithm == other.mIterationAlgorithm; }
	bool operator!=(const ConstLayerIterator& other) const { return mIterationAlgorithm != other.mIterationAlgorithm; }

	void reset() { mIterationAlgorithm.reset(); }

private:
	ITERATION mIterationAlgorithm;
};
/*-----------------------------------------------------------------------------------------------------------*/
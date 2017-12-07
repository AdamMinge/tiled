/*-----------------------------------------------------------------------------------------------------------*/
#include "layeriterator.h"
#include "grouplayer.h"
/*-----------------------------------------------------------------------------------------------------------*/
PostOrderLayerIteration::PostOrderLayerIteration(GroupLayer* root, Layer* start) :
	mFirst(getFirst(root)),
	mLast(getLast(root)),
	mCurrentLayer(start),
	mSiblingIndex(start ? start->siblingIndex() : -1)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
PostOrderLayerIteration::PostOrderLayerIteration(PostOrderLayerIteration&& other) noexcept
{
	mFirst = other.mFirst;
	mLast = other.mLast;
	mCurrentLayer = other.mCurrentLayer;
	mSiblingIndex = other.mSiblingIndex;

	other.mFirst = nullptr;
	other.mLast = nullptr;
	other.mCurrentLayer = nullptr;
	other.mSiblingIndex = -1;
}
/*-----------------------------------------------------------------------------------------------------------*/
PostOrderLayerIteration& PostOrderLayerIteration::operator=(PostOrderLayerIteration&& other) noexcept
{
	mFirst = other.mFirst;
	mLast = other.mLast;
	mCurrentLayer = other.mCurrentLayer;
	mSiblingIndex = other.mSiblingIndex;

	other.mFirst = nullptr;
	other.mLast = nullptr;
	other.mCurrentLayer = nullptr;
	other.mSiblingIndex = -1;

	return *this;
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* PostOrderLayerIteration::currentLayer() const
{
	return mCurrentLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
int PostOrderLayerIteration::currentSiblingIndex() const
{
	return mSiblingIndex;
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* PostOrderLayerIteration::next()
{
	Q_ASSERT(hasNext());
	auto layer = mCurrentLayer;
	auto index = mSiblingIndex;

	if(!layer)
	{
		Q_ASSERT(mFirst);
		layer = mFirst;
		index = layer->siblingIndex();
	}
	else
	{
		++index;

		auto siblings = layer->siblings();
		if (siblings.count() > index)
		{
			layer = siblings.at(index);

			auto groupLayer = dynamic_cast<GroupLayer*>(layer);
			while (groupLayer && groupLayer->layerCount() > 0)
			{
				layer = groupLayer->layer(0);
				index = 0;

				groupLayer = dynamic_cast<GroupLayer*>(layer);
			}
		}
		else
		{
			layer = layer->parent();
			index = layer ? layer->siblingIndex() : -1;
		}
	}

	mCurrentLayer = layer;
	mSiblingIndex = index;

	return mCurrentLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* PostOrderLayerIteration::previous()
{
	Q_ASSERT(hasPrevious());
	auto layer = mCurrentLayer;
	auto index = mSiblingIndex;

	if (!layer)
	{
		Q_ASSERT(mLast);
		layer = mLast;
		index = layer->siblingIndex();
	}
	else
	{
		--index;

		auto groupLayer = dynamic_cast<GroupLayer*>(layer);
		if (groupLayer && groupLayer->layerCount() > 0)
		{
			index = groupLayer->layerCount() - 1;
			layer = groupLayer->layer(index);
		}
		else
		{
			while (index < 0)
			{
				layer = layer->parent();
				Q_ASSERT(layer);

				auto parent = dynamic_cast<GroupLayer*>(layer->parent());
				Q_ASSERT(parent);

				index = parent->layerIndex(layer) - 1;
			}

			auto parent = dynamic_cast<GroupLayer*>(layer->parent());
			Q_ASSERT(parent);

			layer = parent->layer(index);
		}
	}

	mCurrentLayer = layer;
	mSiblingIndex = index;

	return mCurrentLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PostOrderLayerIteration::hasNext() const
{
	if (mCurrentLayer != mLast) return true;
	else return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PostOrderLayerIteration::hasPrevious() const
{
	if (mCurrentLayer != mFirst) return true;
	else return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PostOrderLayerIteration::operator==(const PostOrderLayerIteration& other) const
{
	if (mFirst != other.mFirst ||
		mLast != other.mLast ||
		mCurrentLayer != other.mCurrentLayer ||
		mSiblingIndex != other.mSiblingIndex) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PostOrderLayerIteration::operator!=(const PostOrderLayerIteration& other) const
{
	return !(*this == other);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PostOrderLayerIteration::reset()
{
	mCurrentLayer = nullptr;
	mSiblingIndex = -1;
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* PostOrderLayerIteration::getFirst(GroupLayer* root)
{
	Layer* layer = root;
	auto groupLayer = root;

	while (groupLayer && groupLayer->layerCount() > 0)
	{
		layer = groupLayer->layer(0);
		groupLayer = dynamic_cast<GroupLayer*>(layer);
	}

	Q_ASSERT(layer);
	return layer;
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* PostOrderLayerIteration::getLast(GroupLayer* root)
{
	Q_ASSERT(root);
	return root;
}
/*-----------------------------------------------------------------------------------------------------------*/

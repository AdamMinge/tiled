/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "mapdocument.h"
#include "reparentlayer.h"
#include "grouplayer.h"
#include "layertreemodel.h"
#include "layer.h"
/*-----------------------------------------------------------------------------------------------------------*/
ReparentLayer::ReparentLayer(MapDocument* mapDocument, Layer* layer,
	GroupLayer* newParent, int row, Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mLayer(layer),
	mNewParent(newParent),
	mPreviousParent(layer->parent()),
	mNewIndex(row),
	mPreviousIndex(layer->siblingIndex())
{
	if (mPreviousParent == mNewParent && mPreviousIndex < mNewIndex) --mNewIndex;

	setText(QCoreApplication::translate("Undo Commands", "Reparent Layer"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReparentLayer::undo()
{
	auto layerModel = mMapDocument->layerModel();

	layerModel->takeLayer(mNewParent, mNewIndex);
	layerModel->addLayer(mPreviousParent, mPreviousIndex, mLayer);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReparentLayer::redo()
{
	auto layerModel = mMapDocument->layerModel();

	layerModel->takeLayer(mPreviousParent, mPreviousIndex);
	layerModel->addLayer(mNewParent, mNewIndex, mLayer);
}
/*-----------------------------------------------------------------------------------------------------------*/
int ReparentLayer::id() const
{
	return CommandId::ReparentLayerId;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ReparentLayer::canMergeWith(const Command* other) const
{
	auto changeLayerProperty = static_cast<const ReparentLayer*>(other);

	if (mMapDocument != changeLayerProperty->mMapDocument ||
		mLayer != changeLayerProperty->mLayer) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReparentLayer::mergeWith(const Command* other) 
{
	auto changeLayerProperty = static_cast<const ReparentLayer*>(other);

	mNewParent = changeLayerProperty->mNewParent;
	mNewIndex = changeLayerProperty->mNewIndex;
}
/*-----------------------------------------------------------------------------------------------------------*/

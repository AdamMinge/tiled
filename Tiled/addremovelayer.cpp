/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "addremovelayer.h"
#include "mapdocument.h"
#include "layertreemodel.h"
#include "grouplayer.h"
/*-----------------------------------------------------------------------------------------------------------*/
AddRemoveLayer::AddRemoveLayer(MapDocument* mapDocument, Layer* layer,
	int index, GroupLayer* parentLayer, Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mLayer(layer),
	mParentLayer(parentLayer),
	mIndex(index)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
AddRemoveLayer::~AddRemoveLayer()
{
	if (mLayer) delete mLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddRemoveLayer::addLayer()
{
	mMapDocument->layerModel()->addLayer(mParentLayer, mIndex, mLayer);
	mLayer = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddRemoveLayer::removeLayer()
{
	mLayer = mMapDocument->layerModel()->takeLayer(mParentLayer, mIndex);
}
/*-----------------------------------------------------------------------------------------------------------*/
AddLayer::AddLayer(MapDocument* mapDocument, Layer* layer, GroupLayer* parentLayer, Command* parent) :
	AddLayer(mapDocument, parentLayer->layerCount(), layer,  parentLayer, parent)
{
	
}
/*-----------------------------------------------------------------------------------------------------------*/
AddLayer::AddLayer(MapDocument* mapDocument, int index, Layer* layer, GroupLayer* parentLayer, Command* parent) :
	AddRemoveLayer(mapDocument, layer, index, parentLayer, parent)
{
	setText(QCoreApplication::translate("Undo Commands", "Add Layer"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddLayer::undo()
{
	removeLayer();
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddLayer::redo()
{
	addLayer();
}
/*-----------------------------------------------------------------------------------------------------------*/
RemoveLayer::RemoveLayer(MapDocument* mapDocument, int index, GroupLayer* parentLayer, Command* parent) :
	AddRemoveLayer(mapDocument, parentLayer->layer(index), index, parentLayer, parent)
{
	setText(QCoreApplication::translate("Undo Commands", "Remove Layer"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void RemoveLayer::undo()
{
	addLayer();
}
/*-----------------------------------------------------------------------------------------------------------*/
void RemoveLayer::redo()
{
	removeLayer();
}
/*-----------------------------------------------------------------------------------------------------------*/

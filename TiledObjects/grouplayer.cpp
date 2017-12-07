/*-----------------------------------------------------------------------------------------------------------*/
#include "grouplayer.h"
/*-----------------------------------------------------------------------------------------------------------*/
QList<Tileset*>& operator|=(QList<Tileset*>& united, const QList<Tileset*>& other)
{
	for (decltype(auto) layer : other)
		if (!united.contains(layer)) united.append(layer);

	return united;
}
/*-----------------------------------------------------------------------------------------------------------*/
GroupLayer::GroupLayer(const QString& name) :
	Layer(LayerType::GroupLayerType, name)
{
	
}
/*-----------------------------------------------------------------------------------------------------------*/
GroupLayer::~GroupLayer()
{
	qDeleteAll(mLayers);
}
/*-----------------------------------------------------------------------------------------------------------*/
const QList<Layer*>& GroupLayer::layers() const
{
	return mLayers;
}
/*-----------------------------------------------------------------------------------------------------------*/
const Layer* GroupLayer::layer(int index) const
{
	return const_cast<GroupLayer*>(this)->layer(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* GroupLayer::layer(int index)
{
	return mLayers.value(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
int GroupLayer::layerCount() const
{
	return mLayers.count();
}
/*-----------------------------------------------------------------------------------------------------------*/
int GroupLayer::layerIndex(const Layer* layer) const
{
	return mLayers.indexOf(const_cast<Layer*>(layer));
}
/*-----------------------------------------------------------------------------------------------------------*/
void GroupLayer::addLayer(Layer* layer)
{
	addLayer(layer, layerCount());
}
/*-----------------------------------------------------------------------------------------------------------*/
void GroupLayer::addLayer(Layer* layer, int index)
{
	Q_ASSERT(layer);
	Q_ASSERT(!layer->parent());

	layer->setParent(this);
	mLayers.insert(index, layer);
}
/*-----------------------------------------------------------------------------------------------------------*/
void GroupLayer::removeLayer(int index)
{
	Q_ASSERT(index >= 0 && index < layerCount());
	auto layer = takeLayer(index);

	Q_ASSERT(layer);
	delete layer;
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* GroupLayer::takeLayer(int index)
{
	Q_ASSERT(index >= 0 && index < layerCount());
	auto layer = mLayers.takeAt(index);
	layer->setParent(nullptr);
	return layer;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool GroupLayer::isEmpty() const
{
	return mLayers.isEmpty();
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<Tileset*> GroupLayer::usedTilesets() const
{
	QList<Tileset*> tilesets;

	for (decltype(auto) layer : mLayers)
		tilesets |= layer->usedTilesets();

	return tilesets;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool GroupLayer::referencesTileset(const Tileset* tileset) const
{
	for (decltype(auto) layer : mLayers)
		if (layer->referencesTileset(tileset)) return true;

	return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool GroupLayer::canMergeWith(Layer* layer) const
{
	Q_UNUSED(layer);
	return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* GroupLayer::mergeWith(Layer* layer) const
{
	Q_UNUSED(layer);
	return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<Layer*>::iterator GroupLayer::begin()
{
	return mLayers.begin();
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<Layer*>::const_iterator GroupLayer::begin() const
{
	return mLayers.begin();
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<Layer*>::iterator GroupLayer::end()
{
	return mLayers.end();
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<Layer*>::const_iterator GroupLayer::end() const
{
	return mLayers.end();
}
/*-----------------------------------------------------------------------------------------------------------*/
GroupLayer* GroupLayer::clone() const
{
	return initializeClone(new GroupLayer(name()));
}
/*-----------------------------------------------------------------------------------------------------------*/
GroupLayer* GroupLayer::initializeClone(GroupLayer* clone) const
{
	Layer::initializeClone(clone);

	for (decltype(auto) layer : mLayers)
		clone->addLayer(layer->clone());

	return clone;
}
/*-----------------------------------------------------------------------------------------------------------*/
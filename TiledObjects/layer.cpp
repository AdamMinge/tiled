/*-----------------------------------------------------------------------------------------------------------*/
#include "layer.h"
#include "grouplayer.h"
/*-----------------------------------------------------------------------------------------------------------*/
Layer::Layer(LayerType type, const QString& name) :
	Object(ObjectType::LayerType),
	mName(name),
	mType(type),
	mOpacity(1.0f),
	mParentLayer(nullptr),
	mVisible(true),
	mLocked(false)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
Layer::LayerType Layer::layerType() const
{
	return mType;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& Layer::name() const
{
	return mName;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Layer::setName(const QString& name)
{
	mName = name;
}
/*-----------------------------------------------------------------------------------------------------------*/
float Layer::opacity() const
{
	return mOpacity;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Layer::setOpacity(float opacity)
{
	mOpacity = opacity;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Layer::isVisible() const
{
	return mVisible;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Layer::isHidden() const
{
	if (parent())
		return !isVisible() || parent()->isHidden();
	else
		return !isVisible();
}
/*-----------------------------------------------------------------------------------------------------------*/
void Layer::setVisible(bool visible)
{
	mVisible = visible;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Layer::isLocked() const
{
	return mLocked;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Layer::isUnlocked() const
{
	if (parent())
		return !isLocked() && parent()->isUnlocked();
	else 
		return !isLocked();
}
/*-----------------------------------------------------------------------------------------------------------*/
void Layer::setLocked(bool locked)
{
	mLocked = locked;
}
/*-----------------------------------------------------------------------------------------------------------*/
GroupLayer* Layer::parent() const
{
	return mParentLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
int Layer::siblingIndex() const
{
	if (mParentLayer)
		return mParentLayer->layerIndex(this);
	else
		return 0;
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<Layer*> Layer::siblings() const
{
	if (mParentLayer)
		return mParentLayer->layers();
	else
		return QList<Layer*>();
}
/*-----------------------------------------------------------------------------------------------------------*/
void Layer::setParent(GroupLayer* layer)
{
	mParentLayer = layer;
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* Layer::initializeClone(Layer* clone) const
{
	clone->mOpacity = mOpacity;
	clone->mLocked = mLocked;
	clone->mVisible = mVisible;
	clone->setProperties(properties());
	
	return clone;
}
/*-----------------------------------------------------------------------------------------------------------*/

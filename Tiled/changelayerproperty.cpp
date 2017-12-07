/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "ChangeLayerProperty.h"
#include "mapdocument.h"
#include "layer.h"
/*-----------------------------------------------------------------------------------------------------------*/
ChangeLayerProperty::ChangeLayerProperty(MapDocument* mapDocument, Layer* layer, 
	const QString& newName, Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mLayer(layer),
	mProperty(MapDocument::ChangedPropertyId::NameChangedId),
	mNewValue(newName),
	mPreviousValue(layer->name())
{
	setText(QCoreApplication::translate("Undo Commands", "Set Layer Name"));
}
/*-----------------------------------------------------------------------------------------------------------*/
ChangeLayerProperty::ChangeLayerProperty(MapDocument* mapDocument, Layer* layer, 
	float opacity, Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mLayer(layer),
	mProperty(MapDocument::ChangedPropertyId::OpacityChangedId),
	mNewValue(opacity),
	mPreviousValue(layer->opacity())
{
	setText(QCoreApplication::translate("Undo Commands", "Set Layer Opacity"));
}
/*-----------------------------------------------------------------------------------------------------------*/
ChangeLayerProperty::ChangeLayerProperty(MapDocument* mapDocument, Layer* layer, 
	bool value, BoolProperty property,
	Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mLayer(layer),
	mNewValue(value)
{
	switch(property)
	{
	case BoolProperty::Visible:
		mProperty = MapDocument::ChangedPropertyId::VisibleChangedId;
		mPreviousValue = layer->isVisible();
		setText(QCoreApplication::translate("Undo Commands", "Set Layer Visible"));
		break;
	case BoolProperty::Locked:
		mProperty = MapDocument::ChangedPropertyId::LockedChangedId;
		mPreviousValue = mLayer->isLocked();
		setText(QCoreApplication::translate("Undo Commands", "Set Layer Locked"));
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeLayerProperty::undo()
{
	setValue(mPreviousValue);
	emit mMapDocument->layerChanged(mLayer, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeLayerProperty::redo()
{
	setValue(mNewValue);
	emit mMapDocument->layerChanged(mLayer, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
int ChangeLayerProperty::id() const
{
	return CommandId::ChangeLayerPropertyId;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ChangeLayerProperty::canMergeWith(const Command* other) const
{
	auto changeLayerProperty = static_cast<const ChangeLayerProperty*>(other);

	if (mMapDocument != changeLayerProperty->mMapDocument ||
		mLayer != changeLayerProperty->mLayer ||
		mProperty != changeLayerProperty->mProperty) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeLayerProperty::mergeWith(const Command* other)
{
	auto changeLayerProperty = static_cast<const ChangeLayerProperty*>(other);
	mNewValue = changeLayerProperty->mNewValue;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeLayerProperty::setValue(const QVariant& value)
{
	switch(mProperty)
	{
	case MapDocument::ChangedPropertyId::NameChangedId:
		mLayer->setName(value.toString());
		break;
	case MapDocument::ChangedPropertyId::VisibleChangedId:
		mLayer->setVisible(value.toBool());
		break;
	case MapDocument::ChangedPropertyId::LockedChangedId:
		mLayer->setLocked(value.toBool());
		break;
	case MapDocument::ChangedPropertyId::OpacityChangedId:
		mLayer->setOpacity(value.toFloat());
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
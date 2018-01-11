/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "changemapproperty.h"
#include "mapdocument.h"
/*-----------------------------------------------------------------------------------------------------------*/
ChangeMapProperty::ChangeMapProperty(MapDocument* mapDocument, Map::Orientation newOrientation,
	Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mMap(mapDocument->map()),
	mProperty(MapDocument::ChangedPropertyId::OrientationChangedId),
	mNewValue(static_cast<int>(newOrientation)),
	mPreviousValue(static_cast<int>(mapDocument->map()->orientation()))
{
	setText(QCoreApplication::translate("Undo Commands", "Set Map Orientation"));
}
/*-----------------------------------------------------------------------------------------------------------*/
ChangeMapProperty::ChangeMapProperty(MapDocument* mapDocument, Map::RenderOrder newRenderOrder,
	Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mMap(mapDocument->map()),
	mProperty(MapDocument::ChangedPropertyId::RenderOrderChangedId),
	mNewValue(static_cast<int>(newRenderOrder)),
	mPreviousValue(static_cast<int>(mapDocument->map()->renderOrder()))
{
	setText(QCoreApplication::translate("Undo Commands", "Set Map Render Order"));
}
/*-----------------------------------------------------------------------------------------------------------*/
ChangeMapProperty::ChangeMapProperty(MapDocument* mapDocument, const QSize& newTileSize,
	Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mMap(mapDocument->map()),
	mProperty(MapDocument::ChangedPropertyId::TileSizeChangedId),
	mNewValue(newTileSize),
	mPreviousValue(mapDocument->map()->tileSize())
{
	setText(QCoreApplication::translate("Undo Commands", "Set Map Tile Size"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeMapProperty::undo()
{
	setValue(mPreviousValue);
	emit mMapDocument->mapChanged(mMap, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeMapProperty::redo()
{
	setValue(mNewValue);
	emit mMapDocument->mapChanged(mMap, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ChangeMapProperty::canMergeWith(const Command* other) const
{
	const auto changeTilesetProperty = static_cast<const ChangeMapProperty*>(other);

	if (mMapDocument != changeTilesetProperty->mMapDocument ||
		mMap != changeTilesetProperty->mMap ||
		mProperty != changeTilesetProperty->mProperty) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeMapProperty::mergeWith(const Command* other)
{
	const auto changeTilesetProperty = static_cast<const ChangeMapProperty*>(other);
	mNewValue = changeTilesetProperty->mNewValue;
}
/*-----------------------------------------------------------------------------------------------------------*/
int ChangeMapProperty::id() const
{
	return CommandId::ChangeMapPropertyId;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeMapProperty::setValue(const QVariant& value)
{
	switch (mProperty)
	{
	case MapDocument::ChangedPropertyId::OrientationChangedId:
		mMap->setOrientation(static_cast<Map::Orientation>(value.toInt()));
		break;
	case MapDocument::ChangedPropertyId::RenderOrderChangedId:
		mMap->setRenderOrder(static_cast<Map::RenderOrder>(value.toInt()));
		break;
	case MapDocument::ChangedPropertyId::TileSizeChangedId:
		mMap->setTileSize(value.toSize());
		break;
	default:
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/

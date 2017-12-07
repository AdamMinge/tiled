/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "changetilesetproperty.h"
#include "mapdocument.h"
#include "tileset.h"
/*-----------------------------------------------------------------------------------------------------------*/
ChangedTilesetProperty::ChangedTilesetProperty(MapDocument* mapDocument, Tileset* tileset, 
	const QString& newName, Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mTileset(tileset),
	mProperty(MapDocument::ChangedPropertyId::NameChangedId),
	mNewValue(newName),
	mPreviousValue(mTileset->name())
{
	setText(QCoreApplication::translate("Undo Commands", "Set Tileset Name"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangedTilesetProperty::undo()
{
	setValue(mPreviousValue);
	emit mMapDocument->tilesetChanged(mTileset, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangedTilesetProperty::redo()
{
	setValue(mNewValue);
	emit mMapDocument->tilesetChanged(mTileset, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ChangedTilesetProperty::canMergeWith(const Command* other) const
{
	auto changeTilesetProperty = static_cast<const ChangedTilesetProperty*>(other);

	if (mMapDocument != changeTilesetProperty->mMapDocument ||
		mTileset != changeTilesetProperty->mTileset ||
		mProperty != changeTilesetProperty->mProperty) return false;
	
	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangedTilesetProperty::mergeWith(const Command* other)
{
	auto changeTilesetProperty = static_cast<const ChangedTilesetProperty*>(other);
	mNewValue = changeTilesetProperty->mNewValue;
}
/*-----------------------------------------------------------------------------------------------------------*/
int ChangedTilesetProperty::id() const
{
	return CommandId::ChangeTilesetPropertyId;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangedTilesetProperty::setValue(const QVariant& value)
{
	switch (mProperty)
	{
	case MapDocument::ChangedPropertyId::NameChangedId:
		mTileset->setName(value.toString());
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/

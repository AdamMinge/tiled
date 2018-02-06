/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "changetilesetproperty.h"
#include "tilesetdocument.h"
#include "tileset.h"
/*-----------------------------------------------------------------------------------------------------------*/
ChangedTilesetProperty::ChangedTilesetProperty(TilesetDocument* tilesetDocument, Tileset* tileset,
	const QString& newName, Command* parent) :
	Command(parent),
	mTilesetDocument(tilesetDocument),
	mTileset(tileset),
	mProperty(TilesetDocument::ChangedPropertyId::NameChangedId),
	mNewValue(newName),
	mPreviousValue(mTileset->name())
{
	setText(QCoreApplication::translate("Undo Commands", "Set Tileset Name"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangedTilesetProperty::undo()
{
	setValue(mPreviousValue);
	emit mTilesetDocument->tilesetChanged(mTileset, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangedTilesetProperty::redo()
{
	setValue(mNewValue);
	emit mTilesetDocument->tilesetChanged(mTileset, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ChangedTilesetProperty::canMergeWith(const Command* other) const
{
	const auto changeTilesetProperty = static_cast<const ChangedTilesetProperty*>(other);

	if (mTilesetDocument != changeTilesetProperty->mTilesetDocument ||
		mTileset != changeTilesetProperty->mTileset ||
		mProperty != changeTilesetProperty->mProperty) return false;
	
	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangedTilesetProperty::mergeWith(const Command* other)
{
	const auto changeTilesetProperty = static_cast<const ChangedTilesetProperty*>(other);
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
	case TilesetDocument::ChangedPropertyId::NameChangedId:
		mTileset->setName(value.toString());
		break;
	default:
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/

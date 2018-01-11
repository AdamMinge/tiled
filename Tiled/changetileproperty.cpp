/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "changetileproperty.h"
#include "mapdocument.h"
#include "frame.h"
#include "tile.h"
/*-----------------------------------------------------------------------------------------------------------*/
Q_DECLARE_METATYPE(QVector<Frame>)
/*-----------------------------------------------------------------------------------------------------------*/
ChangeTileProperty::ChangeTileProperty(MapDocument* mapDocument, Tile* tile,
	const QVector<Frame>& frames, Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mTile(tile),
	mProperty(MapDocument::ChangedPropertyId::AnimationChangedId),
	mNewValue(QVariant::fromValue(frames)),
	mPreviousValue(QVariant::fromValue(tile->frames()))
{
	setText(QCoreApplication::translate("Undo Commands", "Changed Tile Animation"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeTileProperty::undo()
{
	mTile->setFrames(mPreviousValue.value<QVector<Frame>>());
	emit mMapDocument->tileChanged(mTile, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeTileProperty::redo()
{
	mTile->setFrames(mNewValue.value<QVector<Frame>>());
	emit mMapDocument->tileChanged(mTile, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ChangeTileProperty::canMergeWith(const Command* other) const
{
	const auto changeTileProperty = static_cast<const ChangeTileProperty*>(other);

	if (changeTileProperty->mMapDocument == mMapDocument &&
		changeTileProperty->mTile == mTile) return true;
	
	return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeTileProperty::mergeWith(const Command* other)
{
	const auto changeTileProperty = static_cast<const ChangeTileProperty*>(other);
	mNewValue = changeTileProperty->mNewValue;
}
/*-----------------------------------------------------------------------------------------------------------*/
int ChangeTileProperty::id() const
{
	return CommandId::ChangeTilePropertyId;
}
/*-----------------------------------------------------------------------------------------------------------*/

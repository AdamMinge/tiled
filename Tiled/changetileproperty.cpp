﻿/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "changetileproperty.h"
#include "tilesetdocument.h"
#include "frame.h"
#include "tile.h"
/*-----------------------------------------------------------------------------------------------------------*/
Q_DECLARE_METATYPE(QVector<Frame>)
/*-----------------------------------------------------------------------------------------------------------*/
ChangeTileProperty::ChangeTileProperty(TilesetDocument* tilesetDocument, Tile* tile,
	const QVector<Frame>& frames, Command* parent) :
	Command(parent),
	mTilesetDocument(tilesetDocument),
	mTile(tile),
	mProperty(TilesetDocument::ChangedPropertyId::AnimationChangedId),
	mNewValue(QVariant::fromValue(frames)),
	mPreviousValue(QVariant::fromValue(tile->frames()))
{
	setText(QCoreApplication::translate("Undo Commands", "Changed Tile Animation"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeTileProperty::undo()
{
	mTile->setFrames(mPreviousValue.value<QVector<Frame>>());
	emit mTilesetDocument->tileChanged(mTile, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ChangeTileProperty::redo()
{
	mTile->setFrames(mNewValue.value<QVector<Frame>>());
	emit mTilesetDocument->tileChanged(mTile, mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ChangeTileProperty::canMergeWith(const Command* other) const
{
	const auto changeTileProperty = static_cast<const ChangeTileProperty*>(other);

	if (changeTileProperty->mTilesetDocument == mTilesetDocument &&
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

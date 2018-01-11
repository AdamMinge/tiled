﻿/*-----------------------------------------------------------------------------------------------------------*/
#include "tilepreview.h"
#include "tileanimationdriver.h"
#include "mapdocument.h"
#include "tileset.h"
#include "frame.h"
#include "tile.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilePreview::TilePreview(QWidget* parent) :
	QLabel(parent),
	mAnimationDriver(new TileAnimationDriver(this)),
	mPreviewFrameIndex(0),
	mPreviewUnusedTime(0),
	mTile(nullptr),
	mMapDocument(nullptr)
{
	connect(mAnimationDriver, &TileAnimationDriver::update, 
		this, &TilePreview::advancePreviewAnimation);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilePreview::setMapDocument(MapDocument* mapDocument)
{
	if (mMapDocument)
	{
		mMapDocument->disconnect(this);
	}

	mMapDocument = mapDocument;

	if (mMapDocument)
	{
		connect(mMapDocument, &MapDocument::tileChanged,
			this, &TilePreview::tileChanged);
		connect(mMapDocument, &MapDocument::currentTileChanged,
			this, &TilePreview::setTile);
	}

	setTile(mMapDocument ? mMapDocument->currentTile() : nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilePreview::showEvent(QShowEvent* event)
{
	Q_UNUSED(event);
	mAnimationDriver->start();
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilePreview::hideEvent(QHideEvent* event)
{
	Q_UNUSED(event);
	mAnimationDriver->stop();
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilePreview::resetPreview()
{
	mPreviewFrameIndex = 0;
	mPreviewUnusedTime = 0;

	if(mTile && mTile->isAnimated())
	{
		const auto tileId = mTile->frames().first().tileId();
		auto tileset = mTile->tileset();
		Q_ASSERT(tileset);
		
		auto tile = tileset->tile(tileId);
		Q_ASSERT(tile);

		setPixmap(tile->image());	
	}
	else
	{
		setPixmap(QPixmap());
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilePreview::advancePreviewAnimation(int ms)
{
	if (!mTile || !mTile->isAnimated()) return;

	mPreviewUnusedTime += ms;

	decltype(auto) frames = mTile->frames();
	auto frame = frames.at(mPreviewFrameIndex);
	const auto previousTileId = frame.tileId();

	while (frame.duration() > 0 && mPreviewUnusedTime > frame.duration()) 
	{
		mPreviewUnusedTime -= frame.duration();
		mPreviewFrameIndex = (mPreviewFrameIndex + 1) % frames.size();

		frame = frames.at(mPreviewFrameIndex);
	}

	if (previousTileId != frame.tileId()) 
	{
		auto tileset = mTile->tileset();
		Q_ASSERT(tileset);

		auto tile = tileset->tile(frame.tileId());
		Q_ASSERT(tile);

		setPixmap(tile->image());
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilePreview::setTile(Tile* tile)
{
	mTile = tile;
	resetPreview();
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilePreview::tileChanged(Tile* tile, int changedPropertyId)
{
	if (mTile != tile) return;
	if (changedPropertyId != MapDocument::ChangedPropertyId::AnimationChangedId) return;

	resetPreview();
}
/*-----------------------------------------------------------------------------------------------------------*/

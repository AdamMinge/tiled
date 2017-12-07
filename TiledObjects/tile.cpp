/*-----------------------------------------------------------------------------------------------------------*/
#include "tile.h"
#include "tileset.h"
#include "frame.h"
/*-----------------------------------------------------------------------------------------------------------*/
Tile::Tile(Tileset* tileset, const QPixmap& image, int id) :
	Object(ObjectType::TileType),
	mTileset(tileset),
	mImage(image),
	mId(id),
	mCurrentFrameIndex(0),
	mUnusedTime(0)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
Tile::~Tile() = default;
/*-----------------------------------------------------------------------------------------------------------*/
const QPixmap& Tile::image() const
{
	return mImage;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Tile::setImage(const QPixmap& image)
{
	mImage = image;
}
/*-----------------------------------------------------------------------------------------------------------*/
const Tile* Tile::currentFrameTile() const
{
	if (isAnimated()) 
	{
		return mTileset->tile(
			mFrames.at(mCurrentFrameIndex).tileId());
	}
	return this;
}
/*-----------------------------------------------------------------------------------------------------------*/
int Tile::width() const
{
	return mImage.width();
}
/*-----------------------------------------------------------------------------------------------------------*/
int Tile::height() const
{
	return mImage.height();
}
/*-----------------------------------------------------------------------------------------------------------*/
QSize Tile::size() const
{
	return mImage.size();
}
/*-----------------------------------------------------------------------------------------------------------*/
int Tile::id() const
{ 
	return mId;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QVector<Frame>& Tile::frames() const
{
	return mFrames;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Tile::setFrames(const QVector<Frame>& frames)
{
	resetAnimation();
	mFrames = frames;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Tile::isAnimated() const
{
	return !mFrames.isEmpty();
}
/*-----------------------------------------------------------------------------------------------------------*/
int Tile::currentFrameIndex() const
{
	return mCurrentFrameIndex;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Tile::resetAnimation()
{
	if (!isAnimated()) return false;

	auto previousFrame = mFrames.at(mCurrentFrameIndex);
	auto currentFrame = mFrames.at(0);

	mCurrentFrameIndex = 0;
	mUnusedTime = 0;

	return previousFrame.tileId() != currentFrame.tileId();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Tile::advanceAnimation(int ms)
{
	if (!isAnimated()) return false;

	mUnusedTime += ms;

	auto frame = mFrames.at(mCurrentFrameIndex);
	const auto previousTileId = frame.tileId();

	while (frame.duration() > 0 && mUnusedTime > frame.duration()) {
		mUnusedTime -= frame.duration();
		mCurrentFrameIndex = (mCurrentFrameIndex + 1) % mFrames.size();

		frame = mFrames.at(mCurrentFrameIndex);
	}

	return previousTileId != frame.tileId();
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* Tile::tileset() const
{
	return mTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
Tile* Tile::clone(Tileset* tileset) const
{
	auto cloneTile = new Tile(tileset, mImage, mId);
	cloneTile->setProperties(properties());

	cloneTile->mFrames = mFrames;
	cloneTile->mCurrentFrameIndex = mCurrentFrameIndex;
	cloneTile->mUnusedTime = mUnusedTime;

	return cloneTile;
}
/*-----------------------------------------------------------------------------------------------------------*/

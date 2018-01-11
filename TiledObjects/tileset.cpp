/*-----------------------------------------------------------------------------------------------------------*/
#include <QBitmap>
#include "tileset.h"
#include "tile.h"
/*-----------------------------------------------------------------------------------------------------------*/
Tileset::Tileset(const QString& name, const ImageReference& imageReference,
	const QSize& tileSize, int spacing, int margin) :
	Object(ObjectType::TilesetType),
	mName(name),
	mImageReference(imageReference),
	mTileSize(tileSize),
	mSpacing(spacing),
	mMargin(margin),
	mColumnCount(0),
	mRowCount(0),
	mValid(false)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset::~Tileset()
{
	qDeleteAll(mTiles);
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& Tileset::name() const 
{
	return mName;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Tileset::setName(const QString& name)
{
	mName = name;
}
/*-----------------------------------------------------------------------------------------------------------*/
const ImageReference& Tileset::imageReference() const 
{
	return mImageReference;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Tileset::setImageReference(const ImageReference& imageReference)
{
	if (mImageReference == imageReference) return;

	mImageReference = imageReference;
	mValid = false;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QSize& Tileset::tileSize() const 
{
	return mTileSize;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Tileset::setTileSize(const QSize& tileSize)
{
	if (mTileSize == tileSize) return;

	mTileSize = tileSize;
	mValid = false;
}
/*-----------------------------------------------------------------------------------------------------------*/
int Tileset::spacing() const 
{
	return mSpacing;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Tileset::setSpacing(int spacing)
{
	if (mSpacing == spacing) return;

	mSpacing = spacing;
	mValid = false;
}
/*-----------------------------------------------------------------------------------------------------------*/
int Tileset::margin() const 
{
	return mMargin;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Tileset::setMargin(int margin)
{
	if (mMargin == margin) return;

	mMargin = margin;
	mValid = false;
}
/*-----------------------------------------------------------------------------------------------------------*/
Tile* Tileset::tile(int id) const
{
	return mTiles[id];
}
/*-----------------------------------------------------------------------------------------------------------*/
int Tileset::tileCount() const
{
	return mTiles.size();
}
/*-----------------------------------------------------------------------------------------------------------*/
int Tileset::columnCount() const 
{
	return mColumnCount;
}
/*-----------------------------------------------------------------------------------------------------------*/
int Tileset::rowCount() const 
{ 
	return mRowCount;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Tileset::contains(Tile* tile) const
{
	auto list = mTiles.values();
	return list.contains(tile);
}
/*-----------------------------------------------------------------------------------------------------------*/
void Tileset::loadTileset()
{
	Q_ASSERT(mTileSize.width() > 0 && mTileSize.height() > 0);
	Q_ASSERT(mSpacing >= 0 && mMargin >= 0);
	Q_ASSERT(mImageReference.hasImage());

	const auto image = mImageReference.createImage();
	if (image.isNull()) return;

	auto tileNum = 0;
	for(auto y = mMargin; y <= image.height() - mTileSize.height(); y += mTileSize.height() + mSpacing)
	{
		for(auto x = mMargin; x <= image.width() - mTileSize.width(); x += mTileSize.width() + mSpacing)
		{
			const auto tileImage = image.copy(x, y, mTileSize.width(), mTileSize.height());
			auto tilePixmap = QPixmap::fromImage(tileImage);

			if(mImageReference.hasTransparent())
			{
				const auto mask = tileImage.createMaskFromColor(mImageReference.transparentColor().rgb());
				tilePixmap.setMask(QBitmap::fromImage(mask));
			}

			auto it = mTiles.find(tileNum);
			
			if (it != mTiles.end()) it.value()->setImage(tilePixmap);
			else mTiles[tileNum] = new Tile(this, tilePixmap, tileNum);

			++tileNum;
		}
	}

	for (decltype(auto) tile : mTiles) 
	{
		if (tile->id() >= tileNum)
		{
			auto tilePixmap = QPixmap(mTileSize);
			tilePixmap.fill();
			tile->setImage(tilePixmap);
		}
	}

	const auto columnCount = ((image.width() - mMargin + mSpacing) / (mTileSize.width() + mSpacing));

	mColumnCount = columnCount;
	Q_ASSERT(mColumnCount > 0);

	mRowCount = mTiles.size() / mColumnCount;
	mRowCount += ((mTiles.size() % mColumnCount > 0) ? 1 : 0);
	Q_ASSERT(mRowCount > 0);

	mValid = true;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Tileset::isValid() const
{
	return mValid;
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* Tileset::clone() const
{
	auto cloneTileset = new Tileset(mName, mImageReference, mTileSize, mSpacing, mMargin);
	cloneTileset->setProperties(properties());
	cloneTileset->mValid = mValid;

	QMapIterator<int, Tile*> iter(mTiles);

	while(iter.hasNext())
	{
		iter.next();

		auto id = iter.key();
		const auto tile = iter.value()->clone(cloneTileset);

		cloneTileset->mTiles[id] = tile;
	}

	return cloneTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QPixmap>
#include "Object.h"
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Tileset;
class Frame;
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT Tile : public Object
{
public:
	explicit Tile(Tileset* tileset, const QPixmap &image, int id);
	~Tile() override;

	Tile(Tile&&) = delete;
	Tile(const Tile&) = delete;

	Tile& operator=(Tile&&) = delete;
	Tile& operator=(const Tile&) = delete;

	const QPixmap& image() const;
	void setImage(const QPixmap& image);

	const Tile *currentFrameTile() const;

	int width() const;
	int height() const;
	QSize size() const;

	int id() const;

	const QVector<Frame> &frames() const;
	void setFrames(const QVector<Frame> &frames);
	bool isAnimated() const;
	int currentFrameIndex() const;
	bool resetAnimation();
	bool advanceAnimation(int ms);

	Tileset* tileset() const;

	Tile* clone(Tileset* tileset) const;

private:
	Tileset* mTileset;
	QPixmap mImage;
	const int mId;	

	QVector<Frame> mFrames;
	int mCurrentFrameIndex;
	int mUnusedTime;
};
/*-----------------------------------------------------------------------------------------------------------*/

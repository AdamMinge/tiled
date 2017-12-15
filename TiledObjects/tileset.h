/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "Object.h"
#include "imagereference.h"
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Tile;
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT Tileset : public Object
{
public:
	explicit Tileset(const QString& name, const ImageReference& imageReference,
		const QSize& tileSize, int spacing, int margin);
	~Tileset() override;

	Tileset(Tileset&&) = delete;
	Tileset(const Tileset&) = delete;

	Tileset& operator=(Tileset&&) = delete;
	Tileset& operator=(const Tileset&) = delete;

	const QString& name() const;
	void setName(const QString& name);

	const ImageReference& imageReference() const;
	void setImageReference(const ImageReference& imageReference);

	const QSize& tileSize() const;
	void setTileSize(const QSize& tileSize);

	int spacing() const;
	void setSpacing(int spacing);

	int margin() const;
	void setMargin(int marign);

	Tile* tile(int id) const;
	int tileCount() const;

	int columnCount() const;
	int rowCount() const;

	bool contains(Tile* tile) const;

	void loadTileset();
	bool isValid();

	Tileset* clone() const;

private:
	QString mName;
	ImageReference mImageReference;
	QMap<int, Tile*> mTiles;

	QSize mTileSize;
	int mSpacing;
	int mMargin;

	int mColumnCount;
	int mRowCount;

	bool mValid;
};
/*-----------------------------------------------------------------------------------------------------------*/
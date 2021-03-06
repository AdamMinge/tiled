﻿/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QLabel>
/*-----------------------------------------------------------------------------------------------------------*/
class TileAnimationDriver;
class TilesetDocument;
class MapDocument;
class Document;
class Tile;
/*-----------------------------------------------------------------------------------------------------------*/
class TilePreview final : public QLabel
{
	Q_OBJECT

public:
	explicit TilePreview(QWidget* parent = nullptr);
	~TilePreview() override = default;

	TilePreview(const TilePreview&) = delete;
	TilePreview(TilePreview&&) = delete;

	TilePreview& operator=(const TilePreview&) = delete;
	TilePreview& operator=(TilePreview&&) = delete;

	void setMapDocument(MapDocument* mapDocument);
	void setTilesetDocument(TilesetDocument* mapDocument);
	Document* document() const;

	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;

private slots:
	void resetPreview();
	void advancePreviewAnimation(int ms);

	void setTile(Tile* tile);
	void tileChanged(Tile *tile, int changedPropertyId);

private:
	TileAnimationDriver* mAnimationDriver;
	int mPreviewFrameIndex;
	int mPreviewUnusedTime;

	Tile* mTile;
	Document* mDocument;
};
/*-----------------------------------------------------------------------------------------------------------*/
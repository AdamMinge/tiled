/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QVariant>
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetDocument;
class Tile;
class Frame;
/*-----------------------------------------------------------------------------------------------------------*/
class ChangeTileProperty final : public Command
{
public:
	explicit ChangeTileProperty(TilesetDocument* tilesetDocument, Tile* tile,
		const QVector<Frame>& frames, Command* parent = nullptr);
	~ChangeTileProperty() override = default;

	ChangeTileProperty(ChangeTileProperty&&) = delete;
	ChangeTileProperty(const ChangeTileProperty&) = delete;

	ChangeTileProperty& operator=(ChangeTileProperty&&) = delete;
	ChangeTileProperty& operator=(const ChangeTileProperty&) = delete;

	void undo() override;
	void redo() override;

	int id() const override;

	bool canMergeWith(const Command* other) const override;
	void mergeWith(const Command* other) override;

private:
	TilesetDocument * mTilesetDocument;
	Tile* mTile;
	int mProperty;
	QVariant mNewValue;
	QVariant mPreviousValue;
};
/*-----------------------------------------------------------------------------------------------------------*/
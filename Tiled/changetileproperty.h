/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QVariant>
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocument;
class Tile;
class Frame;
/*-----------------------------------------------------------------------------------------------------------*/
class ChangeTileProperty final : public Command
{
public:
	explicit ChangeTileProperty(MapDocument* mapDocument, Tile* tile,
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
	MapDocument* mMapDocument;
	Tile* mTile;
	int mProperty;
	QVariant mNewValue;
	QVariant mPreviousValue;
};
/*-----------------------------------------------------------------------------------------------------------*/
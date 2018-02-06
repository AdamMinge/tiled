/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QVariant>
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetDocument;
class Tileset;
/*-----------------------------------------------------------------------------------------------------------*/
class ChangedTilesetProperty final : public Command
{
public:
	explicit ChangedTilesetProperty(TilesetDocument* tilesetDocument, Tileset* tileset,
		const QString& newName, Command* parent = nullptr);

	~ChangedTilesetProperty() override = default;

	ChangedTilesetProperty(ChangedTilesetProperty&&) = delete;
	ChangedTilesetProperty(const ChangedTilesetProperty&) = delete;

	ChangedTilesetProperty& operator=(ChangedTilesetProperty&&) = delete;
	ChangedTilesetProperty& operator=(const ChangedTilesetProperty&) = delete;

	void undo() override;
	void redo() override;

	int id() const override;

	bool canMergeWith(const Command* other) const override;
	void mergeWith(const Command* other) override;

private:
	void setValue(const QVariant& value);

private:
	TilesetDocument * mTilesetDocument;
	Tileset* mTileset;
	int mProperty;
	QVariant mNewValue;
	QVariant mPreviousValue;
};
/*-----------------------------------------------------------------------------------------------------------*/
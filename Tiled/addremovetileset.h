/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocument;
class Tileset;
/*-----------------------------------------------------------------------------------------------------------*/
class AddRemoveTileset abstract : public Command
{
public:
	explicit AddRemoveTileset(MapDocument* mapDocument, int index,
		Tileset* tileset, Command* parent = nullptr);
	virtual ~AddRemoveTileset() override;

	AddRemoveTileset(AddRemoveTileset&&) = delete;
	AddRemoveTileset(const AddRemoveTileset&) = delete;

	AddRemoveTileset& operator=(AddRemoveTileset&&) = delete;
	AddRemoveTileset& operator=(const AddRemoveTileset&) = delete;

protected:
	void addTileset();
	void removeTileset();

private:
	MapDocument* mMapDocument;
	Tileset* mTileset;
	int mIndex;
};
/*-----------------------------------------------------------------------------------------------------------*/
class AddTileset final : public AddRemoveTileset
{
public:
	explicit AddTileset(MapDocument* mapDocument, Tileset* tileset, Command* parent = nullptr);
	~AddTileset() override = default;

	void undo() override;
	void redo() override;
};
/*-----------------------------------------------------------------------------------------------------------*/
class RemoveTileset final : public AddRemoveTileset
{
public:
	explicit RemoveTileset(MapDocument* mapDocument, int index, Command* parent = nullptr);
	~RemoveTileset() override = default;

	void undo() override;
	void redo() override;
};
/*-----------------------------------------------------------------------------------------------------------*/

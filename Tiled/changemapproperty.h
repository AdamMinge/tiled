/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "command.h"
#include "map.h"
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocument;
/*-----------------------------------------------------------------------------------------------------------*/
class ChangeMapProperty final : public Command
{
public:
	explicit ChangeMapProperty(MapDocument* mapDocument, Map::Orientation newOrientation, Command* parent = nullptr);
	explicit ChangeMapProperty(MapDocument* mapDocument, Map::RenderOrder newRenderOrder, Command* parent = nullptr);
	explicit ChangeMapProperty(MapDocument* mapDocument, const QSize& newTileSize, Command* parent = nullptr);

	~ChangeMapProperty() override = default;

	ChangeMapProperty(ChangeMapProperty&&) = delete;
	ChangeMapProperty(const ChangeMapProperty&) = delete;

	ChangeMapProperty& operator=(ChangeMapProperty&&) = delete;
	ChangeMapProperty& operator=(const ChangeMapProperty&) = delete;

	void undo() override;
	void redo() override;

	int id() const override;

	bool canMergeWith(const Command* other) const override;
	void mergeWith(const Command* other) override;

private:
	void setValue(const QVariant& value);

private:
	MapDocument* mMapDocument;
	Map* mMap;
	int mProperty;
	QVariant mNewValue;
	QVariant mPreviousValue;
};
/*-----------------------------------------------------------------------------------------------------------*/

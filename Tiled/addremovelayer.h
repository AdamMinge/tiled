/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocument;
class GroupLayer;
class Layer;
/*-----------------------------------------------------------------------------------------------------------*/
class AddRemoveLayer abstract : public Command
{
public:
	explicit AddRemoveLayer(MapDocument* mapDocument, 
		Layer* layer, int index, GroupLayer* parentLayer, Command* parent = nullptr);
	virtual ~AddRemoveLayer() override;

	AddRemoveLayer(AddRemoveLayer&&) = delete;
	AddRemoveLayer(const AddRemoveLayer&) = delete;

	AddRemoveLayer& operator=(AddRemoveLayer&&) = delete;
	AddRemoveLayer& operator=(const AddRemoveLayer&) = delete;

protected:
	void addLayer();
	void removeLayer();

private:
	MapDocument* mMapDocument;
	Layer* mLayer;
	GroupLayer *mParentLayer;
	int mIndex;
};
/*-----------------------------------------------------------------------------------------------------------*/
class AddLayer final : public AddRemoveLayer
{
public:
	explicit AddLayer(MapDocument* mapDocument, Layer* layer, GroupLayer* parentLayer, Command* parent = nullptr);
	explicit AddLayer(MapDocument* mapDocument, int index, Layer* layer, GroupLayer* parentLayer, Command* parent = nullptr);
	~AddLayer() override = default;

	void undo() override;
	void redo() override;
};
/*-----------------------------------------------------------------------------------------------------------*/
class RemoveLayer final : public AddRemoveLayer
{
public:
	explicit RemoveLayer(MapDocument* mapDocument, int index, GroupLayer* parentLayer, Command* parent = nullptr);
	~RemoveLayer() override = default;

	void undo() override;
	void redo() override;
};
/*-----------------------------------------------------------------------------------------------------------*/

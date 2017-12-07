/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Layer;
class GroupLayer;
class MapDocument;
/*-----------------------------------------------------------------------------------------------------------*/
class ReparentLayer final : public Command
{
public:
	explicit ReparentLayer(MapDocument* mapDocument, Layer* layer, 
		GroupLayer* newParent, int row, Command* parent = nullptr);
	~ReparentLayer() override = default;

	ReparentLayer(const ReparentLayer&) = delete;
	ReparentLayer(ReparentLayer&&) = delete;

	ReparentLayer& operator=(const ReparentLayer&) = delete;
	ReparentLayer& operator=(ReparentLayer&&) = delete;

	void undo() override;
	void redo() override;

	int id() const override;

	bool canMergeWith(const Command* other) const override;
	void mergeWith(const Command* other) override;

private:
	MapDocument* mMapDocument;
	Layer* mLayer;
	GroupLayer* mNewParent;
	GroupLayer* mPreviousParent;
	int mNewIndex;
	int mPreviousIndex;
};
/*-----------------------------------------------------------------------------------------------------------*/

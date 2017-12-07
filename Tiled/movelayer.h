/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Layer;
class MapDocument;
/*-----------------------------------------------------------------------------------------------------------*/
class MoveLayer final : public Command
{
public:
	enum class Move { Lower, Raise };

public:
	explicit MoveLayer(MapDocument* mapDocument, Layer* layer, Move move, Command* parent = nullptr);
	~MoveLayer() override = default;

	MoveLayer(const MoveLayer&) = delete;
	MoveLayer(MoveLayer&&) = delete;

	MoveLayer& operator=(const MoveLayer&) = delete;
	MoveLayer& operator=(MoveLayer&&) = delete;

	void undo() override;
	void redo() override;

private:
	void moveLayer();

private:
	MapDocument* mMapDocument;
	Layer* mLayer;
	Move mMove;
};
/*-----------------------------------------------------------------------------------------------------------*/

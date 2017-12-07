/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QUndoCommand>
/*-----------------------------------------------------------------------------------------------------------*/
class Command : public QUndoCommand
{
public:
	explicit Command(Command* parent = nullptr);
	virtual ~Command() override = default;

	Command(Command&&) = delete;
	Command(const Command&) = delete;

	Command& operator=(Command&&) = delete;
	Command& operator=(const Command&) = delete;

	bool mergeWith(const QUndoCommand* other) override final;

	virtual bool canMergeWith(const Command* other) const;
	virtual void mergeWith(const Command* other);
};
/*-----------------------------------------------------------------------------------------------------------*/
enum CommandId
{
	SetPropertyId,
	ChangeTilesetPropertyId,
	ChangeMapPropertyId,
	GroupCommandId,
	ChangeTilePropertyId,
	ChangeLayerPropertyId,
	ReparentLayerId
};
/*-----------------------------------------------------------------------------------------------------------*/
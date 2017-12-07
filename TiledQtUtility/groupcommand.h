/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class GroupCommand final : public Command
{
public:
	explicit GroupCommand(const QString& text, QList<Command*> &&commands,
		Command* parent = nullptr);
	~GroupCommand() override;

	GroupCommand(GroupCommand&&) = delete;
	GroupCommand(const GroupCommand&) = delete;

	GroupCommand& operator=(GroupCommand&&) = delete;
	GroupCommand& operator=(const GroupCommand&) = delete;

	void undo() override;
	void redo() override;

	int id() const override;

	bool canMergeWith(const Command* other) const override;
	void mergeWith(const Command* other) override;

private:
	QList<Command*> mCommands;
};
/*-----------------------------------------------------------------------------------------------------------*/

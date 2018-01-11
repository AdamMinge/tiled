/*-----------------------------------------------------------------------------------------------------------*/
#include "groupcommand.h"
/*-----------------------------------------------------------------------------------------------------------*/
GroupCommand::GroupCommand(const QString& text,
	QList<Command*> &&commands, Command* parent) :
	Command(parent),
	mCommands(std::move(commands))
{
	setText(text);
}
/*-----------------------------------------------------------------------------------------------------------*/
GroupCommand::~GroupCommand()
{
	qDeleteAll(mCommands);
}
/*-----------------------------------------------------------------------------------------------------------*/
void GroupCommand::undo()
{
	for (auto iter = mCommands.rbegin(); iter != mCommands.rend(); ++iter)
		(*iter)->undo();
}
/*-----------------------------------------------------------------------------------------------------------*/
void GroupCommand::redo()
{
	for (auto iter = mCommands.begin(); iter != mCommands.end(); ++iter)
		(*iter)->redo();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool GroupCommand::canMergeWith(const Command* other) const
{
	const auto changeTilesetProperty = static_cast<const GroupCommand*>(other);
	if (text() != other->text()) return false;
	if (mCommands.count() != changeTilesetProperty->mCommands.count()) return false;

	QListIterator<Command*> iter(mCommands);
	QListIterator<Command*> iterOther(changeTilesetProperty->mCommands);

	while (iter.hasNext())
	{
		const auto iterValue = iter.next();
		const auto iterOtherValue = iterOther.next();

		if (!iterValue->canMergeWith(iterOtherValue)) return false;
	}

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void GroupCommand::mergeWith(const Command* other)
{
	const auto changeTilesetProperty = static_cast<const GroupCommand*>(other);
	QListIterator<Command*> iter(mCommands);
	QListIterator<Command*> iterOther(changeTilesetProperty->mCommands);

	while (iter.hasNext())
	{
		auto iterValue = iter.next();
		const auto iterOtherValue = iterOther.next();

		iterValue->mergeWith(iterOtherValue);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
int GroupCommand::id() const
{
	return GroupCommandId;
}
/*-----------------------------------------------------------------------------------------------------------*/
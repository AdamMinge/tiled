/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QVariant>
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Document;
class Object;
/*-----------------------------------------------------------------------------------------------------------*/
class SetProperty final : public Command
{
public:
	explicit SetProperty(Document* document, Object* object,
		const QString &name, const QVariant &value, Command *parent = nullptr);
	~SetProperty() override = default;

	SetProperty(SetProperty&&) = delete;
	SetProperty(const SetProperty&) = delete;

	SetProperty& operator=(SetProperty&&) = delete;
	SetProperty& operator=(const SetProperty&) = delete;

	void undo() override;
	void redo() override;

	int id() const override;

	bool canMergeWith(const Command* other) const override;
	void mergeWith(const Command* other) override;

private:
	bool mExisted;
	QVariant mPreviousValue;
	QVariant mNewValue;
	Document* mDocument;;
	Object* mObject;
	QString mName;
};
/*-----------------------------------------------------------------------------------------------------------*/
class RemoveProperty final : public Command
{
public:
	explicit RemoveProperty(Document* document, Object* object,
		const QString &name, Command *parent = nullptr);
	~RemoveProperty() override = default;

	RemoveProperty(RemoveProperty&&) = delete;
	RemoveProperty(const RemoveProperty&) = delete;

	RemoveProperty& operator=(RemoveProperty&&) = delete;
	RemoveProperty& operator=(const RemoveProperty&) = delete;

	void undo() override;
	void redo() override;

private:
	QVariant mPreviousValue;
	Document* mDocument;;
	Object* mObject;
	QString mName;
};
/*-----------------------------------------------------------------------------------------------------------*/
class RenameProperty final : public Command
{
public:
	explicit RenameProperty(Document* document, Object* object,
		const QString& oldName, const QString& newName, Command* parent = nullptr);
	~RenameProperty() override = default;

	RenameProperty(RenameProperty&&) = delete;
	RenameProperty(const RenameProperty&) = delete;

	RenameProperty& operator=(RenameProperty&&) = delete;
	RenameProperty& operator=(const RenameProperty&) = delete;
};
/*-----------------------------------------------------------------------------------------------------------*/
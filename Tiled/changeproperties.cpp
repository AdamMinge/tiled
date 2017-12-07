/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "changeproperties.h"
#include "document.h"
#include "object.h"
/*-----------------------------------------------------------------------------------------------------------*/
static void setProperty(Document* document, Object* object,
	const QString& name, const QVariant& value)
{
	auto hadProperty = object->hasProperty(name);
	object->setProperty(name, value);

	if (hadProperty) emit document->propertyChanged(object, name);
	else emit document->propertyAdded(object, name);
}
/*-----------------------------------------------------------------------------------------------------------*/
static void removeProperty(Document* document, Object* object,
	const QString& name)
{
	object->removeProperty(name);
	emit document->propertyRemoved(object, name);
}
/*-----------------------------------------------------------------------------------------------------------*/
SetProperty::SetProperty(Document* document, Object* object,
	const QString& name, const QVariant& value, Command* parent) :
	Command(parent),
	mExisted(object->hasProperty(name)),
	mPreviousValue(object->property(name)),
	mNewValue(value),
	mDocument(document),
	mObject(object),
	mName(name)
{
	if (mExisted) setText(QCoreApplication::translate("Undo Commands", "Set Property"));
	else setText(QCoreApplication::translate("Undo Commands", "Add Property"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void SetProperty::undo()
{
	if(mExisted) setProperty(mDocument, mObject, mName, mPreviousValue);
	else removeProperty(mDocument, mObject, mName);
}
/*-----------------------------------------------------------------------------------------------------------*/
void SetProperty::redo()
{
	setProperty(mDocument, mObject, mName, mNewValue);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool SetProperty::canMergeWith(const Command* other) const
{
	auto setProperty = static_cast<const SetProperty*>(other);

	if (mDocument != setProperty->mDocument ||
		mObject != setProperty->mObject ||
		mName != setProperty->mName ||
		text() != setProperty->text()) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void SetProperty::mergeWith(const Command* other)
{
	auto setProperty = static_cast<const SetProperty*>(other);
	mNewValue = setProperty->mNewValue;
}
/*-----------------------------------------------------------------------------------------------------------*/
int SetProperty::id() const
{
	return CommandId::SetPropertyId;
}
/*-----------------------------------------------------------------------------------------------------------*/
RemoveProperty::RemoveProperty(Document* document,
	Object* object, const QString& name, Command* parent) :
	Command(parent),
	mPreviousValue(object->property(name)),
	mDocument(document),
	mObject(object),
	mName(name)
{
	setText(QCoreApplication::translate("Undo Commands", "Rename Property"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void RemoveProperty::undo()
{
	setProperty(mDocument, mObject, mName, mPreviousValue);
}
/*-----------------------------------------------------------------------------------------------------------*/
void RemoveProperty::redo()
{
	removeProperty(mDocument, mObject, mName);
}
/*-----------------------------------------------------------------------------------------------------------*/
RenameProperty::RenameProperty(Document* document, Object* object,
	const QString& oldName, const QString& newName, Command* parent) :
	Command(parent)
{
	new RemoveProperty(document, object, oldName, this);
	new SetProperty(document, object, newName, object->property(oldName), this);

	setText(QCoreApplication::translate("Undo Commands", "Rename Property"));
}
/*-----------------------------------------------------------------------------------------------------------*/

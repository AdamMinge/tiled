/*-----------------------------------------------------------------------------------------------------------*/
#include <QUndoStack>
#include "object.h"
#include "document.h"
/*-----------------------------------------------------------------------------------------------------------*/
Document::Document(const QString &fileName, const QString& displayName, DocumentType type, QObject* parent) :
	QObject(parent),
	mFileName(fileName),
	mDisplayName(displayName),
	mType(type),
	mUndoStack(new QUndoStack(this)),
	mCurrentObject(nullptr)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
Document::DocumentType Document::type() const
{
	return mType;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& Document::fileName() const 
{
	return mFileName;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& Document::displayName() const
{
	return mDisplayName;
}
/*-----------------------------------------------------------------------------------------------------------*/
QUndoStack* Document::undoStack() const
{
	Q_ASSERT(mUndoStack);
	return mUndoStack;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Document::setCurrentObject(Object* object)
{
	if (mCurrentObject == object) return;

	mCurrentObject = object;
	emit currentObjectChanged(mCurrentObject);
}
/*-----------------------------------------------------------------------------------------------------------*/
Object* Document::currentObject() const
{
	return mCurrentObject;
}
/*-----------------------------------------------------------------------------------------------------------*/

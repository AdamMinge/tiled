/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QObject>
/*-----------------------------------------------------------------------------------------------------------*/
class QUndoStack;
class Object;
class Properties;
/*-----------------------------------------------------------------------------------------------------------*/
class Document : public QObject
{
	Q_OBJECT

public:
	enum DocumentType
	{
		MapDocumentType,
	};

public:
	explicit Document(const QString &fileName, const QString& displayName, 
		DocumentType type, QObject *parent = nullptr);
	virtual ~Document() override = default;

	Document(Document&&) = delete;
	Document(const Document&) = delete;

	Document& operator=(Document&&) = delete;
	Document& operator=(const Document&) = delete;

	DocumentType type() const;

	const QString& fileName() const;
	const QString& displayName() const;

	QUndoStack* undoStack() const;

	void setCurrentObject(Object* object);
	Object* currentObject() const;

signals:
	void currentObjectChanged(Object* object);

	void propertyAdded(Object* object, const QString& name);
	void propertyRemoved(Object* object, const QString& name);
	void propertyChanged(Object* object, const QString& name);

protected:
	QString mFileName;
	QString mDisplayName;
	DocumentType mType;
	QUndoStack* mUndoStack;

	Object* mCurrentObject;
};
/*-----------------------------------------------------------------------------------------------------------*/

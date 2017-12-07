/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QObject>
/*-----------------------------------------------------------------------------------------------------------*/
class Document;
class QDockWidget;
class DialogWithToggleView;
/*-----------------------------------------------------------------------------------------------------------*/
class Editor : public QObject
{
	Q_OBJECT

public:
	explicit Editor(QObject *parent = nullptr);
	virtual ~Editor() override = default;

	Editor(Editor&&) = delete;
	Editor(const Editor&) = delete;

	Editor& operator=(Editor&&) = delete;
	Editor& operator=(const Editor&) = delete;

	virtual void setCurrentDocument(Document* document) = 0;

	virtual Document* currentDocument() const = 0;
	virtual QWidget* editorWidget() const = 0;

	virtual void saveState() = 0;
	virtual void restoreState() = 0;

	virtual QList<QDockWidget*> dockWidgets() const = 0;
	virtual QList<DialogWithToggleView*> dialogWidgets() const = 0;
};
/*-----------------------------------------------------------------------------------------------------------*/

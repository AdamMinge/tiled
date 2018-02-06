/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QObject>
#include <QHash>
#include <QScopedPointer>
#include "document.h"
#include "editor.h"
/*-----------------------------------------------------------------------------------------------------------*/
class QUndoGroup;
class QTabBar;
class QStackedLayout;
class TilesetDocument;
class Tileset;
/*-----------------------------------------------------------------------------------------------------------*/
class DocumentManager final : public QObject
{
	Q_OBJECT

public:
	static DocumentManager* instance();
	static void deleteInstance();

	DocumentManager(DocumentManager&&) = delete;
	DocumentManager(const DocumentManager&) = delete;

	DocumentManager& operator=(DocumentManager&&) = delete;
	DocumentManager& operator=(const DocumentManager&) = delete;

	QWidget* widget() const;

	void addEditor(Document::DocumentType documentType, Editor* editor);
	void removeEditor(Document::DocumentType documentType);
	void removeAllEditors();

	Editor* editor(Document::DocumentType documentType) const;
	Editor* currentEditor() const;

	void addDocument(Document* document);
	void removeDocument(int index);
	void removeAllDocuments();

	Document* document(int index) const;
	Document* currentDocument() const;

	void switchToDocument(int index);
	bool switchToDocument(Document* document);

	QUndoGroup* undoGroup() const;

	void saveState();
	void restoreState();

	void openTilesetDocument(Tileset* tileset);

signals:
	void currentDocumentChanged(Document* document);
	void documentCloseRequested(int index);

private:
	explicit DocumentManager();
	~DocumentManager() override;

	TilesetDocument* findTilesetDocument(const Tileset* tileset);

private slots:
	void currentIndexChanged();
	void documentTabMoved(int from, int to);

	void tilesetRemoved(Tileset* tileset);

private:
	static DocumentManager* mInstance;

	QList<Document*> mDocuments;
	QHash<Document::DocumentType, Editor*> mEditorForType;

	QScopedPointer<QWidget> mWidget;
	QWidget* mNoEditorWidget;
	QTabBar* mTabBar;
	QStackedLayout *mEditorStack;

	QUndoGroup *mUndoGroup;
};
/*-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
#include <QUndoGroup>
#include <QStackedLayout>
#include <QTabBar>
#include "documentmanager.h"
#include "noeditorwidget.h"
#include "tilesetdocument.h"
#include "mapdocument.h"
#include "tileset.h"
#include "map.h"
/*-----------------------------------------------------------------------------------------------------------*/
DocumentManager* DocumentManager::mInstance = nullptr;
/*-----------------------------------------------------------------------------------------------------------*/
DocumentManager* DocumentManager::instance()
{
	if (!mInstance)
		mInstance = new DocumentManager();

	Q_ASSERT(mInstance);
	return mInstance;
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::deleteInstance()
{
	Q_ASSERT(mInstance);
	delete mInstance;
	mInstance = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
QWidget* DocumentManager::widget() const
{
	return mWidget.data();
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::addEditor(Document::DocumentType documentType, Editor* editor)
{
	Q_ASSERT(!mEditorForType.contains(documentType));

	mEditorForType.insert(documentType, editor);
	mEditorStack->addWidget(editor->editorWidget());
}
/*-----------------------------------------------------------------------------------------------------------*/
Editor* DocumentManager::editor(Document::DocumentType documentType) const
{
	return mEditorForType.value(documentType);
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::removeEditor(Document::DocumentType documentType)
{
	Q_ASSERT(mEditorForType.contains(documentType));
	const auto editor = mEditorForType.take(documentType);
	delete editor;
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::removeAllEditors()
{
	while (!mEditorForType.isEmpty())
		removeEditor(mEditorForType.begin().key());
}
/*-----------------------------------------------------------------------------------------------------------*/
Editor* DocumentManager::currentEditor() const
{
	if (const auto document = currentDocument()) return editor(document->type());
	else return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::addDocument(Document* document)
{
	Q_ASSERT(document);
	Q_ASSERT(!mDocuments.contains(document));

	mDocuments.append(document);
	mUndoGroup->addStack(document->undoStack());

	const auto documentIndex = mTabBar->addTab(document->displayName());
	mTabBar->setTabToolTip(documentIndex, document->fileName());

	if(const auto mapDocument = qobject_cast<MapDocument*>(document))
	{
		connect(mapDocument, &MapDocument::tilesetRemoved, this, &DocumentManager::tilesetRemoved);
	}
	else if(auto tilesetDocument = qobject_cast<TilesetDocument*>(document))
	{
		
	}

	switchToDocument(documentIndex);
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::removeDocument(int index)
{
	auto documentToRemove = document(index);
	Q_ASSERT(documentToRemove);

	mDocuments.removeAt(index);
	mUndoGroup->removeStack(documentToRemove->undoStack());

	mTabBar->removeTab(index);

	if(const auto mapDocument = qobject_cast<MapDocument*>(documentToRemove))
	{
		for(auto tileset : mapDocument->map()->tilesets())
			tilesetRemoved(tileset);
	}

	auto editor = mEditorForType[documentToRemove->type()];
	Q_ASSERT(editor);

	editor->setCurrentDocument(nullptr);

	delete documentToRemove;
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::removeAllDocuments()
{
	while (!mDocuments.isEmpty())
		removeDocument(mTabBar->currentIndex());
}
/*-----------------------------------------------------------------------------------------------------------*/
Document* DocumentManager::document(int index) const
{
	if (mDocuments.count() <= index || index < 0) return nullptr;
	else return mDocuments.at(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
Document* DocumentManager::currentDocument() const
{
	const auto index = mTabBar->currentIndex();
	return document(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::switchToDocument(int index)
{
	mTabBar->setCurrentIndex(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool DocumentManager::switchToDocument(Document* document)
{
	const auto index = mDocuments.indexOf(document);
	
	if (index != -1)
	{
		switchToDocument(index);
		return true;
	}
	else return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
QUndoGroup* DocumentManager::undoGroup() const
{
	return mUndoGroup;
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::saveState()
{
	QHashIterator<Document::DocumentType, Editor*> iterator(mEditorForType);
	while (iterator.hasNext()) iterator.next().value()->saveState();
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::restoreState()
{
	QHashIterator<Document::DocumentType, Editor*> iterator(mEditorForType);
	while (iterator.hasNext()) iterator.next().value()->restoreState();
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::openTilesetDocument(Tileset* tileset)
{
	auto tilesetDocument = findTilesetDocument(tileset);

	if (!tilesetDocument)
		tilesetDocument = new TilesetDocument(tileset);

	if (!switchToDocument(tilesetDocument))
		addDocument(tilesetDocument);
}
/*-----------------------------------------------------------------------------------------------------------*/
DocumentManager::DocumentManager() :
	mWidget(new QWidget),
	mNoEditorWidget(new NoEditorWidget(mWidget.data())),
	mTabBar(new QTabBar(mWidget.data())),
	mEditorStack(new QStackedLayout),
	mUndoGroup(new QUndoGroup(this))
{
	mTabBar->setExpanding(false);
	mTabBar->setDocumentMode(true);
	mTabBar->setTabsClosable(true);
	mTabBar->setMovable(true);
	mTabBar->setContextMenuPolicy(Qt::CustomContextMenu);

	auto *vertical = new QVBoxLayout(mWidget.data());
	vertical->addWidget(mTabBar);
	vertical->setMargin(0);
	vertical->setSpacing(0);
	vertical->addLayout(mEditorStack);

	mEditorStack->addWidget(mNoEditorWidget);

	connect(mTabBar, SIGNAL(currentChanged(int)), this, SLOT(currentIndexChanged()));
	connect(mTabBar, SIGNAL(tabMoved(int, int)), this, SLOT(documentTabMoved(int, int)));
	connect(mTabBar, SIGNAL(tabCloseRequested(int)), this, SIGNAL(documentCloseRequested(int)));
}
/*-----------------------------------------------------------------------------------------------------------*/
DocumentManager::~DocumentManager()
{
	removeAllEditors();
	removeAllDocuments();

	Q_ASSERT(mDocuments.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
TilesetDocument* DocumentManager::findTilesetDocument(const Tileset* tileset)
{
	for(auto document : mDocuments)
	{
		const auto tilesetDocument = qobject_cast<TilesetDocument*>(document);

		if (tilesetDocument && tilesetDocument->tileset() == tileset)
			return tilesetDocument;
	}

	return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::currentIndexChanged()
{
	const auto document = currentDocument();
	auto editor = currentEditor();

	if(document)
	{
		mUndoGroup->setActiveStack(document->undoStack());
	}

	if (editor)
	{
		editor->setCurrentDocument(document);
		mEditorStack->setCurrentWidget(editor->editorWidget());
	}
	else
	{
		mEditorStack->setCurrentWidget(mNoEditorWidget);
	}

	emit currentDocumentChanged(document);
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::documentTabMoved(int from, int to)
{
	mDocuments.move(from, to);
}
/*-----------------------------------------------------------------------------------------------------------*/
void DocumentManager::tilesetRemoved(Tileset* tileset)
{
	const auto tilesetDocument = findTilesetDocument(tileset);

	if (tilesetDocument)
		removeDocument(mDocuments.indexOf(tilesetDocument));
}
/*-----------------------------------------------------------------------------------------------------------*/

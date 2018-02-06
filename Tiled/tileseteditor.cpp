/*-----------------------------------------------------------------------------------------------------------*/
#include <QMainWindow>
#include "undodock.h"
#include "tileseteditor.h"
#include "tilesetdocument.h"
#include "propertiesdock.h"
#include "animationcreatordialog.h"
#include "preferencesmanager.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilesetEditor::TilesetEditor() :
	mCurrentTilesetDocument(nullptr),
	mMainWindow(new QMainWindow),
	mUndoDock(new UndoDock(mMainWindow.data())),
	mPropertiesDock(new PropertiesDock(mMainWindow.data())),
	mAnimationCreator(new AnimationCreatorDialog(mMainWindow.data()))
{
	mMainWindow->setDockOptions(mMainWindow->dockOptions() | QMainWindow::GroupedDragging);
	mMainWindow->setDockNestingEnabled(true);

	mMainWindow->addDockWidget(Qt::LeftDockWidgetArea, mUndoDock);
	mMainWindow->addDockWidget(Qt::LeftDockWidgetArea, mPropertiesDock);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetEditor::setCurrentDocument(Document* document)
{
	auto tilesetDocument = qobject_cast<TilesetDocument*>(document);
	Q_ASSERT(tilesetDocument || !document);

	if (mCurrentTilesetDocument == document) return;

	mCurrentTilesetDocument = tilesetDocument;

	mUndoDock->setStack(document ? document->undoStack() : nullptr);
	mPropertiesDock->setDocument(document);
	mAnimationCreator->setTilesetDocument(tilesetDocument);
}
/*-----------------------------------------------------------------------------------------------------------*/
Document* TilesetEditor::currentDocument() const
{
	return mCurrentTilesetDocument;
}
/*-----------------------------------------------------------------------------------------------------------*/
QWidget* TilesetEditor::editorWidget() const
{
	Q_ASSERT(mMainWindow);
	return mMainWindow.data();
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetEditor::saveState()
{
	PreferencesManager::instance()->setTilesetEditorState(mMainWindow->saveState());
	PreferencesManager::instance()->setTilesetEditorSize(mMainWindow->size());
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetEditor::restoreState()
{
	auto state = PreferencesManager::instance()->tilesetEditorState();
	auto size = PreferencesManager::instance()->tilesetEditorSize();

	if (!size.isEmpty()) mMainWindow->resize(size);
	if (!state.isEmpty()) mMainWindow->restoreState(state);
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<QDockWidget*> TilesetEditor::dockWidgets() const
{
	return QList<QDockWidget*>{ mUndoDock, mPropertiesDock };
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<DialogWithToggleView*> TilesetEditor::dialogWidgets() const
{
	return QList<DialogWithToggleView*>{ mAnimationCreator };
}
/*-----------------------------------------------------------------------------------------------------------*/
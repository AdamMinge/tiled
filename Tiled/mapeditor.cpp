/*-----------------------------------------------------------------------------------------------------------*/
#include <QMainWindow>
#include <QAction>
#include "preferencesmanager.h"
#include "mapeditor.h"
#include "mapdocument.h"
#include "undodock.h"
#include "layerdock.h"
#include "tilesetdock.h"
#include "tilesetsdock.h"
#include "propertiesdock.h"
#include "animationcreatordialog.h"
/*-----------------------------------------------------------------------------------------------------------*/
MapEditor::MapEditor() :
	mCurrentMapDocument(nullptr),
	mMainWindow(new QMainWindow),
	mUndoDock(new UndoDock(mMainWindow.data())),
	mTilesetDock(new TilesetDock(mMainWindow.data())),
	mTilesetsDock(new TilesetsDock(mMainWindow.data())),
	mPropertiesDock(new PropertiesDock(mMainWindow.data())),
	mLayerDock(new LayerDock(mMainWindow.data())),
	mAnimationCreator(new AnimationCreatorDialog(mMainWindow.data()))
{
	mMainWindow->setDockOptions(mMainWindow->dockOptions() | QMainWindow::GroupedDragging);
	mMainWindow->setDockNestingEnabled(true);

	mMainWindow->addDockWidget(Qt::LeftDockWidgetArea, mUndoDock);
	mMainWindow->addDockWidget(Qt::LeftDockWidgetArea, mPropertiesDock);
	mMainWindow->addDockWidget(Qt::RightDockWidgetArea, mLayerDock);
	mMainWindow->addDockWidget(Qt::RightDockWidgetArea, mTilesetDock);
	mMainWindow->addDockWidget(Qt::RightDockWidgetArea, mTilesetsDock);

	mMainWindow->tabifyDockWidget(mTilesetDock, mTilesetsDock);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapEditor::setCurrentDocument(Document* document)
{
	auto mapDocument = qobject_cast<MapDocument*>(document);
	Q_ASSERT(mapDocument || !document);

	if (mCurrentMapDocument == document) return;

	mCurrentMapDocument = mapDocument;

	mUndoDock->setStack(document ? document->undoStack() : nullptr);
	mTilesetDock->setMapDocument(mCurrentMapDocument);
	mTilesetsDock->setMapDocument(mCurrentMapDocument);
	mPropertiesDock->setDocument(document);
	mLayerDock->setMapDocument(mCurrentMapDocument);

	mAnimationCreator->setMapDocument(mCurrentMapDocument);
}
/*-----------------------------------------------------------------------------------------------------------*/
Document* MapEditor::currentDocument() const
{
	return mCurrentMapDocument;
}
/*-----------------------------------------------------------------------------------------------------------*/
QWidget* MapEditor::editorWidget() const
{
	Q_ASSERT(mMainWindow);
	return mMainWindow.data();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapEditor::saveState()
{
	PreferencesManager::instance()->setMapEditorState(mMainWindow->saveState());
	PreferencesManager::instance()->setMapEditorSize(mMainWindow->size());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MapEditor::restoreState()
{
	auto state = PreferencesManager::instance()->mapEditorState();
	auto size = PreferencesManager::instance()->mapEditorSize();

	if (!size.isEmpty()) mMainWindow->resize(size);
	if (!state.isEmpty()) mMainWindow->restoreState(state);
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<QDockWidget*> MapEditor::dockWidgets() const
{
	return QList<QDockWidget*>{mUndoDock, mTilesetDock, mTilesetsDock, mPropertiesDock, mLayerDock};
}
/*-----------------------------------------------------------------------------------------------------------*/
QList<DialogWithToggleView*> MapEditor::dialogWidgets() const
{
	return QList<DialogWithToggleView*>{mAnimationCreator};
}
/*-----------------------------------------------------------------------------------------------------------*/

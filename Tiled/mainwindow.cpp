/*-----------------------------------------------------------------------------------------------------------*/
#include <QUndoGroup>
#include <QCloseEvent>
#include <QDockWidget>
#include <QStyleFactory>
#include <qfileinfo.h>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "documentmanager.h"
#include "preferencesmanager.h"
#include "languagemanager.h"
#include "actionmanager.h"
#include "stylemanager.h"
#include "mapeditor.h"
#include "utils.h"
#include "mapdocument.h"
#include "newmapdialog.h"
#include "dialogwithtoggleview.h"
#include "preferencesdialog.h"
#include "mapditorproxystyle.h"
#include "mapdocumentactionhandler.h"
/*-----------------------------------------------------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	mUi(new Ui::MainWindowClass),
	mDocumentManager(DocumentManager::instance()),
	mMapDocumentActionHandler(MapDocumentActionHandler::instance()),
	mPreferencesManager(PreferencesManager::instance()),
	mLanguageManager(LanguageManager::instance()),
	mActionManager(ActionManager::instance()),
	mStyleManager(StyleManager::instance()),
	mCurrentDocument(nullptr),
	mPreferencesDialog(nullptr),
	mFileMenu(nullptr),
	mEditMenu(nullptr),
	mViewMenu(nullptr),
	mTilesetMenu(nullptr),
	mMapMenu(nullptr),
	mLayerMenu(nullptr)
{
	mUi->setupUi(this);

	menuBar()->addMenu(buildFileMenu());
	menuBar()->addMenu(buildEditMenu());
	menuBar()->addMenu(buildViewMenu());
	menuBar()->addMenu(buildMapMenu());
	menuBar()->addMenu(buildTilesetMenu());
	menuBar()->addMenu(buildLayerMenu());

	mDocumentManager->addEditor(Document::DocumentType::MapDocumentType, new MapEditor);
	setCentralWidget(mDocumentManager->widget());

	connect(mDocumentManager, &DocumentManager::documentCloseRequested, this, &MainWindow::closeDocument);
	connect(mDocumentManager, &DocumentManager::currentDocumentChanged, this, &MainWindow::documentChanged);

	connect(mPreferencesManager, &PreferencesManager::languageChanged,
		mLanguageManager, &LanguageManager::setLanguage);
	connect(mPreferencesManager, &PreferencesManager::translationsDirChanged,
		mLanguageManager, &LanguageManager::setTranslationsDir);
	connect(mPreferencesManager, &PreferencesManager::translationsPrefixChanged,
		mLanguageManager, &LanguageManager::setTranslationsPrefix);

	connect(mLanguageManager, &LanguageManager::languageChanged,
		mPreferencesManager, &PreferencesManager::setLanguage);
	connect(mLanguageManager, &LanguageManager::translationsDirChanged,
		mPreferencesManager, &PreferencesManager::setTranslationsDir);
	connect(mLanguageManager, &LanguageManager::translationsPrefixChanged,
		mPreferencesManager, &PreferencesManager::setTranslationsPrefix);

	connect(mPreferencesManager, &PreferencesManager::styleChanged,
		mStyleManager, &StyleManager::setStyle);

	connect(mStyleManager, &StyleManager::styleChanged,
		mPreferencesManager, &PreferencesManager::setStyle);

	readSettings();
	updateActions();
	retranslateUi();

	loadLanguage();
	loadStyle();
}
/*-----------------------------------------------------------------------------------------------------------*/
MainWindow::~MainWindow()
{
	mDocumentManager->removeAllEditors();
	mDocumentManager->removeAllDocuments();

	MapDocumentActionHandler::deleteInstance();
	ActionManager::deleteInstance();
	PreferencesManager::deleteInstance();
	DocumentManager::deleteInstance();
	LanguageManager::deleteInstance();
	StyleManager::deleteInstance();

	delete mUi;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::closeEvent(QCloseEvent* event)
{
	if (confirmAllSave())
	{
		writeSettings();
		event->accept();
	}
	else
	{
		event->ignore();
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::changeEvent(QEvent* event)
{
	QMainWindow::changeEvent(event);
	switch (event->type()) 
	{
	case QEvent::LanguageChange:
		mUi->retranslateUi(this);
		retranslateUi();
		break;
	case QEvent::WindowStateChange:
		mFullScreen->setChecked(isFullScreen());
		break;
	default:
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::newMap()
{
	NewMapDialog newMapDialog(this);

	auto map = newMapDialog.createMap();
	if (!map) return;

	mDocumentManager->addDocument(new MapDocument(map));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::openDocument()
{

}
/*-----------------------------------------------------------------------------------------------------------*/
bool MainWindow::saveDocument()
{
	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool MainWindow::saveDocumentAs()
{
	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::saveAllDocuments()
{

}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::closeDocument(int index)
{
	if (confirmSave(mDocumentManager->document(index)))
		mDocumentManager->removeDocument(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::closeAllDocuments()
{
	if (confirmAllSave())
		mDocumentManager->removeAllDocuments();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::editPreferences()
{
	if(!mPreferencesDialog)
	{
		mPreferencesDialog = new PreferencesDialog(this);
		mPreferencesDialog->setAttribute(Qt::WA_DeleteOnClose);
	}

	mPreferencesDialog->show();
	mPreferencesDialog->activateWindow();
	mPreferencesDialog->raise();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::updateViewsAndToolbarsMenu()
{
	mViewsAndToolbarsMenu->clear();

	if (auto editor = mDocumentManager->currentEditor()) 
	{
		mViewsAndToolbarsMenu->addSeparator();

		const auto dockWidgets = editor->dockWidgets();
		for (auto dockWidget : dockWidgets)
			mViewsAndToolbarsMenu->addAction(dockWidget->toggleViewAction());

		mViewsAndToolbarsMenu->addSeparator();

		const auto dialogWidgets = editor->dialogWidgets();
		for(auto dialogWidget : dialogWidgets)
			mViewsAndToolbarsMenu->addAction(dialogWidget->toggleViewAction());
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::showTilesetGrid()
{
	mPreferencesManager->setShowTilesetGrid(
		mShowTilesetGrid->isChecked());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::showMapGrid()
{
	mPreferencesManager->setShowMapGrid(
		mShowMapGrid->isChecked());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::showTileAnimations()
{
	mPreferencesManager->setShowTileAnimations(
		mShowTileAnimations->isChecked());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::highlightCurrentLayer()
{
	mPreferencesManager->setHighlightCurrentLayer(
		mHighlightCurrentLayer->isChecked());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::zoomIn()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::zoomOut()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::normalSize()
{
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::fullScreen()
{
	if (mFullScreen->isChecked()) this->showFullScreen();
	else this->showNormal();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::openRecentDocument()
{
	auto action = qobject_cast<QAction*>(sender());
	if (action)
	{
		auto documentFile = action->data().toString();
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::updateRecentDocumentMenu()
{
	auto documentNames = mPreferencesManager->recentDocuments();
	auto countOfVisible = mPreferencesManager->countOfVisibleRecentDocuments();
	auto numRecentFiles = qMin<int>(documentNames.count(), countOfVisible);

	Q_ASSERT(mRecentDocumentActions.size() == countOfVisible);

	for (auto i = 0; i < numRecentFiles; i++)
	{
		mRecentDocumentActions[i]->setText(QFileInfo(documentNames[i]).fileName());
		mRecentDocumentActions[i]->setData(documentNames[i]);
		mRecentDocumentActions[i]->setVisible(true);
	}
	for (auto i = numRecentFiles; i < countOfVisible; i++)
	{
		mRecentDocumentActions[i]->setVisible(false);
	}

	mRecentDocumentsMenu->setEnabled(documentNames.count() > 0);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::updateActions()
{
	auto isDocument = static_cast<bool>(mCurrentDocument);
	auto isMapDocument = static_cast<bool>(qobject_cast<MapDocument*>(mCurrentDocument));

	mSaveDocument->setEnabled(isDocument);
	mSaveDocumentAs->setEnabled(isDocument);
	mSaveAllDocuments->setEnabled(isDocument);
	mCloseDocument->setEnabled(isDocument);
	mCloseAllDocuments->setEnabled(isDocument);
	mViewsAndToolbarsMenu->setEnabled(isDocument);

	mMapMenu->menuAction()->setVisible(isMapDocument);
	mTilesetMenu->menuAction()->setVisible(isMapDocument);
	mLayerMenu->menuAction()->setVisible(isMapDocument);
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::documentChanged(Document* document)
{
	mCurrentDocument = document;

	mMapDocumentActionHandler->setMapDocument(dynamic_cast<MapDocument*>(mCurrentDocument));
	updateActions();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::clearRecentDocument()
{
	mPreferencesManager->setRecentDocuments(QStringList());
}
/*-----------------------------------------------------------------------------------------------------------*/
QMenu* MainWindow::buildFileMenu()
{
	Q_ASSERT(!mFileMenu);

	mFileMenu = new QMenu(this);
	mRecentDocumentsMenu = new QMenu(mFileMenu);
	mNewMap = new QAction(mFileMenu);
	mOpenDocument = new QAction(mFileMenu);
	mClearRecentDocuments = new QAction(mRecentDocumentsMenu);
	mSaveDocument = new QAction(mFileMenu);
	mSaveDocumentAs = new QAction(mFileMenu);
	mSaveAllDocuments = new QAction(mFileMenu);
	mCloseDocument = new QAction(mFileMenu);
	mCloseAllDocuments = new QAction(mFileMenu);
	mQuitApplication = new QAction(mFileMenu);


	mNewMap->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-new.png"),
	{ QSize(16,16) }));
	mOpenDocument->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-open.png"),
	{ QSize(16,16) }));
	mClearRecentDocuments->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-clear.png"),
	{ QSize(16,16) }));
	mSaveDocument->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-save.png"),
	{ QSize(16,16) }));
	mSaveDocumentAs->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-save-as.png"),
	{ QSize(16,16) }));
	mCloseDocument->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/window-close.png"),
	{ QSize(16,16) }));
	mQuitApplication->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/application-exit.png"),
	{ QSize(16,16) }));

	auto documentsNames = mPreferencesManager->recentDocuments();
	auto countOfVisible = mPreferencesManager->countOfVisibleRecentDocuments();

	for (auto i = 0; i < countOfVisible; i++)
	{
		auto action = new QAction(this);
		mRecentDocumentsMenu->addAction(action);
		mRecentDocumentActions.push_back(action);

		action->setVisible(false);
		connect(action, &QAction::triggered, this, &MainWindow::openRecentDocument);
	}

	mRecentDocumentsMenu->addSeparator();
	mRecentDocumentsMenu->addAction(mClearRecentDocuments);

	mFileMenu->addAction(mNewMap);
	mFileMenu->addAction(mOpenDocument);
	mFileMenu->addMenu(mRecentDocumentsMenu);
	mFileMenu->addSeparator();
	mFileMenu->addAction(mSaveDocument);
	mFileMenu->addAction(mSaveDocumentAs);
	mFileMenu->addAction(mSaveAllDocuments);
	mFileMenu->addSeparator();
	mFileMenu->addAction(mCloseDocument);
	mFileMenu->addAction(mCloseAllDocuments);
	mFileMenu->addAction(mQuitApplication);

	updateRecentDocumentMenu();

	connect(mPreferencesManager, &PreferencesManager::recentDocumentsChanged,
		this, &MainWindow::updateRecentDocumentMenu);

	connect(mNewMap, &QAction::triggered, this, &MainWindow::newMap);
	connect(mOpenDocument, &QAction::triggered, this, &MainWindow::openDocument);
	connect(mClearRecentDocuments, &QAction::triggered, this, &MainWindow::clearRecentDocument);
	connect(mSaveDocument, &QAction::triggered, this, &MainWindow::saveDocument);
	connect(mSaveDocumentAs, &QAction::triggered, this, &MainWindow::saveDocumentAs);
	connect(mSaveAllDocuments, &QAction::triggered, this, &MainWindow::saveAllDocuments);
	connect(mCloseDocument, &QAction::triggered, this, &MainWindow::closeDocument);
	connect(mCloseAllDocuments, &QAction::triggered, this, &MainWindow::closeAllDocuments);
	connect(mQuitApplication, &QAction::triggered, this, &MainWindow::close);

	mActionManager->registerAction(mNewMap, QLatin1String("MainWindow-NewMap"));

	return mFileMenu;
}
/*-----------------------------------------------------------------------------------------------------------*/
QMenu* MainWindow::buildEditMenu()
{
	Q_ASSERT(!mEditMenu);

	mEditMenu = new QMenu(this);
	auto undoGroup = mDocumentManager->undoGroup();
	mUndo = undoGroup->createUndoAction(mEditMenu);
	mRedo = undoGroup->createRedoAction(mEditMenu);
	mPreferences = new QAction(mEditMenu);

	mRedo->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-redo.png"), 
	{ QSize(24,24) }));
	mUndo->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-undo.png"), 
	{ QSize(24,24) }));

	mEditMenu->addAction(mUndo);
	mEditMenu->addAction(mRedo);
	mEditMenu->addSeparator();
	mEditMenu->addAction(mMapDocumentActionHandler->actionCut());
	mEditMenu->addAction(mMapDocumentActionHandler->actionCut());
	mEditMenu->addAction(mMapDocumentActionHandler->actionPaste());
	mEditMenu->addAction(mMapDocumentActionHandler->actionDelete());
	mEditMenu->addSeparator();
	mEditMenu->addAction(mMapDocumentActionHandler->actionSelectAll());
	mEditMenu->addAction(mMapDocumentActionHandler->actionInvertSelection());
	mEditMenu->addAction(mMapDocumentActionHandler->actionSelectNone());
	mEditMenu->addSeparator();
	mEditMenu->addAction(mPreferences);

	connect(mPreferences, &QAction::triggered, this, &MainWindow::editPreferences);

	return mEditMenu;
}
/*-----------------------------------------------------------------------------------------------------------*/
QMenu* MainWindow::buildViewMenu()
{
	Q_ASSERT(!mViewMenu);

	mViewMenu = new QMenu(this);
	mShowMapGrid = new QAction(mViewMenu);
	mShowTilesetGrid = new QAction(mViewMenu);
	mShowTileAnimations = new QAction(mViewMenu);
	mHighlightCurrentLayer = new QAction(mViewMenu);
	mZoomIn = new QAction(mViewMenu);
	mZoomOut = new QAction(mViewMenu);
	mNormalSize = new QAction(mViewMenu);
	mFullScreen = new QAction(mViewMenu);
	mViewsAndToolbarsMenu = new QMenu(mViewMenu);

	mZoomIn->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/zoom-in.png"),
	{ QSize(16,16) }));
	mZoomOut->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/zoom-out.png"),
	{ QSize(16,16) }));
	mNormalSize->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/zoom-original.png"),
	{ QSize(16,16) }));

	mShowMapGrid->setCheckable(true);
	mShowTilesetGrid->setCheckable(true);
	mShowTileAnimations->setCheckable(true);
	mHighlightCurrentLayer->setCheckable(true);
	mFullScreen->setCheckable(true);

	mViewMenu->addMenu(mViewsAndToolbarsMenu);
	mViewMenu->addSeparator();
	mViewMenu->addAction(mShowMapGrid);
	mViewMenu->addAction(mShowTilesetGrid);
	mViewMenu->addAction(mShowTileAnimations);
	mViewMenu->addAction(mHighlightCurrentLayer);
	mViewMenu->addSeparator();
	mViewMenu->addAction(mZoomIn);
	mViewMenu->addAction(mZoomOut);
	mViewMenu->addAction(mNormalSize);
	mViewMenu->addSeparator();
	mViewMenu->addAction(mFullScreen);
	
	mShowTilesetGrid->setChecked(mPreferencesManager->showTilesetGrid());
	mShowMapGrid->setChecked(mPreferencesManager->showMapGrid());
	mShowTileAnimations->setChecked(mPreferencesManager->showTileAnimations());
	mHighlightCurrentLayer->setChecked(mPreferencesManager->highlightCurrentLayer());
	mFullScreen->setChecked(this->isFullScreen());

	connect(mPreferencesManager, &PreferencesManager::showTilesetGridChanged, 
		mShowTilesetGrid, &QAction::setChecked);
	connect(mPreferencesManager, &PreferencesManager::showMapGridChanged, 
		mShowMapGrid, &QAction::setChecked);
	connect(mPreferencesManager, &PreferencesManager::showTileAnimationsChanged,
		mShowTileAnimations, &QAction::setChecked);
	connect(mPreferencesManager, &PreferencesManager::highlightCurrentLayerChanged, 
		mHighlightCurrentLayer, &QAction::setChecked);

	connect(mViewsAndToolbarsMenu, &QMenu::aboutToShow, this, &MainWindow::updateViewsAndToolbarsMenu);
	connect(mShowMapGrid, &QAction::toggled, this, &MainWindow::showMapGrid);
	connect(mShowTilesetGrid, &QAction::toggled, this, &MainWindow::showTilesetGrid);
	connect(mShowTileAnimations, &QAction::toggled, this, &MainWindow::showTileAnimations);
	connect(mHighlightCurrentLayer, &QAction::toggled, this, &MainWindow::highlightCurrentLayer);
	connect(mZoomIn, &QAction::toggled, this, &MainWindow::zoomIn);
	connect(mZoomOut, &QAction::toggled, this, &MainWindow::zoomOut);
	connect(mNormalSize, &QAction::toggled, this, &MainWindow::normalSize);
	connect(mFullScreen, &QAction::toggled, this, &MainWindow::fullScreen);

	return mViewMenu;
}
/*-----------------------------------------------------------------------------------------------------------*/
QMenu* MainWindow::buildMapMenu()
{
	Q_ASSERT(!mMapMenu);

	mMapMenu = new QMenu(this);
	
	mMapMenu->addAction(mMapDocumentActionHandler->actionResizeMap());
	mMapMenu->addSeparator();
	mMapMenu->addAction(mMapDocumentActionHandler->actionMapProperties());

	return mMapMenu;
}
/*-----------------------------------------------------------------------------------------------------------*/
QMenu* MainWindow::buildTilesetMenu()
{
	Q_ASSERT(!mTilesetMenu);

	mTilesetMenu = new QMenu(this);

	mTilesetMenu->addAction(mMapDocumentActionHandler->actionNewTileset());
	mTilesetMenu->addAction(mMapDocumentActionHandler->actionRemoveTileset());
	mTilesetMenu->addSeparator();
	mTilesetMenu->addAction(mMapDocumentActionHandler->actionTilesetProperties());

	return mTilesetMenu;
}
/*-----------------------------------------------------------------------------------------------------------*/
QMenu* MainWindow::buildLayerMenu()
{
	Q_ASSERT(!mLayerMenu);

	mLayerMenu = new QMenu(this);
	mNewLayerMenu = new QMenu(mLayerMenu);
	mGroupLayerMenu = new QMenu(mLayerMenu);

	mNewLayerMenu->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/document-new.png"),
	{ QSize(16,16) }));

	mLayerMenu->addMenu(mNewLayerMenu);
	mNewLayerMenu->addAction(mMapDocumentActionHandler->actionNewTileLayer());
	mNewLayerMenu->addAction(mMapDocumentActionHandler->actionNewGroupLayer());
	mLayerMenu->addMenu(mGroupLayerMenu);
	mGroupLayerMenu->addAction(mMapDocumentActionHandler->actionGroupLayer());
	mGroupLayerMenu->addAction(mMapDocumentActionHandler->actionUngroupLayer());
	mLayerMenu->addAction(mMapDocumentActionHandler->actionDuplicateLayer());
	mLayerMenu->addAction(mMapDocumentActionHandler->actionMergeLayerUp());
	mLayerMenu->addAction(mMapDocumentActionHandler->actionMergeLayerDown());
	mLayerMenu->addAction(mMapDocumentActionHandler->actionRemoveLayer());
	mLayerMenu->addSeparator();
	mLayerMenu->addAction(mMapDocumentActionHandler->actionSelectNextLayer());
	mLayerMenu->addAction(mMapDocumentActionHandler->actionSelectPreviousLayer());
	mLayerMenu->addAction(mMapDocumentActionHandler->actionRaiseLayer());
	mLayerMenu->addAction(mMapDocumentActionHandler->actionLowerLayer());
	mLayerMenu->addSeparator();
	mLayerMenu->addAction(mMapDocumentActionHandler->actionShowHideAllOtherLayers());
	mLayerMenu->addSeparator();
	mLayerMenu->addAction(mMapDocumentActionHandler->actionLayerProperties());

	return mLayerMenu;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool MainWindow::confirmSave(Document* document)
{
	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool MainWindow::confirmAllSave()
{
	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::writeSettings()
{
	mPreferencesManager->setMainWindowGeometry(saveGeometry());
	mPreferencesManager->setMainWindowState(saveState());

	mDocumentManager->saveState();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::readSettings()
{
	auto geometry = mPreferencesManager->mainWindowGeometry();
	auto state = mPreferencesManager->mainWindowState();

	if (!geometry.isEmpty()) restoreGeometry(geometry);
	if (!state.isEmpty()) restoreState(state);

	mDocumentManager->restoreState();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::retranslateUi()
{
	mNewMap->setText(tr("New Map..."));
	mOpenDocument->setText(tr("Open..."));
	mClearRecentDocuments->setText(tr("Clear Recent Files"));
	mSaveDocument->setText(tr("Save"));
	mSaveDocumentAs->setText(tr("Save As..."));
	mSaveAllDocuments->setText(tr("Save All"));
	mCloseDocument->setText(tr("Close"));
	mCloseAllDocuments->setText(tr("Close All"));
	mQuitApplication->setText(tr("Quit"));
	mFileMenu->setTitle(tr("File"));
	mRecentDocumentsMenu->setTitle(tr("Recent Files"));

	mUndo->setText(tr("Undo"));
	mRedo->setText(tr("Redo"));
	mPreferences->setText(tr("Preferences..."));
	mEditMenu->setTitle(tr("Edit"));

	mShowMapGrid->setText(tr("Show Map Grid"));
	mShowTilesetGrid->setText(tr("Show Tileset Grid"));
	mShowTileAnimations->setText(tr("Show Tile Animations"));
	mHighlightCurrentLayer->setText(tr("Highlight Current Layer"));
	mZoomIn->setText(tr("Zoom In"));
	mZoomOut->setText(tr("Zoom Out"));
	mNormalSize->setText(tr("Normal Size"));
	mFullScreen->setText(tr("Full Screen"));
	mViewMenu->setTitle(tr("View"));
	mViewsAndToolbarsMenu->setTitle(tr("Views and Toolbars"));

	mTilesetMenu->setTitle(tr("Tileset"));
	mMapMenu->setTitle(tr("Map"));

	mLayerMenu->setTitle(tr("Layer"));
	mNewLayerMenu->setTitle(tr("New"));
	mGroupLayerMenu->setTitle(tr("Group"));

	mMapDocumentActionHandler->retranslateUi();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::loadLanguage()
{
	mLanguageManager->setTranslationsDir(mPreferencesManager->translationsDir());
	mLanguageManager->setTranslationsPrefix(mPreferencesManager->translationsPrefix());
	mLanguageManager->setLanguage(mPreferencesManager->language());
}
/*-----------------------------------------------------------------------------------------------------------*/
void MainWindow::loadStyle()
{
	auto styles = QStyleFactory::keys();
	Q_ASSERT(!styles.isEmpty());

	for(decltype(auto) style : styles)
	{
		auto creator = [name = style]() { return QStyleFactory::create(name); };
		mStyleManager->registerStyle(creator, style);
	}

	auto creator = [] { return new MapEitorProxyStyle; };
	mStyleManager->registerStyle(creator, QLatin1String("MapEditor"));

	auto registeredStyles = mStyleManager->availableStyles();
	auto preferencesStyle = mPreferencesManager->style();
	Q_ASSERT(!registeredStyles.isEmpty());
	Q_ASSERT(registeredStyles.contains(preferencesStyle, Qt::CaseInsensitive));
	Q_ASSERT(!preferencesStyle.isEmpty());

	auto iter = std::find_if(registeredStyles.cbegin(), registeredStyles.cend(), 
		[&name = preferencesStyle](auto value) { return name.toLower() == value.toLower(); });

	Q_ASSERT(iter != registeredStyles.end());
	mStyleManager->setStyle(*iter);
}
/*-----------------------------------------------------------------------------------------------------------*/


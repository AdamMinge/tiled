/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QMainWindow>
#include <QPointer>
/*-----------------------------------------------------------------------------------------------------------*/
class DocumentManager;
class MapDocumentActionHandler;
class PreferencesManager;
class PreferencesDialog;
class LanguageManager;
class ActionManager;
class StyleManager;
class Document;
namespace Ui { class MainWindowClass; }
/*-----------------------------------------------------------------------------------------------------------*/
class MainWindow final : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;

	MainWindow(MainWindow&&) = delete;
	MainWindow(const MainWindow&) = delete;

	MainWindow& operator=(MainWindow&&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;

protected:
	void closeEvent(QCloseEvent *event) override;
	void changeEvent(QEvent *event) override;

private slots:
	void newMap();
	void openDocument();
	void openRecentDocument();
	void clearRecentDocument();
	bool saveDocument();
	bool saveDocumentAs();
	void saveAllDocuments();
	void closeDocument(int index);
	void closeAllDocuments();
	void editPreferences();
	void updateViewsAndToolbarsMenu();
	void showTilesetGrid();
	void showMapGrid();
	void showTileAnimations();
	void highlightCurrentLayer();
	void zoomIn();
	void zoomOut();
	void normalSize();
	void fullScreen();
	void updateRecentDocumentMenu();
	void updateActions();
	void documentChanged(Document*  document);

private:
	QMenu* buildFileMenu();
	QMenu* buildEditMenu();
	QMenu* buildViewMenu();
	QMenu* buildMapMenu();
	QMenu* buildTilesetMenu();
	QMenu* buildLayerMenu();

	bool confirmSave(Document* document);
	bool confirmAllSave();

	void writeSettings();
	void readSettings();

	void retranslateUi();

	void loadLanguage();
	void loadStyle();

private:
	Ui::MainWindowClass* mUi;

	DocumentManager* mDocumentManager;
	MapDocumentActionHandler* mMapDocumentActionHandler;
	PreferencesManager* mPreferencesManager;
	LanguageManager* mLanguageManager;
	ActionManager* mActionManager;
	StyleManager* mStyleManager;

	Document* mCurrentDocument;
	QPointer<PreferencesDialog> mPreferencesDialog;

	QVector<QAction*> mRecentDocumentActions;

	QMenu* mFileMenu;
	QMenu* mRecentDocumentsMenu;
	QAction* mNewMap;
	QAction* mOpenDocument;
	QAction* mClearRecentDocuments;
	QAction* mSaveDocument;
	QAction* mSaveDocumentAs;
	QAction* mSaveAllDocuments;
	QAction* mCloseDocument;
	QAction* mCloseAllDocuments;
	QAction* mQuitApplication;

	QMenu* mEditMenu;
	QAction* mUndo;
	QAction* mRedo;
	QAction* mPreferences;

	QMenu* mViewMenu;
	QMenu* mViewsAndToolbarsMenu;
	QAction* mShowMapGrid;
	QAction* mShowTilesetGrid;
	QAction* mShowTileAnimations;
	QAction* mHighlightCurrentLayer;
	QAction* mZoomIn;
	QAction* mZoomOut;
	QAction* mNormalSize;
	QAction* mFullScreen;

	QMenu* mTilesetMenu;
	QMenu* mMapMenu;

	QMenu* mLayerMenu;
	QMenu* mNewLayerMenu;
	QMenu* mGroupLayerMenu;
};
/*-----------------------------------------------------------------------------------------------------------*/

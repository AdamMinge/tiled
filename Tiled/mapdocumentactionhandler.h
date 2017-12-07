/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QObject>
#include <QAction>
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocument;
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocumentActionHandler final : public QObject
{
	Q_OBJECT

public:
	static MapDocumentActionHandler* instance();
	static void deleteInstance();

	MapDocumentActionHandler(MapDocumentActionHandler&&) = delete;
	MapDocumentActionHandler(const MapDocumentActionHandler&) = delete;

	MapDocumentActionHandler& operator=(MapDocumentActionHandler&&) = delete;
	MapDocumentActionHandler& operator=(const MapDocumentActionHandler&) = delete;

	void setMapDocument(MapDocument* mapDocument);
	MapDocument* mapDocument() const;

	void retranslateUi();

	QAction* actionNewTileset();
	QAction* actionRemoveTileset();
	QAction* actionTilesetProperties();
	QAction* actionSelectNextTileset();
	QAction* actionSelectPreviousTileset();

	QAction* actionCut();
	QAction* actionCopy();
	QAction* actionPaste();
	QAction* actionDelete();
	QAction* actionSelectAll();
	QAction* actionInvertSelection();
	QAction* actionSelectNone();

	QAction* actionResizeMap();
	QAction* actionMapProperties();

	QAction* actionNewTileLayer();
	QAction* actionNewGroupLayer();
	QAction* actionGroupLayer();
	QAction* actionUngroupLayer();
	QAction* actionDuplicateLayer();
	QAction* actionMergeLayerDown();
	QAction* actionMergeLayerUp();
	QAction* actionRemoveLayer();
	QAction* actionSelectNextLayer();
	QAction* actionSelectPreviousLayer();
	QAction* actionRaiseLayer();
	QAction* actionLowerLayer();
	QAction* actionShowHideAllOtherLayers();
	QAction* actionLayerProperties();

public slots:
	void newTileset();
	void removeTileset();
	void tilesetProperties();
	void selectNextTileset();
	void selectPreviousTileset();

	void cut();
	void copy();
	void paste();
	void delete_();
	void selectAll();
	void invertSelection();
	void selectNone();

	void resizeMap();
	void mapProperties();

	void newTileLayer();
	void newGroupLayer();
	void groupLayer();
	void ungroupLayer();
	void duplicateLayer();
	void mergeLayerDown();
	void mergeLayerUp();
	void removeLayer();
	void selectNextLayer();
	void selectPreviousLayer();
	void raiseLayer();
	void lowerLayer();
	void showHideAllOtherLayers();
	void layerProperties();

private slots :
	void updateActions();

private:
	explicit MapDocumentActionHandler();
	~MapDocumentActionHandler() = default;

private:
	static MapDocumentActionHandler* mInstance;

	MapDocument* mMapDocument;

	QAction* mNewTileset;
	QAction* mRemoveTileset;
	QAction* mTilesetProperties;
	QAction* mSelectNextTileset;
	QAction* mSelectPreviousTileset;

	QAction* mCut;
	QAction* mCopy;
	QAction* mPaste;
	QAction* mDelete;
	QAction* mSelectAll;
	QAction* mInvertSelection;
	QAction* mSelectNone;

	QAction* mResizeMap;
	QAction* mMapProperties;

	QAction* mNewTileLayer;
	QAction* mNewGroupLayer;
	QAction* mGroupLayer;
	QAction* mUngroupLayer;
	QAction* mDuplicateLayer;
	QAction* mMergeLayerDown;
	QAction* mMergeLayerUp;
	QAction* mRemoveLayer;
	QAction* mSelectNextLayer;
	QAction* mSelectPreviousLayer;
	QAction* mRaiseLayer;
	QAction* mLowerLayer;
	QAction* mShowHideAllOtherLayers;
	QAction* mLayerProperties;
};
/*-----------------------------------------------------------------------------------------------------------*/
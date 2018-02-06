/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDockWidget>
/*-----------------------------------------------------------------------------------------------------------*/
class QTreeView;
class QToolBar;
class MapDocument;
class TilesetListView;
class Tileset;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetListDock final : public QDockWidget
{
	Q_OBJECT

public:
	explicit TilesetListDock(QWidget* parent = nullptr);
	~TilesetListDock() override = default;

	TilesetListDock(TilesetListDock&&) = delete;
	TilesetListDock(const TilesetListDock&) = delete;

	TilesetListDock& operator=(TilesetListDock&&) = delete;
	TilesetListDock& operator=(const TilesetListDock&) = delete;

	void setMapDocument(MapDocument* document);

protected:
	void changeEvent(QEvent* event) override;

private:
	void buildToolBar();
	void retranslateUi();

private:
	MapDocument* mMapDocument;

	TilesetListView* mTilesetsView;
	QToolBar* mToolBar;
};
/*-----------------------------------------------------------------------------------------------------------*/
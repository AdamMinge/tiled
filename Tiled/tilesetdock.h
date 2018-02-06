#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDockWidget>
/*-----------------------------------------------------------------------------------------------------------*/
class QToolBar;
class QTabBar;
class QStackedWidget;
class MapDocument;
class TilesetDocument;
class TilesetView;
class Tileset;
class Tile;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetDock final : public QDockWidget
{
	Q_OBJECT

public:
	explicit TilesetDock(QWidget* parent = nullptr);
	~TilesetDock() override = default;

	TilesetDock(TilesetDock&&) = delete;
	TilesetDock(const TilesetDock&) = delete;

	TilesetDock& operator=(TilesetDock&&) = delete;
	TilesetDock& operator=(const TilesetDock&) = delete;

	void setMapDocument(MapDocument* document);

protected:
	void changeEvent(QEvent* event) override;

private slots:
	void currentTabChanged();
	void currentTilesetChanged(Tileset* tileset);

	void selectionTileChanged();
	void currentTileChanged(const QModelIndex &index);

	void tilesetAdded(Tileset* tileset);
	void tilesetRemoved(Tileset* tileset);

private:
	void buildToolBar();
	void retranslateUi();

	void setupTilesetModel(TilesetView *view, Tileset* tileset);

	Tileset* currentTileset() const;
	TilesetView* currentTilesetView() const;
	TilesetView* tilesetView(int index) const;

private:
	MapDocument* mMapDocument;

	QVector<Tileset*> mTilesets;

	QTabBar* mTabBar;
	QToolBar* mToolBar;
	QStackedWidget* mViewStack;

	bool mUpdating;
};
/*-----------------------------------------------------------------------------------------------------------*/

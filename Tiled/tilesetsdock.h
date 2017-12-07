/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDockWidget>
/*-----------------------------------------------------------------------------------------------------------*/
class QTreeView;
class QToolBar;
class MapDocument;
class TilesetsView;
class Tileset;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetsDock final : public QDockWidget
{
	Q_OBJECT

public:
	explicit TilesetsDock(QWidget* parent = nullptr);
	~TilesetsDock() override = default;

	TilesetsDock(TilesetsDock&&) = delete;
	TilesetsDock(const TilesetsDock&) = delete;

	TilesetsDock& operator=(TilesetsDock&&) = delete;
	TilesetsDock& operator=(const TilesetsDock&) = delete;

	void setMapDocument(MapDocument* document);

protected:
	void changeEvent(QEvent* event) override;

private:
	void buildToolBar();
	void retranslateUi();

private:
	MapDocument* mMapDocument;

	TilesetsView* mTilesetsView;
	QToolBar* mToolBar;
};
/*-----------------------------------------------------------------------------------------------------------*/
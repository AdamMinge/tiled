/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QTreeView>
/*-----------------------------------------------------------------------------------------------------------*/
class ReversingProxyModel;
class MapDocument;
class Tileset;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetListView final : public QTreeView
{
	Q_OBJECT

public:
	explicit TilesetListView(QWidget* parent = nullptr);
	~TilesetListView() = default;

	TilesetListView(const TilesetListView&) = delete;
	TilesetListView(TilesetListView&&) = delete;

	TilesetListView& operator=(const TilesetListView&) = delete;
	TilesetListView& operator=(TilesetListView&&) = delete;

	void setMapDocument(MapDocument* mapDocument);

protected:
	void contextMenuEvent(QContextMenuEvent *event) override;

	private slots:
	void currentTilesetChanged(Tileset* tileset);
	void indexPressed(const QModelIndex& index);
	void currentChanged();

private:
	ReversingProxyModel* mProxyModel;
	MapDocument *mMapDocument;
};
/*-----------------------------------------------------------------------------------------------------------*/

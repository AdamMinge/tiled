/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QTreeView>
/*-----------------------------------------------------------------------------------------------------------*/
class ReversingProxyModel;
class MapDocument;
class Tileset;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetsView final : public QTreeView
{
	Q_OBJECT

public:
	explicit TilesetsView(QWidget* parent = nullptr);
	~TilesetsView() = default;

	TilesetsView(const TilesetsView&) = delete;
	TilesetsView(TilesetsView&&) = delete;

	TilesetsView& operator=(const TilesetsView&) = delete;
	TilesetsView& operator=(TilesetsView&&) = delete;

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

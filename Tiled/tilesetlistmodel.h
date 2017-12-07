/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QAbstractItemModel>
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocument;
class Tileset;
class Map;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetListModel final : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TilesetListModel(MapDocument* mapDocument, QObject* parent = nullptr);
	~TilesetListModel() override = default;

	TilesetListModel(const TilesetListModel&) = delete;
	TilesetListModel(TilesetListModel&&) = delete;

	TilesetListModel& operator=(const TilesetListModel&) = delete;
	TilesetListModel& operator=(TilesetListModel&&) = delete;
	
	QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;

	QModelIndex index(Tileset* tileset, int column = 0) const;
	Tileset* tileset(const QModelIndex& index) const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;

	void addTileset(int index, Tileset* tileset);
	Tileset* takeTileset(int index);

	Qt::ItemFlags flags(const QModelIndex &index) const override;

	void setMapDocument(MapDocument* mapDocument);
	MapDocument* mapDocument() const;

	void resetModel();

signals:
	void tilesetAdded(Tileset* tileset);
	void tilesetRemoved(Tileset* tileset);

private slots:
	void tilesetChanged(Tileset *tileset, int changedPropertyId);

private:
	MapDocument* mMapDocument;
	Map* mMap;
};
/*-----------------------------------------------------------------------------------------------------------*/
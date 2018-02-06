/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QAbstractListModel>
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetDocument;
class MapDocument;
class Document;
class Tileset;
class Tile;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetTableModel final : public QAbstractListModel
{
	Q_OBJECT

public:

	explicit TilesetTableModel(MapDocument* mapDocument, Tileset* tileset, QObject* parent = nullptr);
	explicit TilesetTableModel(TilesetDocument* tilesetDocument, Tileset* tileset, QObject* parent = nullptr);
	~TilesetTableModel() override = default;

	TilesetTableModel(TilesetTableModel&&) = delete;
	TilesetTableModel(const TilesetTableModel&) = delete;

	TilesetTableModel& operator=(TilesetTableModel&&) = delete;
	TilesetTableModel& operator=(const TilesetTableModel&) = delete;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;

	QStringList mimeTypes() const override;
	QMimeData* mimeData(const QModelIndexList& indexes) const override;

	Tile* tile(const QModelIndex& index) const;
	QModelIndex index(Tile* tile) const;

	void setMapDocument(MapDocument* mapDocument);
	void setTilesetDocument(TilesetDocument* tilesetDocument);
	Document* document() const;

	void setTileset(Tileset* tileset);
	Tileset* tileset() const;

	void resetModel();

private slots:
	void tileChanged(Tile *tile, int changedPropertyId);

private:
	Document* mDocument;
	Tileset* mTileset;
};
/*-----------------------------------------------------------------------------------------------------------*/


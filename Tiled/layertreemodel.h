/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QAbstractItemModel>
#include <QIcon>
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocument;
class GroupLayer;
class Layer;
class Map;
/*-----------------------------------------------------------------------------------------------------------*/
class LayerTreeModel final : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit LayerTreeModel(MapDocument* mapDocument, QObject* parent = nullptr);
	~LayerTreeModel() override = default;

	LayerTreeModel(const LayerTreeModel&) = delete;
	LayerTreeModel(LayerTreeModel&&) = delete;

	LayerTreeModel& operator=(const LayerTreeModel&) = delete;
	LayerTreeModel& operator=(LayerTreeModel&&) = delete;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;

	QModelIndex index(Layer* layer, int column = 0) const;
	Layer* layer(const QModelIndex& index) const;

	void setMapDocument(MapDocument* mapDocument);
	MapDocument* mapDocument() const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;

	void addLayer(GroupLayer* parentLayer, int index, Layer* layer);
	Layer* takeLayer(GroupLayer* parentLayer, int index);

	Qt::ItemFlags flags(const QModelIndex &index) const override;

	QStringList mimeTypes() const override;
	QMimeData *mimeData(const QModelIndexList &indexes) const override;
	bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row,
		int column, const QModelIndex &parent) const override;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
		int column, const QModelIndex &parent) override;
	Qt::DropActions supportedDropActions() const override;

	void resetModel();

signals:
	void layerAdded(Layer* layer);
	void layerRemoved(Layer* layer);

private slots:
	void layerChanged(Layer* layer, int changedPropertyId);

private:
	MapDocument* mMapDocument;
	Map* mMap;

	QIcon mTileLayerIcon;
	QIcon mGroupLayerIcon;
};
/*-----------------------------------------------------------------------------------------------------------*/
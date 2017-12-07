/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QAbstractItemModel>
/*-----------------------------------------------------------------------------------------------------------*/
class Tile;
class Frame;
class MapDocument;
/*-----------------------------------------------------------------------------------------------------------*/
class FrameListModel final : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit FrameListModel(MapDocument* mapDocument, Tile* tile, QObject* parent = nullptr);
	~FrameListModel() override = default;

	FrameListModel(const FrameListModel&) = delete;
	FrameListModel(FrameListModel&&) = delete;

	FrameListModel& operator=(const FrameListModel&) = delete;
	FrameListModel& operator=(FrameListModel&&) = delete;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;

	Qt::ItemFlags flags(const QModelIndex &index) const override;
	bool removeRows(int row, int count, const QModelIndex &parent) override;
	bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, 
		const QModelIndex &destinationParent, int destinationChild) override;

	void setMapDocument(MapDocument* mapDocument);
	MapDocument* mapDocument() const;

	void setTile(Tile* tile);
	Tile* tile() const;

	void addFrame(const Frame& frame);

	QStringList mimeTypes() const override;
	QMimeData *mimeData(const QModelIndexList &indexes) const override;
	bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, 
		int column, const QModelIndex &parent) const override;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, 
		int column, const QModelIndex &parent) override;
	Qt::DropActions supportedDropActions() const override;

	void resetModel();

private slots:
	void tileChanged(Tile *tile, int changedPropertyId);

private:
	MapDocument* mMapDocument;
	Tile* mTile;
	bool mUpdate;

	static int mDefaultFrameTime;
};
/*-----------------------------------------------------------------------------------------------------------*/

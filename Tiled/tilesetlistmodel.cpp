/*-----------------------------------------------------------------------------------------------------------*/
#include "changetilesetproperty.h"
#include "addremovetileset.h"
#include "tilesetlistmodel.h"
#include "mapdocument.h"
#include "tileset.h"
#include "map.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilesetListModel::TilesetListModel(MapDocument* mapDocument, QObject* parent) : 
	QAbstractItemModel(parent),
	mMapDocument(nullptr),
	mMap(nullptr)
{
	setMapDocument(mapDocument);
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex TilesetListModel::index(int row, int column, const QModelIndex& parent) const
{
	if (parent.isValid()) return QModelIndex();
	else return createIndex(row, column, nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex TilesetListModel::parent(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return QModelIndex();
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex TilesetListModel::index(Tileset* tileset, int column) const
{
	if (!tileset) return QModelIndex();
	Q_ASSERT(mMap->tilesets().contains(tileset));

	return createIndex(mMap->tilesets().indexOf(tileset), column);
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* TilesetListModel::tileset(const QModelIndex& index) const
{
	if (!index.isValid()) return nullptr;
	Q_ASSERT(mMap->tilesetCount() > index.row());

	return mMap->tilesets().at(index.row());
}
/*-----------------------------------------------------------------------------------------------------------*/
int TilesetListModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid() || !mMap) return 0;
	else return mMap->tilesetCount();
}
/*-----------------------------------------------------------------------------------------------------------*/
int TilesetListModel::columnCount(const QModelIndex& parent) const
{
	if (parent.isValid()) return 0;
	else return 1;
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant TilesetListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case 0:
			return tr("Name");
		}
	}

	return QVariant();
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant TilesetListModel::data(const QModelIndex& index, int role) const
{
	auto tileset = this->tileset(index);
	if (!tileset) return QVariant();

	switch (role)
	{
	case Qt::EditRole:
	case Qt::DisplayRole:
		if (index.column() == 0)
			return tileset->name();
		break;

	}

	return QVariant();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool TilesetListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	auto tileset = this->tileset(index);
	if (!tileset) return false;

	switch (role)
	{
	case Qt::EditRole:
		if (index.column() == 0)
		{
			if (tileset->name() == value.toString()) return true;

			auto undoStack = mMapDocument->undoStack();
			undoStack->push(new ChangedTilesetProperty(mMapDocument, tileset, value.toString()));

			return true;
		}
		break;
	}

	return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetListModel::addTileset(int index, Tileset* tileset)
{
	beginInsertRows(QModelIndex(), index, index);
	mMap->addTileset(tileset, index);
	endInsertRows();

	emit tilesetAdded(tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* TilesetListModel::takeTileset(int index)
{
	beginRemoveRows(QModelIndex(), index, index);
	auto tileset = mMap->takeTileset(index);
	endRemoveRows();

	emit tilesetRemoved(tileset);

	return tileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
Qt::ItemFlags TilesetListModel::flags(const QModelIndex& index) const
{
	auto defaultFlag = QAbstractItemModel::flags(index);
	if (index.column() == 0) defaultFlag |= Qt::ItemIsEditable;

	return defaultFlag;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetListModel::setMapDocument(MapDocument* mapDocument)
{
	if (mMapDocument == mapDocument) return;

	if (mMapDocument)
	{
		mMapDocument->disconnect(this);
	}

	beginResetModel();
	mMapDocument = mapDocument;
	mMap = mMapDocument->map();
	endResetModel();

	if (mMapDocument)
	{
		connect(mMapDocument, &MapDocument::tilesetChanged,
			this, &TilesetListModel::tilesetChanged);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
MapDocument* TilesetListModel::mapDocument() const
{
	return mMapDocument;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetListModel::resetModel()
{
	beginResetModel();
	endResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetListModel::tilesetChanged(Tileset* tileset, int changedPropertyId)
{
	if (mMap->tilesets().isEmpty() || !mMap->tilesets().contains(tileset)) return;
	if (changedPropertyId != MapDocument::ChangedPropertyId::NameChangedId) return;

	emit dataChanged(index(tileset, 0), index(tileset, columnCount() - 1));
}
/*-----------------------------------------------------------------------------------------------------------*/

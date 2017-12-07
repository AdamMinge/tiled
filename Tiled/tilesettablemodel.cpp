/*-----------------------------------------------------------------------------------------------------------*/
#include <QMimeData>
#include "tilesettablemodel.h"
#include "tiledutils.h"
#include "mapdocument.h"
#include "tileset.h"
#include "tile.h"
#include "map.h"
/*-----------------------------------------------------------------------------------------------------------*/
static bool contain(const MapDocument* mapDocument, const Tileset* tileset)
{
	if (!tileset) return true;
	return mapDocument->map()->tilesets().contains(const_cast<Tileset*>(tileset));
}
/*-----------------------------------------------------------------------------------------------------------*/
TilesetTableModel::TilesetTableModel(MapDocument* mapDocument, Tileset* tileset, QObject* parent) :
	QAbstractListModel(parent),
	mMapDocument(nullptr),
	mTileset(nullptr)
{
	setMapDocument(mapDocument);
	setTileset(tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
int TilesetTableModel::rowCount(const QModelIndex& parent) const 
{
	if (parent.isValid() || !mTileset) return 0;
	return mTileset->rowCount();
}
/*-----------------------------------------------------------------------------------------------------------*/
int TilesetTableModel::columnCount(const QModelIndex& parent) const 
{
	if (parent.isValid() || !mTileset) return 0;
	return mTileset->columnCount();
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant TilesetTableModel::data(const QModelIndex& index, int role) const
{
	if(role == Qt::DecorationRole)
	{
		if (auto tileAtIndex = tile(index))
			return tileAtIndex->image();
	}

	return QVariant();
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant TilesetTableModel::headerData(int section, Qt::Orientation orientation, int role) const 
{
	Q_UNUSED(section)
	Q_UNUSED(orientation)

	if (role == Qt::SizeHintRole) return QSize(1, 1);
	return QVariant();
}
/*-----------------------------------------------------------------------------------------------------------*/
Qt::ItemFlags TilesetTableModel::flags(const QModelIndex& index) const 
{
	auto defaultFlags = QAbstractListModel::flags(index);

	if (index.isValid()) return defaultFlags | Qt::ItemIsDragEnabled;
	else return defaultFlags;
}
/*-----------------------------------------------------------------------------------------------------------*/
QStringList TilesetTableModel::mimeTypes() const
{
	QStringList types;
	types << mimeType(MimeTypes::Tiles);

	return types;
}
/*-----------------------------------------------------------------------------------------------------------*/
QMimeData* TilesetTableModel::mimeData(const QModelIndexList& indexes) const
{
	auto mimeData = new QMimeData;
	auto encodedData = QByteArray();

	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	for(decltype(auto) index : indexes)
	{
		stream << tile(index)->id();
	}

	mimeData->setData(mimeType(MimeTypes::Tiles), encodedData);
	return mimeData;
}
/*-----------------------------------------------------------------------------------------------------------*/
Tile* TilesetTableModel::tile(const QModelIndex& index) const
{
	Q_ASSERT(mTileset);

	if (!index.isValid()) return nullptr;

	const auto tileIndex = index.column() + index.row() * columnCount();

	if (tileIndex < mTileset->tileCount())
	{
		auto tile = mTileset->tile(tileIndex);
		Q_ASSERT(tile);
		return tile;
	}
	else return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex TilesetTableModel::index(Tile* tile) const
{
	Q_ASSERT(mTileset);

	if(mTileset->contains(tile))
	{
		auto id = tile->id();
		auto column = id % columnCount();
		auto row = id / columnCount();

		return createIndex(row, column);;
	}
	else
	{
		return QModelIndex();
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetTableModel::setMapDocument(MapDocument* mapDocument)
{
	if (mMapDocument == mapDocument) return;

	if(mMapDocument)
	{
		mMapDocument->disconnect(this);
	}

	beginResetModel();
	mMapDocument = mapDocument;
	mTileset = nullptr;
	endResetModel();

	if(mMapDocument)
	{
		connect(mMapDocument, &MapDocument::tileChanged,
			this, &TilesetTableModel::tileChanged);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
MapDocument* TilesetTableModel::mapDocument() const
{
	return mMapDocument;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetTableModel::setTileset(Tileset* tileset)
{
	if (mTileset == tileset) return;

	beginResetModel();
	mTileset = tileset;
	Q_ASSERT(contain(mMapDocument, mTileset));
	endResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* TilesetTableModel::tileset() const
{
	return mTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetTableModel::resetModel()
{
	beginResetModel();
	endResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetTableModel::tileChanged(Tile* tile, int changedPropertyId)
{
	if (!mTileset || !mTileset->contains(tile)) return;
	if (changedPropertyId != MapDocument::ChangedPropertyId::AnimationChangedId) return;

	emit dataChanged(index(tile), index(tile));
}
/*-----------------------------------------------------------------------------------------------------------*/

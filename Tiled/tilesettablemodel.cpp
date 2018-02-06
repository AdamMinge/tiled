/*-----------------------------------------------------------------------------------------------------------*/
#include <QMimeData>
#include "tilesettablemodel.h"
#include "tiledutils.h"
#include "mapdocument.h"
#include "tilesetdocument.h"
#include "tileset.h"
#include "tile.h"
#include "map.h"
/*-----------------------------------------------------------------------------------------------------------*/
static bool contain(const Document* document, const Tileset* tileset)
{
	const auto tilesetDocument = qobject_cast<const TilesetDocument*>(document);
	const auto mapDocument = qobject_cast<const MapDocument*>(document);

	if(mapDocument)
	{
		Q_ASSERT(mapDocument);

		if (!tileset) return true;
		return mapDocument->map()->tilesets().contains(const_cast<Tileset*>(tileset));
	}
	else
	{
		Q_ASSERT(tilesetDocument);

		if (!tileset) return true;
		return tilesetDocument->tileset() == tileset;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
TilesetTableModel::TilesetTableModel(MapDocument* mapDocument, Tileset* tileset, QObject* parent) :
	QAbstractListModel(parent),
	mDocument(nullptr),
	mTileset(nullptr)
{
	setMapDocument(mapDocument);
	setTileset(tileset);
}
/*-----------------------------------------------------------------------------------------------------------*/
TilesetTableModel::TilesetTableModel(TilesetDocument* tilesetDocument, Tileset* tileset, QObject* parent) :
	QAbstractListModel(parent),
	mDocument(nullptr),
	mTileset(nullptr)
{
	setTilesetDocument(tilesetDocument);
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
		if (const auto tileAtIndex = tile(index))
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
	const auto defaultFlags = QAbstractListModel::flags(index);

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
		const auto id = tile->id();
		const auto column = id % columnCount();
		const auto row = id / columnCount();

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
	if (mDocument == mapDocument) return;

	if (mDocument)
	{
		mDocument->disconnect(this);
	}

	beginResetModel();
	mDocument = mapDocument;
	mTileset = nullptr;
	endResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetTableModel::setTilesetDocument(TilesetDocument* tilesetDocument)
{
	if (mDocument == tilesetDocument) return;

	if (mDocument)
	{
		mDocument->disconnect(this);
	}

	beginResetModel();
	mDocument = tilesetDocument;
	mTileset = nullptr;
	endResetModel();

	if (mDocument)
	{
		connect(tilesetDocument, &TilesetDocument::tileChanged,
			this, &TilesetTableModel::tileChanged);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
Document* TilesetTableModel::document() const
{
	return mDocument;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetTableModel::setTileset(Tileset* tileset)
{
	if (mTileset == tileset) return;

	beginResetModel();
	mTileset = tileset;
	Q_ASSERT(contain(mDocument, mTileset));
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
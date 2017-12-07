/*-----------------------------------------------------------------------------------------------------------*/
#include <QMimeData>
#include "changetileproperty.h"
#include "framelistmodel.h"
#include "mapdocument.h"
#include "tiledutils.h"
#include "tileset.h"
#include "frame.h"
#include "tile.h"
#include "map.h"
/*-----------------------------------------------------------------------------------------------------------*/
int FrameListModel::mDefaultFrameTime = 100;
/*-----------------------------------------------------------------------------------------------------------*/
static bool contain(const MapDocument* mapDocument, const Tile* tile)
{
	if (!tile) return true;
	return mapDocument->map()->tilesets().contains(tile->tileset());
}
/*-----------------------------------------------------------------------------------------------------------*/
FrameListModel::FrameListModel(MapDocument* mapDocument, Tile* tile, QObject* parent) :
	QAbstractItemModel(parent),
	mMapDocument(nullptr),
	mTile(nullptr),
	mUpdate(false)
{
	setMapDocument(mapDocument);
	setTile(tile);
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex FrameListModel::index(int row, int column, const QModelIndex& parent) const
{
	if (parent.isValid()) return QModelIndex();
	else return createIndex(row, column, nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex FrameListModel::parent(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return QModelIndex();
}
/*-----------------------------------------------------------------------------------------------------------*/
int FrameListModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid() || !mTile) return 0;
	else return mTile->frames().count();
}
/*-----------------------------------------------------------------------------------------------------------*/
int FrameListModel::columnCount(const QModelIndex& parent) const
{
	if (parent.isValid()) return 0;
	else return 2;
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant FrameListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return tr("Frame");
		case 1:
			return tr("Time");
		}
	}

	return QVariant();
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant FrameListModel::data(const QModelIndex& index, int role) const
{
	Q_ASSERT(mTile);

	if (index.column() == 0)
	{
		switch (role)
		{
		case Qt::DecorationRole:
			if (auto tile = mTile->tileset()->tile(mTile->frames()[index.row()].tileId()))
				return tile->image();
		}
	}
	else if (index.column() == 1)
	{
		switch (role)
		{
		case Qt::EditRole:
		case Qt::DisplayRole:
			return mTile->frames()[index.row()].duration();
		}
	}

	return QVariant();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool FrameListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	Q_ASSERT(mTile);
	Q_ASSERT(mMapDocument);

	if(index.column() == 1 && role == Qt::EditRole)
	{
		auto duration = value.toInt();

		if (duration > 0 && mTile->frames()[index.row()].duration() != duration)
		{
			auto tileFrames = mTile->frames();
			tileFrames[index.row()].setDuration(duration);
			
			mUpdate = true;
			auto undoStack = mMapDocument->undoStack();
			undoStack->push(new ChangeTileProperty(mMapDocument, mTile, tileFrames));
			mUpdate = false;

			emit dataChanged(index, index);

			return true;
		}
	}
	
	return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
Qt::ItemFlags FrameListModel::flags(const QModelIndex& index) const
{
	auto defaultFlag = QAbstractItemModel::flags(index);
	
	if (index.column() == 1) defaultFlag |= Qt::ItemIsEditable;

	if (index.isValid()) return defaultFlag | Qt::ItemIsDragEnabled;
	else return defaultFlag | Qt::ItemIsDropEnabled;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool FrameListModel::removeRows(int row, int count, const QModelIndex& parent)
{
	Q_ASSERT(mTile);
	Q_ASSERT(mMapDocument);

	if(!parent.isValid())
	{
		if(count > 0)
		{
			beginRemoveRows(parent, row, row + count - 1);

			auto tileFrames = mTile->frames();
			tileFrames.remove(row, count);

			mUpdate = true;
			auto undoStack = mMapDocument->undoStack();
			undoStack->push(new ChangeTileProperty(mMapDocument, mTile, tileFrames));
			mUpdate = false;

			endRemoveRows();

			return true;
		}
	}
	
	return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool FrameListModel::moveRows(const QModelIndex& sourceParent, int sourceRow, int count, 
	const QModelIndex& destinationParent, int destinationChild)
{
	Q_ASSERT(mTile);
	Q_ASSERT(mMapDocument);

	if (!sourceParent.isValid() && !destinationParent.isValid())
	{
		if(count > 0 && destinationChild >= 0 && destinationChild < mTile->frames().size())
		{
			beginMoveRows(sourceParent, sourceRow, sourceRow + count - 1, destinationParent, 
				(destinationChild > sourceRow) ? destinationChild + 1 : destinationChild);

			auto tileFrames = mTile->frames();

			for(auto i = 0;i < count;i++)
				tileFrames.move(sourceRow + i, destinationChild);

			mUpdate = true;
			auto undoStack = mMapDocument->undoStack();
			undoStack->push(new ChangeTileProperty(mMapDocument, mTile, tileFrames));
			mUpdate = false;

			endMoveRows();

			return true;
		}
	}

	return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
void FrameListModel::setMapDocument(MapDocument* mapDocument)
{
	if (mMapDocument == mapDocument) return;

	if(mMapDocument)
	{
		mMapDocument->disconnect(this);
	}

	beginResetModel();
	mMapDocument = mapDocument;
	mTile = nullptr;
	endResetModel();

	if(mMapDocument)
	{
		connect(mMapDocument, &MapDocument::tileChanged, 
			this, &FrameListModel::tileChanged);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
MapDocument* FrameListModel::mapDocument() const
{
	return mMapDocument;
}
/*-----------------------------------------------------------------------------------------------------------*/
void FrameListModel::setTile(Tile* tile)
{
	if (mTile == tile) return;

	beginResetModel();
	mTile = tile;
	Q_ASSERT(contain(mMapDocument, mTile));
	endResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
Tile* FrameListModel::tile() const
{
	return mTile;
}
/*-----------------------------------------------------------------------------------------------------------*/
void FrameListModel::addFrame(const Frame& frame)
{
	Q_ASSERT(mTile);
	Q_ASSERT(mMapDocument);

	auto newFrame = frame;
	newFrame.setDuration(newFrame.duration() > 0 ? newFrame.duration() : mDefaultFrameTime);

	beginInsertRows(QModelIndex(), mTile->frames().size(), mTile->frames().size());

	auto tileFrames = mTile->frames();
	tileFrames.append(std::move(newFrame));

	mUpdate = true;
	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new ChangeTileProperty(mMapDocument, mTile, tileFrames));
	mUpdate = false;

	endInsertRows();
}
/*-----------------------------------------------------------------------------------------------------------*/
QStringList FrameListModel::mimeTypes() const
{
	QStringList types;
	types << mimeType(MimeTypes::Tiles);
	types << mimeType(MimeTypes::Frames);

	return types;
}
/*-----------------------------------------------------------------------------------------------------------*/
QMimeData* FrameListModel::mimeData(const QModelIndexList& indexes) const
{
	Q_ASSERT(mTile);

	if (indexes.isEmpty()) return nullptr;

	auto mimeData = new QMimeData;
	auto encodedData = QByteArray();

	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	for(decltype(auto) index : indexes)
	{
		Q_ASSERT(index.isValid());
		if (index.column() != 0) continue;

		decltype(auto) frame = mTile->frames()[index.row()];
		stream << frame.tileId();
		stream << frame.duration();
	}

	mimeData->setData(mimeType(MimeTypes::Frames), encodedData);
	return mimeData;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool FrameListModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, 
	int row, int column, const QModelIndex& parent) const
{
	Q_UNUSED(data);
	Q_UNUSED(row);
	Q_UNUSED(parent);

	if (action == Qt::IgnoreAction) return false;
	if (column > 1) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool FrameListModel::dropMimeData(const QMimeData* data, Qt::DropAction action,
	int row, int column, const QModelIndex& parent)
{
	Q_UNUSED(action);
	Q_UNUSED(column);

	Q_ASSERT(mTile);
	Q_ASSERT(mMapDocument);

	auto beginRow = 0;
	QVector<Frame> frames;

	if (row != -1)
		beginRow = row;
	else if (parent.isValid())
		beginRow = parent.row();
	else
		beginRow = mTile->frames().count();

	if (data->hasFormat(mimeType(MimeTypes::Frames)))
	{
		auto encodedData = data->data(mimeType(MimeTypes::Frames));
		QDataStream stream(&encodedData, QIODevice::ReadOnly);

		while(!stream.atEnd())
		{
			int tileId, duration;

			Frame frame;
			stream >> tileId;
			stream >> duration;

			frame.setTileId(tileId);
			frame.setDuration(duration);

			frames.append(std::move(frame));
		}
	}
	else if (data->hasFormat(mimeType(MimeTypes::Tiles)))
	{
		auto encodedData = data->data(mimeType(MimeTypes::Tiles));
		QDataStream stream(&encodedData, QIODevice::ReadOnly);

		while (!stream.atEnd())
		{
			int tileId;

			Frame frame;
			stream >> tileId;

			frame.setTileId(tileId);
			frame.setDuration(mDefaultFrameTime);

			frames.append(std::move(frame));
		}
	}

	if (frames.isEmpty()) return false;

	beginInsertRows(QModelIndex(), beginRow, beginRow + frames.count() - 1);

	auto tileFrames = mTile->frames();

	tileFrames.insert(beginRow, frames.count(), Frame());
	for (auto i = 0; i < frames.count(); ++i)
		tileFrames[i + beginRow] = frames[i];

	mUpdate = true;
	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new ChangeTileProperty(mMapDocument, mTile, tileFrames));
	mUpdate = false;

	endInsertRows();

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
Qt::DropActions FrameListModel::FrameListModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}
/*-----------------------------------------------------------------------------------------------------------*/
void FrameListModel::resetModel()
{
	beginResetModel();
	endResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
void FrameListModel::tileChanged(Tile* tile, int changedPropertyId)
{
	if (mTile != tile) return;
	if (mUpdate) return;
	if (changedPropertyId != MapDocument::ChangedPropertyId::AnimationChangedId) return;

	resetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/

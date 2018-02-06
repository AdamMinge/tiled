/*-----------------------------------------------------------------------------------------------------------*/
#include <QApplication>
#include <QMimeData>
#include <QStyle>
#include "changelayerproperty.h"
#include "reparentlayer.h"
#include "groupcommand.h"
#include "layeriterator.h"
#include "mapdocument.h"
#include "layertreemodel.h"
#include "grouplayer.h"
#include "tiledutils.h"
#include "utils.h"
#include "map.h"
/*-----------------------------------------------------------------------------------------------------------*/
static bool contain(GroupLayer* parent, Layer* child)
{
	do
	{
		if (child == parent) return true;
	} while ((child = child->parent()));

	return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
static int globalIndex(GroupLayer* root, Layer* layer)
{
	auto index = 0;
	auto iterator = LayerIterator<PostOrderLayerIteration>(root);

	while(iterator.hasNext())
	{
		const auto iterLayer = iterator.next();
		if (iterLayer == layer) return index;

		++index;
	}

	return -1;
}
/*-----------------------------------------------------------------------------------------------------------*/
static Layer* globalIndex(GroupLayer* root, int globalIndex)
{
	auto iterator = LayerIterator<PostOrderLayerIteration>(root);

	while (iterator.hasNext())
	{
		iterator.next();
		if (globalIndex == 0) return iterator.currentLayer();

		--globalIndex;
	}

	return nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
LayerTreeModel::LayerTreeModel(MapDocument* mapDocument, QObject* parent) :
	QAbstractItemModel(parent),
	mMapDocument(nullptr),
	mMap(nullptr)
{
	setMapDocument(mapDocument);

	mTileLayerIcon = makeIcon(QLatin1String(":/Tiled/images/%1/layer-tile.png"), { QSize(16,16), QSize(32,32) });
	mGroupLayerIcon = QApplication::style()->standardIcon(QStyle::SP_DirIcon);
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex LayerTreeModel::index(int row, int column, const QModelIndex& parent) const
{
	if (const auto layer = dynamic_cast<GroupLayer*>(this->layer(parent)))
	{
		if (row < layer->layerCount())
			return createIndex(row, column, layer);
		else
			return QModelIndex();
	}
	else
	{
		if (row == 0)
			return createIndex(row, column, nullptr);
		else
			return QModelIndex();
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex LayerTreeModel::parent(const QModelIndex& index) const
{
	if (const auto parent = static_cast<GroupLayer*>(index.internalPointer()))
		return this->index(parent);
	else
		return QModelIndex();
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex LayerTreeModel::index(Layer* layer, int column) const
{
	if (!layer) return QModelIndex();

	Q_ASSERT(contain(mMap->rootLayer(), layer));

	if (layer == mMap->rootLayer())
	{
		return createIndex(0, column, nullptr);
	}
	else
	{
		auto parent = layer->parent();
		Q_ASSERT(parent);

		return createIndex(parent->layerIndex(layer), column, parent);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* LayerTreeModel::layer(const QModelIndex& index) const
{
	if (!index.isValid()) return nullptr;

	if (auto parent = static_cast<GroupLayer*>(index.internalPointer()))
		return parent->layer(index.row());
	else
		return mMap->rootLayer();
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerTreeModel::setMapDocument(MapDocument* mapDocument)
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
		connect(mMapDocument, &MapDocument::layerChanged, 
			this, &LayerTreeModel::layerChanged);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
MapDocument* LayerTreeModel::mapDocument() const
{
	return mMapDocument;
}
/*-----------------------------------------------------------------------------------------------------------*/
int LayerTreeModel::rowCount(const QModelIndex& parent) const
{
	const auto layer = this->layer(parent);

	if (!layer && mMap->rootLayer())
		return 1;
	else if (const auto groupLayer = dynamic_cast<GroupLayer*>(layer))
		return groupLayer->layerCount();
	else
		return 0;
}
/*-----------------------------------------------------------------------------------------------------------*/
int LayerTreeModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 3;
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant LayerTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return tr("Layer");
		case 1:
			return tr("Visible");
		case 2:
			return tr("Locked");
		default:
			return QVariant();
		}
	}
	
	return QVariant();
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant LayerTreeModel::data(const QModelIndex& index, int role) const
{
	const auto layer = this->layer(index);
	if (!layer) return QVariant();

	switch(role)
	{
	case Qt::EditRole:
	case Qt::DisplayRole:
		if(index.column() == 0)
			return layer->name();
		break;

	case Qt::DecorationRole:
		if(index.column() == 0)
		{
			switch (layer->layerType())
			{
			case Layer::LayerType::TileLayerType:
				return mTileLayerIcon;
			case Layer::LayerType::GroupLayerType:
				return mGroupLayerIcon;
			}
			break;
		}
		
	case Qt::CheckStateRole:
		if (index.column() == 1)
			return layer->isVisible() ? Qt::Checked : Qt::Unchecked;
		else if (index.column() == 2)
			return layer->isLocked() ? Qt::Checked : Qt::Unchecked;
		break;
	default:
		return QVariant();
	}

	return QVariant();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool LayerTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	const auto layer = this->layer(index);
	if (!layer) return false;

	switch(role)
	{
	case Qt::EditRole:
		if (index.column() == 0)
		{
			if (layer->name() == value.toString()) return true;

			auto undoStack = mMapDocument->undoStack();
			undoStack->push(new ChangeLayerProperty(mMapDocument, layer, value.toString()));

			return true;
		}
		break;

	case Qt::CheckStateRole:
		if (index.column() == 1 || index.column() == 2)
		{
			if (index.column() == 1 && layer->isVisible() == value.toBool()) return true;
			if (index.column() == 2 && layer->isLocked() == value.toBool()) return true;

			auto undoStack = mMapDocument->undoStack();
			undoStack->push(new ChangeLayerProperty(mMapDocument, 
				layer, value.toBool(), (index.column() == 1) ? 
				ChangeLayerProperty::BoolProperty::Visible : 
				ChangeLayerProperty::BoolProperty::Locked));

			return true;
		}
		break;
	default:
		return false;
	}

	return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerTreeModel::addLayer(GroupLayer* parentLayer, int index, Layer* layer)
{
	const auto parent = this->index(parentLayer);
	beginInsertRows(parent, index, index);
	parentLayer->addLayer(layer, index);
	endInsertRows();

	emit layerAdded(layer);
}
/*-----------------------------------------------------------------------------------------------------------*/
Layer* LayerTreeModel::takeLayer(GroupLayer* parentLayer, int index)
{
	const auto parent = this->index(parentLayer);
	beginRemoveRows(parent, index, index);
	const auto layer = parentLayer->takeLayer(index);
	endRemoveRows();

	emit layerRemoved(layer);

	return layer;
}
/*-----------------------------------------------------------------------------------------------------------*/
Qt::ItemFlags LayerTreeModel::flags(const QModelIndex& index) const
{
	auto defaultFlags = QAbstractItemModel::flags(index);
	const auto layer = this->layer(index);
	const auto isRootLayer = layer == mMap->rootLayer();

	if (index.column() == 1 || index.column() == 2)
		defaultFlags |= Qt::ItemIsUserCheckable;
	if (index.column() == 0 && !isRootLayer)
		defaultFlags |= Qt::ItemIsEditable;

	if (layer)
		defaultFlags |= Qt::ItemIsDragEnabled;
	if (dynamic_cast<GroupLayer*>(layer))
		defaultFlags |= Qt::ItemIsDropEnabled;

	return defaultFlags;
}
/*-----------------------------------------------------------------------------------------------------------*/
QStringList LayerTreeModel::mimeTypes() const
{
	QStringList types;
	types << mimeType(MimeTypes::Layers);

	return types;
}
/*-----------------------------------------------------------------------------------------------------------*/
QMimeData* LayerTreeModel::mimeData(const QModelIndexList& indexes) const
{
	Q_ASSERT(mMap->rootLayer());
	Q_ASSERT(mMapDocument);

	if (indexes.isEmpty()) return nullptr;

	auto mimeData = new QMimeData;
	auto encodedData = QByteArray();

	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	for (decltype(auto) index : indexes)
	{
		Q_ASSERT(index.isValid());
		if (index.column() != 0) continue;
		stream << ::globalIndex(mMap->rootLayer(), layer(index));
	}

	mimeData->setData(mimeType(MimeTypes::Layers), encodedData);
	return mimeData;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool LayerTreeModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
	const QModelIndex& parent) const
{
	Q_UNUSED(data);
	Q_UNUSED(row);
	Q_UNUSED(parent);

	if (action != Qt::MoveAction) return false;
	if (column > 3) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool LayerTreeModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
	const QModelIndex& parent)
{
	Q_UNUSED(action);
	Q_UNUSED(column);

	Q_ASSERT(mMap->rootLayer());
	Q_ASSERT(mMapDocument);

	QList<Layer*> layers;
	const auto groupLayer = static_cast<GroupLayer*>(layer(parent));
	if (!groupLayer) return false;

	if (data->hasFormat(mimeType(MimeTypes::Layers)))
	{
		auto encodedData = data->data(mimeType(MimeTypes::Layers));
		QDataStream stream(&encodedData, QIODevice::ReadOnly);

		auto globalIndex = 0;
		while (!stream.atEnd())
		{
			stream >> globalIndex;
			auto layer = ::globalIndex(mMap->rootLayer(), globalIndex);
			layers.append(layer);
		}

		if (row > rowCount(parent)) row = rowCount(parent);
		else if (row == -1) row = 0;
	}

	if (layers.isEmpty()) return false;

	QList<Command*> commands;
	for(decltype(auto) layer : layers)
	{
		Q_ASSERT(layer);
		commands.append(new ReparentLayer(mMapDocument, layer, groupLayer, row));
	}

	auto undoStack = mMapDocument->undoStack();
	undoStack->push(new GroupCommand(tr("Drag Layer(s)", nullptr, commands.size()), std::move(commands)));

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
Qt::DropActions LayerTreeModel::supportedDropActions() const
{
	return Qt::MoveAction;
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerTreeModel::resetModel()
{
	beginResetModel();
	endResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerTreeModel::layerChanged(Layer* layer, int changedPropertyId)
{
	if (!mMap->rootLayer() || !contain(mMap->rootLayer(), layer)) return;
	if (changedPropertyId != MapDocument::ChangedPropertyId::NameChangedId && 
		changedPropertyId != MapDocument::ChangedPropertyId::VisibleChangedId && 
		changedPropertyId != MapDocument::ChangedPropertyId::LockedChangedId) return;

	emit dataChanged(index(layer, 0), index(layer, columnCount() - 1));
}
/*-----------------------------------------------------------------------------------------------------------*/

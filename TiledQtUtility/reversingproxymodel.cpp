/*-----------------------------------------------------------------------------------------------------------*/
#include "reversingproxymodel.h"
/*-----------------------------------------------------------------------------------------------------------*/
class FriendModel : public QAbstractItemModel
{
	friend class ReversingProxyModel;
};
/*-----------------------------------------------------------------------------------------------------------*/
ReversingProxyModel::ReversingProxyModel(QObject *parent) : 
	QAbstractProxyModel(parent)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex ReversingProxyModel::index(int row, int column, const QModelIndex &parent) const
{
	if (row < 0 || column < 0 || !sourceModel())
		return QModelIndex();

	Q_ASSERT(parent.isValid() ? parent.model() == this : true);
	const auto rows = rowCount(parent);
	if (row >= rows)
		return QModelIndex();

	const auto sourceParent = mapToSource(parent);
	const auto sourceIndex = sourceModel()->index(rows - row - 1, column, sourceParent);
	return createIndex(row, column, sourceIndex.internalId());
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex ReversingProxyModel::parent(const QModelIndex &child) const
{
	Q_ASSERT(child.isValid() ? child.model() == this : true);
	const auto sourceIndex = mapToSource(child);
	const auto sourceParent = sourceIndex.parent();
	return mapFromSource(sourceParent);
}
/*-----------------------------------------------------------------------------------------------------------*/
int ReversingProxyModel::rowCount(const QModelIndex &parent) const
{
	Q_ASSERT(parent.isValid() ? parent.model() == this : true);
	if (!sourceModel())
		return 0;

	return sourceModel()->rowCount(mapToSource(parent));
}
/*-----------------------------------------------------------------------------------------------------------*/
int ReversingProxyModel::columnCount(const QModelIndex &parent) const
{
	Q_ASSERT(parent.isValid() ? parent.model() == this : true);
	if (!sourceModel())
		return 0;

	return sourceModel()->columnCount(mapToSource(parent));
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ReversingProxyModel::canDropMimeData(const QMimeData *data, Qt::DropAction action,
	int row, int column, const QModelIndex &parent) const
{
	int sourceDestinationRow;
	QModelIndex sourceParent;
	mapDropCoordinatesToSource(row, parent, &sourceDestinationRow, &sourceParent);
	return sourceModel()->canDropMimeData(data, action, sourceDestinationRow, column, sourceParent);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ReversingProxyModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
	int row, int column, const QModelIndex &parent)
{
	int sourceDestinationRow;
	QModelIndex sourceParent;
	mapDropCoordinatesToSource(row, parent, &sourceDestinationRow, &sourceParent);
	return sourceModel()->dropMimeData(data, action, sourceDestinationRow, column, sourceParent);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::mapDropCoordinatesToSource(int row, const QModelIndex &parent,
	int *sourceRow, QModelIndex *sourceParent) const
{
	*sourceParent = mapToSource(parent);

	if (row == -1)
		*sourceRow = -1;
	else
		*sourceRow = sourceModel()->rowCount(*sourceParent) - row;
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex ReversingProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
	if (!sourceModel() || !proxyIndex.isValid())
		return QModelIndex();

	const auto sourceSiblingIndex = static_cast<FriendModel*>(sourceModel())->createIndex(proxyIndex.row(),
		proxyIndex.column(),
		proxyIndex.internalId());
	const auto sourceParent = sourceSiblingIndex.parent();
	const auto rowCount = sourceModel()->rowCount(sourceParent);

	Q_ASSERT(proxyIndex.row() >= 0 && proxyIndex.row() < rowCount);
	const auto row = rowCount - proxyIndex.row() - 1;
	return sourceModel()->index(row, proxyIndex.column(), sourceParent);
}
/*-----------------------------------------------------------------------------------------------------------*/
QModelIndex ReversingProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
	if (!sourceModel() || !sourceIndex.isValid())
		return QModelIndex();

	const auto rowCount = sourceModel()->rowCount(sourceIndex.parent());

	Q_ASSERT(sourceIndex.row() >= 0 && sourceIndex.row() < rowCount);
	const auto row = rowCount - sourceIndex.row() - 1;
	return createIndex(row, sourceIndex.column(), sourceIndex.internalId());
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::setSourceModel(QAbstractItemModel* newSourceModel)
{
	beginResetModel();

	if (auto source = sourceModel())
	{
		disconnect(source, SIGNAL(rowsAboutToBeInserted(QModelIndex, int, int)),
			this, SLOT(sourceRowsAboutToBeInserted(QModelIndex, int, int)));
		disconnect(source, SIGNAL(rowsInserted(QModelIndex, int, int)),
			this, SLOT(sourceRowsInserted(QModelIndex, int, int)));
		disconnect(source, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
			this, SLOT(sourceRowsAboutToBeRemoved(QModelIndex, int, int)));
		disconnect(source, SIGNAL(rowsRemoved(QModelIndex, int, int)),
			this, SLOT(sourceRowsRemoved(QModelIndex, int, int)));
		disconnect(source, SIGNAL(rowsAboutToBeMoved(QModelIndex, int, int, QModelIndex, int)),
			this, SLOT(sourceRowsAboutToBeMoved(QModelIndex, int, int, QModelIndex, int)));
		disconnect(source, SIGNAL(rowsMoved(QModelIndex, int, int, QModelIndex, int)),
			this, SLOT(sourceRowsMoved(QModelIndex, int, int, QModelIndex, int)));
		disconnect(source, SIGNAL(columnsAboutToBeInserted(QModelIndex, int, int)),
			this, SLOT(sourceColumnsAboutToBeInserted(QModelIndex, int, int)));
		disconnect(source, SIGNAL(columnsInserted(QModelIndex, int, int)),
			this, SLOT(sourceColumnsInserted(QModelIndex, int, int)));
		disconnect(source, SIGNAL(columnsAboutToBeRemoved(QModelIndex, int, int)),
			this, SLOT(sourceColumnsAboutToBeRemoved(QModelIndex, int, int)));
		disconnect(source, SIGNAL(columnsRemoved(QModelIndex, int, int)),
			this, SLOT(sourceColumnsRemoved(QModelIndex, int, int)));
		disconnect(source, SIGNAL(columnsAboutToBeMoved(QModelIndex, int, int, QModelIndex, int)),
			this, SLOT(sourceColumnsAboutToBeMoved(QModelIndex, int, int, QModelIndex, int)));
		disconnect(source, SIGNAL(columnsMoved(QModelIndex, int, int, QModelIndex, int)),
			this, SLOT(sourceColumnsMoved(QModelIndex, int, int, QModelIndex, int)));
		disconnect(source, SIGNAL(modelAboutToBeReset()),
			this, SLOT(sourceModelAboutToBeReset()));
		disconnect(source, SIGNAL(modelReset()),
			this, SLOT(sourceModelReset()));
		disconnect(source, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)),
			this, SLOT(sourceDataChanged(QModelIndex, QModelIndex, QVector<int>)));
		disconnect(source, SIGNAL(headerDataChanged(Qt::Orientation, int, int)),
			this, SLOT(sourceHeaderDataChanged(Qt::Orientation, int, int)));
		disconnect(source, SIGNAL(layoutAboutToBeChanged(QList<QPersistentModelIndex>, QAbstractItemModel::LayoutChangeHint)),
			this, SLOT(sourceLayoutAboutToBeChanged(QList<QPersistentModelIndex>, QAbstractItemModel::LayoutChangeHint)));
		disconnect(source, SIGNAL(layoutChanged(QList<QPersistentModelIndex>, QAbstractItemModel::LayoutChangeHint)),
			this, SLOT(sourceLayoutChanged(QList<QPersistentModelIndex>, QAbstractItemModel::LayoutChangeHint)));
	}

	QAbstractProxyModel::setSourceModel(newSourceModel);

	if (auto *source = sourceModel()) 
	{
		connect(source, SIGNAL(rowsAboutToBeInserted(QModelIndex, int, int)),
			SLOT(sourceRowsAboutToBeInserted(QModelIndex, int, int)));
		connect(source, SIGNAL(rowsInserted(QModelIndex, int, int)),
			SLOT(sourceRowsInserted(QModelIndex, int, int)));
		connect(source, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
			SLOT(sourceRowsAboutToBeRemoved(QModelIndex, int, int)));
		connect(source, SIGNAL(rowsRemoved(QModelIndex, int, int)),
			SLOT(sourceRowsRemoved(QModelIndex, int, int)));
		connect(source, SIGNAL(rowsAboutToBeMoved(QModelIndex, int, int, QModelIndex, int)),
			SLOT(sourceRowsAboutToBeMoved(QModelIndex, int, int, QModelIndex, int)));
		connect(source, SIGNAL(rowsMoved(QModelIndex, int, int, QModelIndex, int)),
			SLOT(sourceRowsMoved(QModelIndex, int, int, QModelIndex, int)));
		connect(source, SIGNAL(columnsAboutToBeInserted(QModelIndex, int, int)),
			SLOT(sourceColumnsAboutToBeInserted(QModelIndex, int, int)));
		connect(source, SIGNAL(columnsInserted(QModelIndex, int, int)),
			SLOT(sourceColumnsInserted(QModelIndex, int, int)));
		connect(source, SIGNAL(columnsAboutToBeRemoved(QModelIndex, int, int)),
			SLOT(sourceColumnsAboutToBeRemoved(QModelIndex, int, int)));
		connect(source, SIGNAL(columnsRemoved(QModelIndex, int, int)),
			SLOT(sourceColumnsRemoved(QModelIndex, int, int)));
		connect(source, SIGNAL(columnsAboutToBeMoved(QModelIndex, int, int, QModelIndex, int)),
			SLOT(sourceColumnsAboutToBeMoved(QModelIndex, int, int, QModelIndex, int)));
		connect(source, SIGNAL(columnsMoved(QModelIndex, int, int, QModelIndex, int)),
			SLOT(sourceColumnsMoved(QModelIndex, int, int, QModelIndex, int)));
		connect(source, SIGNAL(modelAboutToBeReset()),
			SLOT(sourceModelAboutToBeReset()));
		connect(source, SIGNAL(modelReset()),
			SLOT(sourceModelReset()));
		connect(source, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)),
			SLOT(sourceDataChanged(QModelIndex, QModelIndex, QVector<int>)));
		connect(source, SIGNAL(headerDataChanged(Qt::Orientation, int, int)),
			SLOT(sourceHeaderDataChanged(Qt::Orientation, int, int)));
		connect(source, SIGNAL(layoutAboutToBeChanged(QList<QPersistentModelIndex>, QAbstractItemModel::LayoutChangeHint)),
			SLOT(sourceLayoutAboutToBeChanged(QList<QPersistentModelIndex>, QAbstractItemModel::LayoutChangeHint)));
		connect(source, SIGNAL(layoutChanged(QList<QPersistentModelIndex>, QAbstractItemModel::LayoutChangeHint)),
			SLOT(sourceLayoutChanged(QList<QPersistentModelIndex>, QAbstractItemModel::LayoutChangeHint)));
	}

	endResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceColumnsAboutToBeInserted(const QModelIndex &parent, int start, int end)
{
	Q_ASSERT(parent.isValid() ? parent.model() == sourceModel() : true);

	beginInsertColumns(mapFromSource(parent), start, end);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceColumnsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart,
	int sourceEnd, const QModelIndex &destParent, int dest)
{
	Q_ASSERT(sourceParent.isValid() ? sourceParent.model() == sourceModel() : true);
	Q_ASSERT(destParent.isValid() ? destParent.model() == sourceModel() : true);

	beginMoveColumns(mapFromSource(sourceParent), sourceStart, sourceEnd, mapFromSource(destParent), dest);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceColumnsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
	Q_ASSERT(parent.isValid() ? parent.model() == sourceModel() : true);

	beginRemoveColumns(mapFromSource(parent), start, end);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceColumnsInserted(const QModelIndex &parent, int start, int end)
{
	Q_ASSERT(parent.isValid() ? parent.model() == sourceModel() : true);

	Q_UNUSED(parent)
	Q_UNUSED(start)
	Q_UNUSED(end)

	endInsertColumns();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceColumnsMoved(const QModelIndex &sourceParent, int sourceStart,
	int sourceEnd, const QModelIndex &destParent, int dest)
{
	Q_ASSERT(sourceParent.isValid() ? sourceParent.model() == sourceModel() : true);
	Q_ASSERT(destParent.isValid() ? destParent.model() == sourceModel() : true);

	Q_UNUSED(sourceParent)
	Q_UNUSED(sourceStart)
	Q_UNUSED(sourceEnd)
	Q_UNUSED(destParent)
	Q_UNUSED(dest)

	endMoveColumns();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceColumnsRemoved(const QModelIndex &parent, int start, int end)
{
	Q_ASSERT(parent.isValid() ? parent.model() == sourceModel() : true);

	Q_UNUSED(parent)
	Q_UNUSED(start)
	Q_UNUSED(end)

	endRemoveColumns();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
	const QVector<int> &roles)
{
	Q_ASSERT(topLeft.isValid() ? topLeft.model() == sourceModel() : true);
	Q_ASSERT(bottomRight.isValid() ? bottomRight.model() == sourceModel() : true);

	const auto sourceParent = topLeft.parent();
	const auto bottomLeft = sourceModel()->index(bottomRight.row(), topLeft.column(), sourceParent);
	const auto topRight = sourceModel()->index(topLeft.row(), bottomRight.column(), sourceParent);

	const auto rows = sourceModel()->rowCount(sourceParent);
	const auto proxyTop = rows - bottomRight.row() - 1;
	const auto proxyBottom = rows - topLeft.row() - 1;

	const auto proxyTopLeft = createIndex(proxyTop, topLeft.column(), bottomLeft.internalId());
	const auto proxyBottomRight = createIndex(proxyBottom, bottomRight.column(), topRight.internalId());

	dataChanged(proxyTopLeft, proxyBottomRight, roles);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceHeaderDataChanged(Qt::Orientation orientation, int first, int last)
{
	if (orientation == Qt::Vertical) {
		const auto rows = sourceModel()->rowCount();
		const auto proxyFirst = rows - last - 1;
		const auto proxyLast = rows - first - 1;
		first = proxyFirst;
		last = proxyLast;
	}
	headerDataChanged(orientation, first, last);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceLayoutAboutToBeChanged(const QList<QPersistentModelIndex> &sourceParents,
	QAbstractItemModel::LayoutChangeHint hint)
{
	const auto proxyPersistentIndexes = persistentIndexList();
	for (const auto &proxyPersistentIndex : proxyPersistentIndexes) 
	{
		mProxyIndexes << proxyPersistentIndex;
		Q_ASSERT(proxyPersistentIndex.isValid());
		const QPersistentModelIndex srcPersistentIndex = mapToSource(proxyPersistentIndex);
		Q_ASSERT(srcPersistentIndex.isValid());
		mLayoutChangePersistentIndexes << srcPersistentIndex;
	}

	QList<QPersistentModelIndex> parents;
	parents.reserve(sourceParents.size());
	for (const auto &parent : sourceParents) 
	{
		if (!parent.isValid()) 
		{
			parents << QPersistentModelIndex();
			continue;
		}
		const auto mappedParent = mapFromSource(parent);
		Q_ASSERT(mappedParent.isValid());
		parents << mappedParent;
	}

	layoutAboutToBeChanged(parents, hint);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceLayoutChanged(const QList<QPersistentModelIndex> &sourceParents,
	QAbstractItemModel::LayoutChangeHint hint)
{
	for (auto i = 0; i < mProxyIndexes.size(); ++i) {
		changePersistentIndex(mProxyIndexes.at(i),
			mapFromSource(mLayoutChangePersistentIndexes.at(i)));
	}

	mLayoutChangePersistentIndexes.clear();
	mProxyIndexes.clear();

	QList<QPersistentModelIndex> parents;
	parents.reserve(sourceParents.size());
	for (const auto &parent : sourceParents)
	{
		if (!parent.isValid()) 
		{
			parents << QPersistentModelIndex();
			continue;
		}
		const auto mappedParent = mapFromSource(parent);
		Q_ASSERT(mappedParent.isValid());
		parents << mappedParent;
	}

	layoutChanged(parents, hint);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceModelAboutToBeReset()
{
	beginResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceModelReset()
{
	endResetModel();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceRowsAboutToBeInserted(const QModelIndex &parent, int start, int end)
{
	Q_ASSERT(parent.isValid() ? parent.model() == sourceModel() : true);

	const auto rows = sourceModel()->rowCount(parent);
	const auto proxyStart = rows - end;
	const auto proxyEnd = rows - start;

	beginInsertRows(mapFromSource(parent), proxyStart, proxyEnd);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceRowsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, 
	int sourceEnd, const QModelIndex &destParent, int dest)
{
	Q_ASSERT(sourceParent.isValid() ? sourceParent.model() == sourceModel() : true);
	Q_ASSERT(destParent.isValid() ? destParent.model() == sourceModel() : true);

	const auto sourceRows = sourceModel()->rowCount(sourceParent);
	const auto destRows = sourceModel()->rowCount(destParent);

	const auto proxySourceStart = sourceRows - sourceEnd - 1;
	const auto proxySourceEnd = sourceRows - sourceStart - 1;
	const auto proxyDest = destRows - dest;

	beginMoveRows(mapFromSource(sourceParent), proxySourceStart, proxySourceEnd, mapFromSource(destParent), proxyDest);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceRowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
	Q_ASSERT(parent.isValid() ? parent.model() == sourceModel() : true);

	const auto rows = sourceModel()->rowCount(parent);
	const auto proxyStart = rows - end - 1;
	const auto proxyEnd = rows - start - 1;
	const auto proxyParent = mapFromSource(parent);

	beginRemoveRows(proxyParent, proxyStart, proxyEnd);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceRowsInserted(const QModelIndex &parent, int start, int end)
{
	Q_ASSERT(parent.isValid() ? parent.model() == sourceModel() : true);

	Q_UNUSED(parent)
	Q_UNUSED(start)
	Q_UNUSED(end)

	endInsertRows();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceRowsMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, 
	const QModelIndex &destParent, int dest)
{
	Q_ASSERT(sourceParent.isValid() ? sourceParent.model() == sourceModel() : true);
	Q_ASSERT(destParent.isValid() ? destParent.model() == sourceModel() : true);

	Q_UNUSED(sourceParent)
	Q_UNUSED(sourceStart)
	Q_UNUSED(sourceEnd)
	Q_UNUSED(destParent)
	Q_UNUSED(dest)

	endMoveRows();
}
/*-----------------------------------------------------------------------------------------------------------*/
void ReversingProxyModel::sourceRowsRemoved(const QModelIndex &parent, int start, int end)
{
	Q_ASSERT(parent.isValid() ? parent.model() == sourceModel() : true);

	Q_UNUSED(parent)
	Q_UNUSED(start)
	Q_UNUSED(end)

	endRemoveRows();
}
/*-----------------------------------------------------------------------------------------------------------*/
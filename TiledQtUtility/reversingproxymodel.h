/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QAbstractProxyModel>
#include "tiledqtutility_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDQTUTILITY_EXPORT ReversingProxyModel : public QAbstractProxyModel
{
	Q_OBJECT

public:
	explicit ReversingProxyModel(QObject *parent = nullptr);

	QModelIndex index(int row, int column, const QModelIndex &parent) const override;
	QModelIndex parent(const QModelIndex &child) const override;
	int rowCount(const QModelIndex &parent) const override;
	int columnCount(const QModelIndex &parent) const override;

	bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
		int row, int column, const QModelIndex &parent) const override;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action,
		int row, int column, const QModelIndex &parent) override;

	QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
	QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;
	void setSourceModel(QAbstractItemModel *sourceModel) override;

private slots:
	void sourceRowsAboutToBeInserted(const QModelIndex &parent, int start, int end);
	void sourceRowsInserted(const QModelIndex &parent, int start, int end);
	void sourceRowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
	void sourceRowsRemoved(const QModelIndex &parent, int start, int end);
	void sourceRowsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destParent, int dest);
	void sourceRowsMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destParent, int dest);

	void sourceColumnsAboutToBeInserted(const QModelIndex &parent, int start, int end);
	void sourceColumnsInserted(const QModelIndex &parent, int start, int end);
	void sourceColumnsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
	void sourceColumnsRemoved(const QModelIndex &parent, int start, int end);
	void sourceColumnsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destParent, int dest);
	void sourceColumnsMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destParent, int dest);

	void sourceDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
	void sourceHeaderDataChanged(Qt::Orientation orientation, int first, int last);

	void sourceLayoutAboutToBeChanged(const QList<QPersistentModelIndex> &sourceParents, QAbstractItemModel::LayoutChangeHint hint);
	void sourceLayoutChanged(const QList<QPersistentModelIndex> &sourceParents, QAbstractItemModel::LayoutChangeHint hint);
	void sourceModelAboutToBeReset();
	void sourceModelReset();

private:
	void mapDropCoordinatesToSource(int row, const QModelIndex &parent,
		int *sourceRow, QModelIndex *sourceParent) const;

private:
	QList<QPersistentModelIndex> mLayoutChangePersistentIndexes;
	QModelIndexList mProxyIndexes;
};
/*-----------------------------------------------------------------------------------------------------------*/
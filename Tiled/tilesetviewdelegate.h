/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QAbstractItemDelegate>
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetView;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetViewDelegate final : public QAbstractItemDelegate
{
public:
	explicit TilesetViewDelegate(TilesetView* tilesetView, QObject* parent = nullptr);
	~TilesetViewDelegate() override = default;

	TilesetViewDelegate(TilesetViewDelegate&&) = delete;
	TilesetViewDelegate(const TilesetViewDelegate&) = delete;

	TilesetViewDelegate& operator=(TilesetViewDelegate&&) = delete;
	TilesetViewDelegate& operator=(const TilesetViewDelegate&) = delete;

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
	TilesetView* mTilesetView;
};
/*-----------------------------------------------------------------------------------------------------------*/

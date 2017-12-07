/*-----------------------------------------------------------------------------------------------------------*/
#include <QPainter>
#include "tile.h"
#include "tilesetviewdelegate.h"
#include "tilesettablemodel.h"
#include "tilesetview.h"
#include "zoomable.h"
/*-----------------------------------------------------------------------------------------------------------*/
TilesetViewDelegate::TilesetViewDelegate(TilesetView* tilesetView, QObject* parent) :
	QAbstractItemDelegate(parent),
	mTilesetView(tilesetView)
{
	
}
/*-----------------------------------------------------------------------------------------------------------*/
void TilesetViewDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	const auto tilesetModel = qobject_cast<const TilesetTableModel*>(index.model());
	Q_ASSERT(tilesetModel);

	const auto tile = tilesetModel->tile(index);
	if (!tile) return;

	Q_ASSERT(tile);
	const auto& tileImage = tile->image();
	auto tileSize = tile->size();
	const auto zoom = mTilesetView->scale();
	const auto extra = (mTilesetView->drawGrid() ? 1 : 0);

	tileSize *= zoom;

	auto targetRect = option.rect.adjusted(0, 0, -extra, -extra);
	targetRect.setTop(targetRect.bottom() - tileSize.height() + 1);
	targetRect.setRight(targetRect.left() + tileSize.width() - 1);

	painter->drawPixmap(targetRect, tileImage);

	if (mTilesetView->markAnimatedTiles() && tile->isAnimated()) 
	{
		painter->save();

		auto scale = qMin(tileImage.width() / 32.0, tileImage.height() / 32.0);

		painter->setClipRect(targetRect);
		painter->translate(targetRect.right(),
			targetRect.bottom());
		painter->scale(scale * zoom, scale * zoom);
		painter->translate(-18, 3);
		painter->rotate(-45);
		painter->setOpacity(0.8);

		QRectF strip(0, 0, 32, 6);
		painter->fillRect(strip, Qt::black);

		painter->setRenderHint(QPainter::Antialiasing);
		painter->setBrush(Qt::white);
		painter->setPen(Qt::NoPen);

		QRectF hole(0, 0, strip.height() * 0.6, strip.height() * 0.6);
		auto step = (strip.height() - hole.height()) + hole.width();
		auto margin = (strip.height() - hole.height()) / 2;

		for (auto x = (step - hole.width()) / 2; x < strip.right(); x += step) {
			hole.moveTo(x, margin);
			painter->drawRoundedRect(hole, 25, 25, Qt::RelativeSize);
		}

		painter->restore();
	}

	if (option.state & QStyle::State_Selected)
	{
		const auto opacity = painter->opacity();
		painter->setOpacity(0.5);
		painter->fillRect(targetRect, option.palette.highlight());
		painter->setOpacity(opacity);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
QSize TilesetViewDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	Q_UNUSED(option);

	const auto tilesetModel = qobject_cast<const TilesetTableModel*>(index.model());
	const auto extra = mTilesetView->drawGrid() ? 1 : 0;

	Q_ASSERT(tilesetModel);

	if(const auto tile = tilesetModel->tile(index))
	{
		auto const tileSize = tile->size();
	
		return QSize(tileSize.width() * mTilesetView->scale() + extra,
			tileSize.height() * mTilesetView->scale() + extra);
	}

	return QSize(extra, extra);
}
/*-----------------------------------------------------------------------------------------------------------*/

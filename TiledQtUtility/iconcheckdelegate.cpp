/*-----------------------------------------------------------------------------------------------------------*/
#include <QPainter>
#include "iconcheckdelegate.h"
/*-----------------------------------------------------------------------------------------------------------*/
IconCheckDelegate::IconCheckDelegate(const QIcon& checkedIcon, const QIcon& unCheckedIcon, QObject* parent) :
	QItemDelegate(parent),
	mCheckedIcon(checkedIcon),
	mUnCheckedIcon(unCheckedIcon)
{
	Q_ASSERT(!mCheckedIcon.isNull());
	Q_ASSERT(!mUnCheckedIcon.isNull());
}
/*-----------------------------------------------------------------------------------------------------------*/
void IconCheckDelegate::drawCheck(QPainter* painter, const QStyleOptionViewItem& option, 
	const QRect& rect, Qt::CheckState state) const
{
	Q_UNUSED(option);

	decltype(auto) icon = (state == Qt::Checked) ? mCheckedIcon : mUnCheckedIcon;
	decltype(auto) pixmap = icon.pixmap(rect.size());

	auto layoutSize = pixmap.size() / pixmap.devicePixelRatio();
	QRect targetRect(QPoint(0, 0), layoutSize);
	targetRect.moveCenter(rect.center());

	painter->drawPixmap(targetRect, pixmap);
}
/*-----------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QItemDelegate>
#include "tiledqtutility_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDQTUTILITY_EXPORT IconCheckDelegate final : public QItemDelegate
{
public:
	explicit IconCheckDelegate(const QIcon& checkedIcon, const QIcon& unCheckedIcon, QObject* parent = nullptr);
	~IconCheckDelegate() override = default;

	IconCheckDelegate(const IconCheckDelegate&) = delete;
	IconCheckDelegate(IconCheckDelegate&&) = delete;

	IconCheckDelegate& operator=(const IconCheckDelegate&) = delete;
	IconCheckDelegate& operator=(IconCheckDelegate&&) = delete;

protected:
	void drawCheck(QPainter* painter, const QStyleOptionViewItem& option,
		const QRect& rect, Qt::CheckState state) const override;

private:
	QIcon mCheckedIcon;
	QIcon mUnCheckedIcon;
};
/*-----------------------------------------------------------------------------------------------------------*/
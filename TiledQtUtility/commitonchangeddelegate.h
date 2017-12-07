/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QStyledItemDelegate>
#include <QSignalMapper>
#include "tiledqtutility_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDQTUTILITY_EXPORT CommitOnChangedDelegate final : public QStyledItemDelegate
{
public:
	explicit CommitOnChangedDelegate(QObject* parent = nullptr);
	~CommitOnChangedDelegate() override = default;

	CommitOnChangedDelegate(const CommitOnChangedDelegate&) = delete;
	CommitOnChangedDelegate(CommitOnChangedDelegate&&) = delete;

	CommitOnChangedDelegate& operator=(const CommitOnChangedDelegate&) = delete;
	CommitOnChangedDelegate& operator=(CommitOnChangedDelegate&&) = delete;

	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;

private:
	QSignalMapper* mMapper;
};
/*-----------------------------------------------------------------------------------------------------------*/
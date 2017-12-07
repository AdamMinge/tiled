/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QStyledItemDelegate>
#include "tiledqtutility_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDQTUTILITY_EXPORT SpinBoxDelegate final : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit SpinBoxDelegate(const QList<std::pair<QString, QVariant>>& properties, QObject* parent = nullptr);
	~SpinBoxDelegate() override = default;

	SpinBoxDelegate(const SpinBoxDelegate&) = delete;
	SpinBoxDelegate(SpinBoxDelegate&&) = delete;

	SpinBoxDelegate& operator=(const SpinBoxDelegate&) = delete;
	SpinBoxDelegate& operator=(SpinBoxDelegate&&) = delete;

	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;

	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const override;

private:
	QList<std::pair<QString, QVariant>> mProperties;
};
/*-----------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDockWidget>
/*-----------------------------------------------------------------------------------------------------------*/
class QUndoStack;
class QUndoView;
/*-----------------------------------------------------------------------------------------------------------*/
class UndoDock final : public QDockWidget
{
	Q_OBJECT

public:
	explicit UndoDock(QWidget* parent = nullptr);
	~UndoDock() override = default;

	UndoDock(UndoDock&&) = delete;
	UndoDock(const UndoDock&) = delete;

	UndoDock& operator=(UndoDock&&) = delete;
	UndoDock& operator=(const UndoDock&) = delete;

	void setStack(QUndoStack* stack);

protected:
	void changeEvent(QEvent* event) override;

private:
	void retranslateUi();

private:
	QUndoView* mUndoView;
};
/*-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDialog>
#include "tiledqtutility_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDQTUTILITY_EXPORT DialogWithToggleView : public QDialog
{
	Q_OBJECT

public:
	explicit DialogWithToggleView(QWidget* parent = nullptr);
	virtual ~DialogWithToggleView() override = default;

	DialogWithToggleView(const DialogWithToggleView&) = delete;
	DialogWithToggleView(DialogWithToggleView&&) = delete;

	DialogWithToggleView& operator=(const DialogWithToggleView&) = delete;
	DialogWithToggleView& operator=(DialogWithToggleView&&) = delete;
	
	QAction* toggleViewAction() const;

protected:
	virtual void closeEvent(QCloseEvent *event) override;

private slots:
	void titleChanged(const QString& title);

private:
	QAction* mToggleView;
};
/*-----------------------------------------------------------------------------------------------------------*/
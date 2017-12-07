/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QWidget>
/*-----------------------------------------------------------------------------------------------------------*/
class ResetEdit final : public QWidget
{
	Q_OBJECT

public:
	explicit ResetEdit(QWidget *editor, QWidget *parent = nullptr);
	~ResetEdit() override = default;

	ResetEdit(ResetEdit&&) = delete;
	ResetEdit(const ResetEdit&) = delete;

	ResetEdit& operator=(ResetEdit&&) = delete;
	ResetEdit& operator=(const ResetEdit&) = delete;

signals:
	void reseted();

private slots:
	void buttonClicked();
};
/*-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QtProperty>
#include <QWidget>
/*-----------------------------------------------------------------------------------------------------------*/
class ResetEdit final : public QWidget
{
	Q_OBJECT

public:
	explicit ResetEdit(QtProperty *property, QWidget *editor, QWidget *parent = nullptr);
	~ResetEdit() override = default;

	ResetEdit(ResetEdit&&) = delete;
	ResetEdit(const ResetEdit&) = delete;

	ResetEdit& operator=(ResetEdit&&) = delete;
	ResetEdit& operator=(const ResetEdit&) = delete;

signals:
	void resetProperty(QtProperty* property);

private slots:
	void buttonClicked();

private:
	QtProperty* mProperty;
};
/*-----------------------------------------------------------------------------------------------------------*/

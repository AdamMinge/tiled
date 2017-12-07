/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDialog>
/*-----------------------------------------------------------------------------------------------------------*/
namespace Ui { class AddPropertyDialogClass; }
/*-----------------------------------------------------------------------------------------------------------*/
class AddPropertyDialog final : public QDialog
{
	Q_OBJECT

public:
	explicit AddPropertyDialog(QWidget* parent = nullptr);
	~AddPropertyDialog() override;

	AddPropertyDialog(AddPropertyDialog&&) = delete;
	AddPropertyDialog(const AddPropertyDialog&) = delete;

	AddPropertyDialog& operator=(AddPropertyDialog&&) = delete;
	AddPropertyDialog& operator=(const AddPropertyDialog&) = delete;

	QString propertyName() const;
    QVariant propertyValue() const;

protected:
	void changeEvent(QEvent* event) override;

private slots:
	void nameChanged(const QString &text);
	void typeChanged(const QString &text);

private:
	Ui::AddPropertyDialogClass* mUi;
};
/*-----------------------------------------------------------------------------------------------------------*/

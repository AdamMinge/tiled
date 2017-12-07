/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDialog>
/*-----------------------------------------------------------------------------------------------------------*/
namespace Ui { class PreferencesDialog; }
/*-----------------------------------------------------------------------------------------------------------*/
class PreferencesDialog final : public QDialog
{
	Q_OBJECT

public:
	explicit PreferencesDialog(QWidget* parent = nullptr);
	~PreferencesDialog() override;

	PreferencesDialog(const PreferencesDialog&) = delete;
	PreferencesDialog(PreferencesDialog&&) = delete;

	PreferencesDialog& operator=(const PreferencesDialog&) = delete;
	PreferencesDialog& operator=(PreferencesDialog&&) = delete;

protected:
	void changeEvent(QEvent* event) override;

private slots:
	void selectedLanguageChanged();
	void selectedStyleChanged();

	void languageChanged();
	void styleChanged();

private:
	void updateLanguagesList();
	void updateStylesList();

private:
	Ui::PreferencesDialog* mUi;
};
/*-----------------------------------------------------------------------------------------------------------*/

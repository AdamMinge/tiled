/*-----------------------------------------------------------------------------------------------------------*/
#include <QEvent>
#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include "languagemanager.h"
#include "stylemanager.h"
#include "utils.h"
/*-----------------------------------------------------------------------------------------------------------*/
PreferencesDialog::PreferencesDialog(QWidget* parent) : 
	QDialog(parent),
	mUi(new Ui::PreferencesDialog)
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	mUi->setupUi(this);
	resize(dpiScaled(size()));

	updateLanguagesList();
	updateStylesList();

	connect(mUi->languageComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &PreferencesDialog::selectedLanguageChanged);
	connect(LanguageManager::instance(), &LanguageManager::languageChanged,
		this, &PreferencesDialog::languageChanged);
	connect(LanguageManager::instance(), &LanguageManager::translationsDirChanged,
		this, &PreferencesDialog::updateLanguagesList);
	connect(LanguageManager::instance(), &LanguageManager::translationsPrefixChanged,
		this, &PreferencesDialog::updateLanguagesList);

	connect(mUi->stylesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &PreferencesDialog::selectedStyleChanged);
	connect(StyleManager::instance(), &StyleManager::styleChanged,
		this, &PreferencesDialog::styleChanged);
	connect(StyleManager::instance(), &StyleManager::styleRegistered,
		this, &PreferencesDialog::updateStylesList);
	connect(StyleManager::instance(), &StyleManager::styleUnregistered,
		this, &PreferencesDialog::updateStylesList);
}
/*-----------------------------------------------------------------------------------------------------------*/
PreferencesDialog::~PreferencesDialog()
{
	delete mUi;
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesDialog::changeEvent(QEvent* event)
{
	QDialog::changeEvent(event);

	switch (event->type())
	{
	case QEvent::LanguageChange:
		mUi->retranslateUi(this);
		break;
	default:
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesDialog::selectedLanguageChanged()
{
	auto language = mUi->languageComboBox->currentData().toString();
	if (language.isEmpty()) language = QLocale::system().name();
	LanguageManager::instance()->setLanguage(language);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesDialog::selectedStyleChanged()
{
	auto style = mUi->stylesComboBox->currentText();
	StyleManager::instance()->setStyle(style);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesDialog::languageChanged()
{
	auto languageManager = LanguageManager::instance();
	auto language = languageManager->language();

	auto index = mUi->languageComboBox->findData(language);
	if (index == -1) index = 0;
	Q_ASSERT(index >= 0 && index <= mUi->languageComboBox->count());

	mUi->languageComboBox->setCurrentIndex(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesDialog::styleChanged()
{
	auto styleManager = StyleManager::instance();
	auto style = styleManager->style();

	auto index = mUi->stylesComboBox->findText(style);
	Q_ASSERT(index >= 0 && index <= mUi->stylesComboBox->count());

	mUi->stylesComboBox->setCurrentIndex(index);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesDialog::updateLanguagesList()
{
	auto languageManager = LanguageManager::instance();
	auto languages = languageManager->availableLanguages();
	auto language = languageManager->language();
	
	mUi->languageComboBox->blockSignals(true);
	mUi->languageComboBox->clear();

	for(decltype(auto) name : languages)
	{
		QLocale locale(name);
		auto string = QString(QLatin1String("%1 (%2)"))
			.arg(QLocale::languageToString(locale.language()))
			.arg(QLocale::countryToString(locale.country()));
		mUi->languageComboBox->addItem(string, name);
	}
	mUi->languageComboBox->model()->sort(0);
	mUi->languageComboBox->insertItem(0, tr("System default"));

	auto index = mUi->languageComboBox->findData(language);
	if (index == -1) index = 0;

	mUi->languageComboBox->setCurrentIndex(index);
	mUi->languageComboBox->blockSignals(false);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesDialog::updateStylesList()
{
	auto styleManager = StyleManager::instance();
	auto styles = styleManager->availableStyles();
	auto style = styleManager->style();

	mUi->stylesComboBox->blockSignals(true);
	mUi->stylesComboBox->clear();

	mUi->stylesComboBox->addItems(styles);
	mUi->stylesComboBox->model()->sort(0);

	auto index = mUi->stylesComboBox->findText(style);
	Q_ASSERT(index >= 0 && index <= mUi->stylesComboBox->count());
	mUi->stylesComboBox->setCurrentIndex(index);

	mUi->stylesComboBox->blockSignals(false);
}
/*-----------------------------------------------------------------------------------------------------------*/

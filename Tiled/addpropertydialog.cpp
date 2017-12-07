/*-----------------------------------------------------------------------------------------------------------*/
#include <QPushButton>
#include <QUrl>
#include "addpropertydialog.h"
#include "ui_addpropertydialog.h"
#include "preferencesmanager.h"
#include "utils.h"
/*-----------------------------------------------------------------------------------------------------------*/
AddPropertyDialog::AddPropertyDialog(QWidget* parent) :
	QDialog(parent),
	mUi(new Ui::AddPropertyDialogClass)
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	mUi->setupUi(this);
	resize(dpiScaled(size()));

	mUi->typeBox->addItem(typeToName(QVariant::Bool), false);
	mUi->typeBox->addItem(typeToName(QVariant::Int), 0);
	mUi->typeBox->addItem(typeToName(QVariant::Double), 0.0);
	mUi->typeBox->addItem(typeToName(QVariant::String), QString());
	mUi->typeBox->addItem(typeToName(QVariant::Color), QColor());
	mUi->typeBox->addItem(typeToName(QVariant::Url), QUrl());
	
	auto current = PreferencesManager::instance()->newPropertyType();
	mUi->typeBox->setCurrentText(!current.isEmpty() ? current : typeToName(QVariant::Bool));

	mUi->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

	connect(mUi->name, &QLineEdit::textChanged, this, &AddPropertyDialog::nameChanged);
	connect(mUi->typeBox, &QComboBox::currentTextChanged, this, &AddPropertyDialog::typeChanged);
}
/*-----------------------------------------------------------------------------------------------------------*/
AddPropertyDialog::~AddPropertyDialog()
{
	delete mUi;
}
/*-----------------------------------------------------------------------------------------------------------*/
QString AddPropertyDialog::propertyName() const
{
	return mUi->name->text();
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant AddPropertyDialog::propertyValue() const
{
	return mUi->typeBox->currentData();
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddPropertyDialog::changeEvent(QEvent* event)
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
void AddPropertyDialog::nameChanged(const QString& text)
{
	mUi->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
void AddPropertyDialog::typeChanged(const QString &text)
{
	PreferencesManager::instance()->setNewpropertyType(text);
}
/*-----------------------------------------------------------------------------------------------------------*/
/********************************************************************************
** Form generated from reading UI file 'addpropertydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPROPERTYDIALOG_H
#define UI_ADDPROPERTYDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_AddPropertyDialogClass
{
public:
    QGridLayout *gridLayout;
    QLineEdit *name;
    QComboBox *typeBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddPropertyDialogClass)
    {
        if (AddPropertyDialogClass->objectName().isEmpty())
            AddPropertyDialogClass->setObjectName(QStringLiteral("AddPropertyDialogClass"));
        AddPropertyDialogClass->resize(298, 67);
        gridLayout = new QGridLayout(AddPropertyDialogClass);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        name = new QLineEdit(AddPropertyDialogClass);
        name->setObjectName(QStringLiteral("name"));
        name->setReadOnly(false);

        gridLayout->addWidget(name, 0, 0, 1, 1);

        typeBox = new QComboBox(AddPropertyDialogClass);
        typeBox->setObjectName(QStringLiteral("typeBox"));

        gridLayout->addWidget(typeBox, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(AddPropertyDialogClass);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 2);


        retranslateUi(AddPropertyDialogClass);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddPropertyDialogClass, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddPropertyDialogClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddPropertyDialogClass);
    } // setupUi

    void retranslateUi(QDialog *AddPropertyDialogClass)
    {
        AddPropertyDialogClass->setWindowTitle(QApplication::translate("AddPropertyDialogClass", "Add Property", Q_NULLPTR));
        name->setPlaceholderText(QApplication::translate("AddPropertyDialogClass", "Property name", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddPropertyDialogClass: public Ui_AddPropertyDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPROPERTYDIALOG_H

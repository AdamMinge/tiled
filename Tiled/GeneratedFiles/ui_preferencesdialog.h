/********************************************************************************
** Form generated from reading UI file 'preferencesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *preferencesTab;
    QWidget *generalTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *interfaceBox;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *languageComboBox;
    QLabel *label_2;
    QComboBox *stylesComboBox;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *closeButton;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QStringLiteral("PreferencesDialog"));
        PreferencesDialog->resize(356, 346);
        verticalLayout = new QVBoxLayout(PreferencesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        preferencesTab = new QTabWidget(PreferencesDialog);
        preferencesTab->setObjectName(QStringLiteral("preferencesTab"));
        generalTab = new QWidget();
        generalTab->setObjectName(QStringLiteral("generalTab"));
        verticalLayout_2 = new QVBoxLayout(generalTab);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        interfaceBox = new QGroupBox(generalTab);
        interfaceBox->setObjectName(QStringLiteral("interfaceBox"));
        formLayout = new QFormLayout(interfaceBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(interfaceBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        languageComboBox = new QComboBox(interfaceBox);
        languageComboBox->setObjectName(QStringLiteral("languageComboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(languageComboBox->sizePolicy().hasHeightForWidth());
        languageComboBox->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::FieldRole, languageComboBox);

        label_2 = new QLabel(interfaceBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        stylesComboBox = new QComboBox(interfaceBox);
        stylesComboBox->setObjectName(QStringLiteral("stylesComboBox"));
        sizePolicy.setHeightForWidth(stylesComboBox->sizePolicy().hasHeightForWidth());
        stylesComboBox->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::FieldRole, stylesComboBox);


        verticalLayout_2->addWidget(interfaceBox);

        preferencesTab->addTab(generalTab, QString());

        verticalLayout->addWidget(preferencesTab);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        closeButton = new QPushButton(PreferencesDialog);
        closeButton->setObjectName(QStringLiteral("closeButton"));

        hboxLayout->addWidget(closeButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(PreferencesDialog);
        QObject::connect(closeButton, SIGNAL(clicked()), PreferencesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Dialog", Q_NULLPTR));
        interfaceBox->setTitle(QApplication::translate("PreferencesDialog", "Interface", Q_NULLPTR));
        label->setText(QApplication::translate("PreferencesDialog", "Language:", Q_NULLPTR));
        label_2->setText(QApplication::translate("PreferencesDialog", "Styles:", Q_NULLPTR));
        preferencesTab->setTabText(preferencesTab->indexOf(generalTab), QApplication::translate("PreferencesDialog", "General", Q_NULLPTR));
        closeButton->setText(QApplication::translate("PreferencesDialog", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H

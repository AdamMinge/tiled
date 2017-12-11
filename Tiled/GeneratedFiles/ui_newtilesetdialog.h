/********************************************************************************
** Form generated from reading UI file 'newtilesetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWTILESETDIALOG_H
#define UI_NEWTILESETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "colorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_NewTilesetDialogClass
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *tilesetGroupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *name;
    QLabel *nameLabel;
    QGroupBox *imageGroupBox;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QSpinBox *spacing;
    QLabel *marginLabel;
    QLabel *tileWidthLabel;
    QSpinBox *margin;
    QLabel *spacingLabel;
    QLabel *tileHeightLabel;
    QSpinBox *tileWidth;
    QSpinBox *tileHeight;
    QLineEdit *image;
    QCheckBox *useTransparentColor;
    QSpacerItem *horizontalSpacer_2;
    QLabel *sourceLabel;
    ColorButton *colorButton;
    QToolButton *dropperButton;
    QPushButton *browseButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewTilesetDialogClass)
    {
        if (NewTilesetDialogClass->objectName().isEmpty())
            NewTilesetDialogClass->setObjectName(QStringLiteral("NewTilesetDialogClass"));
        NewTilesetDialogClass->resize(374, 244);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewTilesetDialogClass->sizePolicy().hasHeightForWidth());
        NewTilesetDialogClass->setSizePolicy(sizePolicy);
        NewTilesetDialogClass->setMinimumSize(QSize(374, 244));
        NewTilesetDialogClass->setMaximumSize(QSize(374, 244));
        verticalLayout = new QVBoxLayout(NewTilesetDialogClass);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        tilesetGroupBox = new QGroupBox(NewTilesetDialogClass);
        tilesetGroupBox->setObjectName(QStringLiteral("tilesetGroupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tilesetGroupBox->sizePolicy().hasHeightForWidth());
        tilesetGroupBox->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(tilesetGroupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        name = new QLineEdit(tilesetGroupBox);
        name->setObjectName(QStringLiteral("name"));
        sizePolicy1.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
        name->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(name, 0, 1, 1, 2);

        nameLabel = new QLabel(tilesetGroupBox);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(nameLabel, 0, 0, 1, 1);


        verticalLayout->addWidget(tilesetGroupBox);

        imageGroupBox = new QGroupBox(NewTilesetDialogClass);
        imageGroupBox->setObjectName(QStringLiteral("imageGroupBox"));
        sizePolicy1.setHeightForWidth(imageGroupBox->sizePolicy().hasHeightForWidth());
        imageGroupBox->setSizePolicy(sizePolicy1);
        imageGroupBox->setCheckable(false);
        gridLayout = new QGridLayout(imageGroupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 2, 1, 1);

        spacing = new QSpinBox(imageGroupBox);
        spacing->setObjectName(QStringLiteral("spacing"));
        spacing->setMinimum(0);
        spacing->setMaximum(9999);
        spacing->setValue(0);

        gridLayout_3->addWidget(spacing, 1, 4, 1, 1);

        marginLabel = new QLabel(imageGroupBox);
        marginLabel->setObjectName(QStringLiteral("marginLabel"));
        sizePolicy2.setHeightForWidth(marginLabel->sizePolicy().hasHeightForWidth());
        marginLabel->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(marginLabel, 0, 3, 1, 1);

        tileWidthLabel = new QLabel(imageGroupBox);
        tileWidthLabel->setObjectName(QStringLiteral("tileWidthLabel"));
        sizePolicy2.setHeightForWidth(tileWidthLabel->sizePolicy().hasHeightForWidth());
        tileWidthLabel->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(tileWidthLabel, 0, 0, 1, 1);

        margin = new QSpinBox(imageGroupBox);
        margin->setObjectName(QStringLiteral("margin"));
        margin->setMinimum(0);
        margin->setMaximum(9999);
        margin->setValue(0);

        gridLayout_3->addWidget(margin, 0, 4, 1, 1);

        spacingLabel = new QLabel(imageGroupBox);
        spacingLabel->setObjectName(QStringLiteral("spacingLabel"));
        sizePolicy2.setHeightForWidth(spacingLabel->sizePolicy().hasHeightForWidth());
        spacingLabel->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(spacingLabel, 1, 3, 1, 1);

        tileHeightLabel = new QLabel(imageGroupBox);
        tileHeightLabel->setObjectName(QStringLiteral("tileHeightLabel"));
        sizePolicy2.setHeightForWidth(tileHeightLabel->sizePolicy().hasHeightForWidth());
        tileHeightLabel->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(tileHeightLabel, 1, 0, 1, 1);

        tileWidth = new QSpinBox(imageGroupBox);
        tileWidth->setObjectName(QStringLiteral("tileWidth"));
        tileWidth->setEnabled(true);
        tileWidth->setMinimum(1);
        tileWidth->setMaximum(9999);
        tileWidth->setValue(32);

        gridLayout_3->addWidget(tileWidth, 0, 1, 1, 1);

        tileHeight = new QSpinBox(imageGroupBox);
        tileHeight->setObjectName(QStringLiteral("tileHeight"));
        tileHeight->setMinimum(1);
        tileHeight->setMaximum(9999);
        tileHeight->setValue(32);

        gridLayout_3->addWidget(tileHeight, 1, 1, 1, 1);


        gridLayout->addLayout(gridLayout_3, 2, 0, 1, 6);

        image = new QLineEdit(imageGroupBox);
        image->setObjectName(QStringLiteral("image"));

        gridLayout->addWidget(image, 0, 1, 1, 4);

        useTransparentColor = new QCheckBox(imageGroupBox);
        useTransparentColor->setObjectName(QStringLiteral("useTransparentColor"));

        gridLayout->addWidget(useTransparentColor, 1, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(0, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        sourceLabel = new QLabel(imageGroupBox);
        sourceLabel->setObjectName(QStringLiteral("sourceLabel"));
        sizePolicy2.setHeightForWidth(sourceLabel->sizePolicy().hasHeightForWidth());
        sourceLabel->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(sourceLabel, 0, 0, 1, 1);

        colorButton = new ColorButton(imageGroupBox);
        colorButton->setObjectName(QStringLiteral("colorButton"));
        colorButton->setEnabled(false);

        gridLayout->addWidget(colorButton, 1, 2, 1, 1);

        dropperButton = new QToolButton(imageGroupBox);
        dropperButton->setObjectName(QStringLiteral("dropperButton"));
        dropperButton->setEnabled(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MapEditor/images/16x16/stock-tool-color-picker-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        dropperButton->setIcon(icon);

        gridLayout->addWidget(dropperButton, 1, 3, 1, 1);

        browseButton = new QPushButton(imageGroupBox);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        gridLayout->addWidget(browseButton, 0, 5, 1, 1);


        verticalLayout->addWidget(imageGroupBox);

        buttonBox = new QDialogButtonBox(NewTilesetDialogClass);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        nameLabel->setBuddy(name);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(name, image);
        QWidget::setTabOrder(image, useTransparentColor);
        QWidget::setTabOrder(useTransparentColor, colorButton);
        QWidget::setTabOrder(colorButton, dropperButton);
        QWidget::setTabOrder(dropperButton, tileWidth);
        QWidget::setTabOrder(tileWidth, tileHeight);
        QWidget::setTabOrder(tileHeight, margin);
        QWidget::setTabOrder(margin, spacing);

        retranslateUi(NewTilesetDialogClass);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewTilesetDialogClass, SLOT(tryAccept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewTilesetDialogClass, SLOT(reject()));
        QObject::connect(useTransparentColor, SIGNAL(toggled(bool)), colorButton, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(NewTilesetDialogClass);
    } // setupUi

    void retranslateUi(QDialog *NewTilesetDialogClass)
    {
        NewTilesetDialogClass->setWindowTitle(QApplication::translate("NewTilesetDialogClass", "New Tileset", nullptr));
        tilesetGroupBox->setTitle(QApplication::translate("NewTilesetDialogClass", "Tileset", nullptr));
        nameLabel->setText(QApplication::translate("NewTilesetDialogClass", "&Name:", nullptr));
        imageGroupBox->setTitle(QApplication::translate("NewTilesetDialogClass", "Image", nullptr));
        spacing->setSuffix(QApplication::translate("NewTilesetDialogClass", " px", nullptr));
#ifndef QT_NO_TOOLTIP
        marginLabel->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        marginLabel->setText(QApplication::translate("NewTilesetDialogClass", "Margin:", nullptr));
        tileWidthLabel->setText(QApplication::translate("NewTilesetDialogClass", "Tile width:", nullptr));
        margin->setSuffix(QApplication::translate("NewTilesetDialogClass", " px", nullptr));
#ifndef QT_NO_TOOLTIP
        spacingLabel->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        spacingLabel->setText(QApplication::translate("NewTilesetDialogClass", "Spacing:", nullptr));
        tileHeightLabel->setText(QApplication::translate("NewTilesetDialogClass", "Tile height:", nullptr));
        tileWidth->setSuffix(QApplication::translate("NewTilesetDialogClass", " px", nullptr));
        tileHeight->setSuffix(QApplication::translate("NewTilesetDialogClass", " px", nullptr));
        useTransparentColor->setText(QApplication::translate("NewTilesetDialogClass", "Use transparent color:", nullptr));
        sourceLabel->setText(QApplication::translate("NewTilesetDialogClass", "Source:", nullptr));
#ifndef QT_NO_TOOLTIP
        dropperButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        dropperButton->setText(QString());
        browseButton->setText(QApplication::translate("NewTilesetDialogClass", "&Browse...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewTilesetDialogClass: public Ui_NewTilesetDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWTILESETDIALOG_H

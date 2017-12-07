/********************************************************************************
** Form generated from reading UI file 'newmapdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMAPDIALOG_H
#define UI_NEWMAPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_NewMapDialogClass
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QSpinBox *mapWidth;
    QLabel *label_2;
    QSpinBox *mapHeight;
    QLabel *pixelSizeLabel;
    QLabel *label;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QSpinBox *tileWidth;
    QLabel *label_4;
    QSpinBox *tileHeight;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QComboBox *orientation;
    QLabel *renderOrderLabel;
    QComboBox *renderOrder;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewMapDialogClass)
    {
        if (NewMapDialogClass->objectName().isEmpty())
            NewMapDialogClass->setObjectName(QStringLiteral("NewMapDialogClass"));
        NewMapDialogClass->resize(352, 253);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewMapDialogClass->sizePolicy().hasHeightForWidth());
        NewMapDialogClass->setSizePolicy(sizePolicy);
        NewMapDialogClass->setMinimumSize(QSize(352, 253));
        NewMapDialogClass->setMaximumSize(QSize(352, 253));
        gridLayout_3 = new QGridLayout(NewMapDialogClass);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        groupBox_3 = new QGroupBox(NewMapDialogClass);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        mapWidth = new QSpinBox(groupBox_3);
        mapWidth->setObjectName(QStringLiteral("mapWidth"));
        mapWidth->setMinimum(1);
        mapWidth->setMaximum(99999);
        mapWidth->setValue(100);

        gridLayout_2->addWidget(mapWidth, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        mapHeight = new QSpinBox(groupBox_3);
        mapHeight->setObjectName(QStringLiteral("mapHeight"));
        mapHeight->setMinimum(1);
        mapHeight->setMaximum(99999);
        mapHeight->setValue(100);

        gridLayout_2->addWidget(mapHeight, 2, 1, 1, 1);

        pixelSizeLabel = new QLabel(groupBox_3);
        pixelSizeLabel->setObjectName(QStringLiteral("pixelSizeLabel"));
        pixelSizeLabel->setText(QStringLiteral(""));

        gridLayout_2->addWidget(pixelSizeLabel, 4, 0, 1, 2);

        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(NewMapDialogClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        tileWidth = new QSpinBox(groupBox_2);
        tileWidth->setObjectName(QStringLiteral("tileWidth"));
        tileWidth->setMinimum(1);
        tileWidth->setMaximum(9999);
        tileWidth->setValue(32);

        gridLayout->addWidget(tileWidth, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        tileHeight = new QSpinBox(groupBox_2);
        tileHeight->setObjectName(QStringLiteral("tileHeight"));
        tileHeight->setMinimum(1);
        tileHeight->setMaximum(9999);
        tileHeight->setValue(32);

        gridLayout->addWidget(tileHeight, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 2);


        gridLayout_3->addWidget(groupBox_2, 1, 1, 1, 1);

        groupBox = new QGroupBox(NewMapDialogClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        orientation = new QComboBox(groupBox);
        orientation->setObjectName(QStringLiteral("orientation"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(orientation->sizePolicy().hasHeightForWidth());
        orientation->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(orientation, 0, 1, 1, 1);

        renderOrderLabel = new QLabel(groupBox);
        renderOrderLabel->setObjectName(QStringLiteral("renderOrderLabel"));

        gridLayout_4->addWidget(renderOrderLabel, 1, 0, 1, 1);

        renderOrder = new QComboBox(groupBox);
        renderOrder->setObjectName(QStringLiteral("renderOrder"));

        gridLayout_4->addWidget(renderOrder, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 2);

        buttonBox = new QDialogButtonBox(NewMapDialogClass);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 2, 0, 1, 2);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(mapHeight);
        label->setBuddy(mapWidth);
        label_3->setBuddy(tileWidth);
        label_4->setBuddy(tileHeight);
        renderOrderLabel->setBuddy(renderOrder);
        label_5->setBuddy(orientation);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(orientation, renderOrder);
        QWidget::setTabOrder(renderOrder, mapWidth);
        QWidget::setTabOrder(mapWidth, mapHeight);
        QWidget::setTabOrder(mapHeight, tileWidth);
        QWidget::setTabOrder(tileWidth, tileHeight);

        retranslateUi(NewMapDialogClass);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewMapDialogClass, SLOT(tryAccept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewMapDialogClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewMapDialogClass);
    } // setupUi

    void retranslateUi(QDialog *NewMapDialogClass)
    {
        NewMapDialogClass->setWindowTitle(QApplication::translate("NewMapDialogClass", "New Map", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("NewMapDialogClass", "Map size", Q_NULLPTR));
        mapWidth->setSuffix(QApplication::translate("NewMapDialogClass", " tiles", Q_NULLPTR));
        label_2->setText(QApplication::translate("NewMapDialogClass", "Height:", Q_NULLPTR));
        mapHeight->setSuffix(QApplication::translate("NewMapDialogClass", " tiles", Q_NULLPTR));
        label->setText(QApplication::translate("NewMapDialogClass", "Width:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("NewMapDialogClass", "Tile size", Q_NULLPTR));
        label_3->setText(QApplication::translate("NewMapDialogClass", "Width:", Q_NULLPTR));
        tileWidth->setSuffix(QApplication::translate("NewMapDialogClass", " px", Q_NULLPTR));
        label_4->setText(QApplication::translate("NewMapDialogClass", "Height:", Q_NULLPTR));
        tileHeight->setSuffix(QApplication::translate("NewMapDialogClass", " px", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("NewMapDialogClass", "Map", Q_NULLPTR));
        orientation->clear();
        orientation->insertItems(0, QStringList()
         << QApplication::translate("NewMapDialogClass", "Orthogonal", Q_NULLPTR)
         << QApplication::translate("NewMapDialogClass", "Isometric", Q_NULLPTR)
         << QApplication::translate("NewMapDialogClass", "Hexagonal", Q_NULLPTR)
        );
        renderOrderLabel->setText(QApplication::translate("NewMapDialogClass", "Tile render order:", Q_NULLPTR));
        renderOrder->clear();
        renderOrder->insertItems(0, QStringList()
         << QApplication::translate("NewMapDialogClass", "Right Down", Q_NULLPTR)
         << QApplication::translate("NewMapDialogClass", "Right Up", Q_NULLPTR)
         << QApplication::translate("NewMapDialogClass", "Left Down", Q_NULLPTR)
         << QApplication::translate("NewMapDialogClass", "Left Up", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("NewMapDialogClass", "Orientation:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewMapDialogClass: public Ui_NewMapDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMAPDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'imagecolorpickerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGECOLORPICKERWIDGET_H
#define UI_IMAGECOLORPICKERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_ImageColorPickerWidgetClass
{
public:
    QVBoxLayout *verticalLayout;
    ClickableLabel *imageArea;
    QHBoxLayout *horizontalLayout;
    QLabel *preview;
    QLabel *colorName;
    QSpacerItem *horizontalSpacer;

    void setupUi(QFrame *ImageColorPickerWidgetClass)
    {
        if (ImageColorPickerWidgetClass->objectName().isEmpty())
            ImageColorPickerWidgetClass->setObjectName(QStringLiteral("ImageColorPickerWidgetClass"));
        ImageColorPickerWidgetClass->setWindowModality(Qt::WindowModal);
        ImageColorPickerWidgetClass->resize(247, 137);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ImageColorPickerWidgetClass->sizePolicy().hasHeightForWidth());
        ImageColorPickerWidgetClass->setSizePolicy(sizePolicy);
        ImageColorPickerWidgetClass->setMinimumSize(QSize(196, 128));
        ImageColorPickerWidgetClass->setFrameShape(QFrame::StyledPanel);
        verticalLayout = new QVBoxLayout(ImageColorPickerWidgetClass);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        imageArea = new ClickableLabel(ImageColorPickerWidgetClass);
        imageArea->setObjectName(QStringLiteral("imageArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(imageArea->sizePolicy().hasHeightForWidth());
        imageArea->setSizePolicy(sizePolicy1);
        imageArea->setMinimumSize(QSize(222, 0));
        imageArea->setCursor(QCursor(Qt::CrossCursor));
        imageArea->setMouseTracking(true);
        imageArea->setFrameShape(QFrame::StyledPanel);
        imageArea->setFrameShadow(QFrame::Sunken);
        imageArea->setAlignment(Qt::AlignCenter);
        imageArea->setMargin(2);

        verticalLayout->addWidget(imageArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        preview = new QLabel(ImageColorPickerWidgetClass);
        preview->setObjectName(QStringLiteral("preview"));
        preview->setFrameShape(QFrame::StyledPanel);
        preview->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(preview);

        colorName = new QLabel(ImageColorPickerWidgetClass);
        colorName->setObjectName(QStringLiteral("colorName"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(colorName->sizePolicy().hasHeightForWidth());
        colorName->setSizePolicy(sizePolicy2);
        colorName->setText(QStringLiteral("#000000"));

        horizontalLayout->addWidget(colorName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ImageColorPickerWidgetClass);

        QMetaObject::connectSlotsByName(ImageColorPickerWidgetClass);
    } // setupUi

    void retranslateUi(QFrame *ImageColorPickerWidgetClass)
    {
        imageArea->setText(QString());
        preview->setText(QString());
        Q_UNUSED(ImageColorPickerWidgetClass);
    } // retranslateUi

};

namespace Ui {
    class ImageColorPickerWidgetClass: public Ui_ImageColorPickerWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGECOLORPICKERWIDGET_H

/********************************************************************************
** Form generated from reading UI file 'noeditorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOEDITORWIDGET_H
#define UI_NOEDITORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoEditorWidgetClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *newMapButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *NoEditorWidgetClass)
    {
        if (NoEditorWidgetClass->objectName().isEmpty())
            NoEditorWidgetClass->setObjectName(QStringLiteral("NoEditorWidgetClass"));
        NoEditorWidgetClass->resize(400, 355);
        gridLayout = new QGridLayout(NoEditorWidgetClass);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 5, -1, 5);
        label = new QLabel(NoEditorWidgetClass);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(21);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 5, -1, 5);
        newMapButton = new QPushButton(NoEditorWidgetClass);
        newMapButton->setObjectName(QStringLiteral("newMapButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(newMapButton->sizePolicy().hasHeightForWidth());
        newMapButton->setSizePolicy(sizePolicy);
        newMapButton->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(newMapButton);


        gridLayout->addLayout(horizontalLayout_4, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);


        retranslateUi(NoEditorWidgetClass);

        QMetaObject::connectSlotsByName(NoEditorWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *NoEditorWidgetClass)
    {
        NoEditorWidgetClass->setWindowTitle(QApplication::translate("NoEditorWidgetClass", "Form", nullptr));
        label->setText(QApplication::translate("NoEditorWidgetClass", "No Open Documents", nullptr));
        newMapButton->setText(QApplication::translate("NoEditorWidgetClass", "New Map...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NoEditorWidgetClass: public Ui_NoEditorWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOEDITORWIDGET_H

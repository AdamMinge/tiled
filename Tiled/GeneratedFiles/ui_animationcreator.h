/********************************************************************************
** Form generated from reading UI file 'animationcreator.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATIONCREATOR_H
#define UI_ANIMATIONCREATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include "tilepreview.h"
#include "tilesetview.h"

QT_BEGIN_NAMESPACE

class Ui_AnimationCreatorClass
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *toolbarLayout;
    TilesetView *tilesetView;
    TilePreview *preview;
    QTreeView *frameList;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *cancelButton;

    void setupUi(QDialog *AnimationCreatorClass)
    {
        if (AnimationCreatorClass->objectName().isEmpty())
            AnimationCreatorClass->setObjectName(QStringLiteral("AnimationCreatorClass"));
        AnimationCreatorClass->resize(513, 300);
        verticalLayout = new QVBoxLayout(AnimationCreatorClass);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(1);
        toolbarLayout = new QHBoxLayout();
        toolbarLayout->setSpacing(2);
        toolbarLayout->setObjectName(QStringLiteral("toolbarLayout"));
        toolbarLayout->setContentsMargins(-1, 0, -1, -1);

        gridLayout->addLayout(toolbarLayout, 2, 0, 1, 1);

        tilesetView = new TilesetView(AnimationCreatorClass);
        tilesetView->setObjectName(QStringLiteral("tilesetView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tilesetView->sizePolicy().hasHeightForWidth());
        tilesetView->setSizePolicy(sizePolicy);
        tilesetView->setDragEnabled(true);

        gridLayout->addWidget(tilesetView, 0, 1, 4, 1);

        preview = new TilePreview(AnimationCreatorClass);
        preview->setObjectName(QStringLiteral("preview"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(preview->sizePolicy().hasHeightForWidth());
        preview->setSizePolicy(sizePolicy1);
        preview->setFrameShape(QFrame::NoFrame);
        preview->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(preview, 3, 0, 1, 1);

        frameList = new QTreeView(AnimationCreatorClass);
        frameList->setObjectName(QStringLiteral("frameList"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(frameList->sizePolicy().hasHeightForWidth());
        frameList->setSizePolicy(sizePolicy2);
        frameList->setAcceptDrops(true);
        frameList->setProperty("showDropIndicator", QVariant(true));
        frameList->setDragEnabled(true);
        frameList->setDragDropMode(QAbstractItemView::DragDrop);
        frameList->setDefaultDropAction(Qt::MoveAction);
        frameList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        frameList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        frameList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        frameList->setItemsExpandable(true);

        gridLayout->addWidget(frameList, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        cancelButton = new QPushButton(AnimationCreatorClass);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(AnimationCreatorClass);
        QObject::connect(cancelButton, SIGNAL(clicked()), AnimationCreatorClass, SLOT(close()));

        QMetaObject::connectSlotsByName(AnimationCreatorClass);
    } // setupUi

    void retranslateUi(QDialog *AnimationCreatorClass)
    {
        AnimationCreatorClass->setWindowTitle(QApplication::translate("AnimationCreatorClass", "Dialog", nullptr));
        preview->setText(QString());
        cancelButton->setText(QApplication::translate("AnimationCreatorClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnimationCreatorClass: public Ui_AnimationCreatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONCREATOR_H

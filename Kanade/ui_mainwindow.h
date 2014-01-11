/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "kanade.h"
#include "color_wheel.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_2;
    QToolButton *toolButton;
    QToolButton *toolButton_5;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QScrollBar *hSb_Width;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QScrollBar *hSb_Opacity;
    Color_Wheel *colorWheelholder;
    QSpacerItem *verticalSpacer;
    Kanade *canvasHolder;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(626, 472);
        MainWindow->setDockNestingEnabled(false);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        toolButton_2 = new QToolButton(centralWidget);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));

        horizontalLayout_2->addWidget(toolButton_2);

        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout_2->addWidget(toolButton);

        toolButton_5 = new QToolButton(centralWidget);
        toolButton_5->setObjectName(QStringLiteral("toolButton_5"));

        horizontalLayout_2->addWidget(toolButton_5);

        toolButton_3 = new QToolButton(centralWidget);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));

        horizontalLayout_2->addWidget(toolButton_3);

        toolButton_4 = new QToolButton(centralWidget);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));

        horizontalLayout_2->addWidget(toolButton_4);


        verticalLayout->addLayout(horizontalLayout_2);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_2);

        hSb_Width = new QScrollBar(centralWidget);
        hSb_Width->setObjectName(QStringLiteral("hSb_Width"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(15);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(hSb_Width->sizePolicy().hasHeightForWidth());
        hSb_Width->setSizePolicy(sizePolicy1);
        hSb_Width->setMaximumSize(QSize(300, 16777215));
        hSb_Width->setMaximum(40);
        hSb_Width->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(hSb_Width);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_3);

        hSb_Opacity = new QScrollBar(centralWidget);
        hSb_Opacity->setObjectName(QStringLiteral("hSb_Opacity"));
        sizePolicy1.setHeightForWidth(hSb_Opacity->sizePolicy().hasHeightForWidth());
        hSb_Opacity->setSizePolicy(sizePolicy1);
        hSb_Opacity->setMaximumSize(QSize(16777215, 16777215));
        hSb_Opacity->setMaximum(255);
        hSb_Opacity->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(hSb_Opacity);


        verticalLayout->addLayout(horizontalLayout_5);

        colorWheelholder = new Color_Wheel(centralWidget);
        colorWheelholder->setObjectName(QStringLiteral("colorWheelholder"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(colorWheelholder->sizePolicy().hasHeightForWidth());
        colorWheelholder->setSizePolicy(sizePolicy2);
        colorWheelholder->setMinimumSize(QSize(200, 200));
        colorWheelholder->setMaximumSize(QSize(200, 200));

        verticalLayout->addWidget(colorWheelholder);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        canvasHolder = new Kanade(centralWidget);
        canvasHolder->setObjectName(QStringLiteral("canvasHolder"));

        horizontalLayout->addWidget(canvasHolder);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 626, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit(&Q)", 0));
        toolButton_2->setText(QApplication::translate("MainWindow", "...", 0));
        toolButton->setText(QApplication::translate("MainWindow", "...", 0));
        toolButton_5->setText(QApplication::translate("MainWindow", "...", 0));
        toolButton_3->setText(QApplication::translate("MainWindow", "...", 0));
        toolButton_4->setText(QApplication::translate("MainWindow", "...", 0));
        label->setText(QApplication::translate("MainWindow", "Lines:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Width:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Opacity:", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

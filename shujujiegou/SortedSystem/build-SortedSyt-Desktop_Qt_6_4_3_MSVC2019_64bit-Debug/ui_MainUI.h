/********************************************************************************
** Form generated from reading UI file 'MainUI.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINUI_H
#define UI_MAINUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MainCanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainUI
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *canvasWrap;
    QVBoxLayout *verticalLayout_2;
    MainCanvas *canvas;
    QWidget *panel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboType;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpinBox *spinCount;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *spinInterval;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSort;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnStop;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainUI)
    {
        if (MainUI->objectName().isEmpty())
            MainUI->setObjectName("MainUI");
        MainUI->resize(783, 484);
        MainUI->setStyleSheet(QString::fromUtf8("/* \344\270\273\344\275\223 */\n"
"*{\n"
"color:rgb(220, 220, 220);\n"
"}\n"
"QMainWindow,#centralwidget{\n"
"background:black;\n"
"}\n"
"#centralwidget>QWidget{\n"
"border:1px solid rgb(128, 128, 128);\n"
"}\n"
"/* \346\240\207\347\255\276 */\n"
"QLabel{\n"
"border:0;\n"
"}\n"
"/* \344\270\213\346\213\211\346\241\206 */\n"
"QComboBox{\n"
"height:24px;\n"
"padding-left: 5px;\n"
"border:1px solid rgb(128, 128, 128);\n"
"background-color: rgb(40 ,40 ,40);\n"
"border-radius: 3px;\n"
"}\n"
"QComboBox:disabled{\n"
"color:rgb(128, 128, 128);\n"
"}\n"
"QComboBox:hover{\n"
"border-color:rgb(255, 170, 0); \n"
"}\n"
"QComboBox QAbstractItemView{\n"
"outline: 0px; /*\351\200\211\351\241\271\350\231\232\347\272\277*/\n"
"background-color:rgb(110, 110, 110);\n"
"}\n"
"QComboBox QAbstractItemView::item{\n"
"/*\351\253\230\345\272\246\350\256\276\347\275\256\351\234\200\350\246\201\344\273\243\347\240\201\344\270\255setView(new QListView(this));*/\n"
"height:26px;\n"
"}\n"
"QComboBox QAbstractItemView::item:hover{\n"
"color:"
                        "black;\n"
"background-color: rgb(255, 170, 0);\n"
"}\n"
"QComboBox QAbstractItemView::item:selected{\n"
"background-color: rgb(255, 170, 0);\n"
"}\n"
"QComboBox::drop-down {\n"
"width:20px;\n"
"height:20px;\n"
"subcontrol-position: center right;\n"
"right:2px;\n"
"top:3px;\n"
"border:0;\n"
"background-color:transparent;\n"
"}\n"
"QComboBox::down-arrow {\n"
"/*\346\233\277\346\215\242\344\270\211\350\247\222\345\260\217\345\233\276\346\240\207*/\n"
"width:16px;\n"
"height:16px;\n"
"background-color: qconicalgradient(\n"
"cx:0.5, cy:0.6, angle:0.5, \n"
"stop:0.125 rgba(0, 0, 0, 0), \n"
"stop:0.1251 rgba(200, 200, 200, 255), \n"
"stop:0.375 rgba(200, 200, 200, 255), \n"
"stop:0.3751 rgba(0, 0, 0, 0));\n"
"}\n"
"QComboBox::down-arrow:hover {\n"
"background-color: qconicalgradient(\n"
"cx:0.5, cy:0.6, angle:0.5, \n"
"stop:0.125 rgba(0, 0, 0, 0), \n"
"stop:0.1251 rgba(255, 170, 0, 255), \n"
"stop:0.375 rgba(255, 170, 0, 255), \n"
"stop:0.3751 rgba(0, 0, 0, 0));\n"
"}\n"
"/* \346\225\260\345\255\227\346\241\206 */\n"
""
                        "QSpinBox{\n"
"height:24px;\n"
"padding-left: 5px;\n"
"border:1px solid rgb(128, 128, 128);\n"
"background-color: rgb(40 ,40 ,40);\n"
"border-radius: 3px;\n"
"}\n"
"QSpinBox:disabled{\n"
"color:rgb(128, 128, 128);\n"
"}\n"
"QSpinBox:hover{\n"
"border-color:rgb(255, 170, 0); \n"
"}\n"
"QSpinBox::up-button{\n"
"width:14px;\n"
"height:14px;\n"
"subcontrol-origin:border;\n"
"subcontrol-position:top right;\n"
"right:6px;\n"
"top:-2px;\n"
"background-color: qconicalgradient(\n"
"cx:0.5, cy:0.5, angle:0.5, \n"
"stop:0.625 rgba(0, 0, 0, 0), \n"
"stop:0.6251 rgba(200, 200, 200, 255), \n"
"stop:0.875 rgba(200, 200, 200, 255), \n"
"stop:0.8751 rgba(0, 0, 0, 0));\n"
"}\n"
"QSpinBox::up-button:hover{\n"
"background-color: qconicalgradient(\n"
"cx:0.5, cy:0.5, angle:0.5, \n"
"stop:0.625 rgba(0, 0, 0, 0), \n"
"stop:0.6251 rgba(255, 170, 0, 255), \n"
"stop:0.875 rgba(255, 170, 0, 255), \n"
"stop:0.8751 rgba(0, 0, 0, 0));\n"
"}\n"
"QSpinBox::down-button{\n"
"width:14px;\n"
"height:14px;\n"
"subcontrol-origin:border;\n"
"subcont"
                        "rol-position:bottom right;\n"
"right:5px;\n"
"bottom:-2px;\n"
"background-color: qconicalgradient(\n"
"cx:0.5, cy:0.5, angle:0.5, \n"
"stop:0.125 rgba(0, 0, 0, 0), \n"
"stop:0.1251 rgba(200, 200, 200, 255), \n"
"stop:0.375 rgba(200, 200, 200, 255), \n"
"stop:0.3751 rgba(0, 0, 0, 0));\n"
"}\n"
"QSpinBox::down-button:hover{\n"
"background-color: qconicalgradient(\n"
"cx:0.5, cy:0.5, angle:0.5, \n"
"stop:0.125 rgba(0, 0, 0, 0), \n"
"stop:0.1251 rgba(255, 170, 0, 255), \n"
"stop:0.375 rgba(255, 170, 0, 255), \n"
"stop:0.3751 rgba(0, 0, 0, 0));\n"
"}\n"
"/* \346\214\211\351\222\256 */\n"
"QPushButton{\n"
"width:120px;\n"
"height:26px;\n"
"border:1px solid rgb(128, 128, 128);\n"
"background-color: rgb(40 ,40 ,40);\n"
"border-radius: 3px;\n"
"}\n"
"QPushButton:hover{\n"
"border-color:rgb(255, 170, 0); /* \346\251\231\350\211\262\350\276\271\346\241\206 */\n"
"}\n"
"QPushButton:pressed{\n"
"background-color: rgb(255, 170, 0);\n"
"border-color: rgb(128, 128, 128);\n"
"color:black;\n"
"}\n"
"QPushButton:checked{\n"
"col"
                        "or: rgb(0, 170, 255);\n"
"border-color: rgb(0, 170, 255); /* \350\223\235\350\211\262\350\276\271\346\241\206 */\n"
"}\n"
"QPushButton:disabled{\n"
"color: rgb(230, 230, 230);\n"
"background-color: rgb(150, 150, 150);\n"
"}\n"
"QPushButton:checked:pressed{\n"
"color:black;\n"
"}\n"
"QPushButton:checked:hover{\n"
"border-color: rgb(255, 170, 128);\n"
"}"));
        centralwidget = new QWidget(MainUI);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_5 = new QHBoxLayout(centralwidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        canvasWrap = new QWidget(centralwidget);
        canvasWrap->setObjectName("canvasWrap");
        verticalLayout_2 = new QVBoxLayout(canvasWrap);
        verticalLayout_2->setObjectName("verticalLayout_2");
        canvas = new MainCanvas(canvasWrap);
        canvas->setObjectName("canvas");

        verticalLayout_2->addWidget(canvas);


        horizontalLayout_5->addWidget(canvasWrap);

        panel = new QWidget(centralwidget);
        panel->setObjectName("panel");
        panel->setMinimumSize(QSize(220, 0));
        panel->setMaximumSize(QSize(220, 16777215));
        verticalLayout = new QVBoxLayout(panel);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(panel);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        comboType = new QComboBox(panel);
        comboType->setObjectName("comboType");

        horizontalLayout_2->addWidget(comboType);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(panel);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        spinCount = new QSpinBox(panel);
        spinCount->setObjectName("spinCount");
        spinCount->setMinimum(2);
        spinCount->setMaximum(999999999);
        spinCount->setValue(20);

        horizontalLayout_4->addWidget(spinCount);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(panel);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        spinInterval = new QSpinBox(panel);
        spinInterval->setObjectName("spinInterval");
        spinInterval->setMinimum(0);
        spinInterval->setMaximum(999999999);
        spinInterval->setValue(200);

        horizontalLayout_3->addWidget(spinInterval);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 232, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnSort = new QPushButton(panel);
        btnSort->setObjectName("btnSort");

        horizontalLayout->addWidget(btnSort);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnStop = new QPushButton(panel);
        btnStop->setObjectName("btnStop");

        horizontalLayout->addWidget(btnStop);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_5->addWidget(panel);

        MainUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainUI);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 783, 21));
        MainUI->setMenuBar(menubar);
        statusbar = new QStatusBar(MainUI);
        statusbar->setObjectName("statusbar");
        MainUI->setStatusBar(statusbar);

        retranslateUi(MainUI);

        QMetaObject::connectSlotsByName(MainUI);
    } // setupUi

    void retranslateUi(QMainWindow *MainUI)
    {
        MainUI->setWindowTitle(QCoreApplication::translate("MainUI", "SortSyt", nullptr));
        label->setText(QCoreApplication::translate("MainUI", "\346\216\222\345\272\217\346\226\271\345\274\217\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainUI", "\346\225\260\346\215\256\344\270\252\346\225\260\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainUI", "\346\223\215\344\275\234\351\227\264\351\232\224\357\274\232", nullptr));
        btnSort->setText(QCoreApplication::translate("MainUI", "\346\216\222\345\272\217", nullptr));
        btnStop->setText(QCoreApplication::translate("MainUI", "\347\273\223\346\235\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainUI: public Ui_MainUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINUI_H

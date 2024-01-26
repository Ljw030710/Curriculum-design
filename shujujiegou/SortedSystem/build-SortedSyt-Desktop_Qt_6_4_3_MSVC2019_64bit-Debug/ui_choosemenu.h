/********************************************************************************
** Form generated from reading UI file 'choosemenu.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEMENU_H
#define UI_CHOOSEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseMenu
{
public:
    QPushButton *KnowButton;
    QPushButton *BestwayButton;

    void setupUi(QWidget *ChooseMenu)
    {
        if (ChooseMenu->objectName().isEmpty())
            ChooseMenu->setObjectName("ChooseMenu");
        ChooseMenu->resize(400, 300);
        KnowButton = new QPushButton(ChooseMenu);
        KnowButton->setObjectName("KnowButton");
        KnowButton->setGeometry(QRect(120, 50, 131, 51));
        BestwayButton = new QPushButton(ChooseMenu);
        BestwayButton->setObjectName("BestwayButton");
        BestwayButton->setGeometry(QRect(120, 130, 131, 51));

        retranslateUi(ChooseMenu);

        QMetaObject::connectSlotsByName(ChooseMenu);
    } // setupUi

    void retranslateUi(QWidget *ChooseMenu)
    {
        ChooseMenu->setWindowTitle(QCoreApplication::translate("ChooseMenu", "Form", nullptr));
        KnowButton->setText(QCoreApplication::translate("ChooseMenu", "Know", nullptr));
        BestwayButton->setText(QCoreApplication::translate("ChooseMenu", "Show Information", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseMenu: public Ui_ChooseMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEMENU_H

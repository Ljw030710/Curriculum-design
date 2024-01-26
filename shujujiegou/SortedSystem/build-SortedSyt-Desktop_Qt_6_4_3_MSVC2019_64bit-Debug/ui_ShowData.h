/********************************************************************************
** Form generated from reading UI file 'ShowData.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWDATA_H
#define UI_SHOWDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowData
{
public:
    QTextEdit *textEdit;
    QLineEdit *ChooseSort;
    QTextEdit *textEdit_2;
    QPushButton *pushButton;

    void setupUi(QWidget *ShowData)
    {
        if (ShowData->objectName().isEmpty())
            ShowData->setObjectName("ShowData");
        ShowData->resize(547, 471);
        textEdit = new QTextEdit(ShowData);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(20, 140, 411, 321));
        ChooseSort = new QLineEdit(ShowData);
        ChooseSort->setObjectName("ChooseSort");
        ChooseSort->setGeometry(QRect(90, 100, 131, 31));
        textEdit_2 = new QTextEdit(ShowData);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(70, 0, 261, 91));
        pushButton = new QPushButton(ShowData);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(240, 100, 81, 31));

        retranslateUi(ShowData);

        QMetaObject::connectSlotsByName(ShowData);
    } // setupUi

    void retranslateUi(QWidget *ShowData)
    {
        ShowData->setWindowTitle(QCoreApplication::translate("ShowData", "Form", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("ShowData", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1\357\274\214\345\206\222\346\263\241  2\357\274\214\351\200\211\346\213\251 3\357\274\214\345\270\214\345\260\224</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4\357\274\214\345\237\272\346\225\260  5\357\274\214\346\217\222\345\205\245 6\357\274\214\345\240\206  </p>\n"
"<p style=\" margin-top:0px; margin-bo"
                        "ttom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">7\357\274\214\345\277\253\351\200\237  8\357\274\214\345\275\222\345\271\266  91,\346\234\200\344\274\230\350\247\243(\346\257\224\350\276\203\346\254\241\346\225\260)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">92,\346\234\200\344\274\230\350\247\243(\350\277\220\350\241\214\346\227\266\351\227\264)  10,\346\241\266\346\216\222\345\272\217 11\357\274\214\350\256\241\346\225\260\346\216\222\345\272\217</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\351\200\211\346\213\251\345\257\271\345\272\224\357\274\214\350\276\223\345\205\245\344\270\213\346\226\271\347\232\204\347\232\204\346\241\206\345\206\205\357\274\214\347\202\271\345\207\273\346\214\211\351\222\256\343\200\202 </p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("ShowData", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowData: public Ui_ShowData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWDATA_H

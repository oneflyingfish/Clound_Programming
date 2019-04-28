/********************************************************************************
** Form generated from reading UI file 'try1_NotePad.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRY1_NOTEPAD_H
#define UI_TRY1_NOTEPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_try1_NotePadClass
{
public:

    void setupUi(QWidget *try1_NotePadClass)
    {
        if (try1_NotePadClass->objectName().isEmpty())
            try1_NotePadClass->setObjectName(QStringLiteral("try1_NotePadClass"));
        try1_NotePadClass->resize(600, 400);

        retranslateUi(try1_NotePadClass);

        QMetaObject::connectSlotsByName(try1_NotePadClass);
    } // setupUi

    void retranslateUi(QWidget *try1_NotePadClass)
    {
        try1_NotePadClass->setWindowTitle(QApplication::translate("try1_NotePadClass", "try1_NotePad", nullptr));
    } // retranslateUi

};

namespace Ui {
    class try1_NotePadClass: public Ui_try1_NotePadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRY1_NOTEPAD_H

/********************************************************************************
** Form generated from reading UI file 'inputdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDIALOG_H
#define UI_INPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_inputDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *hintLabel;
    QLineEdit *inputLine;

    void setupUi(QDialog *inputDialog)
    {
        if (inputDialog->objectName().isEmpty())
            inputDialog->setObjectName(QStringLiteral("inputDialog"));
        inputDialog->resize(379, 162);
        buttonBox = new QDialogButtonBox(inputDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 110, 341, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        hintLabel = new QLabel(inputDialog);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        hintLabel->setGeometry(QRect(80, 40, 91, 31));
        inputLine = new QLineEdit(inputDialog);
        inputLine->setObjectName(QStringLiteral("inputLine"));
        inputLine->setGeometry(QRect(190, 50, 113, 20));

        retranslateUi(inputDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), inputDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), inputDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(inputDialog);
    } // setupUi

    void retranslateUi(QDialog *inputDialog)
    {
        inputDialog->setWindowTitle(QApplication::translate("inputDialog", "Dialog", 0));
        hintLabel->setText(QApplication::translate("inputDialog", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class inputDialog: public Ui_inputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDIALOG_H

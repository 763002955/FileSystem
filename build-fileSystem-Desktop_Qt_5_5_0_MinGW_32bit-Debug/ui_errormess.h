/********************************************************************************
** Form generated from reading UI file 'errormess.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORMESS_H
#define UI_ERRORMESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_errorMess
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *errorMess)
    {
        if (errorMess->objectName().isEmpty())
            errorMess->setObjectName(QStringLiteral("errorMess"));
        errorMess->resize(398, 125);
        buttonBox = new QDialogButtonBox(errorMess);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 80, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(errorMess);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 30, 261, 41));

        retranslateUi(errorMess);
        QObject::connect(buttonBox, SIGNAL(accepted()), errorMess, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), errorMess, SLOT(reject()));

        QMetaObject::connectSlotsByName(errorMess);
    } // setupUi

    void retranslateUi(QDialog *errorMess)
    {
        errorMess->setWindowTitle(QApplication::translate("errorMess", "Dialog", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class errorMess: public Ui_errorMess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORMESS_H

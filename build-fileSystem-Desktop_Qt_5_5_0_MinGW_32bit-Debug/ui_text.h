/********************************************************************************
** Form generated from reading UI file 'text.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXT_H
#define UI_TEXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_text
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *title;
    QPushButton *pushButton;
    QPushButton *maxWin;
    QPushButton *closeWin;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;

    void setupUi(QWidget *text)
    {
        if (text->objectName().isEmpty())
            text->setObjectName(QStringLiteral("text"));
        text->resize(722, 504);
        horizontalLayoutWidget = new QWidget(text);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 571, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(label);

        title = new QLabel(horizontalLayoutWidget);
        title->setObjectName(QStringLiteral("title"));
        title->setStyleSheet(QStringLiteral("border-image:url(:/icon/backg.png)"));

        horizontalLayout->addWidget(title);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(30, 30));
        pushButton->setStyleSheet(QStringLiteral("border-image:url(:/icon/5.png)"));

        horizontalLayout->addWidget(pushButton);

        maxWin = new QPushButton(horizontalLayoutWidget);
        maxWin->setObjectName(QStringLiteral("maxWin"));
        maxWin->setMaximumSize(QSize(30, 30));
        maxWin->setStyleSheet(QStringLiteral("border-image:url(:/icon/6.png)"));

        horizontalLayout->addWidget(maxWin);

        closeWin = new QPushButton(horizontalLayoutWidget);
        closeWin->setObjectName(QStringLiteral("closeWin"));
        closeWin->setMaximumSize(QSize(30, 30));
        closeWin->setStyleSheet(QStringLiteral("border-image:url(:/icon/4.png)"));

        horizontalLayout->addWidget(closeWin);

        verticalLayoutWidget = new QWidget(text);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 30, 571, 281));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(verticalLayoutWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(text);

        QMetaObject::connectSlotsByName(text);
    } // setupUi

    void retranslateUi(QWidget *text)
    {
        text->setWindowTitle(QApplication::translate("text", "Form", 0));
        label->setText(QString());
        title->setText(QString());
        pushButton->setText(QString());
        maxWin->setText(QString());
        closeWin->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class text: public Ui_text {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXT_H

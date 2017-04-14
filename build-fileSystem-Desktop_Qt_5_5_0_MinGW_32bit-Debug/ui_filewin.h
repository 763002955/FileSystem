/********************************************************************************
** Form generated from reading UI file 'filewin.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEWIN_H
#define UI_FILEWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fileWin
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *backDirect;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QPushButton *goToDirect;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_6;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QTreeWidget *treeWidget;
    QFrame *line;
    QTableWidget *tableWidget;

    void setupUi(QWidget *fileWin)
    {
        if (fileWin->objectName().isEmpty())
            fileWin->setObjectName(QStringLiteral("fileWin"));
        fileWin->resize(629, 440);
        horizontalLayoutWidget = new QWidget(fileWin);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 631, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(30, 30));
        label_2->setStyleSheet(QStringLiteral("border-image:url(:/icon/f.jpg)"));

        horizontalLayout->addWidget(label_2);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("border-image:url(:/icon/backg.png)"));

        horizontalLayout->addWidget(label);

        pushButton_3 = new QPushButton(horizontalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(30, 30));
        pushButton_3->setStyleSheet(QStringLiteral("border-image:url(:/icon/5.png)"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMaximumSize(QSize(30, 30));
        pushButton_2->setStyleSheet(QStringLiteral("border-image:url(:/icon/6.png)"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(30, 30));
        pushButton->setStyleSheet(QStringLiteral("border-image:url(:/icon/4.png)"));

        horizontalLayout->addWidget(pushButton);

        horizontalLayoutWidget_2 = new QWidget(fileWin);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 30, 631, 32));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        backDirect = new QPushButton(horizontalLayoutWidget_2);
        backDirect->setObjectName(QStringLiteral("backDirect"));
        backDirect->setMaximumSize(QSize(30, 30));
        backDirect->setStyleSheet(QStringLiteral("border-image:url(:/icon/2.jpg)"));

        horizontalLayout_2->addWidget(backDirect);

        horizontalSpacer = new QSpacerItem(30, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        lineEdit = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaximumSize(QSize(600, 30));

        horizontalLayout_2->addWidget(lineEdit);

        goToDirect = new QPushButton(horizontalLayoutWidget_2);
        goToDirect->setObjectName(QStringLiteral("goToDirect"));
        goToDirect->setMaximumSize(QSize(30, 30));
        goToDirect->setStyleSheet(QStringLiteral("border-image:url(:/icon/1.jpg)"));

        horizontalLayout_2->addWidget(goToDirect);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_6 = new QPushButton(horizontalLayoutWidget_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMaximumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(pushButton_6);

        horizontalLayoutWidget_3 = new QWidget(fileWin);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(-1, 59, 631, 381));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(horizontalLayoutWidget_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("\346\234\254\347\224\265\350\204\221"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem2);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_3->addWidget(treeWidget);

        line = new QFrame(horizontalLayoutWidget_3);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line);

        tableWidget = new QTableWidget(horizontalLayoutWidget_3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        horizontalLayout_3->addWidget(tableWidget);


        retranslateUi(fileWin);

        QMetaObject::connectSlotsByName(fileWin);
    } // setupUi

    void retranslateUi(QWidget *fileWin)
    {
        fileWin->setWindowTitle(QApplication::translate("fileWin", "Form", 0));
        label_2->setText(QString());
        label->setText(QApplication::translate("fileWin", "\346\210\221\347\232\204\346\226\207\344\273\266", 0));
        pushButton_3->setText(QString());
        pushButton_2->setText(QString());
        pushButton->setText(QString());
        backDirect->setText(QString());
        goToDirect->setText(QString());
        pushButton_6->setText(QApplication::translate("fileWin", "PushButton", 0));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->topLevelItem(0);
        ___qtreewidgetitem->setText(0, QApplication::translate("fileWin", "C", 0));
        QTreeWidgetItem *___qtreewidgetitem1 = ___qtreewidgetitem->child(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("fileWin", "1", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem->child(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("fileWin", "2", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QApplication::translate("fileWin", "2.1", 0));
        treeWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class fileWin: public Ui_fileWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEWIN_H

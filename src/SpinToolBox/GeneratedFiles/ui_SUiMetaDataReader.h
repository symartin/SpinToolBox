/********************************************************************************
** Form generated from reading UI file 'SUiMetaDataReader.ui'
**
** Created: Thu 8. Nov 11:25:14 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUIMETADATAREADER_H
#define UI_SUIMETADATAREADER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SUiMetaDataReader
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTreeView *tvMetaData;
    QHBoxLayout *horizontalLayout;
    QPushButton *cmdRefresh;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SUiMetaDataReader)
    {
        if (SUiMetaDataReader->objectName().isEmpty())
            SUiMetaDataReader->setObjectName(QString::fromUtf8("SUiMetaDataReader"));
        SUiMetaDataReader->resize(634, 339);
        verticalLayoutWidget = new QWidget(SUiMetaDataReader);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 631, 326));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tvMetaData = new QTreeView(verticalLayoutWidget);
        tvMetaData->setObjectName(QString::fromUtf8("tvMetaData"));

        verticalLayout->addWidget(tvMetaData);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cmdRefresh = new QPushButton(verticalLayoutWidget);
        cmdRefresh->setObjectName(QString::fromUtf8("cmdRefresh"));
        cmdRefresh->setAutoRepeat(false);

        horizontalLayout->addWidget(cmdRefresh);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SUiMetaDataReader);

        QMetaObject::connectSlotsByName(SUiMetaDataReader);
    } // setupUi

    void retranslateUi(QWidget *SUiMetaDataReader)
    {
        SUiMetaDataReader->setWindowTitle(QApplication::translate("SUiMetaDataReader", "Form", 0, QApplication::UnicodeUTF8));
        cmdRefresh->setText(QApplication::translate("SUiMetaDataReader", "Refresh", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SUiMetaDataReader: public Ui_SUiMetaDataReader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUIMETADATAREADER_H

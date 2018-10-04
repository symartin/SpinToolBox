/********************************************************************************
** Form generated from reading UI file 'SUiCpDaqFieldOneAxisOptions.ui'
**
** Created: Thu 8. Nov 11:24:40 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUICPDAQFIELDONEAXISOPTIONS_H
#define UI_SUICPDAQFIELDONEAXISOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SUiCpDaqFieldOneAxisOptions
{
public:
    QPushButton *cmdOk;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *txtCoeff;
    QLabel *label;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *SUiCpDaqFieldOneAxisOptions)
    {
        if (SUiCpDaqFieldOneAxisOptions->objectName().isEmpty())
            SUiCpDaqFieldOneAxisOptions->setObjectName(QString::fromUtf8("SUiCpDaqFieldOneAxisOptions"));
        SUiCpDaqFieldOneAxisOptions->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SUiCpDaqFieldOneAxisOptions->sizePolicy().hasHeightForWidth());
        SUiCpDaqFieldOneAxisOptions->setSizePolicy(sizePolicy);
        cmdOk = new QPushButton(SUiCpDaqFieldOneAxisOptions);
        cmdOk->setObjectName(QString::fromUtf8("cmdOk"));
        cmdOk->setGeometry(QRect(305, 260, 75, 23));
        cmdOk->setDefault(true);
        groupBox = new QGroupBox(SUiCpDaqFieldOneAxisOptions);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 376, 231));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 25, 356, 196));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        txtCoeff = new QLineEdit(gridLayoutWidget);
        txtCoeff->setObjectName(QString::fromUtf8("txtCoeff"));

        gridLayout->addWidget(txtCoeff, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QString::fromUtf8("for a kepco -12/+12 le coeficient is 10/12"));
#endif // QT_NO_TOOLTIP
        label->setText(QString::fromUtf8("Dac/Kepco coefficient"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(SUiCpDaqFieldOneAxisOptions);

        QMetaObject::connectSlotsByName(SUiCpDaqFieldOneAxisOptions);
    } // setupUi

    void retranslateUi(QDialog *SUiCpDaqFieldOneAxisOptions)
    {
        SUiCpDaqFieldOneAxisOptions->setWindowTitle(QApplication::translate("SUiCpDaqFieldOneAxisOptions", "Daq Field One Axis Options ", 0, QApplication::UnicodeUTF8));
        cmdOk->setText(QApplication::translate("SUiCpDaqFieldOneAxisOptions", "Ok", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SUiCpDaqFieldOneAxisOptions", "Main Options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txtCoeff->setToolTip(QApplication::translate("SUiCpDaqFieldOneAxisOptions", "You can put a simple java script expression that give a number.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class SUiCpDaqFieldOneAxisOptions: public Ui_SUiCpDaqFieldOneAxisOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUICPDAQFIELDONEAXISOPTIONS_H

/********************************************************************************
** Form generated from reading UI file 'SUiCpRSSMA100A.ui'
**
** Created: Mon 4. Feb 15:45:25 2013
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUICPRSSMA100A_H
#define UI_SUICPRSSMA100A_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include <SDK/SUi/QTechSpinBox.h>
#include <SDK/SUi/SUiLblLed.h>

QT_BEGIN_NAMESPACE

class Ui_SUiCpRSSMA100A
{
public:
    QGroupBox *gbxSaFreq_3;
    QWidget *gridLayoutWidget_9;
    QGridLayout *gridLayout_11;
    QLabel *lblMwPowerLimit;
    QTechSpinBox *dsbMwPowerLimit;
    SUiLblLed *ledMw;
    QPushButton *cmdMwOnOff;
    QGroupBox *gbxSaFreq_2;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lblMwFreq;
    QLabel *lblMwPower;
    QTechSpinBox *dsbMwPower;
    QTechSpinBox *dsbMwFreq;
    QPushButton *cmdMwGo;
    QCheckBox *chkbxMwRealTime;
    QLabel *lblMwState;
    QLabel *label;

    void setupUi(QWidget *SUiCpRSSMA100A)
    {
        if (SUiCpRSSMA100A->objectName().isEmpty())
            SUiCpRSSMA100A->setObjectName(QString::fromUtf8("SUiCpRSSMA100A"));
        SUiCpRSSMA100A->resize(623, 378);
        gbxSaFreq_3 = new QGroupBox(SUiCpRSSMA100A);
        gbxSaFreq_3->setObjectName(QString::fromUtf8("gbxSaFreq_3"));
        gbxSaFreq_3->setGeometry(QRect(318, 40, 300, 131));
        gridLayoutWidget_9 = new QWidget(gbxSaFreq_3);
        gridLayoutWidget_9->setObjectName(QString::fromUtf8("gridLayoutWidget_9"));
        gridLayoutWidget_9->setGeometry(QRect(108, 20, 71, 41));
        gridLayout_11 = new QGridLayout(gridLayoutWidget_9);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        lblMwPowerLimit = new QLabel(gridLayoutWidget_9);
        lblMwPowerLimit->setObjectName(QString::fromUtf8("lblMwPowerLimit"));
        lblMwPowerLimit->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_11->addWidget(lblMwPowerLimit, 0, 0, 1, 1);

        dsbMwPowerLimit = new QTechSpinBox(gridLayoutWidget_9);
        dsbMwPowerLimit->setObjectName(QString::fromUtf8("dsbMwPowerLimit"));
        dsbMwPowerLimit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbMwPowerLimit->setMinimum(-135);
        dsbMwPowerLimit->setMaximum(0);
        dsbMwPowerLimit->setValue(-10);

        gridLayout_11->addWidget(dsbMwPowerLimit, 1, 0, 1, 1);

        ledMw = new SUiLblLed(SUiCpRSSMA100A);
        ledMw->setObjectName(QString::fromUtf8("ledMw"));
        ledMw->setGeometry(QRect(8, 10, 25, 25));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ledMw->sizePolicy().hasHeightForWidth());
        ledMw->setSizePolicy(sizePolicy);
        ledMw->setMinimumSize(QSize(25, 25));
        ledMw->setMaximumSize(QSize(25, 25));
        ledMw->setTextFormat(Qt::RichText);
        cmdMwOnOff = new QPushButton(SUiCpRSSMA100A);
        cmdMwOnOff->setObjectName(QString::fromUtf8("cmdMwOnOff"));
        cmdMwOnOff->setGeometry(QRect(538, 10, 75, 25));
        cmdMwOnOff->setCheckable(true);
        gbxSaFreq_2 = new QGroupBox(SUiCpRSSMA100A);
        gbxSaFreq_2->setObjectName(QString::fromUtf8("gbxSaFreq_2"));
        gbxSaFreq_2->setGeometry(QRect(8, 40, 301, 131));
        gridLayoutWidget_6 = new QWidget(gbxSaFreq_2);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(58, 20, 191, 41));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        lblMwFreq = new QLabel(gridLayoutWidget_6);
        lblMwFreq->setObjectName(QString::fromUtf8("lblMwFreq"));
        lblMwFreq->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_6->addWidget(lblMwFreq, 0, 0, 1, 1);

        lblMwPower = new QLabel(gridLayoutWidget_6);
        lblMwPower->setObjectName(QString::fromUtf8("lblMwPower"));
        lblMwPower->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_6->addWidget(lblMwPower, 0, 2, 1, 1);

        dsbMwPower = new QTechSpinBox(gridLayoutWidget_6);
        dsbMwPower->setObjectName(QString::fromUtf8("dsbMwPower"));
        dsbMwPower->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbMwPower->setMinimum(-135);
        dsbMwPower->setMaximum(0);

        gridLayout_6->addWidget(dsbMwPower, 1, 2, 1, 1);

        dsbMwFreq = new QTechSpinBox(gridLayoutWidget_6);
        dsbMwFreq->setObjectName(QString::fromUtf8("dsbMwFreq"));
        dsbMwFreq->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(dsbMwFreq, 1, 0, 1, 1);

        cmdMwGo = new QPushButton(gbxSaFreq_2);
        cmdMwGo->setObjectName(QString::fromUtf8("cmdMwGo"));
        cmdMwGo->setGeometry(QRect(211, 98, 75, 23));
        chkbxMwRealTime = new QCheckBox(gbxSaFreq_2);
        chkbxMwRealTime->setObjectName(QString::fromUtf8("chkbxMwRealTime"));
        chkbxMwRealTime->setGeometry(QRect(18, 100, 71, 18));
        lblMwState = new QLabel(SUiCpRSSMA100A);
        lblMwState->setObjectName(QString::fromUtf8("lblMwState"));
        lblMwState->setGeometry(QRect(48, 5, 491, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lblMwState->setFont(font);
        lblMwState->setText(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600; color:#838383;\">Microwave generator OFF</span></p></body></html>"));
        label = new QLabel(SUiCpRSSMA100A);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 190, 486, 171));

        retranslateUi(SUiCpRSSMA100A);

        QMetaObject::connectSlotsByName(SUiCpRSSMA100A);
    } // setupUi

    void retranslateUi(QWidget *SUiCpRSSMA100A)
    {
        SUiCpRSSMA100A->setWindowTitle(QApplication::translate("SUiCpRSSMA100A", "Form", 0, QApplication::UnicodeUTF8));
        gbxSaFreq_3->setTitle(QApplication::translate("SUiCpRSSMA100A", "Output", 0, QApplication::UnicodeUTF8));
        lblMwPowerLimit->setText(QApplication::translate("SUiCpRSSMA100A", "Power Limit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbMwPowerLimit->setToolTip(QApplication::translate("SUiCpRSSMA100A", "Power of the microwave in dBm", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ledMw->setText(QApplication::translate("SUiCpRSSMA100A", "\n"
"<img src=\":/led/circle_grey.png\" width=\"25\" height=\"25\"/>", 0, QApplication::UnicodeUTF8));
        cmdMwOnOff->setText(QApplication::translate("SUiCpRSSMA100A", "OFF", 0, QApplication::UnicodeUTF8));
        gbxSaFreq_2->setTitle(QApplication::translate("SUiCpRSSMA100A", "Output", 0, QApplication::UnicodeUTF8));
        lblMwFreq->setText(QApplication::translate("SUiCpRSSMA100A", "Frequency", 0, QApplication::UnicodeUTF8));
        lblMwPower->setText(QApplication::translate("SUiCpRSSMA100A", "Power", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbMwPower->setToolTip(QApplication::translate("SUiCpRSSMA100A", "Power of the microwave in dBm", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        dsbMwFreq->setToolTip(QApplication::translate("SUiCpRSSMA100A", "Frequency of the microwave in Hz", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdMwGo->setText(QApplication::translate("SUiCpRSSMA100A", "Go !", 0, QApplication::UnicodeUTF8));
        chkbxMwRealTime->setText(QApplication::translate("SUiCpRSSMA100A", "Real time ?", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SUiCpRSSMA100A", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/image/RSSMA100A.png\" height=150 /></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SUiCpRSSMA100A: public Ui_SUiCpRSSMA100A {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUICPRSSMA100A_H

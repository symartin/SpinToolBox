/********************************************************************************
** Form generated from reading UI file 'SUiCpK2400.ui'
**
** Created: Thu 8. Nov 11:24:55 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUICPK2400_H
#define UI_SUICPK2400_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include <SDK/SUi/SUiLblLed.h>

QT_BEGIN_NAMESPACE

class Ui_SUiCpK2400
{
public:
    QLabel *lblDcState;
    QGroupBox *gbxDcMeasurments;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_5;
    QLabel *lblDcCurrent;
    QLabel *lblDcVoltage;
    QLabel *lblDcResistance;
    QGroupBox *gbxDcOutput;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QDoubleSpinBox *dsbDcValue;
    QPushButton *cmdDcGo;
    QCheckBox *chkbxDcRealTime;
    QSpacerItem *horizontalSpacer_9;
    SUiLblLed *ledDc;
    QPushButton *cmdDcOnOff;
    QGroupBox *gbxDcMode;
    QWidget *gridLayoutWidget_11;
    QGridLayout *gridLayout_13;
    QRadioButton *radbttDcVoltage;
    QRadioButton *radbttDcCurrent;
    QGroupBox *gbxDcLimits;
    QWidget *gridLayoutWidget_8;
    QGridLayout *gridLayout_9;
    QDoubleSpinBox *dsbDcCurrentMax;
    QLabel *lblDcLimitCurrent;
    QLabel *lblDcLimitVoltage;
    QDoubleSpinBox *dsbDcVoltageMax;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *SUiCpK2400)
    {
        if (SUiCpK2400->objectName().isEmpty())
            SUiCpK2400->setObjectName(QString::fromUtf8("SUiCpK2400"));
        SUiCpK2400->resize(636, 348);
        lblDcState = new QLabel(SUiCpK2400);
        lblDcState->setObjectName(QString::fromUtf8("lblDcState"));
        lblDcState->setGeometry(QRect(0, 15, 611, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lblDcState->setFont(font);
        lblDcState->setText(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600; color:#969696;\">DC source OFF</span></p></body></html>"));
        gbxDcMeasurments = new QGroupBox(SUiCpK2400);
        gbxDcMeasurments->setObjectName(QString::fromUtf8("gbxDcMeasurments"));
        gbxDcMeasurments->setGeometry(QRect(320, 50, 300, 131));
        gridLayoutWidget_5 = new QWidget(gbxDcMeasurments);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(40, 30, 221, 81));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        lblDcCurrent = new QLabel(gridLayoutWidget_5);
        lblDcCurrent->setObjectName(QString::fromUtf8("lblDcCurrent"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        lblDcCurrent->setFont(font1);

        gridLayout_5->addWidget(lblDcCurrent, 0, 0, 1, 1);

        lblDcVoltage = new QLabel(gridLayoutWidget_5);
        lblDcVoltage->setObjectName(QString::fromUtf8("lblDcVoltage"));
        lblDcVoltage->setFont(font1);

        gridLayout_5->addWidget(lblDcVoltage, 1, 0, 1, 1);

        lblDcResistance = new QLabel(gridLayoutWidget_5);
        lblDcResistance->setObjectName(QString::fromUtf8("lblDcResistance"));
        lblDcResistance->setFont(font1);

        gridLayout_5->addWidget(lblDcResistance, 2, 0, 1, 1);

        gbxDcOutput = new QGroupBox(SUiCpK2400);
        gbxDcOutput->setObjectName(QString::fromUtf8("gbxDcOutput"));
        gbxDcOutput->setGeometry(QRect(10, 50, 300, 131));
        gridLayoutWidget = new QWidget(gbxDcOutput);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 30, 231, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        dsbDcValue = new QDoubleSpinBox(gridLayoutWidget);
        dsbDcValue->setObjectName(QString::fromUtf8("dsbDcValue"));
        dsbDcValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbDcValue->setMinimum(-100);
        dsbDcValue->setMaximum(100);
        dsbDcValue->setSingleStep(0.5);

        gridLayout->addWidget(dsbDcValue, 0, 0, 1, 1);

        cmdDcGo = new QPushButton(gridLayoutWidget);
        cmdDcGo->setObjectName(QString::fromUtf8("cmdDcGo"));

        gridLayout->addWidget(cmdDcGo, 0, 2, 1, 1);

        chkbxDcRealTime = new QCheckBox(gridLayoutWidget);
        chkbxDcRealTime->setObjectName(QString::fromUtf8("chkbxDcRealTime"));
#ifndef QT_NO_TOOLTIP
        chkbxDcRealTime->setToolTip(QString::fromUtf8("It can lead to some strange bug in this case, press [local] and wait"));
#endif // QT_NO_TOOLTIP

        gridLayout->addWidget(chkbxDcRealTime, 1, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 0, 1, 1, 1);

        ledDc = new SUiLblLed(SUiCpK2400);
        ledDc->setObjectName(QString::fromUtf8("ledDc"));
        ledDc->setGeometry(QRect(10, 20, 25, 25));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ledDc->sizePolicy().hasHeightForWidth());
        ledDc->setSizePolicy(sizePolicy);
        ledDc->setMinimumSize(QSize(25, 25));
        ledDc->setMaximumSize(QSize(25, 25));
        ledDc->setTextFormat(Qt::RichText);
        cmdDcOnOff = new QPushButton(SUiCpK2400);
        cmdDcOnOff->setObjectName(QString::fromUtf8("cmdDcOnOff"));
        cmdDcOnOff->setGeometry(QRect(540, 20, 75, 25));
        cmdDcOnOff->setCheckable(true);
        gbxDcMode = new QGroupBox(SUiCpK2400);
        gbxDcMode->setObjectName(QString::fromUtf8("gbxDcMode"));
        gbxDcMode->setGeometry(QRect(170, 190, 141, 141));
        gridLayoutWidget_11 = new QWidget(gbxDcMode);
        gridLayoutWidget_11->setObjectName(QString::fromUtf8("gridLayoutWidget_11"));
        gridLayoutWidget_11->setGeometry(QRect(10, 30, 122, 80));
        gridLayout_13 = new QGridLayout(gridLayoutWidget_11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        radbttDcVoltage = new QRadioButton(gridLayoutWidget_11);
        radbttDcVoltage->setObjectName(QString::fromUtf8("radbttDcVoltage"));

        gridLayout_13->addWidget(radbttDcVoltage, 0, 0, 1, 1);

        radbttDcCurrent = new QRadioButton(gridLayoutWidget_11);
        radbttDcCurrent->setObjectName(QString::fromUtf8("radbttDcCurrent"));
        radbttDcCurrent->setChecked(true);

        gridLayout_13->addWidget(radbttDcCurrent, 1, 0, 1, 1);

        gbxDcLimits = new QGroupBox(SUiCpK2400);
        gbxDcLimits->setObjectName(QString::fromUtf8("gbxDcLimits"));
        gbxDcLimits->setGeometry(QRect(10, 190, 141, 141));
        gridLayoutWidget_8 = new QWidget(gbxDcLimits);
        gridLayoutWidget_8->setObjectName(QString::fromUtf8("gridLayoutWidget_8"));
        gridLayoutWidget_8->setGeometry(QRect(10, 30, 122, 80));
        gridLayout_9 = new QGridLayout(gridLayoutWidget_8);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        dsbDcCurrentMax = new QDoubleSpinBox(gridLayoutWidget_8);
        dsbDcCurrentMax->setObjectName(QString::fromUtf8("dsbDcCurrentMax"));
        dsbDcCurrentMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbDcCurrentMax->setDecimals(3);
        dsbDcCurrentMax->setMinimum(0.001);
        dsbDcCurrentMax->setValue(0.1);

        gridLayout_9->addWidget(dsbDcCurrentMax, 0, 1, 1, 1);

        lblDcLimitCurrent = new QLabel(gridLayoutWidget_8);
        lblDcLimitCurrent->setObjectName(QString::fromUtf8("lblDcLimitCurrent"));
        QFont font2;
        font2.setPointSize(10);
        lblDcLimitCurrent->setFont(font2);

        gridLayout_9->addWidget(lblDcLimitCurrent, 0, 0, 1, 1);

        lblDcLimitVoltage = new QLabel(gridLayoutWidget_8);
        lblDcLimitVoltage->setObjectName(QString::fromUtf8("lblDcLimitVoltage"));
        lblDcLimitVoltage->setFont(font2);

        gridLayout_9->addWidget(lblDcLimitVoltage, 2, 0, 1, 1);

        dsbDcVoltageMax = new QDoubleSpinBox(gridLayoutWidget_8);
        dsbDcVoltageMax->setObjectName(QString::fromUtf8("dsbDcVoltageMax"));
        dsbDcVoltageMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbDcVoltageMax->setDecimals(3);
        dsbDcVoltageMax->setMinimum(0.2);
        dsbDcVoltageMax->setMaximum(1000);
        dsbDcVoltageMax->setSingleStep(0.1);
        dsbDcVoltageMax->setValue(0.2);

        gridLayout_9->addWidget(dsbDcVoltageMax, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_9->addItem(verticalSpacer_3, 1, 1, 1, 1);


        retranslateUi(SUiCpK2400);

        QMetaObject::connectSlotsByName(SUiCpK2400);
    } // setupUi

    void retranslateUi(QWidget *SUiCpK2400)
    {
        SUiCpK2400->setWindowTitle(QApplication::translate("SUiCpK2400", "Form", 0, QApplication::UnicodeUTF8));
        gbxDcMeasurments->setTitle(QApplication::translate("SUiCpK2400", "Measurments", 0, QApplication::UnicodeUTF8));
        lblDcCurrent->setText(QApplication::translate("SUiCpK2400", "I = ......... mA", 0, QApplication::UnicodeUTF8));
        lblDcVoltage->setText(QApplication::translate("SUiCpK2400", "V = ......... mV", 0, QApplication::UnicodeUTF8));
        lblDcResistance->setText(QApplication::translate("SUiCpK2400", "R = ......... \316\251", 0, QApplication::UnicodeUTF8));
        gbxDcOutput->setTitle(QApplication::translate("SUiCpK2400", "Output", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbDcValue->setToolTip(QApplication::translate("SUiCpK2400", "Current in mA or Voltage in mV", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdDcGo->setText(QApplication::translate("SUiCpK2400", "Go !", 0, QApplication::UnicodeUTF8));
        chkbxDcRealTime->setText(QApplication::translate("SUiCpK2400", "Real time ?", 0, QApplication::UnicodeUTF8));
        ledDc->setText(QApplication::translate("SUiCpK2400", "\n"
"<img src=\":/led/circle_grey.png\" width=\"25\" height=\"25\"/>", 0, QApplication::UnicodeUTF8));
        cmdDcOnOff->setText(QApplication::translate("SUiCpK2400", "OFF", 0, QApplication::UnicodeUTF8));
        gbxDcMode->setTitle(QApplication::translate("SUiCpK2400", "Modes", 0, QApplication::UnicodeUTF8));
        radbttDcVoltage->setText(QApplication::translate("SUiCpK2400", "Voltage", 0, QApplication::UnicodeUTF8));
        radbttDcCurrent->setText(QApplication::translate("SUiCpK2400", "Current", 0, QApplication::UnicodeUTF8));
        gbxDcLimits->setTitle(QApplication::translate("SUiCpK2400", "Limites", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbDcCurrentMax->setToolTip(QApplication::translate("SUiCpK2400", "Current maximum in mA", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lblDcLimitCurrent->setText(QApplication::translate("SUiCpK2400", "Current", 0, QApplication::UnicodeUTF8));
        lblDcLimitVoltage->setText(QApplication::translate("SUiCpK2400", "Voltage", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbDcVoltageMax->setToolTip(QApplication::translate("SUiCpK2400", "Voltage maximum  in mV", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class SUiCpK2400: public Ui_SUiCpK2400 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUICPK2400_H

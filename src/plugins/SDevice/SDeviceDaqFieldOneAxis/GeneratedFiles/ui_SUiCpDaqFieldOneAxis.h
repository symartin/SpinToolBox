/********************************************************************************
** Form generated from reading UI file 'SUiCpDaqFieldOneAxis.ui'
**
** Created: Thu 8. Nov 11:24:40 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUICPDAQFIELDONEAXIS_H
#define UI_SUICPDAQFIELDONEAXIS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <SDK/SUi/SUiLblLed.h>

QT_BEGIN_NAMESPACE

class Ui_SUiCpDaqFieldOneAxis
{
public:
    QPushButton *cmdFieldOnOff;
    QLabel *lblFieldState;
    QGroupBox *gbxFieldOptions;
    QWidget *gridLayoutWidget_7;
    QGridLayout *gridLayout_8;
    QLabel *lblFieldSpeed;
    QSpinBox *dsbFieldChannel;
    QLabel *lblFieldChannel;
    QSpacerItem *horizontalSpacer_6;
    QDoubleSpinBox *dsbFieldSpeed;
    QSpacerItem *verticalSpacer;
    QCheckBox *chkbxFieldRealTime;
    QGroupBox *gbxFieldOutput;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QDoubleSpinBox *dsbFieldValue;
    QPushButton *cmdFieldGo;
    QSpacerItem *horizontalSpacer_5;
    QSlider *sldFieldValue;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cmdFieldAP;
    QPushButton *cmdFieldZero;
    QPushButton *cmdFieldP;
    SUiLblLed *ledField;
    QPushButton *cmdOpt;

    void setupUi(QWidget *SUiCpDaqFieldOneAxis)
    {
        if (SUiCpDaqFieldOneAxis->objectName().isEmpty())
            SUiCpDaqFieldOneAxis->setObjectName(QString::fromUtf8("SUiCpDaqFieldOneAxis"));
        SUiCpDaqFieldOneAxis->resize(637, 349);
        cmdFieldOnOff = new QPushButton(SUiCpDaqFieldOneAxis);
        cmdFieldOnOff->setObjectName(QString::fromUtf8("cmdFieldOnOff"));
        cmdFieldOnOff->setGeometry(QRect(540, 10, 75, 25));
        cmdFieldOnOff->setCheckable(true);
        lblFieldState = new QLabel(SUiCpDaqFieldOneAxis);
        lblFieldState->setObjectName(QString::fromUtf8("lblFieldState"));
        lblFieldState->setGeometry(QRect(0, 5, 641, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lblFieldState->setFont(font);
        lblFieldState->setText(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600; color:#8a8a8a;\">Field OFF</span></p></body></html>"));
        gbxFieldOptions = new QGroupBox(SUiCpDaqFieldOneAxis);
        gbxFieldOptions->setObjectName(QString::fromUtf8("gbxFieldOptions"));
        gbxFieldOptions->setGeometry(QRect(320, 45, 300, 116));
        gridLayoutWidget_7 = new QWidget(gbxFieldOptions);
        gridLayoutWidget_7->setObjectName(QString::fromUtf8("gridLayoutWidget_7"));
        gridLayoutWidget_7->setGeometry(QRect(45, 20, 204, 86));
        gridLayout_8 = new QGridLayout(gridLayoutWidget_7);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setVerticalSpacing(8);
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        lblFieldSpeed = new QLabel(gridLayoutWidget_7);
        lblFieldSpeed->setObjectName(QString::fromUtf8("lblFieldSpeed"));
        lblFieldSpeed->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(lblFieldSpeed, 0, 0, 1, 1);

        dsbFieldChannel = new QSpinBox(gridLayoutWidget_7);
        dsbFieldChannel->setObjectName(QString::fromUtf8("dsbFieldChannel"));
        dsbFieldChannel->setMinimumSize(QSize(50, 0));
        dsbFieldChannel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbFieldChannel->setMaximum(1);

        gridLayout_8->addWidget(dsbFieldChannel, 1, 2, 1, 1);

        lblFieldChannel = new QLabel(gridLayoutWidget_7);
        lblFieldChannel->setObjectName(QString::fromUtf8("lblFieldChannel"));
        lblFieldChannel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(lblFieldChannel, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        dsbFieldSpeed = new QDoubleSpinBox(gridLayoutWidget_7);
        dsbFieldSpeed->setObjectName(QString::fromUtf8("dsbFieldSpeed"));
        dsbFieldSpeed->setMaximumSize(QSize(60, 16777215));
        dsbFieldSpeed->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbFieldSpeed->setMinimum(0.1);
        dsbFieldSpeed->setMaximum(2);
        dsbFieldSpeed->setValue(0.5);

        gridLayout_8->addWidget(dsbFieldSpeed, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer, 2, 0, 1, 1);

        chkbxFieldRealTime = new QCheckBox(gridLayoutWidget_7);
        chkbxFieldRealTime->setObjectName(QString::fromUtf8("chkbxFieldRealTime"));

        gridLayout_8->addWidget(chkbxFieldRealTime, 3, 1, 1, 1);

        gbxFieldOutput = new QGroupBox(SUiCpDaqFieldOneAxis);
        gbxFieldOutput->setObjectName(QString::fromUtf8("gbxFieldOutput"));
        gbxFieldOutput->setGeometry(QRect(10, 40, 300, 120));
        verticalLayoutWidget_2 = new QWidget(gbxFieldOutput);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 20, 258, 85));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        dsbFieldValue = new QDoubleSpinBox(verticalLayoutWidget_2);
        dsbFieldValue->setObjectName(QString::fromUtf8("dsbFieldValue"));
        dsbFieldValue->setMinimumSize(QSize(60, 0));
        dsbFieldValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbFieldValue->setMinimum(-6);
        dsbFieldValue->setMaximum(6);
        dsbFieldValue->setSingleStep(0.01);

        horizontalLayout->addWidget(dsbFieldValue);

        cmdFieldGo = new QPushButton(verticalLayoutWidget_2);
        cmdFieldGo->setObjectName(QString::fromUtf8("cmdFieldGo"));

        horizontalLayout->addWidget(cmdFieldGo);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout);

        sldFieldValue = new QSlider(verticalLayoutWidget_2);
        sldFieldValue->setObjectName(QString::fromUtf8("sldFieldValue"));
        sldFieldValue->setMinimum(-600);
        sldFieldValue->setMaximum(600);
        sldFieldValue->setSingleStep(1);
        sldFieldValue->setOrientation(Qt::Horizontal);
        sldFieldValue->setTickPosition(QSlider::TicksAbove);
        sldFieldValue->setTickInterval(100);

        verticalLayout_2->addWidget(sldFieldValue);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cmdFieldAP = new QPushButton(verticalLayoutWidget_2);
        cmdFieldAP->setObjectName(QString::fromUtf8("cmdFieldAP"));

        horizontalLayout_2->addWidget(cmdFieldAP);

        cmdFieldZero = new QPushButton(verticalLayoutWidget_2);
        cmdFieldZero->setObjectName(QString::fromUtf8("cmdFieldZero"));

        horizontalLayout_2->addWidget(cmdFieldZero);

        cmdFieldP = new QPushButton(verticalLayoutWidget_2);
        cmdFieldP->setObjectName(QString::fromUtf8("cmdFieldP"));

        horizontalLayout_2->addWidget(cmdFieldP);


        verticalLayout_2->addLayout(horizontalLayout_2);

        ledField = new SUiLblLed(SUiCpDaqFieldOneAxis);
        ledField->setObjectName(QString::fromUtf8("ledField"));
        ledField->setGeometry(QRect(10, 10, 25, 25));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ledField->sizePolicy().hasHeightForWidth());
        ledField->setSizePolicy(sizePolicy);
        ledField->setMinimumSize(QSize(25, 25));
        ledField->setMaximumSize(QSize(25, 25));
        ledField->setTextFormat(Qt::RichText);
        cmdOpt = new QPushButton(SUiCpDaqFieldOneAxis);
        cmdOpt->setObjectName(QString::fromUtf8("cmdOpt"));
        cmdOpt->setEnabled(true);
        cmdOpt->setGeometry(QRect(45, 1, 40, 40));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(40);
        sizePolicy1.setVerticalStretch(40);
        sizePolicy1.setHeightForWidth(cmdOpt->sizePolicy().hasHeightForWidth());
        cmdOpt->setSizePolicy(sizePolicy1);
        cmdOpt->setMinimumSize(QSize(40, 40));
        cmdOpt->setMaximumSize(QSize(40, 40));
#ifndef QT_NO_TOOLTIP
        cmdOpt->setToolTip(QString::fromUtf8("Options and settings: the settings is editable if the plugin was already loaded at the start program"));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cmdOpt->setStatusTip(QString::fromUtf8("Edit the option of this plugin."));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        cmdOpt->setWhatsThis(QString::fromUtf8(""));
#endif // QT_NO_WHATSTHIS
        cmdOpt->setText(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/gears.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdOpt->setIcon(icon);
        cmdOpt->setIconSize(QSize(25, 25));
        cmdOpt->setAutoDefault(false);
        cmdOpt->setFlat(true);
        lblFieldState->raise();
        cmdFieldOnOff->raise();
        gbxFieldOptions->raise();
        gbxFieldOutput->raise();
        ledField->raise();
        cmdOpt->raise();

        retranslateUi(SUiCpDaqFieldOneAxis);

        QMetaObject::connectSlotsByName(SUiCpDaqFieldOneAxis);
    } // setupUi

    void retranslateUi(QWidget *SUiCpDaqFieldOneAxis)
    {
        SUiCpDaqFieldOneAxis->setWindowTitle(QApplication::translate("SUiCpDaqFieldOneAxis", "Form", 0, QApplication::UnicodeUTF8));
        cmdFieldOnOff->setText(QApplication::translate("SUiCpDaqFieldOneAxis", "OFF", 0, QApplication::UnicodeUTF8));
        gbxFieldOptions->setTitle(QApplication::translate("SUiCpDaqFieldOneAxis", "Options", 0, QApplication::UnicodeUTF8));
        lblFieldSpeed->setText(QApplication::translate("SUiCpDaqFieldOneAxis", "Sweep speed", 0, QApplication::UnicodeUTF8));
        lblFieldChannel->setText(QApplication::translate("SUiCpDaqFieldOneAxis", "Channel", 0, QApplication::UnicodeUTF8));
        chkbxFieldRealTime->setText(QApplication::translate("SUiCpDaqFieldOneAxis", "Real time ?", 0, QApplication::UnicodeUTF8));
        gbxFieldOutput->setTitle(QApplication::translate("SUiCpDaqFieldOneAxis", "Output", 0, QApplication::UnicodeUTF8));
        cmdFieldGo->setText(QApplication::translate("SUiCpDaqFieldOneAxis", "Go !", 0, QApplication::UnicodeUTF8));
        cmdFieldAP->setText(QApplication::translate("SUiCpDaqFieldOneAxis", "<- -6", 0, QApplication::UnicodeUTF8));
        cmdFieldZero->setText(QApplication::translate("SUiCpDaqFieldOneAxis", "-0-", 0, QApplication::UnicodeUTF8));
        cmdFieldP->setText(QApplication::translate("SUiCpDaqFieldOneAxis", "+6 ->", 0, QApplication::UnicodeUTF8));
        ledField->setText(QApplication::translate("SUiCpDaqFieldOneAxis", "\n"
"<img src=\":/led/circle_grey.png\" width=\"25\" height=\"25\"/>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SUiCpDaqFieldOneAxis: public Ui_SUiCpDaqFieldOneAxis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUICPDAQFIELDONEAXIS_H

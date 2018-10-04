/********************************************************************************
** Form generated from reading UI file 'SUiCpPSAE4440A.ui'
**
** Created: Thu 28. Mar 14:06:13 2013
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUICPPSAE4440A_H
#define UI_SUICPPSAE4440A_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <SDK/SUi/QTechSpinBox.h>
#include <SDK/SUi/SUiLblLed.h>

QT_BEGIN_NAMESPACE

class Ui_SUiCpPSAE4440A
{
public:
    QGroupBox *gbxSaData;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QLabel *lblSaFileName;
    QLabel *lblSaComment;
    QLineEdit *txtSaFileName;
    QLineEdit *txtSaComments;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *txtSaTargetFolder;
    QPushButton *cmdSaTargetFolder;
    QLabel *lblSaTargetFolder;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *cmdSaMeasure;
    QLabel *lblSaState;
    QGroupBox *gbxSaFreq;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_10;
    QLabel *lblSaStartFreq;
    QTechSpinBox *dsbSaStartFreq;
    QLabel *lblSaStopFreq;
    QTechSpinBox *dsbSaStopFreq;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_4;
    QLabel *RBW;
    QTechSpinBox *dsbSaRbw;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_4;
    QPushButton *cmdSaCheckRbw;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_5;
    QPushButton *cmdSaAskRbw;
    QSpacerItem *horizontalSpacer;
    QGroupBox *gbxSaOptions;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QSpinBox *dsbSaAverage;
    QComboBox *cmbxSaAttenuation;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *dsbSaNbPoints;
    QLabel *label_7;
    QDoubleSpinBox *dsbSaLevel;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *chkbxSaRealTime;
    QCheckBox *chkbxSaLog;
    QGroupBox *gbxSaMarker;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_4;
    QCheckBox *chkbxSaMarkerOnOff;
    QTechSpinBox *dsbSaMarker;
    QLabel *lblSaMarker;
    QPushButton *cmdSaMax;
    QSlider *sldSaMarker;
    QPushButton *cmdSaGo;
    SUiLblLed *ledSa;

    void setupUi(QWidget *SUiCpPSAE4440A)
    {
        if (SUiCpPSAE4440A->objectName().isEmpty())
            SUiCpPSAE4440A->setObjectName(QString::fromUtf8("SUiCpPSAE4440A"));
        SUiCpPSAE4440A->resize(628, 333);
        gbxSaData = new QGroupBox(SUiCpPSAE4440A);
        gbxSaData->setObjectName(QString::fromUtf8("gbxSaData"));
        gbxSaData->setGeometry(QRect(320, 130, 300, 191));
        gridLayoutWidget_3 = new QWidget(gbxSaData);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 13, 281, 164));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        lblSaFileName = new QLabel(gridLayoutWidget_3);
        lblSaFileName->setObjectName(QString::fromUtf8("lblSaFileName"));
        lblSaFileName->setMinimumSize(QSize(0, 10));
        lblSaFileName->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_3->addWidget(lblSaFileName, 2, 0, 1, 1);

        lblSaComment = new QLabel(gridLayoutWidget_3);
        lblSaComment->setObjectName(QString::fromUtf8("lblSaComment"));
        lblSaComment->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_3->addWidget(lblSaComment, 4, 0, 1, 1);

        txtSaFileName = new QLineEdit(gridLayoutWidget_3);
        txtSaFileName->setObjectName(QString::fromUtf8("txtSaFileName"));

        gridLayout_3->addWidget(txtSaFileName, 3, 0, 1, 1);

        txtSaComments = new QLineEdit(gridLayoutWidget_3);
        txtSaComments->setObjectName(QString::fromUtf8("txtSaComments"));

        gridLayout_3->addWidget(txtSaComments, 5, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        txtSaTargetFolder = new QLineEdit(gridLayoutWidget_3);
        txtSaTargetFolder->setObjectName(QString::fromUtf8("txtSaTargetFolder"));

        horizontalLayout_5->addWidget(txtSaTargetFolder);

        cmdSaTargetFolder = new QPushButton(gridLayoutWidget_3);
        cmdSaTargetFolder->setObjectName(QString::fromUtf8("cmdSaTargetFolder"));
        cmdSaTargetFolder->setMaximumSize(QSize(23, 16777215));

        horizontalLayout_5->addWidget(cmdSaTargetFolder);


        gridLayout_3->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        lblSaTargetFolder = new QLabel(gridLayoutWidget_3);
        lblSaTargetFolder->setObjectName(QString::fromUtf8("lblSaTargetFolder"));
        lblSaTargetFolder->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_3->addWidget(lblSaTargetFolder, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        cmdSaMeasure = new QPushButton(gridLayoutWidget_3);
        cmdSaMeasure->setObjectName(QString::fromUtf8("cmdSaMeasure"));

        horizontalLayout_6->addWidget(cmdSaMeasure);


        gridLayout_3->addLayout(horizontalLayout_6, 6, 0, 1, 1);

        lblSaState = new QLabel(SUiCpPSAE4440A);
        lblSaState->setObjectName(QString::fromUtf8("lblSaState"));
        lblSaState->setGeometry(QRect(0, 7, 611, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lblSaState->setFont(font);
        lblSaState->setText(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600; color:#0000ff;\">Spectrum analyzer</span></p></body></html>"));
        gbxSaFreq = new QGroupBox(SUiCpPSAE4440A);
        gbxSaFreq->setObjectName(QString::fromUtf8("gbxSaFreq"));
        gbxSaFreq->setGeometry(QRect(10, 40, 300, 121));
        verticalLayoutWidget_6 = new QWidget(gbxSaFreq);
        verticalLayoutWidget_6->setObjectName(QString::fromUtf8("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(10, 20, 281, 92));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        lblSaStartFreq = new QLabel(verticalLayoutWidget_6);
        lblSaStartFreq->setObjectName(QString::fromUtf8("lblSaStartFreq"));
        lblSaStartFreq->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_10->addWidget(lblSaStartFreq, 0, 0, 1, 1);

        dsbSaStartFreq = new QTechSpinBox(verticalLayoutWidget_6);
        dsbSaStartFreq->setObjectName(QString::fromUtf8("dsbSaStartFreq"));
        dsbSaStartFreq->setMinimumSize(QSize(80, 20));
        dsbSaStartFreq->setMaximumSize(QSize(100, 16777215));
        dsbSaStartFreq->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(dsbSaStartFreq, 1, 0, 1, 1);

        lblSaStopFreq = new QLabel(verticalLayoutWidget_6);
        lblSaStopFreq->setObjectName(QString::fromUtf8("lblSaStopFreq"));
        lblSaStopFreq->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_10->addWidget(lblSaStopFreq, 0, 1, 1, 1);

        dsbSaStopFreq = new QTechSpinBox(verticalLayoutWidget_6);
        dsbSaStopFreq->setObjectName(QString::fromUtf8("dsbSaStopFreq"));
        dsbSaStopFreq->setMinimumSize(QSize(0, 20));
        dsbSaStopFreq->setMaximumSize(QSize(100, 16777215));
        dsbSaStopFreq->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(dsbSaStopFreq, 1, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_10);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        RBW = new QLabel(verticalLayoutWidget_6);
        RBW->setObjectName(QString::fromUtf8("RBW"));
        RBW->setMaximumSize(QSize(500, 20));
        RBW->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_4->addWidget(RBW);

        dsbSaRbw = new QTechSpinBox(verticalLayoutWidget_6);
        dsbSaRbw->setObjectName(QString::fromUtf8("dsbSaRbw"));
        dsbSaRbw->setMinimumSize(QSize(80, 0));
        dsbSaRbw->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_4->addWidget(dsbSaRbw);


        horizontalLayout_7->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        cmdSaCheckRbw = new QPushButton(verticalLayoutWidget_6);
        cmdSaCheckRbw->setObjectName(QString::fromUtf8("cmdSaCheckRbw"));
        cmdSaCheckRbw->setMaximumSize(QSize(20, 20));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/check.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSaCheckRbw->setIcon(icon);
        cmdSaCheckRbw->setIconSize(QSize(12, 12));

        verticalLayout_5->addWidget(cmdSaCheckRbw);


        horizontalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_5);

        cmdSaAskRbw = new QPushButton(verticalLayoutWidget_6);
        cmdSaAskRbw->setObjectName(QString::fromUtf8("cmdSaAskRbw"));
        cmdSaAskRbw->setMaximumSize(QSize(20, 20));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/ask.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSaAskRbw->setIcon(icon1);
        cmdSaAskRbw->setIconSize(QSize(12, 12));

        verticalLayout_7->addWidget(cmdSaAskRbw);


        horizontalLayout_7->addLayout(verticalLayout_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout_6->addLayout(horizontalLayout_7);

        gbxSaOptions = new QGroupBox(SUiCpPSAE4440A);
        gbxSaOptions->setObjectName(QString::fromUtf8("gbxSaOptions"));
        gbxSaOptions->setGeometry(QRect(10, 170, 300, 151));
        gridLayoutWidget_2 = new QWidget(gbxSaOptions);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(50, 20, 191, 121));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(gridLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        dsbSaAverage = new QSpinBox(gridLayoutWidget_2);
        dsbSaAverage->setObjectName(QString::fromUtf8("dsbSaAverage"));
        dsbSaAverage->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbSaAverage->setMaximum(1000);

        gridLayout_2->addWidget(dsbSaAverage, 1, 0, 1, 1);

        cmbxSaAttenuation = new QComboBox(gridLayoutWidget_2);
        cmbxSaAttenuation->setObjectName(QString::fromUtf8("cmbxSaAttenuation"));

        gridLayout_2->addWidget(cmbxSaAttenuation, 1, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_2->addWidget(label_5, 0, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        dsbSaNbPoints = new QSpinBox(gridLayoutWidget_2);
        dsbSaNbPoints->setObjectName(QString::fromUtf8("dsbSaNbPoints"));
        dsbSaNbPoints->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbSaNbPoints->setMinimum(0);
        dsbSaNbPoints->setMaximum(8050);
        dsbSaNbPoints->setValue(8001);

        gridLayout_2->addWidget(dsbSaNbPoints, 3, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_2->addWidget(label_7, 2, 1, 1, 1);

        dsbSaLevel = new QDoubleSpinBox(gridLayoutWidget_2);
        dsbSaLevel->setObjectName(QString::fromUtf8("dsbSaLevel"));
        dsbSaLevel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbSaLevel->setMinimum(-500);
        dsbSaLevel->setMaximum(500);

        gridLayout_2->addWidget(dsbSaLevel, 3, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 1, 1, 1);

        chkbxSaRealTime = new QCheckBox(gridLayoutWidget_2);
        chkbxSaRealTime->setObjectName(QString::fromUtf8("chkbxSaRealTime"));

        gridLayout_2->addWidget(chkbxSaRealTime, 5, 1, 1, 1);

        chkbxSaLog = new QCheckBox(gridLayoutWidget_2);
        chkbxSaLog->setObjectName(QString::fromUtf8("chkbxSaLog"));
#ifndef QT_NO_WHATSTHIS
        chkbxSaLog->setWhatsThis(QString::fromUtf8("if it is checked: Log display, otherwise display linear"));
#endif // QT_NO_WHATSTHIS
        chkbxSaLog->setText(QString::fromUtf8("Log/Lin"));

        gridLayout_2->addWidget(chkbxSaLog, 5, 0, 1, 1);

        gbxSaMarker = new QGroupBox(SUiCpPSAE4440A);
        gbxSaMarker->setObjectName(QString::fromUtf8("gbxSaMarker"));
        gbxSaMarker->setGeometry(QRect(320, 40, 301, 81));
        verticalLayoutWidget = new QWidget(gbxSaMarker);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 286, 51));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        chkbxSaMarkerOnOff = new QCheckBox(verticalLayoutWidget);
        chkbxSaMarkerOnOff->setObjectName(QString::fromUtf8("chkbxSaMarkerOnOff"));
        chkbxSaMarkerOnOff->setMaximumSize(QSize(60, 16777215));
        chkbxSaMarkerOnOff->setTristate(false);

        gridLayout_4->addWidget(chkbxSaMarkerOnOff, 0, 0, 1, 1);

        dsbSaMarker = new QTechSpinBox(verticalLayoutWidget);
        dsbSaMarker->setObjectName(QString::fromUtf8("dsbSaMarker"));
        dsbSaMarker->setMinimumSize(QSize(85, 0));
        dsbSaMarker->setMaximumSize(QSize(75, 16777215));
        dsbSaMarker->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(dsbSaMarker, 0, 3, 1, 1);

        lblSaMarker = new QLabel(verticalLayoutWidget);
        lblSaMarker->setObjectName(QString::fromUtf8("lblSaMarker"));

        gridLayout_4->addWidget(lblSaMarker, 0, 2, 1, 1);

        cmdSaMax = new QPushButton(verticalLayoutWidget);
        cmdSaMax->setObjectName(QString::fromUtf8("cmdSaMax"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmdSaMax->sizePolicy().hasHeightForWidth());
        cmdSaMax->setSizePolicy(sizePolicy);
        cmdSaMax->setMaximumSize(QSize(35, 16777215));

        gridLayout_4->addWidget(cmdSaMax, 0, 4, 1, 1);


        verticalLayout->addLayout(gridLayout_4);

        sldSaMarker = new QSlider(verticalLayoutWidget);
        sldSaMarker->setObjectName(QString::fromUtf8("sldSaMarker"));
        sldSaMarker->setMinimum(100000000);
        sldSaMarker->setMaximum(1000000000);
        sldSaMarker->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(sldSaMarker);

        cmdSaGo = new QPushButton(SUiCpPSAE4440A);
        cmdSaGo->setObjectName(QString::fromUtf8("cmdSaGo"));
        cmdSaGo->setGeometry(QRect(540, 10, 75, 25));
        ledSa = new SUiLblLed(SUiCpPSAE4440A);
        ledSa->setObjectName(QString::fromUtf8("ledSa"));
        ledSa->setGeometry(QRect(10, 10, 25, 25));
        sizePolicy.setHeightForWidth(ledSa->sizePolicy().hasHeightForWidth());
        ledSa->setSizePolicy(sizePolicy);
        ledSa->setMinimumSize(QSize(25, 25));
        ledSa->setMaximumSize(QSize(25, 25));
        ledSa->setTextFormat(Qt::RichText);

        retranslateUi(SUiCpPSAE4440A);

        QMetaObject::connectSlotsByName(SUiCpPSAE4440A);
    } // setupUi

    void retranslateUi(QWidget *SUiCpPSAE4440A)
    {
        SUiCpPSAE4440A->setWindowTitle(QApplication::translate("SUiCpPSAE4440A", "Form", 0, QApplication::UnicodeUTF8));
        gbxSaData->setTitle(QApplication::translate("SUiCpPSAE4440A", "Save data", 0, QApplication::UnicodeUTF8));
        lblSaFileName->setText(QApplication::translate("SUiCpPSAE4440A", "File Name", 0, QApplication::UnicodeUTF8));
        lblSaComment->setText(QApplication::translate("SUiCpPSAE4440A", "Comment", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        txtSaFileName->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        txtSaFileName->setText(QApplication::translate("SUiCpPSAE4440A", "spectre_", 0, QApplication::UnicodeUTF8));
        cmdSaTargetFolder->setText(QApplication::translate("SUiCpPSAE4440A", "...", 0, QApplication::UnicodeUTF8));
        lblSaTargetFolder->setText(QApplication::translate("SUiCpPSAE4440A", "Target folder", 0, QApplication::UnicodeUTF8));
        cmdSaMeasure->setText(QApplication::translate("SUiCpPSAE4440A", "Take data", 0, QApplication::UnicodeUTF8));
        gbxSaFreq->setTitle(QApplication::translate("SUiCpPSAE4440A", "Frequencies", 0, QApplication::UnicodeUTF8));
        lblSaStartFreq->setText(QApplication::translate("SUiCpPSAE4440A", "Start frequency", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbSaStartFreq->setToolTip(QApplication::translate("SUiCpPSAE4440A", "Start frequency in Hz", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lblSaStopFreq->setText(QApplication::translate("SUiCpPSAE4440A", "Stop frequency", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbSaStopFreq->setToolTip(QApplication::translate("SUiCpPSAE4440A", "Stop frequency in Hz", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        RBW->setText(QApplication::translate("SUiCpPSAE4440A", "RBW", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbSaRbw->setToolTip(QApplication::translate("SUiCpPSAE4440A", "Resolution of bandwidth in Hz", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cmdSaCheckRbw->setToolTip(QApplication::translate("SUiCpPSAE4440A", "Check if this RBW existes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdSaCheckRbw->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdSaAskRbw->setToolTip(QApplication::translate("SUiCpPSAE4440A", "ask the closer RBW", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdSaAskRbw->setText(QString());
        gbxSaOptions->setTitle(QApplication::translate("SUiCpPSAE4440A", "Options", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SUiCpPSAE4440A", "Average", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbSaAverage->setToolTip(QApplication::translate("SUiCpPSAE4440A", "Average", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cmbxSaAttenuation->setToolTip(QApplication::translate("SUiCpPSAE4440A", "Attenuation in dB", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("SUiCpPSAE4440A", "Attenuation", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SUiCpPSAE4440A", "Num points", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbSaNbPoints->setToolTip(QApplication::translate("SUiCpPSAE4440A", "Number of measurment points (do not change it without a good reason !)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("SUiCpPSAE4440A", "Level", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dsbSaLevel->setToolTip(QApplication::translate("SUiCpPSAE4440A", "Reference level in dBm", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chkbxSaRealTime->setText(QApplication::translate("SUiCpPSAE4440A", "Real time ?", 0, QApplication::UnicodeUTF8));
        gbxSaMarker->setTitle(QApplication::translate("SUiCpPSAE4440A", "Marker", 0, QApplication::UnicodeUTF8));
        chkbxSaMarkerOnOff->setText(QApplication::translate("SUiCpPSAE4440A", "On/Off", 0, QApplication::UnicodeUTF8));
        lblSaMarker->setText(QApplication::translate("SUiCpPSAE4440A", "M = ... V", 0, QApplication::UnicodeUTF8));
        cmdSaMax->setText(QApplication::translate("SUiCpPSAE4440A", "Max", 0, QApplication::UnicodeUTF8));
        cmdSaGo->setText(QApplication::translate("SUiCpPSAE4440A", "Go !", 0, QApplication::UnicodeUTF8));
        ledSa->setText(QApplication::translate("SUiCpPSAE4440A", "\n"
"<img src=\":/led/circle_grey.png\" width=\"25\" height=\"25\"/>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SUiCpPSAE4440A: public Ui_SUiCpPSAE4440A {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUICPPSAE4440A_H

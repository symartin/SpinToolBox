/********************************************************************************
** Form generated from reading UI file 'SPlotSetScale.ui'
**
** Created: Thu 8. Nov 11:40:09 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPLOTSETSCALE_H
#define UI_SPLOTSETSCALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include <SDK/SUi/QScienceSpinBox.h>

QT_BEGIN_NAMESPACE

class Ui_SPlotSetScale
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *lblXStart;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblXStop;
    QLabel *lblYStart;
    QLabel *lblYStop;
    QScienceSpinBox *dsbYStart;
    QSpacerItem *horizontalSpacer;
    QLabel *lblX;
    QLabel *lblY;
    QSpacerItem *horizontalSpacer_3;
    QScienceSpinBox *dsbXStart;
    QScienceSpinBox *dsbYStop;
    QSpacerItem *horizontalSpacer_4;
    QScienceSpinBox *dsbXStop;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *cmdScaleAll;

    void setupUi(QDialog *SPlotSetScale)
    {
        if (SPlotSetScale->objectName().isEmpty())
            SPlotSetScale->setObjectName(QString::fromUtf8("SPlotSetScale"));
        SPlotSetScale->setWindowModality(Qt::WindowModal);
        SPlotSetScale->resize(274, 140);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/compass.ico"), QSize(), QIcon::Normal, QIcon::Off);
        SPlotSetScale->setWindowIcon(icon);
        SPlotSetScale->setModal(true);
        buttonBox = new QDialogButtonBox(SPlotSetScale);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(0, 110, 271, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        gridLayoutWidget = new QWidget(SPlotSetScale);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 289, 101));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lblXStart = new QLabel(gridLayoutWidget);
        lblXStart->setObjectName(QString::fromUtf8("lblXStart"));

        gridLayout->addWidget(lblXStart, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        lblXStop = new QLabel(gridLayoutWidget);
        lblXStop->setObjectName(QString::fromUtf8("lblXStop"));

        gridLayout->addWidget(lblXStop, 1, 4, 1, 1);

        lblYStart = new QLabel(gridLayoutWidget);
        lblYStart->setObjectName(QString::fromUtf8("lblYStart"));

        gridLayout->addWidget(lblYStart, 3, 1, 1, 1);

        lblYStop = new QLabel(gridLayoutWidget);
        lblYStop->setObjectName(QString::fromUtf8("lblYStop"));

        gridLayout->addWidget(lblYStop, 3, 4, 1, 1);

        dsbYStart = new QScienceSpinBox(gridLayoutWidget);
        dsbYStart->setObjectName(QString::fromUtf8("dsbYStart"));
        dsbYStart->setMinimumSize(QSize(90, 0));
        dsbYStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbYStart->setDecimals(2);
        dsbYStart->setMinimum(-10000);
        dsbYStart->setMaximum(10000);
        dsbYStart->setValue(0);

        gridLayout->addWidget(dsbYStart, 3, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 6, 1, 1);

        lblX = new QLabel(gridLayoutWidget);
        lblX->setObjectName(QString::fromUtf8("lblX"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lblX->setFont(font);
        lblX->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblX, 0, 3, 1, 1);

        lblY = new QLabel(gridLayoutWidget);
        lblY->setObjectName(QString::fromUtf8("lblY"));
        lblY->setFont(font);
        lblY->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblY, 2, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 3, 1, 1);

        dsbXStart = new QScienceSpinBox(gridLayoutWidget);
        dsbXStart->setObjectName(QString::fromUtf8("dsbXStart"));
        dsbXStart->setMinimumSize(QSize(90, 0));
        dsbXStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbXStart->setDecimals(2);
        dsbXStart->setMinimum(-10000);
        dsbXStart->setMaximum(10000);
        dsbXStart->setSingleStep(0.1);
        dsbXStart->setValue(0);

        gridLayout->addWidget(dsbXStart, 1, 2, 1, 1);

        dsbYStop = new QScienceSpinBox(gridLayoutWidget);
        dsbYStop->setObjectName(QString::fromUtf8("dsbYStop"));
        dsbYStop->setMinimumSize(QSize(90, 0));
        dsbYStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbYStop->setDecimals(2);
        dsbYStop->setMinimum(-10000);
        dsbYStop->setMaximum(10000);
        dsbYStop->setValue(0);

        gridLayout->addWidget(dsbYStop, 3, 5, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 6, 1, 1);

        dsbXStop = new QScienceSpinBox(gridLayoutWidget);
        dsbXStop->setObjectName(QString::fromUtf8("dsbXStop"));
        dsbXStop->setMinimumSize(QSize(90, 0));
        dsbXStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbXStop->setDecimals(2);
        dsbXStop->setMinimum(-10000);
        dsbXStop->setMaximum(10000);
        dsbXStop->setValue(0);

        gridLayout->addWidget(dsbXStop, 1, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        cmdScaleAll = new QPushButton(SPlotSetScale);
        cmdScaleAll->setObjectName(QString::fromUtf8("cmdScaleAll"));
        cmdScaleAll->setGeometry(QRect(0, 113, 41, 26));
#ifndef QT_NO_TOOLTIP
        cmdScaleAll->setToolTip(QString::fromUtf8("Apply the scale at all the 2D plot open."));
#endif // QT_NO_TOOLTIP

        retranslateUi(SPlotSetScale);
        QObject::connect(buttonBox, SIGNAL(accepted()), SPlotSetScale, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SPlotSetScale, SLOT(reject()));

        QMetaObject::connectSlotsByName(SPlotSetScale);
    } // setupUi

    void retranslateUi(QDialog *SPlotSetScale)
    {
        SPlotSetScale->setWindowTitle(QApplication::translate("SPlotSetScale", "Set the scale", 0, QApplication::UnicodeUTF8));
        lblXStart->setText(QApplication::translate("SPlotSetScale", "Start: ", 0, QApplication::UnicodeUTF8));
        lblXStop->setText(QApplication::translate("SPlotSetScale", "Stop: ", 0, QApplication::UnicodeUTF8));
        lblYStart->setText(QApplication::translate("SPlotSetScale", "Start: ", 0, QApplication::UnicodeUTF8));
        lblYStop->setText(QApplication::translate("SPlotSetScale", "Stop: ", 0, QApplication::UnicodeUTF8));
        lblX->setText(QApplication::translate("SPlotSetScale", "X", 0, QApplication::UnicodeUTF8));
        lblY->setText(QApplication::translate("SPlotSetScale", "Y", 0, QApplication::UnicodeUTF8));
        cmdScaleAll->setText(QApplication::translate("SPlotSetScale", "All", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SPlotSetScale: public Ui_SPlotSetScale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPLOTSETSCALE_H

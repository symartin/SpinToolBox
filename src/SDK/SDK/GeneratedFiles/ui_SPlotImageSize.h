/********************************************************************************
** Form generated from reading UI file 'SPlotImageSize.ui'
**
** Created: Thu 8. Nov 11:40:09 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPLOTIMAGESIZE_H
#define UI_SPLOTIMAGESIZE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SPlotImageSize
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *spbWidth;
    QSpacerItem *horizontalSpacer;
    QSpinBox *spbHeight;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *spbScale;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QCheckBox *ckbCosmeticPen;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SPlotImageSize)
    {
        if (SPlotImageSize->objectName().isEmpty())
            SPlotImageSize->setObjectName(QString::fromUtf8("SPlotImageSize"));
        SPlotImageSize->setWindowModality(Qt::ApplicationModal);
        SPlotImageSize->resize(253, 131);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SPlotImageSize->sizePolicy().hasHeightForWidth());
        SPlotImageSize->setSizePolicy(sizePolicy);
        SPlotImageSize->setMinimumSize(QSize(253, 131));
        SPlotImageSize->setMaximumSize(QSize(253, 131));
        SPlotImageSize->setSizeGripEnabled(false);
        verticalLayoutWidget = new QWidget(SPlotImageSize);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 251, 128));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        spbWidth = new QSpinBox(verticalLayoutWidget);
        spbWidth->setObjectName(QString::fromUtf8("spbWidth"));
        spbWidth->setMaximum(1000);
        spbWidth->setValue(200);

        horizontalLayout->addWidget(spbWidth);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        spbHeight = new QSpinBox(verticalLayoutWidget);
        spbHeight->setObjectName(QString::fromUtf8("spbHeight"));
        spbHeight->setMaximum(1000);
        spbHeight->setValue(200);

        horizontalLayout->addWidget(spbHeight);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spbScale = new QDoubleSpinBox(verticalLayoutWidget);
        spbScale->setObjectName(QString::fromUtf8("spbScale"));
        spbScale->setValue(1);

        horizontalLayout_2->addWidget(spbScale);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        ckbCosmeticPen = new QCheckBox(verticalLayoutWidget);
        ckbCosmeticPen->setObjectName(QString::fromUtf8("ckbCosmeticPen"));
        ckbCosmeticPen->setChecked(true);

        horizontalLayout_3->addWidget(ckbCosmeticPen);


        verticalLayout->addLayout(horizontalLayout_3);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SPlotImageSize);
        QObject::connect(buttonBox, SIGNAL(accepted()), SPlotImageSize, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SPlotImageSize, SLOT(reject()));

        QMetaObject::connectSlotsByName(SPlotImageSize);
    } // setupUi

    void retranslateUi(QDialog *SPlotImageSize)
    {
        SPlotImageSize->setWindowTitle(QApplication::translate("SPlotImageSize", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SPlotImageSize", "\"What size do you want? (width x height in pixels)\"", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SPlotImageSize", "Scale (for PNG)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SPlotImageSize", "Cosmetic Pen (for PDF)", 0, QApplication::UnicodeUTF8));
        ckbCosmeticPen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SPlotImageSize: public Ui_SPlotImageSize {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPLOTIMAGESIZE_H

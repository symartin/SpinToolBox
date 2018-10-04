/********************************************************************************
** Form generated from reading UI file 'SUiPluginManager.ui'
**
** Created: Thu 8. Nov 11:25:14 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUIPLUGINMANAGER_H
#define UI_SUIPLUGINMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SUiPluginManager
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *chkQtCore;
    QCheckBox *chkQtGui;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cmdOK;
    QListWidget *lstchkPlugin;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *lblTitre;
    QLabel *lblTitre_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkScriptable;
    QCheckBox *chkCtlPanel;
    QPushButton *cmdOpt;
    QLabel *lblTitre_3;
    QLabel *lblSdkVersion;
    QLabel *lblPluginVersion;
    QLabel *lblPluginVersionTxt;
    QLabel *lblSdkVersionTxt;
    QLabel *lblTitle;
    QLabel *lblDescription;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *SUiPluginManager)
    {
        if (SUiPluginManager->objectName().isEmpty())
            SUiPluginManager->setObjectName(QString::fromUtf8("SUiPluginManager"));
        SUiPluginManager->resize(795, 555);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SUiPluginManager->sizePolicy().hasHeightForWidth());
        SUiPluginManager->setSizePolicy(sizePolicy);
        SUiPluginManager->setMinimumSize(QSize(795, 555));
        SUiPluginManager->setMaximumSize(QSize(795, 555));
        SUiPluginManager->setSizeGripEnabled(false);
        horizontalLayoutWidget = new QWidget(SUiPluginManager);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 510, 791, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        chkQtCore = new QCheckBox(horizontalLayoutWidget);
        chkQtCore->setObjectName(QString::fromUtf8("chkQtCore"));

        horizontalLayout_4->addWidget(chkQtCore);

        chkQtGui = new QCheckBox(horizontalLayoutWidget);
        chkQtGui->setObjectName(QString::fromUtf8("chkQtGui"));

        horizontalLayout_4->addWidget(chkQtGui);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        cmdOK = new QPushButton(horizontalLayoutWidget);
        cmdOK->setObjectName(QString::fromUtf8("cmdOK"));

        horizontalLayout_4->addWidget(cmdOK);

        lstchkPlugin = new QListWidget(SUiPluginManager);
        lstchkPlugin->setObjectName(QString::fromUtf8("lstchkPlugin"));
        lstchkPlugin->setEnabled(true);
        lstchkPlugin->setGeometry(QRect(0, 10, 391, 461));
        sizePolicy.setHeightForWidth(lstchkPlugin->sizePolicy().hasHeightForWidth());
        lstchkPlugin->setSizePolicy(sizePolicy);
        lstchkPlugin->setMinimumSize(QSize(300, 459));
        lstchkPlugin->setBaseSize(QSize(302, 0));
        layoutWidget = new QWidget(SUiPluginManager);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(400, 10, 391, 486));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lblTitre = new QLabel(layoutWidget);
        lblTitre->setObjectName(QString::fromUtf8("lblTitre"));

        gridLayout->addWidget(lblTitre, 0, 0, 1, 1);

        lblTitre_2 = new QLabel(layoutWidget);
        lblTitre_2->setObjectName(QString::fromUtf8("lblTitre_2"));
        lblTitre_2->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(lblTitre_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chkScriptable = new QCheckBox(layoutWidget);
        chkScriptable->setObjectName(QString::fromUtf8("chkScriptable"));

        horizontalLayout->addWidget(chkScriptable);

        chkCtlPanel = new QCheckBox(layoutWidget);
        chkCtlPanel->setObjectName(QString::fromUtf8("chkCtlPanel"));
        chkCtlPanel->setEnabled(true);
        chkCtlPanel->setTristate(false);

        horizontalLayout->addWidget(chkCtlPanel);

        cmdOpt = new QPushButton(layoutWidget);
        cmdOpt->setObjectName(QString::fromUtf8("cmdOpt"));
        cmdOpt->setEnabled(false);
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

        horizontalLayout->addWidget(cmdOpt);


        gridLayout->addLayout(horizontalLayout, 5, 1, 1, 1);

        lblTitre_3 = new QLabel(layoutWidget);
        lblTitre_3->setObjectName(QString::fromUtf8("lblTitre_3"));

        gridLayout->addWidget(lblTitre_3, 5, 0, 1, 1);

        lblSdkVersion = new QLabel(layoutWidget);
        lblSdkVersion->setObjectName(QString::fromUtf8("lblSdkVersion"));

        gridLayout->addWidget(lblSdkVersion, 4, 1, 1, 1);

        lblPluginVersion = new QLabel(layoutWidget);
        lblPluginVersion->setObjectName(QString::fromUtf8("lblPluginVersion"));

        gridLayout->addWidget(lblPluginVersion, 3, 1, 1, 1);

        lblPluginVersionTxt = new QLabel(layoutWidget);
        lblPluginVersionTxt->setObjectName(QString::fromUtf8("lblPluginVersionTxt"));

        gridLayout->addWidget(lblPluginVersionTxt, 3, 0, 1, 1);

        lblSdkVersionTxt = new QLabel(layoutWidget);
        lblSdkVersionTxt->setObjectName(QString::fromUtf8("lblSdkVersionTxt"));

        gridLayout->addWidget(lblSdkVersionTxt, 4, 0, 1, 1);

        lblTitle = new QLabel(layoutWidget);
        lblTitle->setObjectName(QString::fromUtf8("lblTitle"));

        gridLayout->addWidget(lblTitle, 0, 1, 1, 1);

        lblDescription = new QLabel(layoutWidget);
        lblDescription->setObjectName(QString::fromUtf8("lblDescription"));
        lblDescription->setMinimumSize(QSize(0, 350));
        lblDescription->setMaximumSize(QSize(500, 16777215));
        lblDescription->setAlignment(Qt::AlignJustify|Qt::AlignTop);
        lblDescription->setWordWrap(true);

        gridLayout->addWidget(lblDescription, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);


        retranslateUi(SUiPluginManager);

        QMetaObject::connectSlotsByName(SUiPluginManager);
    } // setupUi

    void retranslateUi(QDialog *SUiPluginManager)
    {
        SUiPluginManager->setWindowTitle(QApplication::translate("SUiPluginManager", "Plugin Manager", 0, QApplication::UnicodeUTF8));
        chkQtCore->setText(QApplication::translate("SUiPluginManager", "Plugin script Qt Core", 0, QApplication::UnicodeUTF8));
        chkQtGui->setText(QApplication::translate("SUiPluginManager", "Plugin script Qt Gui", 0, QApplication::UnicodeUTF8));
        cmdOK->setText(QApplication::translate("SUiPluginManager", "Ok", 0, QApplication::UnicodeUTF8));
        lblTitre->setText(QApplication::translate("SUiPluginManager", "Title:", 0, QApplication::UnicodeUTF8));
        lblTitre_2->setText(QApplication::translate("SUiPluginManager", "description", 0, QApplication::UnicodeUTF8));
        chkScriptable->setText(QApplication::translate("SUiPluginManager", "Scriptable", 0, QApplication::UnicodeUTF8));
        chkCtlPanel->setText(QApplication::translate("SUiPluginManager", "Control panel", 0, QApplication::UnicodeUTF8));
        lblTitre_3->setText(QApplication::translate("SUiPluginManager", "Properties", 0, QApplication::UnicodeUTF8));
        lblSdkVersion->setText(QApplication::translate("SUiPluginManager", "0.0", 0, QApplication::UnicodeUTF8));
        lblPluginVersion->setText(QApplication::translate("SUiPluginManager", "0.0", 0, QApplication::UnicodeUTF8));
        lblPluginVersionTxt->setText(QApplication::translate("SUiPluginManager", "Plugin version", 0, QApplication::UnicodeUTF8));
        lblSdkVersionTxt->setText(QApplication::translate("SUiPluginManager", "SDK version", 0, QApplication::UnicodeUTF8));
        lblTitle->setText(QString());
        lblDescription->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SUiPluginManager: public Ui_SUiPluginManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUIPLUGINMANAGER_H

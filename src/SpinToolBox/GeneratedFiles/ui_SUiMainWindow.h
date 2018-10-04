/********************************************************************************
** Form generated from reading UI file 'SUiMainWindow.ui'
**
** Created: Fri 16. Nov 16:00:33 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUIMAINWINDOW_H
#define UI_SUIMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SUiMainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdOpen;
    QPushButton *cmdNewScript;
    QPushButton *cmdCmdMan;
    QPushButton *cmdPlgMng;
    QSpacerItem *verticalSpacer;
    QPushButton *cmdQuit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *chkbErrorLog;
    QCheckBox *chkbEventLog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SUiMainWindow)
    {
        if (SUiMainWindow->objectName().isEmpty())
            SUiMainWindow->setObjectName(QString::fromUtf8("SUiMainWindow"));
        SUiMainWindow->resize(450, 250);
        SUiMainWindow->setMinimumSize(QSize(450, 250));
        SUiMainWindow->setMaximumSize(QSize(450, 250));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/compass32.png"), QSize(), QIcon::Normal, QIcon::Off);
        SUiMainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(SUiMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(265, 10, 160, 181));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cmdOpen = new QPushButton(verticalLayoutWidget);
        cmdOpen->setObjectName(QString::fromUtf8("cmdOpen"));

        verticalLayout->addWidget(cmdOpen);

        cmdNewScript = new QPushButton(verticalLayoutWidget);
        cmdNewScript->setObjectName(QString::fromUtf8("cmdNewScript"));

        verticalLayout->addWidget(cmdNewScript);

        cmdCmdMan = new QPushButton(verticalLayoutWidget);
        cmdCmdMan->setObjectName(QString::fromUtf8("cmdCmdMan"));

        verticalLayout->addWidget(cmdCmdMan);

        cmdPlgMng = new QPushButton(verticalLayoutWidget);
        cmdPlgMng->setObjectName(QString::fromUtf8("cmdPlgMng"));

        verticalLayout->addWidget(cmdPlgMng);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        cmdQuit = new QPushButton(verticalLayoutWidget);
        cmdQuit->setObjectName(QString::fromUtf8("cmdQuit"));

        verticalLayout->addWidget(cmdQuit);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(35, 0, 221, 141));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 130, 226, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 160, 226, 41));
        chkbErrorLog = new QCheckBox(centralwidget);
        chkbErrorLog->setObjectName(QString::fromUtf8("chkbErrorLog"));
        chkbErrorLog->setEnabled(false);
        chkbErrorLog->setGeometry(QRect(10, 470, 71, 18));
        chkbEventLog = new QCheckBox(centralwidget);
        chkbEventLog->setObjectName(QString::fromUtf8("chkbEventLog"));
        chkbEventLog->setEnabled(false);
        chkbEventLog->setGeometry(QRect(110, 470, 71, 18));
        SUiMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SUiMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 450, 18));
        SUiMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SUiMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SUiMainWindow->setStatusBar(statusbar);

        retranslateUi(SUiMainWindow);

        QMetaObject::connectSlotsByName(SUiMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SUiMainWindow)
    {
        SUiMainWindow->setWindowTitle(QApplication::translate("SUiMainWindow", "SpinToolBox", 0, QApplication::UnicodeUTF8));
        cmdOpen->setText(QApplication::translate("SUiMainWindow", "Open file", 0, QApplication::UnicodeUTF8));
        cmdNewScript->setText(QApplication::translate("SUiMainWindow", "New Script", 0, QApplication::UnicodeUTF8));
        cmdCmdMan->setText(QApplication::translate("SUiMainWindow", "Control panel", 0, QApplication::UnicodeUTF8));
        cmdPlgMng->setText(QApplication::translate("SUiMainWindow", "Plugin Manager", 0, QApplication::UnicodeUTF8));
        cmdQuit->setText(QApplication::translate("SUiMainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SUiMainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/compass128.png\" /></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SUiMainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600; color:#00007f;\">SpinToolBox V2.6</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SUiMainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic; color:#00007f;\">Sylvain Martin</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic; color:#00007f;\">2010-2012</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        chkbErrorLog->setText(QApplication::translate("SUiMainWindow", "Error Log", 0, QApplication::UnicodeUTF8));
        chkbEventLog->setText(QApplication::translate("SUiMainWindow", "Event Log", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SUiMainWindow: public Ui_SUiMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUIMAINWINDOW_H

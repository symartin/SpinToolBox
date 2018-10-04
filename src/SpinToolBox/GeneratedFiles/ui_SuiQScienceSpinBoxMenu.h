/********************************************************************************
** Form generated from reading UI file 'SuiQScienceSpinBoxMenu.ui'
**
** Created: Thu 8. Nov 11:25:14 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUIQSCIENCESPINBOXMENU_H
#define UI_SUIQSCIENCESPINBOXMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radScientific;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radEngineer;
    QVBoxLayout *verticalLayout;
    QLabel *lblPrecision;
    QLineEdit *lineEdit;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(161, 87);
        gridLayout_2 = new QGridLayout(Form);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radScientific = new QRadioButton(Form);
        radScientific->setObjectName(QString::fromUtf8("radScientific"));

        horizontalLayout->addWidget(radScientific);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        radEngineer = new QRadioButton(Form);
        radEngineer->setObjectName(QString::fromUtf8("radEngineer"));

        horizontalLayout->addWidget(radEngineer);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblPrecision = new QLabel(Form);
        lblPrecision->setObjectName(QString::fromUtf8("lblPrecision"));

        verticalLayout->addWidget(lblPrecision);


        gridLayout_2->addLayout(verticalLayout, 1, 0, 1, 1);

        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 2, 0, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        radScientific->setText(QApplication::translate("Form", "scientific", 0, QApplication::UnicodeUTF8));
        radEngineer->setText(QApplication::translate("Form", "engineer", 0, QApplication::UnicodeUTF8));
        lblPrecision->setText(QApplication::translate("Form", "precision", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUIQSCIENCESPINBOXMENU_H

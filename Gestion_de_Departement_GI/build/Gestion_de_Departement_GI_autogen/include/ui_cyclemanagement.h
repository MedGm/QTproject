/********************************************************************************
** Form generated from reading UI file 'cyclemanagement.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CYCLEMANAGEMENT_H
#define UI_CYCLEMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cyclemanagement
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *sidebarWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *levelComboBox;
    QPushButton *studentsButton;
    QPushButton *scheduleButton;
    QPushButton *internshipsButton;
    QSpacerItem *verticalSpacer;
    QLabel *logoLabel;
    QPushButton *logoutButton;
    QStackedWidget *mainStack;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *cyclemanagement)
    {
        if (cyclemanagement->objectName().isEmpty())
            cyclemanagement->setObjectName("cyclemanagement");
        cyclemanagement->resize(1200, 800);
        cyclemanagement->setMinimumSize(QSize(1200, 800));
        cyclemanagement->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-image: url(:/assets/fst.jpeg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}\n"
"QWidget#centralwidget {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"                               stop:0 rgba(0, 123, 255, 0.35),\n"
"                               stop:1 rgba(0, 123, 255, 0.3));\n"
"}"));
        centralwidget = new QWidget(cyclemanagement);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        sidebarWidget = new QWidget(centralwidget);
        sidebarWidget->setObjectName("sidebarWidget");
        sidebarWidget->setMinimumSize(QSize(250, 0));
        sidebarWidget->setMaximumSize(QSize(250, 16777215));
        sidebarWidget->setStyleSheet(QString::fromUtf8("QWidget#sidebarWidget {\n"
"    background-color: rgba(41, 128, 185, 0.9);\n"
"    border-radius: 15px;\n"
"    margin: 10px;\n"
"}\n"
"QComboBox {\n"
"    background-color: white;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    margin: 10px;\n"
"    font-size: 14px;\n"
"    font-family: 'Segoe UI', Arial;\n"
"}\n"
"QPushButton {\n"
"    background-color: rgba(255, 255, 255, 0.1);\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 10px;\n"
"    margin: 5px 10px;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-family: 'Segoe UI', Arial;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(255, 255, 255, 0.2);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(255, 255, 255, 0.3);\n"
"}\n"
"QPushButton#logoutButton {\n"
"    background-color: rgba(231, 76, 60, 0.8);\n"
"    margin-top: 20px;\n"
"    margin-bottom: 10px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#logoutButton:hover {\n"
"    background-color: rgba(231, 76, 6"
                        "0, 1.0);\n"
"}"));
        verticalLayout = new QVBoxLayout(sidebarWidget);
        verticalLayout->setObjectName("verticalLayout");
        levelComboBox = new QComboBox(sidebarWidget);
        levelComboBox->setObjectName("levelComboBox");

        verticalLayout->addWidget(levelComboBox);

        studentsButton = new QPushButton(sidebarWidget);
        studentsButton->setObjectName("studentsButton");

        verticalLayout->addWidget(studentsButton);

        scheduleButton = new QPushButton(sidebarWidget);
        scheduleButton->setObjectName("scheduleButton");

        verticalLayout->addWidget(scheduleButton);

        internshipsButton = new QPushButton(sidebarWidget);
        internshipsButton->setObjectName("internshipsButton");

        verticalLayout->addWidget(internshipsButton);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        logoLabel = new QLabel(sidebarWidget);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setMinimumSize(QSize(225, 90));
        logoLabel->setMaximumSize(QSize(225, 100));
        logoLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: white;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"	margin-left:5px;\n"
"}"));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(logoLabel);

        logoutButton = new QPushButton(sidebarWidget);
        logoutButton->setObjectName("logoutButton");

        verticalLayout->addWidget(logoutButton);


        horizontalLayout->addWidget(sidebarWidget);

        mainStack = new QStackedWidget(centralwidget);
        mainStack->setObjectName("mainStack");
        mainStack->setStyleSheet(QString::fromUtf8("QStackedWidget {\n"
"    background-color: rgba(255, 255, 255, 0.9);\n"
"    border-radius: 15px;\n"
"    margin: 10px;\n"
"}\n"
"QTableWidget {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    gridline-color: #bdc3c7;\n"
"    font-family: 'Segoe UI', Arial;\n"
"    font-size: 13px;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #2980b9;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));

        horizontalLayout->addWidget(mainStack);

        cyclemanagement->setCentralWidget(centralwidget);
        menubar = new QMenuBar(cyclemanagement);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 21));
        cyclemanagement->setMenuBar(menubar);
        statusbar = new QStatusBar(cyclemanagement);
        statusbar->setObjectName("statusbar");
        cyclemanagement->setStatusBar(statusbar);

        retranslateUi(cyclemanagement);

        QMetaObject::connectSlotsByName(cyclemanagement);
    } // setupUi

    void retranslateUi(QMainWindow *cyclemanagement)
    {
        cyclemanagement->setWindowTitle(QCoreApplication::translate("cyclemanagement", "Gestion du Cycle d'Ing\303\251nieur", nullptr));
        studentsButton->setText(QCoreApplication::translate("cyclemanagement", "\303\211tudiants", nullptr));
        scheduleButton->setText(QCoreApplication::translate("cyclemanagement", "Emploi du temps", nullptr));
        internshipsButton->setText(QCoreApplication::translate("cyclemanagement", "Stages PFE/PFA", nullptr));
        logoutButton->setText(QCoreApplication::translate("cyclemanagement", "D\303\251connexion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cyclemanagement: public Ui_cyclemanagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CYCLEMANAGEMENT_H

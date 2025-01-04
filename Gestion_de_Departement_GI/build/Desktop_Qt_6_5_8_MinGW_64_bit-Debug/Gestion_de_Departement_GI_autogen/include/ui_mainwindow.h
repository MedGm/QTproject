/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *headerLabel;
    QLabel *welcomeLabel;
    QSpacerItem *topSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *Adminbutton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *bottomSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-image: url(:/assets/fst.jpeg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}\n"
"QWidget#centralwidget {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"                               stop:0 rgba(0, 123, 255, 0.35),\n"
"                               stop:1 rgba(0, 123, 255, 0.3));\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(40);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(60, -1, 60, -1);
        headerLabel = new QLabel(centralwidget);
        headerLabel->setObjectName("headerLabel");
        headerLabel->setStyleSheet(QString::fromUtf8("QLabel#headerLabel {\n"
"    color: #2980b9;\n"
"    font-size: 34px;\n"
"    font-weight: bold;\n"
"    padding: 20px 30px;\n"
"    background-color: rgba(255, 255, 255, 0.9);\n"
"    border-radius: 15px;\n"
"    border-left: 8px solid #3498db;\n"
"    margin: 10px;\n"
"    font-family: 'Segoe UI', Arial;\n"
"    letter-spacing: 1px;\n"
"}"));
        headerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(headerLabel);

        welcomeLabel = new QLabel(centralwidget);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setStyleSheet(QString::fromUtf8("QLabel#welcomeLabel {\n"
"    color: white;\n"
"    font-size: 20px;\n"
"    font-weight: normal;\n"
"    padding: 15px;\n"
"    background-color: rgba(41, 128, 185, 0.7);\n"
"    border-radius: 10px;\n"
"    margin: 10px;\n"
"    font-family: 'Segoe UI', Arial;\n"
"    letter-spacing: 0.5px;\n"
"}"));
        welcomeLabel->setAlignment(Qt::AlignCenter);
        welcomeLabel->setWordWrap(true);

        verticalLayout->addWidget(welcomeLabel);

        topSpacer = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(topSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Adminbutton = new QPushButton(centralwidget);
        Adminbutton->setObjectName("Adminbutton");
        Adminbutton->setMinimumSize(QSize(250, 50));
        Adminbutton->setMaximumSize(QSize(250, 50));
        Adminbutton->setCursor(QCursor(Qt::PointingHandCursor));
        Adminbutton->setStyleSheet(QString::fromUtf8("QPushButton#Adminbutton {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    border: 2px solid white;\n"
"    border-radius: 25px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    padding-left: 15px;\n"
"    font-family: \"Roboto\",sans-serif;\n"
"    letter-spacing: 0.5px;\n"
"    text-align: left;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        Adminbutton->setIcon(icon);
        Adminbutton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(Adminbutton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        bottomSpacer = new QSpacerItem(20, 150, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(bottomSpacer);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "D\303\251partement G\303\251nie Informatique", nullptr));
        headerLabel->setText(QCoreApplication::translate("MainWindow", "D\303\251partement G\303\251nie Informatique", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("MainWindow", "Bienvenue au d\303\251partement de G\303\251nie Informatique. \n"
"Veuillez vous connecter pour acc\303\251der \303\240 l'interface d'administration.", nullptr));
        Adminbutton->setText(QCoreApplication::translate("MainWindow", "  Connecter comme Admin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

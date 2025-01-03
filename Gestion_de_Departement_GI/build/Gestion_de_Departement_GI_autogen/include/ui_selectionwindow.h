/********************************************************************************
** Form generated from reading UI file 'selectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTIONWINDOW_H
#define UI_SELECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectionWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topButtonsLayout;
    QPushButton *professorsButton;
    QPushButton *demandsButton;
    QPushButton *reservationsButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *topSpacer;
    QLabel *headerLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer1;
    QPushButton *masterButton;
    QPushButton *licenceButton;
    QPushButton *engineerButton;
    QSpacerItem *horizontalSpacer2;
    QSpacerItem *bottomSpacer;
    QStackedWidget *mainStack;

    void setupUi(QMainWindow *SelectionWindow)
    {
        if (SelectionWindow->objectName().isEmpty())
            SelectionWindow->setObjectName("SelectionWindow");
        SelectionWindow->resize(1000, 600);
        SelectionWindow->setMinimumSize(QSize(1000, 600));
        SelectionWindow->setStyleSheet(QString::fromUtf8("\n"
"    QMainWindow {\n"
"        background-image: url(:/assets/fst.jpeg);\n"
"        background-repeat: no-repeat;\n"
"        background-position: center;\n"
"    }\n"
"    QWidget#centralwidget {\n"
"        background: rgba(41, 128, 185, 0.85);\n"
"    }\n"
"    #professorsButton, #demandsButton, #reservationsButton {\n"
"        background-color: rgba(255, 255, 255, 0.15);\n"
"        color: white;\n"
"        border: none;\n"
"        border-radius: 8px;\n"
"        font-family: 'Segoe UI', Arial;\n"
"        font-size: 14px;\n"
"        font-weight: bold;\n"
"        padding: 8px 15px;\n"
"    }\n"
"    #professorsButton:hover, #demandsButton:hover, #reservationsButton:hover {\n"
"        background-color: rgba(255, 255, 255, 0.25);\n"
"    }\n"
"    QLabel {\n"
"        color: white;\n"
"        font-family: 'Segoe UI', Arial;\n"
"    }\n"
"   "));
        centralwidget = new QWidget(SelectionWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        topButtonsLayout = new QHBoxLayout();
        topButtonsLayout->setSpacing(20);
        topButtonsLayout->setObjectName("topButtonsLayout");
        topButtonsLayout->setContentsMargins(20, -1, 20, -1);
        professorsButton = new QPushButton(centralwidget);
        professorsButton->setObjectName("professorsButton");
        professorsButton->setMinimumSize(QSize(180, 40));
        professorsButton->setStyleSheet(QString::fromUtf8("\n"
"          background-color: rgba(255, 255, 255, 0.15);\n"
"          font-size: 14px;\n"
"         "));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/professor.png"), QSize(), QIcon::Normal, QIcon::Off);
        professorsButton->setIcon(icon);

        topButtonsLayout->addWidget(professorsButton);

        demandsButton = new QPushButton(centralwidget);
        demandsButton->setObjectName("demandsButton");
        demandsButton->setMinimumSize(QSize(180, 40));
        demandsButton->setStyleSheet(QString::fromUtf8("\n"
"          background-color: rgba(255, 255, 255, 0.15);\n"
"          font-size: 14px;\n"
"         "));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/assets/document.png"), QSize(), QIcon::Normal, QIcon::Off);
        demandsButton->setIcon(icon1);

        topButtonsLayout->addWidget(demandsButton);

        reservationsButton = new QPushButton(centralwidget);
        reservationsButton->setObjectName("reservationsButton");
        reservationsButton->setMinimumSize(QSize(180, 40));
        reservationsButton->setStyleSheet(QString::fromUtf8("\n"
"                background-color: rgba(255, 255, 255, 0.15);\n"
"                color: white;\n"
"                border: none;\n"
"                border-radius: 8px;\n"
"                font-family: 'Segoe UI', Arial;\n"
"                font-size: 14px;\n"
"                font-weight: bold;\n"
"                padding: 8px 15px;\n"
"            "));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/assets/calendar.png"), QSize(), QIcon::Normal, QIcon::Off);
        reservationsButton->setIcon(icon2);

        topButtonsLayout->addWidget(reservationsButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topButtonsLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(topButtonsLayout);

        topSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(topSpacer);

        headerLabel = new QLabel(centralwidget);
        headerLabel->setObjectName("headerLabel");
        headerLabel->setStyleSheet(QString::fromUtf8("font-size: 24px;\n"
"font-weight: bold;\n"
"color: white;\n"
"background-color: transparent;\n"
"padding: 20px;\n"
"border-radius: 10px;\n"
"font-family: 'Roboto', sans-serif;"));
        headerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(headerLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(30);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer1);

        masterButton = new QPushButton(centralwidget);
        masterButton->setObjectName("masterButton");
        masterButton->setMinimumSize(QSize(300, 250));
        masterButton->setCursor(QCursor(Qt::PointingHandCursor));
        masterButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 15px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 rgba(41, 128, 185, 0.9), \n"
"                               stop:1 rgba(41, 128, 185, 0.7));\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', Arial;\n"
"    text-align: center;\n"
"    padding-bottom: 20px;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 rgba(52, 152, 219, 0.9),\n"
"                               stop:1 rgba(52, 152, 219, 0.7));\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 rgba(41, 128, 185, 1),\n"
"                               stop:1 rgba(41, 128, 185, 0.8));\n"
"}"));

        horizontalLayout->addWidget(masterButton);

        licenceButton = new QPushButton(centralwidget);
        licenceButton->setObjectName("licenceButton");
        licenceButton->setMinimumSize(QSize(300, 250));
        licenceButton->setCursor(QCursor(Qt::PointingHandCursor));
        licenceButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 15px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 rgba(41, 128, 185, 0.85), \n"
"                               stop:1 rgba(41, 128, 185, 0.65));\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', Arial;\n"
"    text-align: center;\n"
"    padding-bottom: 20px;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 rgba(52, 152, 219, 0.85),\n"
"                               stop:1 rgba(52, 152, 219, 0.65));\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 rgba(41, 128, 185, 0.95),\n"
"                               stop:1 rgba(41, 128, 185, 0.75));\n"
"}"));

        horizontalLayout->addWidget(licenceButton);

        engineerButton = new QPushButton(centralwidget);
        engineerButton->setObjectName("engineerButton");
        engineerButton->setMinimumSize(QSize(300, 250));
        engineerButton->setCursor(QCursor(Qt::PointingHandCursor));
        engineerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 15px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 rgba(41, 128, 185, 0.95), \n"
"                               stop:1 rgba(41, 128, 185, 0.75));\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', Arial;\n"
"    text-align: center;\n"
"    padding-bottom: 20px;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 rgba(52, 152, 219, 0.95),\n"
"                               stop:1 rgba(52, 152, 219, 0.75));\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 rgba(41, 128, 185, 1),\n"
"                               stop:1 rgba(41, 128, 185, 0.8));\n"
"}"));

        horizontalLayout->addWidget(engineerButton);

        horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer2);


        verticalLayout->addLayout(horizontalLayout);

        bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(bottomSpacer);

        mainStack = new QStackedWidget(centralwidget);
        mainStack->setObjectName("mainStack");

        verticalLayout->addWidget(mainStack);

        SelectionWindow->setCentralWidget(centralwidget);

        retranslateUi(SelectionWindow);

        QMetaObject::connectSlotsByName(SelectionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SelectionWindow)
    {
        SelectionWindow->setWindowTitle(QCoreApplication::translate("SelectionWindow", "Selection des Formations", nullptr));
        professorsButton->setText(QCoreApplication::translate("SelectionWindow", "Professeurs", nullptr));
        demandsButton->setText(QCoreApplication::translate("SelectionWindow", "Demandes", nullptr));
        reservationsButton->setText(QCoreApplication::translate("SelectionWindow", "R\303\251servations", nullptr));
        headerLabel->setText(QCoreApplication::translate("SelectionWindow", "S\303\251lectionnez une Formation", nullptr));
        masterButton->setText(QCoreApplication::translate("SelectionWindow", "Master en Sciences\n"
"et Techniques", nullptr));
        licenceButton->setText(QCoreApplication::translate("SelectionWindow", "Licence en Sciences\n"
"et Techniques", nullptr));
        engineerButton->setText(QCoreApplication::translate("SelectionWindow", "Cycle d'Ing\303\251nieur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectionWindow: public Ui_SelectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTIONWINDOW_H

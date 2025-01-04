/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *errorLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(500, 300);
        LoginDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"                               stop:0 rgba(0, 123, 255, 0.35),\n"
"                               stop:1 rgba(0, 123, 255, 0.3));\n"
"}\n"
"QLabel {\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', Arial;\n"
"}\n"
"QLineEdit {\n"
"    padding: 8px;\n"
"    padding-left: 40px;\n"
"    font-size: 14px;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 8px;\n"
"    background-color: rgba(255, 255, 255, 0.9);\n"
"    color: #2c3e50;\n"
"    font-family: 'Segoe UI', Arial;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #2980b9;\n"
"    background-color: white;\n"
"}"));
        verticalLayout = new QVBoxLayout(LoginDialog);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(15);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(40, -1, 40, -1);
        usernameLabel = new QLabel(LoginDialog);
        usernameLabel->setObjectName("usernameLabel");
        usernameLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(usernameLabel, 0, 0, 1, 1);

        usernameLineEdit = new QLineEdit(LoginDialog);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setMinimumSize(QSize(250, 45));

        gridLayout->addWidget(usernameLineEdit, 0, 1, 1, 1);

        passwordLabel = new QLabel(LoginDialog);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(passwordLabel, 1, 0, 1, 1);

        passwordLineEdit = new QLineEdit(LoginDialog);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setMinimumSize(QSize(250, 45));
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(passwordLineEdit, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        errorLabel = new QLabel(LoginDialog);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setAlignment(Qt::AlignCenter);
        errorLabel->setVisible(false);

        verticalLayout->addWidget(errorLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        loginButton = new QPushButton(LoginDialog);
        loginButton->setObjectName("loginButton");
        loginButton->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(loginButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginDialog", "Username:", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginDialog", "Password:", nullptr));
        errorLabel->setText(QCoreApplication::translate("LoginDialog", "Le nom ou mot de passe incorrect", nullptr));
        errorLabel->setStyleSheet(QCoreApplication::translate("LoginDialog", "color: red; font-size: 12px;", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H

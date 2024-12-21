#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include <QPainter>
#include <QStyle>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setModal(true);

    setupAnimations();
    setupInputIcons();
    ui->loginButton->installEventFilter(this);

    updateButtonStylesheet(0.0);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setupAnimations()
{
    buttonColorAnimation = new QVariantAnimation(this);
    buttonColorAnimation->setDuration(200);
    connect(buttonColorAnimation, &QVariantAnimation::valueChanged,
            this, &LoginDialog::updateButtonStylesheet);
}

void LoginDialog::updateButtonStylesheet(const QVariant &value)
{
    double opacity = value.toDouble();
    QString color = opacity > 0.5 ? "#2980b9" : "white";
    
    QString style = QString("QPushButton#loginButton {"
                          "background-color: rgba(255, 255, 255, %1);"
                          "color: %2;"
                          "border: 2px solid %2;"
                          "border-radius: 15px;"
                          "font-size: 14px;"
                          "font-weight: bold;"
                          "font-family: 'Roboto',sans-serif;"
                          "letter-spacing: 0.5px;"
                          "}")
                    .arg(opacity)
                    .arg(color);
    ui->loginButton->setStyleSheet(style);
}

bool LoginDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->loginButton) {
        if (event->type() == QEvent::Enter) {
            buttonColorAnimation->setStartValue(0.0);
            buttonColorAnimation->setEndValue(0.9);
            buttonColorAnimation->start();
        } else if (event->type() == QEvent::Leave) {
            buttonColorAnimation->setStartValue(0.9);
            buttonColorAnimation->setEndValue(0.0);
            buttonColorAnimation->start();
        }
    }
    return QDialog::eventFilter(obj, event);
}

void LoginDialog::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    
    ui->errorLabel->setVisible(false);
    
    // username w password dyal admin
    if (username == "admin" && password == "admin") {
        accept();
    } else {
        ui->errorLabel->setVisible(true);  // message d erreur
        ui->passwordLineEdit->clear();
        qDebug() << "Invalid credentials";
    }
}

void LoginDialog::setupInputIcons() // design de login
{
    QIcon userIcon(":/assets/user.png");
    QPixmap userPixmap = userIcon.pixmap(QSize(24, 24));
    
    QLabel* userIconLabel = new QLabel(ui->usernameLineEdit);
    userIconLabel->setPixmap(userPixmap);
    userIconLabel->setStyleSheet("QLabel { background-color: transparent; }");
    userIconLabel->setGeometry(8, (ui->usernameLineEdit->height() - 24) / 2, 24, 24);

    QIcon lockIcon(":/assets/padlock.png");
    QPixmap lockPixmap = lockIcon.pixmap(QSize(24, 24));
    
    QLabel* lockIconLabel = new QLabel(ui->passwordLineEdit);
    lockIconLabel->setPixmap(lockPixmap);
    lockIconLabel->setStyleSheet("QLabel { background-color: transparent; }");
    lockIconLabel->setGeometry(8, (ui->passwordLineEdit->height() - 24) / 2, 24, 24);
}

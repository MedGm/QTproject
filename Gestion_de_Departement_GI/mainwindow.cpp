#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupAnimations();

    // Install event filters
    ui->Adminbutton->installEventFilter(this);
    ui->headerLabel->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Adminbutton_clicked()
{
    LoginDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        SelectionWindow *selectionWindow = new SelectionWindow();
        selectionWindow->show();
        this->close();
    }
}

void MainWindow::setupAnimations()
{
    buttonColorAnimation = new QVariantAnimation(this);
    buttonColorAnimation->setDuration(200);
    connect(buttonColorAnimation, &QVariantAnimation::valueChanged,
            this, &MainWindow::updateButtonStylesheet);

    headerColorAnimation = new QVariantAnimation(this);
    headerColorAnimation->setDuration(200);
    connect(headerColorAnimation, &QVariantAnimation::valueChanged,
            this, &MainWindow::updateHeaderStylesheet);
}

void MainWindow::updateButtonStylesheet(const QVariant &value)
{
    double opacity = value.toDouble();
    QString color = opacity > 0.5 ? "#2980b9" : "white";
    
    QString style = QString("QPushButton#Adminbutton {"
                          "background-color: rgba(255, 255, 255, %1);"
                          "color: %2;"
                          "border: 2px solid %2;"
                          "border-radius: 25px;"
                          "font-size: 14px;"
                          "font-weight: bold;"
                          "padding-left: 15px;"
                          "font-family: 'Roboto',sans-serif;"
                          "letter-spacing: 0.5px;"
                          "text-align: left;"
                          "}")
                    .arg(opacity)
                    .arg(color);
    ui->Adminbutton->setStyleSheet(style);

    // Update icon color
    QIcon icon(":/assets/user.png");
    QPixmap pixmap = icon.pixmap(QSize(24, 24));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), QColor(color));
    ui->Adminbutton->setIcon(QIcon(pixmap));
}

void MainWindow::updateHeaderStylesheet(const QVariant &value)
{
    double opacity = value.toDouble();
    QString style = QString("QLabel#headerLabel {"
                          "color: #2980b9;"
                          "font-size: 34px;"
                          "font-weight: bold;"
                          "padding: 20px 30px;"
                          "background-color: rgba(255, 255, 255, %1);"
                          "border-radius: 15px;"
                          "border-left: 8px solid #3498db;"
                          "margin: 10px;"
                          "font-family: 'Segoe UI', Arial;"
                          "letter-spacing: 1px;"
                          "}")
                    .arg(opacity);
    ui->headerLabel->setStyleSheet(style);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->Adminbutton) {
        if (event->type() == QEvent::Enter) {
            buttonColorAnimation->setStartValue(0.0);
            buttonColorAnimation->setEndValue(0.9);
            buttonColorAnimation->start();
        } else if (event->type() == QEvent::Leave) {
            buttonColorAnimation->setStartValue(0.9);
            buttonColorAnimation->setEndValue(0.0);
            buttonColorAnimation->start();
        }
    } else if (obj == ui->headerLabel) {
        if (event->type() == QEvent::Enter) {
            headerColorAnimation->setStartValue(0.9);
            headerColorAnimation->setEndValue(1.0);
            headerColorAnimation->start();
        } else if (event->type() == QEvent::Leave) {
            headerColorAnimation->setStartValue(1.0);
            headerColorAnimation->setEndValue(0.9);
            headerColorAnimation->start();
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

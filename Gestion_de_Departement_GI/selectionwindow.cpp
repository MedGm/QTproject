#include "selectionwindow.h"
#include "ui_selectionwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QGraphicsEffect>
#include <QLineEdit>
#include <QFormLayout>
#include <QCheckBox>
#include <QFileDialog>
#include <QMessageBox>

SelectionWindow::SelectionWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SelectionWindow)
{
    ui->setupUi(this);
    setupIcons();
    
    connect(ui->engineerButton, &QPushButton::clicked, this, &SelectionWindow::onEngineerButtonClicked);
    connect(ui->professorsButton, &QPushButton::clicked, this, &SelectionWindow::onProfessorsButtonClicked);
    connect(ui->demandsButton, &QPushButton::clicked, this, &SelectionWindow::onDemandsButtonClicked);
    connect(ui->reservationsButton, &QPushButton::clicked, this, &SelectionWindow::onReservationsButtonClicked);
    
    professorsWindow = nullptr;
    demandsWindow = nullptr;
    reservationsWindow = nullptr;
}

SelectionWindow::~SelectionWindow()
{
    delete ui;
}

void SelectionWindow::setupIcons()
{
    const int ICON_SIZE = 80;
    
    auto setupButton = [this](QPushButton* button, const QString& iconPath) {
        QIcon icon(iconPath);
        QPixmap pixmap(ICON_SIZE, ICON_SIZE);
        pixmap.fill(Qt::transparent);
        
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.drawPixmap(0, 0, icon.pixmap(ICON_SIZE, ICON_SIZE));
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(pixmap.rect(), Qt::white);
        
        button->setIcon(QIcon(pixmap));
        button->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
        button->setStyleSheet(button->styleSheet() + 
            "QPushButton { text-align: center; padding-top: 40px; }"
            "QPushButton::icon { margin-bottom: 20px; }"
        );
    };

    setupButton(ui->masterButton, ":/assets/master.png");
    setupButton(ui->licenceButton, ":/assets/licence.png");
    setupButton(ui->engineerButton, ":/assets/cycle.png");
    
    for(auto button : {ui->masterButton, ui->licenceButton, ui->engineerButton}) {
        button->setFlat(true);
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setColor(QColor(0, 0, 0, 80));
        shadow->setOffset(0, 4);
        button->setGraphicsEffect(shadow);
    }
}

void SelectionWindow::onEngineerButtonClicked() //configuration de button de cycle d'ing
{
    cyclemanagement *cycleWindow = new cyclemanagement(this);
    cycleWindow->show();
    this->hide();
}

void SelectionWindow::onProfessorsButtonClicked() //configuration de button de professeur
{
    if (!professorsWindow) {
        professorsWindow = new ProfessorsWindow(this);
    }
    professorsWindow->show();
}

void SelectionWindow::onDemandsButtonClicked() //configuration de button des demandes
{
    if (!demandsWindow) {
        demandsWindow = new DemandsWindow(this);
    }
    demandsWindow->show();
}

void SelectionWindow::onReservationsButtonClicked()
{
    if (!reservationsWindow) {
        reservationsWindow = new ReservationsWindow(this);
    }
    reservationsWindow->show();
}

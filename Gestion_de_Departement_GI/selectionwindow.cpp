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
<<<<<<< HEAD



=======
    
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    connect(ui->engineerButton, &QPushButton::clicked, this, &SelectionWindow::onEngineerButtonClicked);
    connect(ui->professorsButton, &QPushButton::clicked, this, &SelectionWindow::onProfessorsButtonClicked);
    connect(ui->demandsButton, &QPushButton::clicked, this, &SelectionWindow::onDemandsButtonClicked);
    connect(ui->reservationsButton, &QPushButton::clicked, this, &SelectionWindow::onReservationsButtonClicked);
    connect(ui->licenceButton, &QPushButton::clicked, this, &SelectionWindow::onLicenceButtonClicked);
    connect(ui->masterButton, &QPushButton::clicked, this, &SelectionWindow::onMasterButtonClicked);

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
<<<<<<< HEAD

=======
    
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    auto setupButton = [this](QPushButton* button, const QString& iconPath) {
        QIcon icon(iconPath);
        QPixmap pixmap(ICON_SIZE, ICON_SIZE);
        pixmap.fill(Qt::transparent);
<<<<<<< HEAD

=======
        
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.drawPixmap(0, 0, icon.pixmap(ICON_SIZE, ICON_SIZE));
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(pixmap.rect(), Qt::white);
<<<<<<< HEAD

        button->setIcon(QIcon(pixmap));
        button->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
        button->setStyleSheet(button->styleSheet() +
                              "QPushButton { text-align: center; padding-top: 40px; }"
                              "QPushButton::icon { margin-bottom: 20px; }"
                              );
=======
        
        button->setIcon(QIcon(pixmap));
        button->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
        button->setStyleSheet(button->styleSheet() + 
            "QPushButton { text-align: center; padding-top: 40px; }"
            "QPushButton::icon { margin-bottom: 20px; }"
        );
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    };

    setupButton(ui->masterButton, ":/assets/master.png");
    setupButton(ui->licenceButton, ":/assets/licence.png");
    setupButton(ui->engineerButton, ":/assets/cycle.png");
<<<<<<< HEAD

=======
    
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    for(auto button : {ui->masterButton, ui->licenceButton, ui->engineerButton}) {
        button->setFlat(true);
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setColor(QColor(0, 0, 0, 80));
        shadow->setOffset(0, 4);
        button->setGraphicsEffect(shadow);
    }
}

<<<<<<< HEAD
void SelectionWindow::onEngineerButtonClicked()
=======
void SelectionWindow::onEngineerButtonClicked() //configuration de button de cycle d'ing
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
{
    cyclemanagement *cycleWindow = new cyclemanagement(this);
    cycleWindow->show();
    this->hide();
}

<<<<<<< HEAD
void SelectionWindow::onProfessorsButtonClicked()
=======
void SelectionWindow::onProfessorsButtonClicked() //configuration de button de professeur
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
{
    if (!professorsWindow) {
        professorsWindow = new ProfessorsWindow(this);
    }
    professorsWindow->show();
}

<<<<<<< HEAD
void SelectionWindow::onDemandsButtonClicked()
=======
void SelectionWindow::onDemandsButtonClicked() //configuration de button des demandes
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
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

<<<<<<< HEAD

=======
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
void SelectionWindow::onLicenceButtonClicked(){
    licence *licencew = new licence(this);
    licencew->show();
}

void SelectionWindow::onMasterButtonClicked(){
    Master *MasterWindow = new Master(this);
    MasterWindow->show();
}

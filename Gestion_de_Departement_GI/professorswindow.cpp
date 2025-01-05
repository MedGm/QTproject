#include "professorswindow.h"
#include "databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QSqlError>
#include <QStackedWidget>
#include <QComboBox>
#include <QDateEdit>

ProfessorsWindow::ProfessorsWindow(QWidget *parent) //lwindow dyal page d professeurs
    : QMainWindow(parent)
{
    setWindowTitle("Gestion des Professeurs");
    setMinimumSize(800, 600);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    setupProfessorsTable();
    loadProfessors();
}

ProfessorsWindow::~ProfessorsWindow()
{
}

void ProfessorsWindow::setupProfessorsTable() //
{
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    // suprimation et ajoutes des profs
    QPushButton* addButton = new QPushButton("Ajouter", this);
    QPushButton* deleteButton = new QPushButton("Supprimer Sélection", this);
    
    // Style dyal buttons
    QString buttonStyle = 
        "QPushButton {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 15px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3498db;"
        "}";
    
    addButton->setStyleSheet(buttonStyle);
    deleteButton->setStyleSheet(buttonStyle);

    // creer button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();

    // Add button for showing reservations
    QPushButton* showReservationsButton = new QPushButton("Réservations", this);
    showReservationsButton->setStyleSheet(buttonStyle);
    buttonLayout->addWidget(showReservationsButton);

    // creation d table
    professorsTable = new QTableWidget(this);
    professorsTable->setColumnCount(4);
    professorsTable->setHorizontalHeaderLabels({"Sélection", "Nom", "CIN", "Spécialité"});
    
    // tol dyal les columns
    professorsTable->setColumnWidth(0, 70);
    professorsTable->setColumnWidth(1, 250);
    professorsTable->setColumnWidth(2, 150);
    professorsTable->setColumnWidth(3, 200);
    
    // Style d tables
    professorsTable->setStyleSheet(
        "QTableWidget {"
        "    background-color: white;"
        "    alternate-background-color: #f5f5f5;"
        "    selection-background-color: #2980b9;"
        "    selection-color: white;"
        "    border: none;"
        "    border-radius: 15px;"
        "    padding: 10px;"
        "}"
    );

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(professorsTable);

    // connecter les buttons mea les fonctions
    connect(addButton, &QPushButton::clicked, this, &ProfessorsWindow::onAddProfessorClicked);
    connect(deleteButton, &QPushButton::clicked, this, &ProfessorsWindow::onDeleteProfessorClicked);
    connect(showReservationsButton, &QPushButton::clicked, this, &ProfessorsWindow::onShowReservationsClicked);

    // Initialize stacked widget and pages
    mainStack = new QStackedWidget(this);
    professorsPage = new QWidget();
    professorsPage->setLayout(mainLayout);
    
    setupReservationsTable();
    
    mainStack->addWidget(professorsPage);
    mainStack->addWidget(reservationsPage);
    setCentralWidget(mainStack);

    //window style
    setStyleSheet(
        "QMainWindow {"
        "    background-color: #f5f5f5;"
        "}"
        "QWidget {"
        "    font-family: 'Segoe UI', Arial;"
        "}"
        "QPushButton {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 8px 15px;"
        "    font-weight: bold;"
        "    min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3498db;"
        "}"
        "QTableWidget {"
        "    border: 1px solid #ddd;"
        "    border-radius: 4px;"
        "    background-color: white;"
        "}"
        "QHeaderView::section {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    padding: 8px;"
        "    border: none;"
        "    font-weight: bold;"
        "}"
    );
}

void ProfessorsWindow::setupReservationsTable()
{
    reservationsPage = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(reservationsPage);
    
    // Create buttons
    QPushButton* addButton = new QPushButton("Ajouter Réservation", this);
    QPushButton* deleteButton = new QPushButton("Supprimer Sélection", this);
    QPushButton* backButton = new QPushButton("Retour", this);
    
    QString buttonStyle = "QPushButton {"
                         "    background-color: #2980b9;"
                         "    color: white;"
                         "    border: none;"
                         "    border-radius: 5px;"
                         "    padding: 8px 15px;"
                         "    font-weight: bold;"
                         "}"
                         "QPushButton:hover {"
                         "    background-color: #3498db;"
                         "}";
    
    addButton->setStyleSheet(buttonStyle);
    deleteButton->setStyleSheet(buttonStyle);
    backButton->setStyleSheet(buttonStyle);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch();

    // Create table
    reservationsTable = new QTableWidget(this);
    reservationsTable->setColumnCount(5);
    reservationsTable->setHorizontalHeaderLabels({"Sélection", "Professeur", "Salle", "Date", "Horaire"});
    
    // Set column widths
    reservationsTable->setColumnWidth(0, 70);
    reservationsTable->setColumnWidth(1, 200);
    reservationsTable->setColumnWidth(2, 100);
    reservationsTable->setColumnWidth(3, 150);
    reservationsTable->setColumnWidth(4, 150);

    layout->addLayout(buttonLayout);
    layout->addWidget(reservationsTable);

    // Connect signals
    connect(addButton, &QPushButton::clicked, this, &ProfessorsWindow::onAddReservationClicked);
    connect(deleteButton, &QPushButton::clicked, this, &ProfessorsWindow::onDeleteReservationClicked);
    connect(backButton, &QPushButton::clicked, [this]() {
        mainStack->setCurrentWidget(professorsPage);
    });
}

void ProfessorsWindow::loadProfessors()
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.exec("SELECT * FROM Professors");
    
    professorsTable->setRowCount(0);
    int row = 0;
    
    while (query.next()) {
        professorsTable->insertRow(row);

        QWidget* checkBoxWidget = new QWidget();
        QCheckBox* checkBox = new QCheckBox();
        QHBoxLayout* layout = new QHBoxLayout(checkBoxWidget);
        layout->addWidget(checkBox);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(layout);
        professorsTable->setCellWidget(row, 0, checkBoxWidget);

        //data dyal les profs
        professorsTable->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));
        professorsTable->setItem(row, 2, new QTableWidgetItem(query.value("cin").toString()));
        professorsTable->setItem(row, 3, new QTableWidgetItem(query.value("speciality").toString()));
        
        professorsTable->setRowHeight(row, 35);
        row++;
    }
}

void ProfessorsWindow::loadReservations()
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT * FROM Reservations");
    
    if (!query.exec()) {
        qDebug() << "Error loading reservations:" << query.lastError().text();
        return;
    }

    reservationsTable->setRowCount(0);
    int row = 0;
    
    while (query.next()) {
        reservationsTable->insertRow(row);

        // Add checkbox
        QWidget* checkBoxWidget = new QWidget();
        QCheckBox* checkBox = new QCheckBox();
        QHBoxLayout* layout = new QHBoxLayout(checkBoxWidget);
        layout->addWidget(checkBox);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(layout);
        reservationsTable->setCellWidget(row, 0, checkBoxWidget);

        // Add reservation data
        reservationsTable->setItem(row, 1, new QTableWidgetItem(query.value("professor_name").toString()));
        reservationsTable->setItem(row, 2, new QTableWidgetItem(query.value("room_number").toString()));
        reservationsTable->setItem(row, 3, new QTableWidgetItem(query.value("date").toString()));
        reservationsTable->setItem(row, 4, new QTableWidgetItem(query.value("time_slot").toString()));

        row++;
    }
}

void ProfessorsWindow::onAddProfessorClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter Professeur");

    QLineEdit* nameEdit = new QLineEdit(&dialog);
    QLineEdit* cinEdit = new QLineEdit(&dialog);
    QLineEdit* specialityEdit = new QLineEdit(&dialog);
    QPushButton* okButton = new QPushButton("OK", &dialog);
    QPushButton* cancelButton = new QPushButton("Annuler", &dialog);

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Nom:", nameEdit);
    formLayout->addRow("CIN:", cinEdit);
    formLayout->addRow("Spécialité:", specialityEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    formLayout->addRow(buttonLayout);

    dialog.setLayout(formLayout);

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        DatabaseManager::instance().addProfessor(
            nameEdit->text(),
            cinEdit->text(),
            specialityEdit->text()
        );
        loadProfessors();
    }
}

void ProfessorsWindow::onDeleteProfessorClicked()
{
    bool anyDeleted = false;

    for(int row = professorsTable->rowCount() - 1; row >= 0; row--) {
        QWidget* widget = professorsTable->cellWidget(row, 0);
        QCheckBox* checkBox = widget->findChild<QCheckBox*>();

        if(checkBox && checkBox->isChecked()) {
            QString cin = professorsTable->item(row, 2)->text();
            DatabaseManager::instance().removeProfessor(cin);
            anyDeleted = true;
        }
    }

    if(anyDeleted) {
        loadProfessors();
    }
}

void ProfessorsWindow::onShowReservationsClicked()
{
    loadReservations();
    mainStack->setCurrentWidget(reservationsPage);
}

void ProfessorsWindow::onAddReservationClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter Réservation");

    QComboBox* professorCombo = new QComboBox(&dialog);
    QLineEdit* roomEdit = new QLineEdit(&dialog);
    QDateEdit* dateEdit = new QDateEdit(&dialog);
    QComboBox* timeSlotCombo = new QComboBox(&dialog);
    
    // Load professors into combo box
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.exec("SELECT name FROM Professors");
    while (query.next()) {
        professorCombo->addItem(query.value(0).toString());
    }

    // Add time slots
    timeSlotCombo->addItems({"8:30-10:30", "10:45-12:45", "14:30-16:30", "16:45-18:45"});
    
    dateEdit->setCalendarPopup(true);
    dateEdit->setMinimumDate(QDate::currentDate());

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Professeur:", professorCombo);
    formLayout->addRow("Salle:", roomEdit);
    formLayout->addRow("Date:", dateEdit);
    formLayout->addRow("Horaire:", timeSlotCombo);

    QPushButton* okButton = new QPushButton("OK", &dialog);
    QPushButton* cancelButton = new QPushButton("Annuler", &dialog);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    formLayout->addRow(buttonLayout);

    dialog.setLayout(formLayout);

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        DatabaseManager::instance().addReservation(
            professorCombo->currentText(),
            roomEdit->text(),
            dateEdit->date().toString("dd/MM/yyyy"),
            timeSlotCombo->currentText()
        );
        loadReservations();
    }
}

void ProfessorsWindow::onDeleteReservationClicked()
{
    for (int row = reservationsTable->rowCount() - 1; row >= 0; row--) {
        QWidget* widget = reservationsTable->cellWidget(row, 0);
        QCheckBox* checkBox = widget->findChild<QCheckBox*>();
        
        if (checkBox && checkBox->isChecked()) {
            QString professorName = reservationsTable->item(row, 1)->text();
            QString roomNumber = reservationsTable->item(row, 2)->text();
            QString date = reservationsTable->item(row, 3)->text();
            QString timeSlot = reservationsTable->item(row, 4)->text();
            
            QSqlQuery query(DatabaseManager::instance().getDatabase());
            query.prepare("DELETE FROM Reservations WHERE professor_name = ? AND room_number = ? AND date = ? AND time_slot = ?");
            query.addBindValue(professorName);
            query.addBindValue(roomNumber);
            query.addBindValue(date);
            query.addBindValue(timeSlot);
            query.exec();
        }
    }
    loadReservations();
}

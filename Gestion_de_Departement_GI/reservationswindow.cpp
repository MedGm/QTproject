#include "reservationswindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QMessageBox>
#include <QCheckBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QApplication>

ReservationsWindow::ReservationsWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    loadReservations();
}

void ReservationsWindow::setupUI()
{
    setWindowTitle("Réservations des Salles");
    setMinimumSize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    reservationsTable = new QTableWidget(this);
    reservationsTable->setColumnCount(5);
    reservationsTable->setHorizontalHeaderLabels({
        "Sélection", "Professeur", "Salle", "Date", "Horaire"
    });

    reservationsTable->setStyleSheet(
        "QTableWidget {"
        "    background-color: white;"
        "    alternate-background-color: #f5f5f5;"
        "    selection-background-color: #2980b9;"
        "    selection-color: white;"
        "    border: 1px solid #ddd;"
        "    border-radius: 5px;"
        "}"
        "QHeaderView::section {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    padding: 8px;"
        "    border: none;"
        "    font-weight: bold;"
        "}"
    );

    QPushButton* addButton = new QPushButton("Ajouter Réservation", this);
    QPushButton* deleteButton = new QPushButton("Supprimer Sélection", this);

    QString buttonStyle = 
        "QPushButton {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 15px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "    min-width: 120px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3498db;"
        "}";

    addButton->setStyleSheet(buttonStyle);
    deleteButton->setStyleSheet(buttonStyle.replace("#2980b9", "#e74c3c").replace("#3498db", "#f15a4a"));

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(reservationsTable);

    connect(addButton, &QPushButton::clicked, this, &ReservationsWindow::onAddReservationClicked);
    connect(deleteButton, &QPushButton::clicked, this, &ReservationsWindow::onDeleteReservationClicked);
}

ReservationsWindow::~ReservationsWindow()
{
}

void ReservationsWindow::loadReservations()
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

        // Create checkbox
        QWidget* checkBoxWidget = new QWidget();
        QCheckBox* checkBox = new QCheckBox();
        QHBoxLayout* layout = new QHBoxLayout(checkBoxWidget);
        layout->addWidget(checkBox);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(layout);
        reservationsTable->setCellWidget(row, 0, checkBoxWidget);

        // Get values from query with validation
        QString professorName = query.value("professor_name").toString();
        QString roomNumber = query.value("room_number").toString();
        QString date = query.value("date").toString();
        QString timeSlot = query.value("time_slot").toString();

        // Create and set table items with alignment
        QTableWidgetItem* profItem = new QTableWidgetItem(professorName);
        QTableWidgetItem* roomItem = new QTableWidgetItem(roomNumber);
        QTableWidgetItem* dateItem = new QTableWidgetItem(date);
        QTableWidgetItem* timeItem = new QTableWidgetItem(timeSlot);

        profItem->setTextAlignment(Qt::AlignCenter);
        roomItem->setTextAlignment(Qt::AlignCenter);
        dateItem->setTextAlignment(Qt::AlignCenter);
        timeItem->setTextAlignment(Qt::AlignCenter);

        reservationsTable->setItem(row, 1, profItem);
        reservationsTable->setItem(row, 2, roomItem);
        reservationsTable->setItem(row, 3, dateItem);
        reservationsTable->setItem(row, 4, timeItem);

        reservationsTable->setRowHeight(row, 35);
        row++;
    }

    // Adjust column widths
    reservationsTable->setColumnWidth(0, 70);  // Checkbox
    reservationsTable->setColumnWidth(1, 200); // Professor name
    reservationsTable->setColumnWidth(2, 100); // Room number
    reservationsTable->setColumnWidth(3, 120); // Date
    reservationsTable->setColumnWidth(4, 120); // Time slot

    // Enable alternating row colors
    reservationsTable->setAlternatingRowColors(true);
}

void ReservationsWindow::onAddReservationClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter Réservation");
    dialog.setStyleSheet(
        "QDialog {"
        "    background-color: #f0f0f0;"
        "}"
        "QLineEdit, QComboBox, QDateEdit {"
        "    background-color: white;"
        "    border: 1px solid #bdc3c7;"
        "    border-radius: 4px;"
        "    padding: 5px;"
        "    min-width: 200px;"
        "}"
        "QLabel {"
        "    color: #2c3e50;"
        "    font-weight: bold;"
        "}"
        "QPushButton {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    border: none;"
        "    padding: 5px 15px;"
        "    border-radius: 4px;"
        "    min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3498db;"
        "}"
        "QPushButton#cancelButton {"
        "    background-color: #e74c3c;"
        "}"
        "QPushButton#cancelButton:hover {"
        "    background-color: #f15a4a;"
        "}"
    );

    QStringList professorNames;
    QSqlQuery query("SELECT name FROM Professors");
    while (query.next()) {
        professorNames << query.value(0).toString();
    }

    QComboBox* professorCombo = new QComboBox(&dialog);
    professorCombo->addItems(professorNames);
    
    QLineEdit* roomEdit = new QLineEdit(&dialog);
    QDateEdit* dateEdit = new QDateEdit(&dialog);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDate(QDate::currentDate());
    
    QComboBox* timeSlotCombo = new QComboBox(&dialog);
    timeSlotCombo->addItems({"08:30 - 10:30", "10:45 - 12:45", "14:30 - 16:30", "16:45 - 18:45"});

    QPushButton* okButton = new QPushButton("OK", &dialog);
    QPushButton* cancelButton = new QPushButton("Annuler", &dialog);

    okButton->setObjectName("okButton");
    cancelButton->setObjectName("cancelButton");

    QFormLayout* formLayout = new QFormLayout;
    formLayout->setSpacing(10);
    formLayout->setContentsMargins(20, 20, 20, 20);
    
    formLayout->addRow("Professeur:", professorCombo);
    formLayout->addRow("Salle:", roomEdit);
    formLayout->addRow("Date:", dateEdit);
    formLayout->addRow("Horaire:", timeSlotCombo);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    formLayout->addRow(buttonLayout);

    dialog.setLayout(formLayout);

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Style message boxes
    qApp->setStyleSheet(
        "QMessageBox {"
        "    background-color: #f0f0f0;"
        "}"
        "QMessageBox QLabel {"
        "    color: #2c3e50;"
        "    font-weight: bold;"
        "}"
        "QMessageBox QPushButton {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    border: none;"
        "    padding: 5px 15px;"
        "    border-radius: 4px;"
        "    min-width: 80px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "    background-color: #3498db;"
        "}"
    );

    formLayout->setSpacing(15);
    formLayout->setContentsMargins(30, 30, 30, 30);

    buttonLayout->setSpacing(15);
    buttonLayout->setContentsMargins(0, 15, 0, 0);

    dialog.setMinimumWidth(450);

    if (dialog.exec() == QDialog::Accepted) {
        QString professorName = professorCombo->currentText();
        QString roomNumber = roomEdit->text().trimmed();
        QString date = dateEdit->date().toString("yyyy-MM-dd");
        QString timeSlot = timeSlotCombo->currentText();

        if (roomNumber.isEmpty()) {
            QMessageBox::warning(this, "Error", "Veuillez remplir tous les champs.");
            return;
        }

        if (DatabaseManager::instance().addReservation(professorName, roomNumber, date, timeSlot)) {
            loadReservations();
            QMessageBox::information(this, "Succès", "Réservation ajoutée avec succès.");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de l'ajout de la réservation.");
        }
    }
}

void ReservationsWindow::onDeleteReservationClicked()
{
    bool anyDeleted = false;
    QVector<int> rowsToDelete;

    for(int row = reservationsTable->rowCount() - 1; row >= 0; row--) {
        QWidget* widget = reservationsTable->cellWidget(row, 0);
        QCheckBox* checkBox = widget->findChild<QCheckBox*>();

        if(checkBox && checkBox->isChecked()) {
            rowsToDelete.append(row);
            anyDeleted = true;
        }
    }

    if(anyDeleted) {
        QMessageBox msgBox(this);
        msgBox.setStyleSheet(
            "QMessageBox {"
            "    background-color: #f0f0f0;"
            "}"
            "QLabel {"
            "    color: #2c3e50;"
            "    font-weight: bold;"
            "    min-width: 300px;"
            "}"
            "QPushButton {"
            "    background-color: #2980b9;"
            "    color: white;"
            "    border: none;"
            "    padding: 5px 15px;"
            "    border-radius: 4px;"
            "    min-width: 80px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #3498db;"
            "}"
        );
        msgBox.setWindowTitle("Confirmation");
        msgBox.setText("Êtes-vous sûr de vouloir supprimer les réservations sélectionnées ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        if(msgBox.exec() == QMessageBox::Yes) {
    for(int row : rowsToDelete) {
        QString professorName = reservationsTable->item(row, 1)->text();
        QString roomNumber = reservationsTable->item(row, 2)->text();
        QString date = reservationsTable->item(row, 3)->text();
        QString timeSlot = reservationsTable->item(row, 4)->text();

        QSqlQuery query;
        query.prepare("DELETE FROM Reservations WHERE professor_name = ? AND room_number = ? AND date = ? AND time_slot = ?");
        query.addBindValue(professorName);
        query.addBindValue(roomNumber);
        query.addBindValue(date);
        query.addBindValue(timeSlot);
        
        if (!query.exec()) {
            qDebug() << "Error deleting reservation:" << query.lastError().text();
        }
    }
    loadReservations();
}
    }
}

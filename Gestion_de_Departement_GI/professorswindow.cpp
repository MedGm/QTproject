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

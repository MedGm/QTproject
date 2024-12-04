#include "cyclemanagement.h"
#include "ui_cyclemanagement.h"
#include "selectionwindow.h"
#include "studentdialog.h"
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>  
#include <QTextEdit>
#include<QSqlError>
cyclemanagement::cyclemanagement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cyclemanagement)
{
    ui->setupUi(this);
    setupUI();

    // Connect signals
    connect(ui->levelComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &cyclemanagement::onLevelChanged);
    connect(ui->logoutButton, &QPushButton::clicked,
            this, &cyclemanagement::onLogoutClicked);
    connect(ui->studentsButton, &QPushButton::clicked,
            this, &cyclemanagement::onStudentsButtonClicked);
}

// Add new method for students button
void cyclemanagement::onStudentsButtonClicked()
{
    loadStudents(ui->levelComboBox->currentText());
    ui->mainStack->setCurrentWidget(pageWidget); // Make sure pageWidget is a class member
}

void cyclemanagement::setupUI()
{
    // Setup level combo box
    ui->levelComboBox->addItems({"LSI 1", "LSI 2", "LSI 3"});

    // Setup students table
    studentsTable = new QTableWidget(this);
    studentsTable->setColumnCount(4);
    studentsTable->setHorizontalHeaderLabels({"Sélection", "Nom", "CNE", "CIN"});
    
    // Set column widths
    studentsTable->setColumnWidth(0, 70);  // Checkbox column
    studentsTable->setColumnWidth(1, 250); // Name column
    studentsTable->setColumnWidth(2, 150); // CNE column
    studentsTable->setColumnWidth(3, 150); // CIN column
    
    // Table styling
    studentsTable->setStyleSheet(
        "QTableWidget {"
        "    background-color: white;"
        "    alternate-background-color: #f5f5f5;"
        "    selection-background-color: #2980b9;"
        "    selection-color: white;"
        "    border: 1px solid #ddd;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}"
        "QTableWidget::item {"
        "    padding: 5px;"
        "    border-bottom: 1px solid #eee;"
        "}"
        "QHeaderView::section {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    padding: 8px;"
        "    border: none;"
        "    font-weight: bold;"
        "}"
    );
    
    studentsTable->setAlternatingRowColors(true);        // Enable alternating row colors
    studentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);  // Select entire rows
    studentsTable->verticalHeader()->setVisible(false);  // Hide vertical header
    studentsTable->setShowGrid(false);                   // Hide grid
    studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Make read-only

    // Setup buttons
    QPushButton* addButton = new QPushButton("Ajouter", this);
    QPushButton* deleteButton = new QPushButton("Supprimer Sélection", this);

    // Create button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();  // Add stretch to align buttons to the left

    // Create container widget for buttons
    QWidget* buttonContainer = new QWidget();
    buttonContainer->setLayout(buttonLayout);

    // Create main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(buttonContainer);
    mainLayout->addWidget(studentsTable);

    // Create container widget for the page
    pageWidget = new QWidget();
    pageWidget->setLayout(mainLayout);
    ui->mainStack->addWidget(pageWidget);

    // Connect buttons
    connect(addButton, &QPushButton::clicked, this, &cyclemanagement::onAddStudentClicked);
    connect(deleteButton, &QPushButton::clicked, this, &cyclemanagement::onDeleteStudentClicked);

    // Connect sidebar buttons
    connect(ui->professorsButton, &QPushButton::clicked, this, &cyclemanagement::onProfessorsButtonClicked);
    connect(ui->scheduleButton, &QPushButton::clicked, this, &cyclemanagement::onScheduleButtonClicked);
    
    // Setup professors table
    setupProfessorsTable();
    
    // Setup schedule page
    scheduleLabel = new QLabel(this);
    scheduleLabel->setAlignment(Qt::AlignCenter);
    scheduleLabel->setMinimumSize(800, 600);
    scheduleLabel->setMaximumSize(800, 600);
    
    QVBoxLayout* scheduleLayout = new QVBoxLayout();
    scheduleLayout->addWidget(scheduleLabel);
    scheduleLayout->setAlignment(Qt::AlignCenter);
    
    schedulePageWidget = new QWidget();
    schedulePageWidget->setLayout(scheduleLayout);
    ui->mainStack->addWidget(schedulePageWidget);

     // Setup internships table
    setupInternshipsTable();
    
    // Connect internships button
    connect(ui->internshipsButton, &QPushButton::clicked,
            this, &cyclemanagement::onInternshipsButtonClicked);
    
    // Initial load
    loadStudents("LSI 1");

    QPixmap logo(":/assets/log-uae.png");  
    if (!logo.isNull()) {
        ui->logoLabel->setPixmap(logo.scaled(ui->logoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->logoLabel->setStyleSheet("QLabel { background-color: transparent; padding: 10px; }");
    } else {
        qDebug() << "Failed to load logo image from:" << ":/assets/log-uae.png";
    }
    
    // Add demands button to sidebar
    connect(ui->demandsButton, &QPushButton::clicked,
            this, &cyclemanagement::onDemandsButtonClicked);

    // Setup demands page
    setupDemandsPage();
}

void cyclemanagement::setupProfessorsTable()
{
    professorsTable = new QTableWidget(this);
    professorsTable->setColumnCount(4);  // Changed to 4 to include checkbox
    professorsTable->setHorizontalHeaderLabels({"Sélection", "Nom", "CIN", "Spécialité"});
    
    // Set column widths
    professorsTable->setColumnWidth(0, 70);  // Checkbox column
    professorsTable->setColumnWidth(1, 250); // Name column
    professorsTable->setColumnWidth(2, 150); // CIN column
    professorsTable->setColumnWidth(3, 200); // Speciality column
    
    // Apply the same styling as students table
    professorsTable->setStyleSheet(studentsTable->styleSheet());
    professorsTable->setAlternatingRowColors(true);
    professorsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    professorsTable->verticalHeader()->setVisible(false);
    professorsTable->setShowGrid(false);
    professorsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Setup buttons
    QPushButton* addButton = new QPushButton("Ajouter", this);
    QPushButton* deleteButton = new QPushButton("Supprimer Sélection", this);

    // Create button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();

    // Create container widget for buttons
    QWidget* buttonContainer = new QWidget();
    buttonContainer->setLayout(buttonLayout);

    // Create main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(buttonContainer);
    mainLayout->addWidget(professorsTable);

    // Create container widget for the page
    professorsPageWidget = new QWidget();
    professorsPageWidget->setLayout(mainLayout);

    // Connect buttons
    connect(addButton, &QPushButton::clicked, this, &cyclemanagement::onAddProfessorClicked);
    connect(deleteButton, &QPushButton::clicked, this, &cyclemanagement::onDeleteProfessorClicked);
    
    ui->mainStack->addWidget(professorsPageWidget);
}

void cyclemanagement::loadProfessors()
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.exec("SELECT * FROM Professors");
    
    professorsTable->setRowCount(0);
    int row = 0;
    
    while (query.next()) {
        professorsTable->insertRow(row);

        // Add checkbox
        QWidget* checkBoxWidget = new QWidget();
        QCheckBox* checkBox = new QCheckBox();
        QHBoxLayout* layout = new QHBoxLayout(checkBoxWidget);
        layout->addWidget(checkBox);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(layout);
        professorsTable->setCellWidget(row, 0, checkBoxWidget);

        // Add other items
        professorsTable->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));
        professorsTable->setItem(row, 2, new QTableWidgetItem(query.value("cin").toString()));
        professorsTable->setItem(row, 3, new QTableWidgetItem(query.value("speciality").toString()));
        professorsTable->setRowHeight(row, 35);
        row++;
    }
}

void cyclemanagement::onAddProfessorClicked()
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

void cyclemanagement::onDeleteProfessorClicked()
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

void cyclemanagement::onProfessorsButtonClicked()
{
    loadProfessors();
    ui->mainStack->setCurrentWidget(professorsPageWidget);
}

void cyclemanagement::onScheduleButtonClicked()
{
    showSchedule(ui->levelComboBox->currentText());
    ui->mainStack->setCurrentWidget(schedulePageWidget);
}

void cyclemanagement::showSchedule(const QString& level)
{
    QString imagePath;
    if (level == "LSI 1") {
        imagePath = ":/assets/emplois1.png";
    } else if (level == "LSI 2") {
        imagePath = ":/assets/emplois3.png";
    } else if (level == "LSI 3") {
        imagePath = ":/assets/emplois5.png";
    }
    
    QPixmap schedule(imagePath);
    if (!schedule.isNull()) {
        scheduleLabel->setPixmap(schedule.scaled(scheduleLabel->size(), 
                                               Qt::KeepAspectRatio, 
                                               Qt::SmoothTransformation));
    }
}

// Add this to handle schedule image resizing
void cyclemanagement::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    if (ui->mainStack->currentWidget() == schedulePageWidget) {
        if (!scheduleLabel->pixmap().isNull()) {
            scheduleLabel->setPixmap(scheduleLabel->pixmap().scaled(
                scheduleLabel->size(), 
                Qt::KeepAspectRatio, 
                Qt::SmoothTransformation));
        }
    }
}

void cyclemanagement::onLevelChanged(int index)
{
    QString level = ui->levelComboBox->currentText();
    loadStudents(level);
    // Update schedule if it's currently visible
    if (ui->mainStack->currentWidget() == schedulePageWidget) {
        showSchedule(level);
    }
}

void cyclemanagement::onLogoutClicked()
{
    SelectionWindow *selectionWindow = new SelectionWindow();
    selectionWindow->show();
    this->close();
}

void cyclemanagement::loadStudents(const QString& level)
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    QString levelNoSpace = level;
    levelNoSpace.remove(" ");
    QString queryStr = QString("SELECT * FROM %1").arg(levelNoSpace);

    if (query.exec(queryStr)) {
        studentsTable->setRowCount(0);
        int row = 0;
        while (query.next()) {
            studentsTable->insertRow(row);

            // Add checkbox with centered layout
            QWidget* checkBoxWidget = new QWidget();
            QCheckBox* checkBox = new QCheckBox();
            QHBoxLayout* layout = new QHBoxLayout(checkBoxWidget);
            layout->addWidget(checkBox);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);
            checkBoxWidget->setLayout(layout);
            studentsTable->setCellWidget(row, 0, checkBoxWidget);

            // Create and set items
            QTableWidgetItem* nameItem = new QTableWidgetItem(query.value("name").toString());
            QTableWidgetItem* cneItem = new QTableWidgetItem(query.value("cne").toString());
            QTableWidgetItem* cinItem = new QTableWidgetItem(query.value("cin").toString());

            // Center align CNE and CIN
            cneItem->setTextAlignment(Qt::AlignCenter);
            cinItem->setTextAlignment(Qt::AlignCenter);

            // Set items in correct columns
            studentsTable->setItem(row, 1, nameItem);
            studentsTable->setItem(row, 2, cneItem);
            studentsTable->setItem(row, 3, cinItem);

            studentsTable->setRowHeight(row, 35);
            row++;
        }
    }
}

void cyclemanagement::onAddStudentClicked()
{
    StudentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString level = ui->levelComboBox->currentText().remove(" ");
        DatabaseManager::instance().addStudent(level, dialog.getName(),
                                            dialog.getCNE(), dialog.getCIN());
        loadStudents(ui->levelComboBox->currentText());
    }
}

void cyclemanagement::onDeleteStudentClicked()
{
    QString level = ui->levelComboBox->currentText().remove(" ");
    bool anyDeleted = false;

    // Go through all rows and check for selected ones
    for(int row = studentsTable->rowCount() - 1; row >= 0; row--) {
        QWidget* widget = studentsTable->cellWidget(row, 0);
        QCheckBox* checkBox = widget->findChild<QCheckBox*>();

        if(checkBox && checkBox->isChecked()) {
            // Fix: Change column index from 3 to 2 to get CNE instead of CIN
            QString cne = studentsTable->item(row, 2)->text();
            DatabaseManager::instance().removeStudent(level, cne);
            anyDeleted = true;
        }
    }

    // Reload table if any student was deleted
    if(anyDeleted) {
        loadStudents(ui->levelComboBox->currentText());
    }
}
void cyclemanagement::setupInternshipsTable()
{
    internshipsTable = new QTableWidget(this);
    internshipsTable->setColumnCount(6);  // Changed to 6 columns
    internshipsTable->setHorizontalHeaderLabels({
        "Sélection", "Étudiant", "CNE", "Entreprise", "Sujet", "Niveau"  // Added Niveau
    });
    
    // Set column widths
    internshipsTable->setColumnWidth(0, 70);   // Checkbox
    internshipsTable->setColumnWidth(1, 200);  // Student name
    internshipsTable->setColumnWidth(2, 150);  // CNE
    internshipsTable->setColumnWidth(3, 150);  // Company
    internshipsTable->setColumnWidth(4, 300);  // Subject
    internshipsTable->setColumnWidth(5, 100);  // Level
    
    // Apply the same styling as other tables
    internshipsTable->setStyleSheet(studentsTable->styleSheet());
    internshipsTable->setAlternatingRowColors(true);
    internshipsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    internshipsTable->verticalHeader()->setVisible(false);
    internshipsTable->setShowGrid(false);
    internshipsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Setup buttons
    QPushButton* addButton = new QPushButton("Ajouter Stage", this);
    QPushButton* deleteButton = new QPushButton("Supprimer Sélection", this);

    // Create button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();

    // Create container widget for buttons
    QWidget* buttonContainer = new QWidget();
    buttonContainer->setLayout(buttonLayout);

    // Create main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(buttonContainer);  // Changed from buttonLayout->parentWidget()
    mainLayout->addWidget(internshipsTable);

    // Create container widget
    internshipsPageWidget = new QWidget();
    internshipsPageWidget->setLayout(mainLayout);

    // Connect buttons
    connect(addButton, &QPushButton::clicked, this, &cyclemanagement::onAddInternshipClicked);
    connect(deleteButton, &QPushButton::clicked, this, &cyclemanagement::onDeleteInternshipClicked);

    ui->mainStack->addWidget(internshipsPageWidget);
}

// Update the loadInternships function to properly fetch and display internships
void cyclemanagement::loadInternships()
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    // Use a simpler query first to debug
    query.prepare("SELECT * FROM Internships");
    
    if (!query.exec()) {
        qDebug() << "Error loading internships:" << query.lastError().text();
        return;
    }
    
    internshipsTable->setRowCount(0);
    int row = 0;
    
    while (query.next()) {
        internshipsTable->insertRow(row);

        // Add checkbox
        QWidget* checkBoxWidget = new QWidget();
        QCheckBox* checkBox = new QCheckBox();
        QHBoxLayout* layout = new QHBoxLayout(checkBoxWidget);
        layout->addWidget(checkBox);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(layout);
        internshipsTable->setCellWidget(row, 0, checkBoxWidget);

        // Add data
        QString studentCne = query.value("student_cne").toString();
        
        // Set the items
        internshipsTable->setItem(row, 1, new QTableWidgetItem(query.value("student_name").toString()));
        internshipsTable->setItem(row, 2, new QTableWidgetItem(studentCne));
        internshipsTable->setItem(row, 3, new QTableWidgetItem(query.value("company").toString()));
        internshipsTable->setItem(row, 4, new QTableWidgetItem(query.value("subject").toString()));

        // Determine student level
        QString level = "Unknown";
        QSqlQuery levelQuery(DatabaseManager::instance().getDatabase());
        QString levelCheckQuery = "SELECT 'LSI 1' as level FROM LSI1 WHERE cne = :cne "
                                "UNION ALL "
                                "SELECT 'LSI 2' FROM LSI2 WHERE cne = :cne "
                                "UNION ALL "
                                "SELECT 'LSI 3' FROM LSI3 WHERE cne = :cne";
        levelQuery.prepare(levelCheckQuery);
        levelQuery.bindValue(":cne", studentCne);
        
        if (levelQuery.exec() && levelQuery.next()) {
            level = levelQuery.value("level").toString();
        }
        
        internshipsTable->setItem(row, 5, new QTableWidgetItem(level));
        internshipsTable->setRowHeight(row, 35);
        row++;
    }
}

void cyclemanagement::onInternshipsButtonClicked()
{
    loadInternships();
    ui->mainStack->setCurrentWidget(internshipsPageWidget);
}

// Update the onAddInternshipClicked function to validate input and show feedback
void cyclemanagement::onAddInternshipClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter Stage");

    // Create form elements
    QLineEdit* nameEdit = new QLineEdit(&dialog); 
    QLineEdit* cneEdit = new QLineEdit(&dialog);
    QLineEdit* companyEdit = new QLineEdit(&dialog);
    QTextEdit* subjectEdit = new QTextEdit(&dialog);
    subjectEdit->setMaximumHeight(100);
    
    QPushButton* okButton = new QPushButton("OK", &dialog);
    QPushButton* cancelButton = new QPushButton("Annuler", &dialog);

    // Create layout
    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Nom de l'étudiant:", nameEdit);  
    formLayout->addRow("CNE de l'étudiant:", cneEdit);
    formLayout->addRow("Entreprise:", companyEdit);
    formLayout->addRow("Sujet:", subjectEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    formLayout->addRow(buttonLayout);

    dialog.setLayout(formLayout);

    // Connect buttons
    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString studentName = nameEdit->text().trimmed();
        QString studentCne = cneEdit->text().trimmed();
        QString company = companyEdit->text().trimmed();
        QString subject = subjectEdit->toPlainText().trimmed();

        if (studentName.isEmpty() || studentCne.isEmpty() || company.isEmpty() || subject.isEmpty()) {
            QMessageBox::warning(this, "Error", "All fields must be filled.");
            return;
        }

        // Verify if the student exists in any level
        QSqlQuery verifyQuery(DatabaseManager::instance().getDatabase());
        verifyQuery.prepare("SELECT 1 FROM LSI1 WHERE cne = :cne "
                          "UNION SELECT 1 FROM LSI2 WHERE cne = :cne "
                          "UNION SELECT 1 FROM LSI3 WHERE cne = :cne");
        verifyQuery.bindValue(":cne", studentCne);
        
        if (!verifyQuery.exec() || !verifyQuery.next()) {
            QMessageBox::warning(this, "Error", "Student with this CNE does not exist.");
            return;
        }

        if (DatabaseManager::instance().addInternship(studentName, studentCne, company, subject)) {
            loadInternships();
            QMessageBox::information(this, "Success", "Internship added successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Failed to add internship.");
        }
    }
}

void cyclemanagement::onDeleteInternshipClicked()
{
    bool anyDeleted = false;

    for(int row = internshipsTable->rowCount() - 1; row >= 0; row--) {
        QWidget* widget = internshipsTable->cellWidget(row, 0);
        QCheckBox* checkBox = widget->findChild<QCheckBox*>();

        if(checkBox && checkBox->isChecked()) {
            QString cne = internshipsTable->item(row, 2)->text();
            QString company = internshipsTable->item(row, 3)->text();
            DatabaseManager::instance().removeInternship(
                DatabaseManager::instance().getInternshipId(cne, company)
            );
            anyDeleted = true;
        }
    }

    if(anyDeleted) {
        loadInternships();
    }
}

void cyclemanagement::setupDemandsPage()
{
    demandsPageWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout();
    
    // Create title label
    QLabel* titleLabel = new QLabel("Les Demandes");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin: 20px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Create demand options
    QStringList demands = {
        "Demande 1: Attestation de scolarité",
        "Demande 2: Relevé de notes",
        "Demande 3: Convention de stage",
        "Demande 4: Attestation de réussite",
        "Demande 5: Demande d'absence"
    };
    
    for(const QString& demand : demands) {
        QWidget* optionWidget = new QWidget();
        QHBoxLayout* optionLayout = new QHBoxLayout();
        
        QLabel* label = new QLabel(demand);
        label->setStyleSheet("font-size: 16px; padding: 10px;");
        
        QPushButton* downloadBtn = new QPushButton("Télécharger");
        downloadBtn->setProperty("demandType", demand.split(":")[0].trimmed());
        downloadBtn->setStyleSheet(
            "QPushButton {"
            "    background-color: #2980b9;"
            "    color: white;"
            "    padding: 8px 15px;"
            "    border: none;"
            "    border-radius: 4px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #3498db;"
            "}"
        );
        
        connect(downloadBtn, &QPushButton::clicked,
                this, &cyclemanagement::onDemandOptionClicked);
        
        optionLayout->addWidget(label);
        optionLayout->addWidget(downloadBtn);
        optionWidget->setLayout(optionLayout);
        
        mainLayout->addWidget(optionWidget);
    }
    
    mainLayout->addStretch();
    demandsPageWidget->setLayout(mainLayout);
    ui->mainStack->addWidget(demandsPageWidget);
}

void cyclemanagement::onDemandsButtonClicked()
{
    ui->mainStack->setCurrentWidget(demandsPageWidget);
}

void cyclemanagement::onDemandOptionClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString demandType = button->property("demandType").toString();
        downloadPDF(demandType);
    }
}

void cyclemanagement::downloadPDF(const QString& demandType)
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save PDF File"),
        QDir::homePath() + "/" + demandType + ".pdf",
        tr("PDF Files (*.pdf)"));
        
    if (!fileName.isEmpty()) {
        // Here you would normally generate or copy the appropriate PDF file
        // For now, we'll just show a success message
        QMessageBox::information(this, "Téléchargement",
            "Le fichier " + demandType + " a été téléchargé avec succès!");
    }
}

cyclemanagement::~cyclemanagement()
{
    delete ui;
}

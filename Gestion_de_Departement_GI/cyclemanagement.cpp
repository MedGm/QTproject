#include "cyclemanagement.h"
#include "ui_cyclemanagement.h"
#include "selectionwindow.h"
#include "studentdialog.h"
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>  // Add this line

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

    // Initial load
    loadStudents("LSI 1");
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

            // Create and style items
            QTableWidgetItem* idItem = new QTableWidgetItem(query.value("id").toString());
            QTableWidgetItem* nameItem = new QTableWidgetItem(query.value("name").toString());
            QTableWidgetItem* cneItem = new QTableWidgetItem(query.value("cne").toString());
            QTableWidgetItem* cinItem = new QTableWidgetItem(query.value("cin").toString());

            // Center align ID, CNE, and CIN
            idItem->setTextAlignment(Qt::AlignCenter);
            cneItem->setTextAlignment(Qt::AlignCenter);
            cinItem->setTextAlignment(Qt::AlignCenter);

            // Set items
            studentsTable->setItem(row, 1, idItem);
            studentsTable->setItem(row, 2, nameItem);
            studentsTable->setItem(row, 3, cneItem);
            studentsTable->setItem(row, 4, cinItem);

            row++;
        }
        
        // Adjust row heights
        for(int i = 0; i < studentsTable->rowCount(); i++) {
            studentsTable->setRowHeight(i, 35);
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
            QString cne = studentsTable->item(row, 3)->text();
            DatabaseManager::instance().removeStudent(level, cne);
            anyDeleted = true;
        }
    }

    // Reload table if any student was deleted
    if(anyDeleted) {
        loadStudents(ui->levelComboBox->currentText());
    }
}

cyclemanagement::~cyclemanagement()
{
    delete ui;
}

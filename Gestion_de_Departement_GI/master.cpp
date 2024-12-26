#include "master.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSet>
#include <QComboBox>






// Constructeur de Master
Master::Master(QWidget *parent) : QMainWindow(parent) {
    // Configuration de la fenêtre principale
    this->setWindowTitle("Gestion de la Filière Master");
    this->resize(1050, 678);

    // Création des widgets principaux
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Layout pour les boutons en haut
    QHBoxLayout *formLayout = new QHBoxLayout();

    // Création des widgets de la barre supérieure
    filiereComboBox = new QComboBox();
    filiereComboBox->addItems({"SBD1", "SBD2", "AISD1", "AISD2"});
    formLayout->addWidget(filiereComboBox);

    etudiantButton = new QPushButton("Étudiant");
    formLayout->addWidget(etudiantButton);

    moduleButton = new QPushButton("Module");
    formLayout->addWidget(moduleButton);

    profButton = new QPushButton("Professeur");
    formLayout->addWidget(profButton);

    emploitButton = new QPushButton("Emploi du temps");
    formLayout->addWidget(emploitButton);

    stageButton = new QPushButton("Stage PFE/PFA");
    formLayout->addWidget(stageButton);

    mainLayout->addLayout(formLayout);

    // Création des widgets pour la page des étudiants
    QHBoxLayout *studentButtonsLayout = new QHBoxLayout();
    addButton = new QPushButton("Ajouter");
    studentButtonsLayout->addWidget(addButton);

    delButton = new QPushButton("Supprimer");
    studentButtonsLayout->addWidget(delButton);

    mainLayout->addLayout(studentButtonsLayout);

    // Création du QStackedWidget
    stackedWidget = new QStackedWidget(this);
    studentPage = new QWidget(this);
    QVBoxLayout *studentLayout = new QVBoxLayout(studentPage);

    studentTable = new QTableWidget();
    studentTable->setMaximumSize(1100, 600);
    studentTable->setColumnCount(4);
    studentTable->setHorizontalHeaderLabels({"ID", "Prénom", "Nom", "Année"});
    studentLayout->addWidget(studentTable);

    studentPage->setLayout(studentLayout);
    stackedWidget->addWidget(studentPage);

    emploiPage = new QWidget(this);
    QVBoxLayout *emploiLayout = new QVBoxLayout(emploiPage);

    emploiLabel = new QLabel();
    emploiLabel->setMaximumSize(1100, 600);
    emploiLabel->setAlignment(Qt::AlignCenter);
    emploiLayout->addWidget(emploiLabel);

    emploiPage->setLayout(emploiLayout);
    stackedWidget->addWidget(emploiPage);

    mainLayout->addWidget(stackedWidget);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);

    // Connexions des boutons
    connect(etudiantButton, &QPushButton::clicked, this, &Master::showStudents);
    connect(emploitButton, &QPushButton::clicked, this, &Master::showSchedule);
    connect(profButton, &QPushButton::clicked, this, &Master::deleteStudent);
    connect(filiereComboBox, &QComboBox::currentTextChanged, this, &Master::onComboBoxChanged);

    // Connexion à la base de données
    if (!connectToDatabase()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée !");
        return;
    }

    // Charger les étudiants par défaut
    loadStudents(filiereComboBox->currentText());
}

// Destructeur
Master::~Master() {
    if (db.isOpen()) {
        db.close();
    }
}

// Reste de vos fonctions...

bool Master::connectToDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("master.db");

    if (!db.open()) {
        qDebug() << "Erreur : " << db.lastError().text();
        return false;
    }
    return true;
}

void Master::addStudent() {
    /*QSqlQuery query;
    query.prepare("INSERT INTO AISD2 (name, cne) VALUES (?, ?)");
    query.addBindValue("salah");  // Exemple de données
    query.addBindValue("12345678");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'étudiant !");
        qDebug() << "Erreur : " << query.lastError().text();
        return;
    }*/

    QMessageBox::information(this, "Succès", "Étudiant ajouté avec succès !");
    loadStudents(filiereComboBox->currentText());
}

void Master::updateStudent() {
    QMessageBox::information(this, "Mise à jour", "Mise à jour de l'étudiant (à implémenter).");
}


void Master::emploits(const QString &level) {
    QString imagePath;
    if (level == "SBD1") {
        imagePath = ":/assets/SBD1.png";
    } else if (level == "SBD2") {
        imagePath = ":/assets/SBD2.png";
    } else if (level == "AISD1") {
        imagePath = ":/assets/AISD1.png";
    } else if (level == "AISD2") {
        imagePath = ":/assets/AISD2.png";
    }

    QPixmap schedule(imagePath);
    if (!schedule.isNull()) {
        emploiLabel->setPixmap(schedule.scaled(emploiLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}


void Master::showSchedule() {
    QString level = filiereComboBox->currentText();
    emploits(level);  // Charger l'emploi du temps pour le niveau sélectionné
    stackedWidget->setCurrentWidget(emploiPage);  // Basculer sur la page emploi du temps
}


void Master::showStudents() {
    stackedWidget->setCurrentWidget(studentPage);  // Basculer sur la page des étudiants
}


void Master::deleteStudent() {
    QMessageBox::information(this, "Suppression", "Suppression de l'étudiant (à implémenter).");
}


void Master::onComboBoxChanged() {
    // Recharger les étudiants en fonction de la sélection dans la ComboBox
    loadStudents(filiereComboBox->currentText());
}


void Master::loadStudents(const QString &level) {
    // Vérifier si le niveau est valide
    QSet<QString> validLevels = {"SBD1", "SBD2", "AISD1", "AISD2"};
    if (!validLevels.contains(level)) {
        QMessageBox::critical(this, "Erreur", "Niveau invalide !");
        qDebug() << "Niveau invalide : " << level;
        return;
    }

    // Construire et exécuter la requête SQL
    /*QString queryStr = QString("SELECT id, name, cne, cin FROM %1").arg(level);
    QSqlQuery query(queryStr);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec du chargement des étudiants !");
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError().text();
        return;
    }

    // Vider le tableau avant d'ajouter de nouvelles données
    studentTable->setRowCount(0);

    // Remplir le tableau avec les données de la base
    int row = 0;
    while (query.next()) {
        studentTable->insertRow(row);
        studentTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        studentTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        studentTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        studentTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        row++;
    }*/

    qDebug() << "Étudiants chargés avec succès depuis la table : " << level;
}

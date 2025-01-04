#include "master.h"
#include <QMessageBox>
<<<<<<< HEAD
#include "database.h"
=======
#include <QSqlQuery>
#include <QSqlError>
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSet>
#include <QComboBox>
<<<<<<< HEAD
#include <QFile>
#include <QLineEdit>
#include <QFormLayout>
#include <QSpinBox>
#include <QHeaderView>
=======




>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241


// Constructeur de Master
Master::Master(QWidget *parent) : QMainWindow(parent) {
    // Configuration de la fenêtre principale
    this->setWindowTitle("Gestion de la Filière Master");
    this->resize(1050, 678);

<<<<<<< HEAD

    // Appliquer un style général à l'application
    this->setStyleSheet(R"(
        QMainWindow {
            background-color: #f5f5f5;
        }
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 10px;
            font-size: 14px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
        QPushButton:pressed {
            background-color: #3e8e41;
        }
        QTableWidget {
            background-color: white;
            border: 1px solid #ccc;
            color: #333;
            gridline-color: #ddd;
            font-size: 13px;
        }
        QTableWidget::item {
            padding: 5px;
        }
        QTableWidget::item:selected {
            background-color: #d1e7ff;
            color: black;
        }
        QComboBox {
            background-color: white;
            color: #333;
            border: 1px solid #ccc;
            padding: 5px;
            font-size: 14px;
        }
        QLabel {
            font-size: 16px;
            font-weight: bold;
            color: #333;
        }
    )");

    studentTable = new QTableWidget(this);


    //studentTable = new QTableWidget();
    studentTable->setColumnCount(4);
    studentTable->setHorizontalHeaderLabels({"ID", "Prénom", "Nom", "Date de Naissance"});
    studentTable->setColumnWidth(3,100);
    studentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    studentTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    stageTable = new QTableWidget(this);

    stageTable->setColumnCount(3);
    stageTable->setColumnWidth(0, 200);
    stageTable->setColumnWidth(1,200);
    stageTable->setColumnWidth(2,200);
    stageTable->setHorizontalHeaderLabels({"Nom", "Sujet de stage", "lieu de stage"});
    stageTable->setSelectionMode(QAbstractItemView::SingleSelection);
    stageTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    stageTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    stageTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);




    /*stackedWidget = new QStackedWidget(this);
    stagePage = new QWidget(this);
    QVBoxLayout *stageLayout = new QVBoxLayout(stagePage);
    stageLayout->addWidget(stageTable);
    stagePage->setLayout(stageLayout);
    stackedWidget->addWidget(stagePage);*/

    //stageTable->setVisible(false);
    //setupStudentTable();
    //stageTable = new QTableWidget(this);
    //setupStageTable();

=======
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
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

<<<<<<< HEAD
    stageButton = new QPushButton("Stage PFE/PFA");
    formLayout->addWidget(stageButton);

    addStage = new QPushButton("Ajouter Stage");
    formLayout->addWidget(addStage);
=======
    moduleButton = new QPushButton("Module");
    formLayout->addWidget(moduleButton);

    profButton = new QPushButton("Professeur");
    formLayout->addWidget(profButton);
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241

    emploitButton = new QPushButton("Emploi du temps");
    formLayout->addWidget(emploitButton);

<<<<<<< HEAD
    logout = new QPushButton("Déconnexion");
    formLayout->addWidget(logout);
=======
    stageButton = new QPushButton("Stage PFE/PFA");
    formLayout->addWidget(stageButton);
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241

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

<<<<<<< HEAD
    /*studentTable = new QTableWidget();
    studentTable->setMaximumSize(1100, 600);
    studentTable->setColumnCount(4);
    studentTable->setHorizontalHeaderLabels({"ID", "Prénom", "Nom", "Année"});*/
=======
    studentTable = new QTableWidget();
    studentTable->setMaximumSize(1100, 600);
    studentTable->setColumnCount(4);
    studentTable->setHorizontalHeaderLabels({"ID", "Prénom", "Nom", "Année"});
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    studentLayout->addWidget(studentTable);

    studentPage->setLayout(studentLayout);
    stackedWidget->addWidget(studentPage);

<<<<<<< HEAD

    stagePage = new QWidget(this);
    QVBoxLayout *stageLayout = new QVBoxLayout(stagePage);
    stageLayout->addWidget(stageTable);
    stagePage->setLayout(stageLayout);
    stackedWidget->addWidget(stagePage);


=======
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
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
<<<<<<< HEAD
    connect(addButton, &QPushButton::clicked, this, &Master::addStudent);
    connect(delButton, &QPushButton::clicked, this, &Master::delStudent);
    connect(emploitButton, &QPushButton::clicked, this, &Master::showSchedule);
    connect(logout, &QPushButton::clicked, this, &Master::deleteStudent);
    connect(filiereComboBox, &QComboBox::currentTextChanged, this, &Master::onComboBoxChanged);
    connect(stageButton, &QPushButton::clicked, this, &Master::showStage);
    connect(addStage, &QPushButton::clicked, this , &Master::AjouterStage);


=======
    connect(emploitButton, &QPushButton::clicked, this, &Master::showSchedule);
    connect(profButton, &QPushButton::clicked, this, &Master::deleteStudent);
    connect(filiereComboBox, &QComboBox::currentTextChanged, this, &Master::onComboBoxChanged);

    // Connexion à la base de données
    if (!connectToDatabase()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée !");
        return;
    }

    // Charger les étudiants par défaut
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    loadStudents(filiereComboBox->currentText());
}

// Destructeur
Master::~Master() {
<<<<<<< HEAD
    /*if (db.isOpen()) {
        db.close();
    }*/
}



void Master::showStage(){

    //stackedWidget->setCurrentWidget(studentPage);
    stackedWidget->setCurrentWidget(stagePage);

    stageTable->setVisible(true);
    studentTable->setVisible(false);

    QString level = filiereComboBox->currentText();
    loadStage(level);

}


bool Master::writeDataToFile(const QStringList& data) {


    QString level = filiereComboBox->currentText();
    QString filename = QString("/home/medgm/Desktop/Gestion_de_Departement_GI/%1.txt").arg(level);
    QFile file(filename);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Error opening file.";
        return false;
    }

    QTextStream out(&file);
    out << data.join(",") << "\n";
    file.close();

    return true;
}

bool Master::writeDataStage(const QStringList& data) {


    QString level = filiereComboBox->currentText();
    QString filename = QString("/home/medgm/Desktop/Gestion_de_Departement_GI/stage_%1.txt").arg(level);
    QFile file(filename);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Error opening file.";
        return false;
    }

    QTextStream out(&file);
    out << data.join(",") << "\n";
    file.close();

    return true;
}


bool Master::readDataStage(QList<QStringList>& studentsData) {
    QString level = filiereComboBox->currentText();
    QString filename = QString("/home/medgm/Desktop/Gestion_de_Departement_GI/stage_%1.txt").arg(level);
    if (filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/stage_SBD1.txt" && filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/stage_SBD2.txt" && filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/stage_AISD1.txt" && filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/stage_AISD2.txt") {
        qDebug() << "Error: Invalid file path!";
        return false;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file: " << file.errorString();
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << "Reading line: " << line;
        QStringList fields = line.split(",");
        if (fields.size() >= 3) {
            QString level = fields.at(3).trimmed();
            qDebug() << "Level from file: " << level;
            studentsData.append(fields);
            qDebug() << "Data added: " << fields.join(", ");

        }
    }
    file.close();
    return true;
}




bool Master::readDataFromFile(QList<QStringList>& studentsData) {
    QString level = filiereComboBox->currentText();
    QString filename = QString("/home/medgm/Desktop/Gestion_de_Departement_GI/%1.txt").arg(level);
    if (filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/SBD1.txt" && filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/SBD2.txt" && filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/AISD1.txt" && filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/AISD2.txt") {
        qDebug() << "Error: Invalid file path!";
        return false;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file: " << file.errorString();
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << "Reading line: " << line;
        QStringList fields = line.split(",");
        if (fields.size() >= 3) {
            QString level = fields.at(3).trimmed();
            qDebug() << "Level from file: " << level;
                studentsData.append(fields);
                qDebug() << "Data added: " << fields.join(", ");

        }
    }
    file.close();
    return true;
}

bool Master::removeLigneFromFile(const QStringList& data) {
    QString level = filiereComboBox->currentText();
    QString filename = QString("/home/medgm/Desktop/Gestion_de_Departement_GI/%1.txt").arg(level);
    QFile file(filename);

    // Vérifier si le fichier existe
    if (!file.exists()) {
        qDebug() << "File does not exist.";
        return false;
    }

    // Ouvrir le fichier en mode lecture
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for reading.";
        return false;
    }

    QStringList lines;
    QTextStream in(&file);

    // Convertir `data` en une chaîne pour comparaison
    QString dataToDelete = data.join(",");

    // Lire toutes les lignes
    while (!in.atEnd()) {
        QString line = in.readLine();
        // Ajouter uniquement les lignes qui ne correspondent pas à `dataToDelete`
        if (line.trimmed() != dataToDelete.trimmed()) {
            lines.append(line);
        }
    }
    file.close();

    // Ouvrir le fichier en mode écriture pour réécrire les données
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Error opening file for writing.";
        return false;
    }

    QTextStream out(&file);
    for (const QString& line : lines) {
        out << line << "\n";
    }

    file.close();
    return true;
}

void Master::delStudent(){
    // Création de la fenêtre de dialogue
    QDialog dialog(this);
    dialog.setWindowTitle("Supprimer un étudiant");
    dialog.setFixedSize(900, 600);

    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // Formulaire
    QFormLayout *formLayout = new QFormLayout();
    QLineEdit *idLineEdit = new QLineEdit();
    QLineEdit *firstNameLineEdit = new QLineEdit();
    QLineEdit *lastNameLineEdit = new QLineEdit();
    QLineEdit *yearLineEdit = new QLineEdit();

    formLayout->addRow("ID :", idLineEdit);
    formLayout->addRow("Prénom :", firstNameLineEdit);
    formLayout->addRow("Nom :", lastNameLineEdit);
    formLayout->addRow("Année :", yearLineEdit);

    layout->addLayout(formLayout);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("Supprimer");
    QPushButton *cancelButton = new QPushButton("Annuler");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    // Connexions
    connect(addButton, &QPushButton::clicked, [&]() {
        QString id = idLineEdit->text().trimmed();
        QString firstName = firstNameLineEdit->text().trimmed();
        QString lastName = lastNameLineEdit->text().trimmed();
        QString year = yearLineEdit->text().trimmed();

        if (id.isEmpty() || firstName.isEmpty() || lastName.isEmpty() || year.isEmpty()) {
            QMessageBox::warning(&dialog, "Erreur", "Tous les champs doivent être remplis !");
            return;
        }

        // Ajouter les données à la table
        /*int row = studentTable->rowCount();
        studentTable->insertRow(row);
        studentTable->setItem(row, 0, new QTableWidgetItem(id));
        studentTable->setItem(row, 1, new QTableWidgetItem(firstName));
        studentTable->setItem(row, 2, new QTableWidgetItem(lastName));
        studentTable->setItem(row, 3, new QTableWidgetItem(year));*/

        QStringList studentData;
        studentData << id << firstName << lastName << year ;

        bool success = Master::removeLigneFromFile(studentData);
        if (success) {
            qDebug() << "Supprimer un étudiant : ";
        } else {
            qDebug() << "Erreur lors de l'ajout de l'étudiant.";
        }

        QMessageBox::information(&dialog, "Succès", "Étudiant supprimer avec succès !");
        dialog.accept();
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Afficher la boîte de dialogue
    dialog.exec();
}


void Master::AjouterStage() {
    // Création de la fenêtre de dialogue
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter Votre Stage");
    dialog.setFixedSize(300, 200);

    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // Formulaire
    QFormLayout *formLayout = new QFormLayout();
    QLineEdit *Nom = new QLineEdit();
    QLineEdit *sujetDeStage = new QLineEdit();
    QLineEdit *lieuStage = new QLineEdit();
    //QLineEdit *yearLineEdit = new QLineEdit();

    formLayout->addRow("Nom et Prénom :", Nom);
    formLayout->addRow("Sujet de Stage :", sujetDeStage);
    formLayout->addRow("Lieur de Stage :", lieuStage);
    //formLayout->addRow("Année :", yearLineEdit);

    layout->addLayout(formLayout);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("Ajouter");
    QPushButton *cancelButton = new QPushButton("Annuler");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    QString level = filiereComboBox->currentText();

    // Connexions
    connect(addButton, &QPushButton::clicked, [&]() {
        QString nom = Nom->text().trimmed();
        QString sujet = sujetDeStage->text().trimmed();
        QString lieu = lieuStage->text().trimmed();
        //QString year = yearLineEdit->text().trimmed();

        if (nom.isEmpty() || sujet.isEmpty() || lieu.isEmpty()) {
            QMessageBox::warning(&dialog, "Erreur", "Tous les champs doivent être remplis !");
            return;
        }

        // Ajouter les données à la table
        int row = stageTable->rowCount();
        stageTable->insertRow(row);
        stageTable->setItem(row, 0, new QTableWidgetItem(nom));
        stageTable->setItem(row, 1, new QTableWidgetItem(sujet));
        stageTable->setItem(row, 2, new QTableWidgetItem(lieu));
        //stageTable->setItem(row, 3, new QTableWidgetItem(year));

        QStringList stageData;
        stageData << nom << sujet << lieu << level ;

        bool success = Master::writeDataStage(stageData);
        if (success) {
            qDebug() << "Nouveau étudiant ajouté : " << stageData.join(", ");
        } else {
            qDebug() << "Erreur lors de l'ajout de l'étudiant.";
        }

        QMessageBox::information(&dialog, "Succès", "Étudiant ajouté avec succès !");
        dialog.accept();
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Afficher la boîte de dialogue
    dialog.exec();
}


void Master::addStudent() {
    // Création de la fenêtre de dialogue
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter un étudiant");
    dialog.setFixedSize(300, 200);

    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // Formulaire
    QFormLayout *formLayout = new QFormLayout();
    QLineEdit *idLineEdit = new QLineEdit();
    QLineEdit *firstNameLineEdit = new QLineEdit();
    QLineEdit *lastNameLineEdit = new QLineEdit();
    QLineEdit *yearLineEdit = new QLineEdit();

    formLayout->addRow("ID :", idLineEdit);
    formLayout->addRow("Prénom :", firstNameLineEdit);
    formLayout->addRow("Nom :", lastNameLineEdit);
    formLayout->addRow("Année :", yearLineEdit);

    layout->addLayout(formLayout);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("Ajouter");
    QPushButton *cancelButton = new QPushButton("Annuler");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    // Connexions
    connect(addButton, &QPushButton::clicked, [&]() {
        QString id = idLineEdit->text().trimmed();
        QString firstName = firstNameLineEdit->text().trimmed();
        QString lastName = lastNameLineEdit->text().trimmed();
        QString year = yearLineEdit->text().trimmed();

        if (id.isEmpty() || firstName.isEmpty() || lastName.isEmpty() || year.isEmpty()) {
            QMessageBox::warning(&dialog, "Erreur", "Tous les champs doivent être remplis !");
            return;
        }

        // Ajouter les données à la table
        int row = studentTable->rowCount();
        studentTable->insertRow(row);
        studentTable->setItem(row, 0, new QTableWidgetItem(id));
        studentTable->setItem(row, 1, new QTableWidgetItem(firstName));
        studentTable->setItem(row, 2, new QTableWidgetItem(lastName));
        studentTable->setItem(row, 3, new QTableWidgetItem(year));

        QStringList studentData;
        studentData << "\n" << id << firstName << lastName << year ;

        bool success = Master::writeDataToFile(studentData);
        if (success) {
            qDebug() << "Nouveau étudiant ajouté : " << studentData.join(", ");
        } else {
            qDebug() << "Erreur lors de l'ajout de l'étudiant.";
        }

        QMessageBox::information(&dialog, "Succès", "Étudiant ajouté avec succès !");
        dialog.accept();
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Afficher la boîte de dialogue
    dialog.exec();
}


/*void Master::addStudent3(){

    QString level = filiereComboBox->currentText();
    //stackedWidget->setCurrentWidget(studentPage);
    studentTable->setVisible(false);
    //stageTable->setVisible(false);

    QWidget *formWidget = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formWidget);
    QLineEdit *Name = new QLineEdit(formWidget);
    Name->setPlaceholderText("Nom");
    QLineEdit *surnameEdit = new QLineEdit(formWidget);
    surnameEdit->setPlaceholderText("Prénom");
    QLineEdit *Cne = new QLineEdit(formWidget);
    Cne->setPlaceholderText("CNE");

    QString inputStyle = "QLineEdit {"
                         "background-color: #ADD8E6;"
                         "color: #333;"
                         "border: 1px solid #b0c4de;"
                         "border-radius: 5px;"
                         "padding: 8px;"
                         "font-size: 14px;"
                         "margin-bottom: 15px;"
                         "margin-left: 320px;"
                         "margin-right: 320px;"
                         "width: 250px;"
                         "} "
                         "QLineEdit:focus {"
                         "border-color: #6495ed;"
                         "}";

    Name->setStyleSheet(inputStyle);
    surnameEdit->setStyleSheet(inputStyle);
    Cne->setStyleSheet(inputStyle);

    QPushButton *saveButton = new QPushButton("Sauvegarder", formWidget);
    saveButton->setStyleSheet("QPushButton {"
                              "background-color: #6495ed;"
                              "color: white;"
                              "padding: 12px 25px;"
                              "border-radius: 5px;"
                              "font-size: 16px;"
                              "margin-left: 320px;"
                              "margin-right: 320px;"
                              "width: 250px;"
                              "} "
                              "QPushButton:hover {"
                              "background-color: #4169e1;"
                              "} "
                              "QPushButton:pressed {"
                              "background-color: #1e90ff;}");

    connect(saveButton, &QPushButton::clicked, [=]() {
        QString name = Name->text();
        QString surname = surnameEdit->text();
        QString cne = Cne->text();
        QStringList studentData;
        studentData << cne << name << level;

        bool success = Master::writeDataToFile(studentData);
        if (success) {
            qDebug() << "Nouveau étudiant ajouté : " << studentData.join(", ");
        } else {
            qDebug() << "Erreur lors de l'ajout de l'étudiant.";
        }

        // Réafficher le tableau des étudiants
        studentTable->setVisible(true);
        //stageTable->setVisible(true);

        // Afficher le ComboBox pour "Afficher les Etudiants"
        //levelComboBoxStudents->setVisible(true);

        // Mettre à jour l'interface et afficher le tableau des étudiants
        stackedWidget->setCurrentWidget(studentTable);

        // Recharger les données des étudiants après l'ajout
        loadStudents();
    });

    formLayout->addWidget(Name);
    formLayout->addWidget(surnameEdit);
    formLayout->addWidget(Cne);
    formWidget->setStyleSheet("background-color: #f0f8ff;border-radius: 10px;margin-left: 320px;margin-right: 320px;");

}*/




=======
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

>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
void Master::updateStudent() {
    QMessageBox::information(this, "Mise à jour", "Mise à jour de l'étudiant (à implémenter).");
}


<<<<<<< HEAD




















void Master::emploits(const QString &niveau) {
    QWidget *tableWidgetContainer = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(tableWidgetContainer);

    QTableWidget *timeTable = new QTableWidget(this);
    timeTable->setRowCount(6);
    timeTable->setColumnCount(5);

    timeTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QStringList plagesHoraires = {"09h00 - 10h30", "10h45 - 12h15", "12h30 - 14h00", "14h15 - 15h45", "16h00 - 17h30"};
    timeTable->setHorizontalHeaderLabels(plagesHoraires);

    QStringList jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
    timeTable->setVerticalHeaderLabels(jours);

    timeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    timeTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QList<QStringList> donneesEmploiDuTemps;
    Database db;

    QString nomFichier = "/home/medgm/Desktop/Gestion_de_Departement_GI/E22.txt";
    int indexJour = 0;
    int indexPlageHoraire = 0;
    if (db.readTimetableDataFromFile(nomFichier, donneesEmploiDuTemps, niveau)) {
        for (int i = 0; i < donneesEmploiDuTemps.size(); ++i) {
            QStringList champs = donneesEmploiDuTemps.at(i);

            QString jour = champs.at(1).trimmed();
            QString plageHoraire = champs.at(2).trimmed();
            QString cours = champs.at(3).trimmed();
            QString salle = champs.at(4).trimmed();

            if (indexJour >= 6) {
                indexJour = 0;
            }

            if (indexPlageHoraire >= 5) {
                indexPlageHoraire = 0;
                indexJour++;
            }

            if (!cours.isEmpty()) {
                timeTable->setItem(indexJour, indexPlageHoraire, new QTableWidgetItem(cours + " (" + salle + ")"));
            }

            indexPlageHoraire++;
        }
    } else {
        qDebug() << "Erreur : Impossible de charger les données de l'emploi du temps.";
    }

    timeTable->setStyleSheet("QTableWidget {"
                             "background-color: #f9f9f9;"
                             "border: 1px solid #ddd;"
                             "border-radius: 8px;"
                             "font-family: 'Arial', sans-serif;"
                             "font-size: 11pt;"
                             "width: 100%;"
                             "alternate-background-color: #f2f2f2;} "
                             "QTableWidget::item {"
                             "padding: 4px;"
                             "border: 1px solid #e2e2e2;"
                             "background-color: #ffffff;} "
                             "QTableWidget::item:selected {"
                             "background-color: #3498db;"
                             "color: white;} "
                             "QHeaderView::section {"
                             "background-color: #2980b9;"
                             "color: white;"
                             "padding: 12px;"
                             "font-weight: bold;"
                             "border: none;}");

    layout->addWidget(timeTable);
    tableWidgetContainer->setLayout(layout);

    stackedWidget->addWidget(tableWidgetContainer);
    stackedWidget->setCurrentWidget(tableWidgetContainer);

    qDebug() <<"moussssssssssa";

}



















void Master::showSchedule() {
    QString level = filiereComboBox->currentText();
    emploits(level);  // Charger l'emploi du temps pour le niveau sélectionné
    //stackedWidget->setCurrentWidget(emploiPage);  // Basculer sur la page emploi du temps
    //emploits(level);
=======
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
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
}


void Master::showStudents() {
    stackedWidget->setCurrentWidget(studentPage);  // Basculer sur la page des étudiants
<<<<<<< HEAD
    studentTable->setVisible(true);
    QString level = filiereComboBox->currentText();
    loadStudents(level);
    stackedWidget->setCurrentWidget(studentPage);
=======
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
}


void Master::deleteStudent() {
<<<<<<< HEAD

    this->close();
=======
    QMessageBox::information(this, "Suppression", "Suppression de l'étudiant (à implémenter).");
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
}


void Master::onComboBoxChanged() {
<<<<<<< HEAD
    QString level = filiereComboBox->currentText();
    QWidget *currentWidget = stackedWidget->currentWidget();

    if (currentWidget == studentPage) {
        loadStudents(level);
    } else if (currentWidget == stagePage) {
        loadStage(level);
    } else {
        emploits(level);
    }
}



void Master::loadStudents(const QString& level) {
    // Vérifier si le niveau est valide
    //QString level = filiereComboBox->currentText();
=======
    // Recharger les étudiants en fonction de la sélection dans la ComboBox
    loadStudents(filiereComboBox->currentText());
}


void Master::loadStudents(const QString &level) {
    // Vérifier si le niveau est valide
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    QSet<QString> validLevels = {"SBD1", "SBD2", "AISD1", "AISD2"};
    if (!validLevels.contains(level)) {
        QMessageBox::critical(this, "Erreur", "Niveau invalide !");
        qDebug() << "Niveau invalide : " << level;
        return;
    }

<<<<<<< HEAD
    // Vider la table avant d'ajouter de nouvelles données
    studentTable->setRowCount(0); // Supprime toutes les lignes

    QList<QStringList> studentsData;
    if (!Master::readDataFromFile(studentsData)) {
        qDebug() << "Le fichier est vide ou introuvable.";
        return;
    }
    if (studentsData.isEmpty()) {
        qDebug() << "Aucune donnée dans le fichier.";
        return;
    }
    int row = 0;
    for (const QStringList &fields : studentsData) {
        if (fields.size() >= 4) {
            studentTable->insertRow(row);
            studentTable->setItem(row, 0, new QTableWidgetItem(fields.at(0)));
            studentTable->setItem(row, 1, new QTableWidgetItem(fields.at(1)));
            studentTable->setItem(row, 2, new QTableWidgetItem(fields.at(2)));
            studentTable->setItem(row, 3, new QTableWidgetItem(fields.at(3)));

            row++;
        } else {
            qDebug() << "Les données à la ligne" << row << "sont incomplètes.";
        }
    }

    qDebug() << "Étudiants chargés avec succès depuis le fichier : " << level << ".txt";
}


void Master::loadStage(const QString& level) {
    // Vérifier si le niveau est valide
    //QString level = filiereComboBox->currentText();
    QSet<QString> validLevels = {"SBD1", "SBD2", "AISD1", "AISD2"};
    if (!validLevels.contains(level)) {
        QMessageBox::critical(this, "Erreur", "Niveau invalide !");
        qDebug() << "Niveau invalide : " << level;
        return;
    }

    // Vider la table avant d'ajouter de nouvelles données
    stageTable->setRowCount(0); // Supprime toutes les lignes

    QList<QStringList> stageData;
    if (!Master::readDataStage(stageData)) {
        qDebug() << "Le fichier est vide ou introuvable.";
        return;
    }
    if (stageData.isEmpty()) {
        qDebug() << "Aucune donnée dans le fichier.";
        return;
    }
    int row = 0;
    for (const QStringList &fields : stageData) {
        if (fields.size() >= 3) {
            stageTable->insertRow(row);
            stageTable->setItem(row, 0, new QTableWidgetItem(fields.at(0)));
            stageTable->setItem(row, 1, new QTableWidgetItem(fields.at(1)));
            stageTable->setItem(row, 2, new QTableWidgetItem(fields.at(2)));

            row++;
        } else {
            qDebug() << "Les données à la ligne" << row << "sont incomplètes.";
        }
    }

    qDebug() << "Étudiants chargés avec succès depuis le fichier : " << level << ".txt";
=======
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
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
}

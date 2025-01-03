#include "master.h"
#include <QMessageBox>


#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSet>
#include <QComboBox>
#include <QFile>
#include <QLineEdit>
#include <QFormLayout>
#include <QSpinBox>

// Constructeur de Master
Master::Master(QWidget *parent) : QMainWindow(parent) {
    // Configuration de la fenêtre principale
    this->setWindowTitle("Gestion de la Filière Master");
    this->resize(1050, 678);


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

    stageButton = new QPushButton("Stage PFE/PFA");
    formLayout->addWidget(stageButton);

    addStage = new QPushButton("Ajouter Stage");
    formLayout->addWidget(addStage);

    emploitButton = new QPushButton("Emploi du temps");
    formLayout->addWidget(emploitButton);

    logout = new QPushButton("Déconnexion");
    formLayout->addWidget(logout);

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

    /*studentTable = new QTableWidget();
    studentTable->setMaximumSize(1100, 600);
    studentTable->setColumnCount(4);
    studentTable->setHorizontalHeaderLabels({"ID", "Prénom", "Nom", "Année"});*/
    studentLayout->addWidget(studentTable);

    studentPage->setLayout(studentLayout);
    stackedWidget->addWidget(studentPage);


    stagePage = new QWidget(this);
    QVBoxLayout *stageLayout = new QVBoxLayout(stagePage);
    stageLayout->addWidget(stageTable);
    stagePage->setLayout(stageLayout);
    stackedWidget->addWidget(stagePage);


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
    connect(addButton, &QPushButton::clicked, this, &Master::addStudent);
    connect(delButton, &QPushButton::clicked, this, &Master::delStudent);
    connect(emploitButton, &QPushButton::clicked, this, &Master::showSchedule);
    connect(logout, &QPushButton::clicked, this, &Master::deleteStudent);
    connect(filiereComboBox, &QComboBox::currentTextChanged, this, &Master::onComboBoxChanged);
    connect(stageButton, &QPushButton::clicked, this, &Master::showStage);
    connect(addStage, &QPushButton::clicked, this , &Master::AjouterStage);


    loadStudents(filiereComboBox->currentText());
}

// Destructeur
Master::~Master() {
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
    QString filename = QString("C:/Users/Lenovo/Documents/new/%1.txt").arg(level);
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
    QString filename = QString("C:/Users/Lenovo/Documents/new/stage_%1.txt").arg(level);
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
    QString filename = QString("C:/Users/Lenovo/Documents/new/stage_%1.txt").arg(level);
    if (filename != "C:/Users/Lenovo/Documents/new/stage_SBD1.txt" && filename != "C:/Users/Lenovo/Documents/new/stage_SBD2.txt" && filename != "C:/Users/Lenovo/Documents/new/stage_AISD1.txt" && filename != "C:/Users/Lenovo/Documents/new/stage_AISD2.txt") {
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
    QString filename = QString("C:/Users/Lenovo/Documents/new/%1.txt").arg(level);
    if (filename != "C:/Users/Lenovo/Documents/new/SBD1.txt" && filename != "C:/Users/Lenovo/Documents/new/SBD2.txt" && filename != "C:/Users/Lenovo/Documents/new/AISD1.txt" && filename != "C:/Users/Lenovo/Documents/new/AISD2.txt") {
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
    QString filename = QString("C:/Users/Lenovo/Documents/new/%1.txt").arg(level);
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




void Master::updateStudent() {
    QMessageBox::information(this, "Mise à jour", "Mise à jour de l'étudiant (à implémenter).");
}


void Master::emploits(const QString &level) {
    QString imagePath;
    if (level == "SBD1") {
        imagePath = ":/assets/emplois1.png";
    } else if (level == "SBD2") {
        imagePath = ":/assets/emplois3.png";
    } else if (level == "AISD1") {
        imagePath = ":/assets/AISD1.png";
    } else if (level == "AISD2") {
        imagePath = ":/assets/etad.png";
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
    studentTable->setVisible(true);
    QString level = filiereComboBox->currentText();
    loadStudents(level);
    stackedWidget->setCurrentWidget(studentPage);
}


void Master::deleteStudent() {

    this->close();
}


void Master::onComboBoxChanged() {
    QString level = filiereComboBox->currentText();
    loadStudents(level);
}


void Master::loadStudents(const QString& level) {
    // Vérifier si le niveau est valide
    //QString level = filiereComboBox->currentText();
    QSet<QString> validLevels = {"SBD1", "SBD2", "AISD1", "AISD2"};
    if (!validLevels.contains(level)) {
        QMessageBox::critical(this, "Erreur", "Niveau invalide !");
        qDebug() << "Niveau invalide : " << level;
        return;
    }

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
}

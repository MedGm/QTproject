#include "mastermanagement.h"
#include <QMessageBox>


#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSet>
#include <QComboBox>
#include <QFile>
#include <QLineEdit>
#include <QSpinBox>

// Constructeur de Master
MasterManagement::MasterManagement(QWidget *parent) : QMainWindow(parent) {
    // Configuration de la fenêtre principale
    this->setWindowTitle("Gestion de la Filière MasterManagement");
    this->resize(1050, 678);

    studentTable = new QTableWidget(this);
    setupStudentTable();
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
    connect(etudiantButton, &QPushButton::clicked, this, &MasterManagement::addStudent3);
    connect(emploitButton, &QPushButton::clicked, this, &MasterManagement::showSchedule);
    connect(profButton, &QPushButton::clicked, this, &MasterManagement::deleteStudent);
    connect(filiereComboBox, &QComboBox::currentTextChanged, this, &MasterManagement::onComboBoxChanged);
    connect(stageButton, &QPushButton::clicked, this, &MasterManagement::showStudents);


    loadStudents();
}

// Destructeur
MasterManagement::~MasterManagement() {
    /*if (db.isOpen()) {
        db.close();
    }*/
}



void MasterManagement::setupStudentTable(){
    studentPage = new QWidget(this);
    auto *layout = new QVBoxLayout(studentPage);

    // Table to display students
    auto *table = new QTableWidget(studentPage);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"ID", "Name", "Age"});

    // Load data from a file (placeholder)
    table->insertRow(0);
    table->setItem(0, 0, new QTableWidgetItem("1"));
    table->setItem(0, 1, new QTableWidgetItem("John Doe"));
    table->setItem(0, 2, new QTableWidgetItem("20"));

    layout->addWidget(table);
    studentPage->setLayout(layout);
    stackedWidget->addWidget(studentPage);

}


bool MasterManagement::writeDataToFile(const QStringList& data) {


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


bool MasterManagement::readDataFromFile(QList<QStringList>& studentsData) {
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




void MasterManagement::addStudent() {
    QString level = filiereComboBox->currentText();

    //hideAllComboBoxes();
    studentTable->setVisible(false);
    //stageTable->setVisible(false);
    setWindowTitle("Ajouter un étudiant");
    setFixedSize(1200, 900);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Champ Nom et le prénom
    mainLayout->addWidget(new QLabel("Nom et Prenom :"));
    QLineEdit *FullNameInput = new QLineEdit(this);
    mainLayout->addWidget(FullNameInput);

    // Champ Prénom
    mainLayout->addWidget(new QLabel("CNE :"));
    QLineEdit *CneInput = new QLineEdit(this);
    mainLayout->addWidget(CneInput);


    // Champ Niveau d'études
    mainLayout->addWidget(new QLabel("CIN :"));
    QLineEdit *CinInput = new QLineEdit(this);
    mainLayout->addWidget(CinInput);



    // Bouton Ajouter
    QPushButton *addButton = new QPushButton("Ajouter", this);
    mainLayout->addWidget(addButton);



    connect(addButton, &QPushButton::clicked, [=]() {
        QString name = FullNameInput->text();

        QString cne = CneInput->text();
        QString cin = CinInput->text();



        QStringList studentData;
        studentData << name << cne << cin << level;

        bool success = MasterManagement::writeDataToFile(studentData);
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


    QMessageBox::information(this, "Succès", "Étudiant ajouté avec succès !");
    loadStudents();
}


void MasterManagement::addStudent2() {
    // Masquer les éléments actuels
    studentTable->setVisible(false);
    setWindowTitle("Ajouter un étudiant");
    setFixedSize(1200, 900);

    // Créer un widget pour contenir le formulaire
    QWidget *formWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(formWidget);

    // Champs du formulaire
    mainLayout->addWidget(new QLabel("Nom et Prenom :"));
    QLineEdit *fullNameInput = new QLineEdit(formWidget);
    mainLayout->addWidget(fullNameInput);

    mainLayout->addWidget(new QLabel("CNE :"));
    QLineEdit *cneInput = new QLineEdit(formWidget);
    mainLayout->addWidget(cneInput);

    mainLayout->addWidget(new QLabel("CIN :"));
    QLineEdit *cinInput = new QLineEdit(formWidget);
    mainLayout->addWidget(cinInput);

    // Bouton Ajouter
    QPushButton *addButton = new QPushButton("Ajouter", formWidget);
    mainLayout->addWidget(addButton);

    // Afficher le formulaire
    formWidget->setLayout(mainLayout);
    formWidget->show();

    // Connecter le bouton Ajouter
    connect(addButton, &QPushButton::clicked, [=]() {
        QString name = fullNameInput->text();
        QString cne = cneInput->text();
        QString cin = cinInput->text();

        if (name.isEmpty() || cne.isEmpty() || cin.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
            return;
        }

        QString level = filiereComboBox->currentText();
        QStringList studentData = {name, cne, cin, level};

        // Écriture des données dans un fichier
        bool success = MasterManagement::writeDataToFile(studentData);
        if (!success) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ajouter l'étudiant !");
            return;
        }

        // Réafficher les tableaux et mettre à jour
        studentTable->setVisible(true);
        stackedWidget->setCurrentWidget(studentTable);
        loadStudents();

        QMessageBox::information(this, "Succès", "Étudiant ajouté avec succès !");
        formWidget->close();  // Fermer le formulaire
    });
}


void MasterManagement::addStudent3(){

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

        bool success = MasterManagement::writeDataToFile(studentData);
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

}




void MasterManagement::updateStudent() {
    QMessageBox::information(this, "Mise à jour", "Mise à jour de l'étudiant (à implémenter).");
}


void MasterManagement::emploits(const QString &level) {
    QString imagePath;
    if (level == "SBD1") {
        imagePath = ":/assets/etad.png";
    } else if (level == "SBD2") {
        imagePath = ":/assets/etad.png";
    } else if (level == "AISD1") {
        imagePath = ":/assets/etad.png";
    } else if (level == "AISD2") {
        imagePath = ":/assets/etad.png";
    }

    QPixmap schedule(imagePath);
    if (!schedule.isNull()) {
        emploiLabel->setPixmap(schedule.scaled(emploiLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}


void MasterManagement::showSchedule() {
    QString level = filiereComboBox->currentText();
    emploits(level);  // Charger l'emploi du temps pour le niveau sélectionné
    stackedWidget->setCurrentWidget(emploiPage);  // Basculer sur la page emploi du temps
}


void MasterManagement::showStudents() {
    //stackedWidget->setCurrentWidget(studentPage);  // Basculer sur la page des étudiants

    QString level = filiereComboBox->currentText();
    loadStudents();
    stackedWidget->setCurrentWidget(studentPage);
}


void MasterManagement::deleteStudent() {

    this->close();
}


void MasterManagement::onComboBoxChanged() {
    // Recharger les étudiants en fonction de la sélection dans la ComboBox
    loadStudents();
}


void MasterManagement::loadStudents() {
    // Vérifier si le niveau est valide
    QString level = filiereComboBox->currentText();
    QSet<QString> validLevels = {"SBD1", "SBD2", "AISD1", "AISD2"};
    if (!validLevels.contains(level)) {
        QMessageBox::critical(this, "Erreur", "Niveau invalide !");
        qDebug() << "Niveau invalide : " << level;
        return;
    }

    QList<QStringList> studentsData;
    if (!MasterManagement::readDataFromFile(studentsData)) {
        qDebug() << "Le fichier est vide ou introuvable.";
        return;
    }
    if (studentsData.isEmpty()) {
        qDebug() << "Aucune donnée dans le fichier.";
        return;
    }
    int row = 0;
    for (const QStringList &fields : studentsData) {
        if (fields.size() >= 3) {
            studentTable->insertRow(row);
            studentTable->setItem(row, 0, new QTableWidgetItem(fields.at(0)));
            studentTable->setItem(row, 1, new QTableWidgetItem(fields.at(1)));
            studentTable->setItem(row, 2, new QTableWidgetItem(fields.at(2)));

            row++;
        } else {
            qDebug() << "Les données à la ligne" << row << "sont incomplètes.";
        }
    }

    qDebug() << "Étudiants chargés avec succès depuis la table : " << level;
}

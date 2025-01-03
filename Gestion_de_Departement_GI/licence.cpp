#include "licence.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QtSql>
#include <qheaderview.h>
#include <qlabel.h>
#include <qlineedit.h>
#include "database.h"

licence::licence(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 1600, 900);
    setWindowTitle("Gestion des Etudiants");
    this->setStyleSheet("QWidget {"
                        "background-color: rgba(0, 0, 255, 10);"
                        "border-radius: 10px;"

                        "}");
    setupNavbar();

    levelComboBoxStudents = new QComboBox(this);
    levelComboBoxStudents->addItem("Analyse des données", "AD");
    levelComboBoxStudents->addItem("Ingénierie du développement des applications informatiques", "IDAI");
    levelComboBoxStudents->setStyleSheet("QComboBox {background-color: #f39c12;color: white;padding: 8px 15px;border-radius: 5px;font-weight: bold;} QComboBox:hover {background-color: #e67e22;}QComboBox:pressed {background-color: #d35400;}");
    connect(levelComboBoxStudents, SIGNAL(currentIndexChanged(int)), this, SLOT(onLevelChangedForStudents(int)));

    levelComboBoxStages = new QComboBox(this);
    levelComboBoxStages->addItem("Analyse des données", "AD");
    levelComboBoxStages->addItem("Ingénierie du développement des applications informatiques", "IDAI");
    levelComboBoxStages->setStyleSheet("QComboBox {background-color: #f39c12;color: white;padding: 8px 15px;border-radius: 5px;font-weight: bold;} QComboBox:hover {background-color: #e67e22;}QComboBox:pressed {background-color: #d35400;}");
    connect(levelComboBoxStages, SIGNAL(currentIndexChanged(int)), this, SLOT(onLevelChangedForStages(int)));

    levelComboBoxTimetable = new QComboBox(this);
    levelComboBoxTimetable->addItem("Analyse des données", "AD");
    levelComboBoxTimetable->addItem("Ingénierie du développement des applications informatiques", "IDAI");
    levelComboBoxTimetable->setStyleSheet("QComboBox {background-color: #f39c12;color: white;padding: 8px 15px;border-radius: 5px;font-weight: bold;} QComboBox:hover {background-color: #e67e22;}QComboBox:pressed {background-color: #d35400;}");
    connect(levelComboBoxTimetable, SIGNAL(currentIndexChanged(int)), this, SLOT(onLevelChangedForTimetable(int)));

    studentsTable = new QTableWidget(this);
    setupStudentsTable();
    stageTable = new QTableWidget(this);
    setupStageTable();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(navbarLayout);
    mainLayout->addWidget(levelComboBoxStudents);
    mainLayout->addWidget(levelComboBoxStages);
    mainLayout->addWidget(levelComboBoxTimetable);
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(studentsTable);
    stackedWidget->addWidget(stageTable);
    mainLayout->addWidget(stackedWidget);
    QWidget *containerWidget = new QWidget();
    containerWidget->setLayout(mainLayout);
    setCentralWidget(containerWidget);

    levelComboBoxStages->setVisible(false);
    levelComboBoxTimetable->setVisible(false);
    levelComboBoxStudents->setVisible(true);

    loadStudents("AD");
}

void licence::setupNavbar() {
    studentsButton = new QPushButton("Afficher les Etudiants", this);
    connect(studentsButton, &QPushButton::clicked, this, &licence::onStudentsButtonClicked);
    addButton = new QPushButton("Ajouter un Etudiant", this);
    connect(addButton, &QPushButton::clicked, this, &licence::onAddStudentClicked);
    stage = new QPushButton("Afficher Stage", this);
    connect(stage, &QPushButton::clicked, this, &licence::onstageClicked);
    timetableButton = new QPushButton("Emploi du Temps", this);
    connect(timetableButton, &QPushButton::clicked, this, [this]() {
        QString selectedLevel = levelComboBoxStudents->currentData().toString();
        updateTimeTableImage(selectedLevel);
    });
    backButton = new QPushButton("Retour", this);
    connect(backButton, &QPushButton::clicked, this, &licence::onBackButtonClicked);
    navbarLayout = new QHBoxLayout();
    navbarLayout->addWidget(studentsButton);
    navbarLayout->addWidget(addButton);
    navbarLayout->addWidget(stage);
    navbarLayout->addWidget(timetableButton);
    QSpacerItem *spacer = new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    navbarLayout->addSpacerItem(spacer);
    navbarLayout->addWidget(backButton);
    navbarLayout->setSpacing(1);
    QString buttonStyle = "QPushButton {background-color: #f39c12;width: 180px;color: white;padding: 8px 15px;border-radius: 5px;font-weight: bold;font-size: 15px;margin-bottom: 25px;height: 20px;} QPushButton:hover {background-color: #e67e22;} QPushButton:pressed {background-color: #d35400;}";
    studentsButton->setStyleSheet(buttonStyle);
    addButton->setStyleSheet(buttonStyle);
    stage->setStyleSheet(buttonStyle);
    backButton->setStyleSheet(buttonStyle);
    timetableButton->setStyleSheet(buttonStyle);
}

void licence::hideAllComboBoxes() {
    levelComboBoxStudents->setVisible(false);
    levelComboBoxStages->setVisible(false);
    levelComboBoxTimetable->setVisible(false);
}

















//student
void licence::onLevelChangedForStudents(int index) {
    QString selectedLevel = levelComboBoxStudents->currentData().toString();
    qDebug() << "Selected Level for Students: " << selectedLevel;
    loadStudents(selectedLevel);
}

void licence::setupStudentsTable() {
    studentsTable->setColumnCount(7);
    studentsTable->setHorizontalHeaderLabels({"CNE", "Nom", "Prénom", "Spécialité", "Afficher", "Ajouter un Stage", "Supprimer"});
    studentsTable->setColumnWidth(0, 160);
    studentsTable->setColumnWidth(1, 240);
    studentsTable->setColumnWidth(2, 240);
    studentsTable->setColumnWidth(3, 240);
    studentsTable->setColumnWidth(4, 120);
    studentsTable->setColumnWidth(5, 120);
    studentsTable->setColumnWidth(6, 120);
    studentsTable->setStyleSheet("QTableWidget {background-color: #f9f9f9;border: 1px solid #ddd;border-radius: 8px;font-family: 'Arial', sans-serif;font-size: 11pt;width: 100%;alternate-background-color: #f2f2f2;} QTableWidget::item {padding: 4px;border: 1px solid #e2e2e2;background-color: #ffffff;} QTableWidget::item:selected {background-color: #3498db;color: white;} QHeaderView::section {background-color: #2980b9;color: white;padding: 12px;font-weight: bold;border: none;} QPushButton {background-color: #f39c12;color: white;padding: 2px 4px;border-radius: 5px;font-weight: bold;width: 120px;} QPushButton:hover {background-color: #a4a4a4de;} QPushButton:pressed {background-color: #d35400;}");
    studentsTable->setAlternatingRowColors(true);
    studentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    studentsTable->verticalHeader()->setVisible(false);
    studentsTable->setShowGrid(false);
}

void licence::loadStudents(const QString &level) {
    studentsTable->clearContents();
    studentsTable->setRowCount(0);
    QString fileName;
    if (level == "AD" || level == "Analyse des données") {
        fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/ad_data.txt";
    } else if (level == "IDAI" || level == "Ingénierie du développement des applications informatiques") {
        fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/idai_data.txt";
    }
    if (fileName.isEmpty()) {
        qDebug() << "File name is empty!";
        return;
    }
    QList<QStringList> studentsData;
    if (!Database::readDataFromFile(fileName, studentsData, level)) {
        qDebug() << "Le fichier est vide ou introuvable.";
        return;
    }
    if (studentsData.isEmpty()) {
        qDebug() << "Aucune donnée dans le fichier.";
        return;
    }
    int row = 0;
    for (const QStringList &fields : studentsData) {
        if (fields.size() >= 7) {
            studentsTable->insertRow(row);
            studentsTable->setItem(row, 0, new QTableWidgetItem(fields.at(0)));
            studentsTable->setItem(row, 1, new QTableWidgetItem(fields.at(1)));
            studentsTable->setItem(row, 2, new QTableWidgetItem(fields.at(2)));
            studentsTable->setItem(row, 3, new QTableWidgetItem(fields.at(3)));
            studentsTable->setItem(row, 4, new QTableWidgetItem());
            studentsTable->setItem(row, 5, new QTableWidgetItem());
            studentsTable->setItem(row, 6, new QTableWidgetItem());
            QPushButton *showButton = new QPushButton("Afficher", this);
            connect(showButton, &QPushButton::clicked, this, [this, row]() {
                onShowStudentInfoClicked(row);
            });
            QPushButton *addStageButton = new QPushButton("Ajouter un Stage", this);
            connect(addStageButton, &QPushButton::clicked, this, [this, row]() {
                onAddInternshipClicked(row);
            });
            QPushButton *deleteButton = new QPushButton("Supprimer", this);
            connect(deleteButton, &QPushButton::clicked, this, [this, row]() {
                onConfirmDeleteStudent(row);
            });
            studentsTable->setCellWidget(row, 4, showButton);
            studentsTable->setCellWidget(row, 5, addStageButton);
            studentsTable->setCellWidget(row, 6, deleteButton);
            row++;
        } else {
            qDebug() << "Les données à la ligne" << row << "sont incomplètes.";
        }
    }
    studentsTable->setVisible(true);
    stageTable->setVisible(false);
    stackedWidget->setCurrentWidget(studentsTable);
}

void licence::onStudentsButtonClicked() {
    hideAllComboBoxes();
    levelComboBoxStudents->setVisible(true);
    studentsTable->setVisible(true);
    stageTable->setVisible(false);
    foreach (QWidget *widget, stackedWidget->findChildren<QWidget*>()) {
        if (widget != studentsTable) {
            stackedWidget->removeWidget(widget);
        }
    }
    stackedWidget->setCurrentWidget(studentsTable);
}

void licence::onShowStudentInfoClicked(int row) {
    QString cne = studentsTable->item(row, 0)->text();
    QString name = studentsTable->item(row, 1)->text();
    QString surname = studentsTable->item(row, 2)->text();
    QString specialty = studentsTable->item(row, 3)->text();
    QString phone = studentsTable->item(row, 4)->text();
    QString email = studentsTable->item(row, 5)->text();
    QString dob = studentsTable->item(row, 6)->text();
    QString level = levelComboBoxStudents->currentText();
    QString fileName;
    if (level == "Analyse des données" || level == "AD") {
        fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/ad_data.txt";
    } else if (level == "Ingénierie du développement des applications informatiques" || level == "IDAI") {
        fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/idai_data.txt";
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Le fichier n'a pas pu être ouvert.");
        return;
    }
    QTextStream in(&file);
    QStringList studentDetails;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 7 && fields.at(0) == cne) {
            studentDetails = fields;
            break;
        }
    }
    file.close();
    if (studentDetails.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Étudiant non trouvé.");
        return;
    }
    QDialog *infoDialog = new QDialog(this);
    infoDialog->setWindowTitle("Informations de l'Étudiant");
    infoDialog->resize(800, 450);
    infoDialog->setStyleSheet("QDialog {background-color: #f2f2f2; border-radius: 12px; font-size: 16px; padding: 25px; border: 2px solid #3498db;}");
    QVBoxLayout *layout = new QVBoxLayout(infoDialog);
    QLabel *infoLabel = new QLabel(infoDialog);
    infoLabel->setText("<b>CNE:</b> " + studentDetails.at(0) + "<br><br>" +
                       "<b>Nom:</b> " + studentDetails.at(1) + "<br><br>" +
                       "<b>Prénom:</b> " + studentDetails.at(2) + "<br><br>" +
                       "<b>Spécialité:</b> " + studentDetails.at(3) + "<br><br>" +
                       "<b>Numéro de téléphone:</b> " + studentDetails.at(4) + "<br><br>" +
                       "<b>Email:</b> " + studentDetails.at(5) + "<br><br>" +
                       "<b>Date de naissance:</b> " + studentDetails.at(6));
    infoLabel->setWordWrap(true);
    infoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    infoLabel->setStyleSheet("font-size: 18px; color: #2c3e50;");
    layout->addWidget(infoLabel);
    QPushButton *closeButton = new QPushButton("Retour", infoDialog);
    closeButton->setStyleSheet("QPushButton {background-color: #f39c12; color: white; padding: 12px 30px; border-radius: 12px; font-weight: bold; font-size: 16px;} "
                               "QPushButton:hover {background-color: #e67e22;} QPushButton:pressed {background-color: #d35400;}");
    connect(closeButton, &QPushButton::clicked, infoDialog, &QDialog::accept);
    layout->addWidget(closeButton);
    infoDialog->setLayout(layout);
    infoDialog->exec();
}

void licence::onConfirmDeleteStudent(int row) {
    QString cne = studentsTable->item(row, 0)->text();
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Confirmer la suppression");
    msgBox.setText(QString("Êtes-vous sûr de vouloir supprimer l'étudiant avec CNE %1 ?").arg(cne));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.button(QMessageBox::Yes)->setText("Oui");
    msgBox.button(QMessageBox::No)->setText("Non");
    msgBox.setStyleSheet("QMessageBox {"
                         "background-color: #f0f8ff; border-radius: 10px; font-size: 14px; padding: 20px;} "
                         "QMessageBox QLabel {font-size: 16px; color: #2980b9; font-weight: bold;} "
                         "QMessageBox QPushButton {background-color: #f39c12; color: white; padding: 10px 20px; font-weight: bold; border-radius: 5px;} "
                         "QMessageBox QPushButton:hover {background-color: #e67e22;} "
                         "QMessageBox QPushButton:pressed {background-color: #d35400;}");
    int reply = msgBox.exec();
    if (reply == QMessageBox::Yes) {
        QString selectedLevel = levelComboBoxStudents->currentData().toString();
        QString fileName;
        if (selectedLevel == "AD") {
            fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/ad_data.txt";
        } else if (selectedLevel == "IDAI") {
            fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/idai_data.txt";
        }
        if (fileName.isEmpty()) {
            qDebug() << "File name is empty!";
            return;
        }
        QFile file(fileName);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "Error opening file: " << file.errorString();
            return;
        }
        QTextStream in(&file);
        QStringList lines;
        bool studentFound = false;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 7 && fields.at(0) == cne) {
                studentFound = true;
                continue;
            }
            lines.append(line);
        }
        if (studentFound) {
            file.resize(0);
            QTextStream out(&file);
            for (const QString &line : lines) {
                out << line << "\n";
            }
        } else {
            QMessageBox::warning(this, "Erreur", "L'étudiant n'a pas été trouvé.");
        }
        file.close();
        studentsTable->removeRow(row);
    }
}

void licence::colorSelectedRow(int row) {
    for (int i = 0; i < studentsTable->rowCount(); ++i) {
        if (i == row) {
            studentsTable->item(i, 0)->setBackground(Qt::lightGray);
        } else {
            studentsTable->item(i, 0)->setBackground(Qt::white);
        }
    }
}

void licence::onAddInternshipClicked(int row) {
    QString cne = studentsTable->item(row, 0)->text();
    QString name = studentsTable->item(row, 1)->text();
    QString surname = studentsTable->item(row, 2)->text();
    QString level = levelComboBoxStudents->currentText();
    QString email = studentsTable->item(row, 5)->text();
    QString phone = studentsTable->item(row, 4)->text();

    QDialog *addInternshipDialog = new QDialog(this);
    addInternshipDialog->setWindowTitle("Ajouter un Stage");
    addInternshipDialog->resize(400, 300);

    QString css = R"(
        QDialog {
            background-color: #f0f8ff;
            border-radius: 12px;
            padding: 20px;
            font-family: Arial, sans-serif;
        }

        QLabel {
            font-size: 14px;
            color: #2c3e50;
            font-weight: bold;
        }

        QLineEdit {
            background-color: #ADD8E6;
            color: #333;
            border: 1px solid #b0c4de;
            border-radius: 5px;
            padding: 8px;
            font-size: 14px;
            margin-bottom: 15px;
            width: 300px;
        }

        QLineEdit:focus {
            border-color: #6495ed;
        }

        QPushButton {
            background-color: #6495ed;
            color: white;
            padding: 12px 25px;
            border-radius: 5px;
            font-size: 16px;
            width: 300px;
            margin-top: 20px;
        }

        QPushButton:hover {
            background-color: #4169e1;
        }

        QPushButton:pressed {
            background-color: #1e90ff;
        }
    )";

    addInternshipDialog->setStyleSheet(css);

    QVBoxLayout *formLayout = new QVBoxLayout(addInternshipDialog);

    QLabel *subjectLabel = new QLabel("Sujet de Stage:", addInternshipDialog);
    QLineEdit *subjectInput = new QLineEdit(addInternshipDialog);
    subjectInput->setPlaceholderText("Entrez le sujet du stage");

    QLabel *companyLabel = new QLabel("Entreprise:", addInternshipDialog);
    QLineEdit *companyInput = new QLineEdit(addInternshipDialog);
    companyInput->setPlaceholderText("Entrez le nom de l'entreprise");

    formLayout->addWidget(subjectLabel);
    formLayout->addWidget(subjectInput);
    formLayout->addWidget(companyLabel);
    formLayout->addWidget(companyInput);

    QPushButton *submitButton = new QPushButton("Envoyer", addInternshipDialog);
    connect(submitButton, &QPushButton::clicked, this, [=]() {
        QString subject = subjectInput->text();
        QString company = companyInput->text();

        if (subject.isEmpty() || company.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
            return;
        }

        QString fileName;
        if (level == "AD" || level == "Analyse des données") {
            fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/tt/stage_ad.txt";
        } else if (level == "IDAI" || level == "Ingénierie du développement des applications informatiques") {
            fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/tt/stage_idai.txt";
        }

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                qDebug() << "Error opening file: " << file.errorString();
                return;
            }

            QTextStream out(&file);
            out << cne << "," << name << "," << surname << "," << level << "," << phone << "," << email << "," << studentsTable->item(row, 6)->text() << "," << subject << "," << company << "\n";
            file.close();

            QMessageBox::information(this, "Succès", "Stage ajouté avec succès.");
            addInternshipDialog->accept();
            loadStages(level);
        }
    });

    formLayout->addWidget(submitButton);
    addInternshipDialog->setLayout(formLayout);
    addInternshipDialog->exec();
}
















//ajoute etud
void licence::onAddStudentClicked() {
    hideAllComboBoxes();
    studentsTable->setVisible(false);
    stageTable->setVisible(false);

    QWidget *formWidget = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formWidget);
    nameEdit = new QLineEdit(formWidget);
    nameEdit->setPlaceholderText("Nom");
    surnameEdit = new QLineEdit(formWidget);
    surnameEdit->setPlaceholderText("Prénom");
    cneEdit = new QLineEdit(formWidget);
    cneEdit->setPlaceholderText("CNE");
    emailEdit = new QLineEdit(formWidget);
    emailEdit->setPlaceholderText("Email");
    phoneEdit = new QLineEdit(formWidget);
    phoneEdit->setPlaceholderText("Numéro de téléphone");
    dobEdit = new QLineEdit(formWidget);
    dobEdit->setPlaceholderText("Date de naissance");
    levelComboBox = new QComboBox(formWidget);
    levelComboBox->addItems({"Analyse des données", "Ingénierie du développement des applications informatiques"});
    specialtyEdit = new QLineEdit(formWidget);
    specialtyEdit->setPlaceholderText("Spécialité (ex: MIPC, GEGM)");

    // Apply style
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

    nameEdit->setStyleSheet(inputStyle);
    surnameEdit->setStyleSheet(inputStyle);
    cneEdit->setStyleSheet(inputStyle);
    emailEdit->setStyleSheet(inputStyle);
    phoneEdit->setStyleSheet(inputStyle);
    dobEdit->setStyleSheet(inputStyle);
    specialtyEdit->setStyleSheet(inputStyle);

    levelComboBox->setStyleSheet("QComboBox {"
                                 "background-color: #ADD8E6;"
                                 "color: #333;"
                                 "border: 1px solid #b0c4de;"
                                 "border-radius: 5px;"
                                 "padding: 8px;"
                                 "font-size: 14px;"
                                 "margin-left: 320px;"
                                 "margin-right: 320px;"
                                 "height: 30px;"
                                 "} "
                                 "QComboBox::drop-down {"
                                 "subcontrol-origin: padding;"
                                 "subcontrol-position: top right;"
                                 "width: 20px;"
                                 "border-left: 1px solid #b0c4de;"
                                 "} "
                                 "QComboBox::down-arrow {"
                                 "image: url(:/images/down-arrow.png);"
                                 "} "
                                 "QComboBox:hover {"
                                 "background-color: #87CEFA;"
                                 "} "
                                 "QComboBox:pressed {"
                                 "background-color: #4682B4;"
                                 "} "
                                 "QComboBox::item {"
                                 "padding: 5px;"
                                 "min-height: 25px;"
                                 "} "
                                 "QComboBox::item:selected {"
                                 "background-color: #6495ed;"
                                 "color: white;"
                                 "} ");

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
        QString name = nameEdit->text();
        QString surname = surnameEdit->text();
        QString cne = cneEdit->text();
        QString email = emailEdit->text();
        QString phone = phoneEdit->text();
        QString dob = dobEdit->text();
        QString level = levelComboBox->currentText();
        QString specialty = specialtyEdit->text();
        QStringList studentData;
        studentData << cne << name << surname << specialty << phone << email << dob << (level == "Analyse des données" ? "AD" : "IDAI");

        bool success = Database::writeDataToFile(level, studentData);
        if (success) {
            qDebug() << "Nouveau étudiant ajouté : " << studentData.join(", ");
        } else {
            qDebug() << "Erreur lors de l'ajout de l'étudiant.";
        }

        // Réafficher le tableau des étudiants
        studentsTable->setVisible(true);
        stageTable->setVisible(true);

        // Afficher le ComboBox pour "Afficher les Etudiants"
        levelComboBoxStudents->setVisible(true);

        // Mettre à jour l'interface et afficher le tableau des étudiants
        stackedWidget->setCurrentWidget(studentsTable);

        // Recharger les données des étudiants après l'ajout
        loadStudents("AD");
    });

    formLayout->addWidget(nameEdit);
    formLayout->addWidget(surnameEdit);
    formLayout->addWidget(cneEdit);
    formLayout->addWidget(emailEdit);
    formLayout->addWidget(phoneEdit);
    formLayout->addWidget(dobEdit);
    formLayout->addWidget(specialtyEdit);
    formLayout->addWidget(levelComboBox);
    formLayout->addWidget(saveButton);
    stackedWidget->addWidget(formWidget);
    stackedWidget->setCurrentWidget(formWidget);

    formWidget->setStyleSheet("background-color: #f0f8ff;border-radius: 10px;margin-left: 320px;margin-right: 320px;");
}



















//stage

void licence::setupStageTable() {
    stageTable->setColumnCount(7);
    stageTable->setHorizontalHeaderLabels({"CNE", "Nom", "Prénom", "Spécialité", "Sujet de Stage", "Afficher", "Supprimer"});
    stageTable->setColumnWidth(0, 165);
    stageTable->setColumnWidth(1, 190);
    stageTable->setColumnWidth(2, 190);
    stageTable->setColumnWidth(3, 240);
    stageTable->setColumnWidth(4, 220);
    stageTable->setColumnWidth(5, 120);
    stageTable->setColumnWidth(6, 120);
    stageTable->verticalHeader()->setVisible(false);
    stageTable->setStyleSheet("QTableWidget {background-color: #f9f9f9;border: 1px solid #ddd;border-radius: 8px;font-family: 'Arial', sans-serif;font-size: 11pt;width: 100%;alternate-background-color: #f2f2f2;} QTableWidget::item {padding: 4px;border: 1px solid #e2e2e2;background-color: #ffffff;} QTableWidget::item:selected {background-color: #3498db;color: white;} QHeaderView::section {background-color: #2980b9;color: white;padding: 12px;font-weight: bold;border: none;} QPushButton {background-color: #f39c12;color: white;padding: 2px 4px;border-radius: 5px;font-weight: bold;width: 120px;} QPushButton:hover {background-color: #a4a4a4de;} QPushButton:pressed {background-color: #d35400;}");
}

void licence::onLevelChangedForStages(int index) {
    QString selectedLevel = levelComboBoxStages->currentData().toString();
    levelComboBoxStudents->setVisible(false);
    levelComboBoxTimetable->setVisible(false);
    levelComboBoxStages->setVisible(true);
    studentsTable->setVisible(false);
    stageTable->setVisible(true);
    loadStages(selectedLevel);
}


void licence::loadStages(const QString &level) {
    stageTable->clearContents();
    stageTable->setRowCount(0);
    QString fileName;
    if (level == "IDAI" || level == "Ingénierie du développement des applications informatiques") {
        fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/tt/stage_idai.txt";
    } else if (level == "AD" || level == "Analyse des données") {
        fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/tt/stage_ad.txt";
    } else {
        return;
    }

    if (fileName.isEmpty()) {
        return;
    }

    QList<QStringList> stageData;
    if (!Database::readStageDataFromFile(fileName, stageData, level)) {
        return;
    }

    if (stageData.isEmpty()) {
        return;
    }

    int row = 0;
    for (const QStringList &fields : stageData) {
        if (fields.size() >= 10) {
            stageTable->insertRow(row);
            stageTable->setItem(row, 0, new QTableWidgetItem(fields.at(0)));
            stageTable->setItem(row, 1, new QTableWidgetItem(fields.at(1)));
            stageTable->setItem(row, 2, new QTableWidgetItem(fields.at(2)));
            stageTable->setItem(row, 3, new QTableWidgetItem(fields.at(3)));
            stageTable->setItem(row, 4, new QTableWidgetItem(fields.at(8)));

            QPushButton *showButton = new QPushButton("Afficher", this);
            connect(showButton, &QPushButton::clicked, this, [this, row]() {
                onShowStageInfoClicked(row);
            });

            QPushButton *deleteButton = new QPushButton("Supprimer", this);
            connect(deleteButton, &QPushButton::clicked, this, [this, row]() {
                onConfirmDeleteStage(row);
            });

            stageTable->setCellWidget(row, 5, showButton);
            stageTable->setCellWidget(row, 6, deleteButton);

            row++;
        }
    }

    stageTable->setVisible(true);
    studentsTable->setVisible(false);
    stackedWidget->setCurrentWidget(stageTable);
}



void licence::onstageClicked() {
    hideAllComboBoxes();
    levelComboBoxStages->setVisible(true);
    studentsTable->setVisible(false);
    stageTable->setVisible(true);
    foreach (QWidget *widget, stackedWidget->findChildren<QWidget*>()) {
        if (widget != stageTable) {
            stackedWidget->removeWidget(widget);
        }
    }
    stackedWidget->setCurrentWidget(stageTable);
}

void licence::onShowStageInfoClicked(int row) {
    QString cne = stageTable->item(row, 0)->text();
    QString name = stageTable->item(row, 1)->text();
    QString surname = stageTable->item(row, 2)->text();
    QString specialty = stageTable->item(row, 3)->text();
    QString stageSubject = stageTable->item(row, 4)->text();

    // Lire les données du stage selon le CNE
    QString level = levelComboBoxStages->currentText();
    QString fileName;
    if (level == "Analyse des données" || level == "AD") {
        fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/tt/stage_ad.txt";
    } else if (level == "Ingénierie du développement des applications informatiques" || level == "IDAI") {
        fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/tt/stage_idai.txt";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Le fichier n'a pas pu être ouvert.");
        return;
    }

    QTextStream in(&file);
    QStringList stageDetails;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 10 && fields.at(0) == cne) {
            stageDetails = fields;
            break;
        }
    }
    file.close();

    if (stageDetails.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucune information trouvée pour ce stage.");
        return;
    }

    // Afficher une fenêtre d'informations avec tous les détails
    QDialog *infoDialog = new QDialog(this);
    infoDialog->setWindowTitle("Informations du Stage");
    infoDialog->resize(800, 450);
    infoDialog->setStyleSheet("QDialog {background-color: #f2f2f2; border-radius: 12px; font-size: 16px; padding: 25px; border: 2px solid #3498db;}");

    QVBoxLayout *layout = new QVBoxLayout(infoDialog);
    QLabel *infoLabel = new QLabel(infoDialog);
    infoLabel->setText("<b>CNE:</b> " + stageDetails.at(0) + "<br><br>" +
                       "<b>Nom:</b> " + stageDetails.at(1) + "<br><br>" +
                       "<b>Prénom:</b> " + stageDetails.at(2) + "<br><br>" +
                       "<b>Spécialité:</b> " + stageDetails.at(3) + "<br><br>" +
                       "<b>Sujet de Stage:</b> " + stageDetails.at(8) + "<br><br>" +
                       "<b>Numéro de téléphone:</b> " + stageDetails.at(4) + "<br><br>" +
                       "<b>Email:</b> " + stageDetails.at(5) + "<br><br>" +
                       "<b>Date de naissance:</b> " + stageDetails.at(6) + "<br><br>" +
                       "<b>Adresse:</b> " + stageDetails.at(7) + "<br><br>");
    infoLabel->setWordWrap(true);
    infoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    infoLabel->setStyleSheet("font-size: 18px; color: #2c3e50;");
    layout->addWidget(infoLabel);

    QPushButton *closeButton = new QPushButton("Retour", infoDialog);
    closeButton->setStyleSheet("QPushButton {background-color: #f39c12; color: white; padding: 12px 30px; border-radius: 12px; font-weight: bold; font-size: 16px;} "
                               "QPushButton:hover {background-color: #e67e22;} QPushButton:pressed {background-color: #d35400;}");
    connect(closeButton, &QPushButton::clicked, infoDialog, &QDialog::accept);
    layout->addWidget(closeButton);

    infoDialog->setLayout(layout);
    infoDialog->exec();
}

void licence::onConfirmDeleteStage(int row) {
    QString cne = stageTable->item(row, 0)->text();
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Confirmer la suppression");
    msgBox.setText(QString("Êtes-vous sûr de vouloir supprimer l'étudiant avec CNE %1 du stage?").arg(cne));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.button(QMessageBox::Yes)->setText("Oui");
    msgBox.button(QMessageBox::No)->setText("Non");
    msgBox.setStyleSheet("QMessageBox {"
                         "background-color: #f0f8ff; border-radius: 10px; font-size: 14px; padding: 20px;} "
                         "QMessageBox QLabel {font-size: 16px; color: #2980b9; font-weight: bold;} "
                         "QMessageBox QPushButton {background-color: #f39c12; color: white; padding: 10px 20px; font-weight: bold; border-radius: 5px;} "
                         "QMessageBox QPushButton:hover {background-color: #e67e22;} "
                         "QMessageBox QPushButton:pressed {background-color: #d35400;}");
    int reply = msgBox.exec();
    if (reply == QMessageBox::Yes) {
        stageTable->removeRow(row);
        QString selectedLevel = levelComboBoxStages->currentData().toString();
        QString fileName;
        if (selectedLevel == "AD") {
            fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GI/tt/stage_ad.txt";
        } else if (selectedLevel == "IDAI") {
            fileName = "C:/Users/moonx/Documents/Gestion_de_Departement_GItt/stage_idai.txt";
        }
        if (fileName.isEmpty()) {
            qDebug() << "File name is empty!";
            return;
        }
        QFile file(fileName);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "Error opening file: " << file.errorString();
            return;
        }
        QTextStream in(&file);
        QStringList lines;
        bool stageFound = false;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 10 && fields.at(0) == cne) {
                stageFound = true;
                continue;
            }
            lines.append(line);
        }
        if (stageFound) {
            file.resize(0);
            QTextStream out(&file);
            for (const QString &line : lines) {
                out << line << "/n";
            }
            QMessageBox::information(this, "Supprimé", QString("Le stage de l'étudiant avec CNE %1 a été supprimé.").arg(cne));
        } else {
            QMessageBox::warning(this, "Erreur", "Le stage n'a pas été trouvé.");
        }
        file.close();
    }
}
void licence::onDeleteStageClicked(int row) {
    stageTable->removeRow(row);
    QMessageBox::information(this, "Supprimé", QString("Le stage a été supprimé à la ligne %1").arg(row + 1));
}























//imag
void licence::onLevelChangedForTimetable(int index) {
    QString selectedLevel = levelComboBoxTimetable->currentData().toString();
    qDebug() << "Selected Level for Timetable: " << selectedLevel;

    levelComboBoxStudents->setVisible(false);
    levelComboBoxStages->setVisible(false);

    studentsTable->setVisible(false);
    stageTable->setVisible(false);

    levelComboBoxTimetable->setVisible(true);

    updateTimeTableImage(selectedLevel);

    stackedWidget->setCurrentWidget(imageWidget);
}

void licence::updateTimeTableImage(const QString &level) {
    foreach (QWidget *widget, stackedWidget->findChildren<QWidget*>()) {
        if (widget != imageWidget) {
            stackedWidget->removeWidget(widget);
        }
    }

    levelComboBoxStudents->setVisible(false);
    levelComboBoxStages->setVisible(false);

    studentsTable->setVisible(false);
    stageTable->setVisible(false);
    levelComboBoxTimetable->setVisible(true);

    imageWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(imageWidget);
    QLabel *imageLabel = new QLabel(this);

    QString imagePath;
    if (level == "AD") {
        imagePath = ":/assets/etad.png";
    } else if (level == "IDAI") {
        imagePath = ":/assets/etidai.png";
    }

    QPixmap schedule(imagePath);
    if (!schedule.isNull()) {
        imageLabel->setPixmap(schedule.scaled(800, 550, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);
    imageWidget->setLayout(layout);

    stackedWidget->addWidget(imageWidget);
}

void licence::refreshPage() {
    foreach (QWidget *widget, stackedWidget->findChildren<QWidget*>()) {
        widget->setVisible(false);
    }

    imageWidget->setVisible(true);
}




















//ret
void licence::onBackButtonClicked() {
    this->close();
}








//des
licence::~licence()
{
    delete studentsTable;
    delete levelComboBoxStudents;
    delete levelComboBoxStages;
    delete levelComboBoxTimetable;
    delete studentsButton;
    delete addButton;
    delete stage;
    delete backButton;
    delete timetableButton;
}

#include "salle.h"
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QHBoxLayout>
#include <QPushButton>

Salle::Salle(QWidget *parent)
    : QWidget(parent)
{
    table = new QTableWidget(this);
    table->setRowCount(6);
    table->setColumnCount(5);
    QStringList horaires = {"09h00 - 10h30", "10h45 - 12h15", "12h30 - 14h00", "14h15 - 15h45", "16h00 - 17h30"};
    table->setHorizontalHeaderLabels(horaires);
    QStringList jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
    table->setVerticalHeaderLabels(jours);

    table->resize(600, 350);

    table->setStyleSheet(
        "QTableWidget {"
        "    background-color: #f9f9f9;"
        "    border: 1px solid #ddd;"
        "    font-family: Arial, sans-serif;"
        "    font-size: 10pt;"
        "    color: #333;"
        "    border-radius: 8px;"
        "}"
        );

    QPushButton *returnButton = new QPushButton("Retour", this);
    returnButton->setStyleSheet(
        "background-color: #f39c12;"
        "color: white;"
        "border: none;"
        "padding: 10px 20px;"
        "border-radius: 5px;"
        "font-size: 14px;"
        "font-weight: bold;"
        );
    connect(returnButton, &QPushButton::clicked, this, &Salle::onReturnClicked);

    QPushButton *ajouterButton = new QPushButton("Ajouter", this);
    ajouterButton->setStyleSheet(
        "background-color: #3498db;"
        "color: white;"
        "border: none;"
        "padding: 10px 20px;"
        "border-radius: 5px;"
        "font-size: 14px;"
        "font-weight: bold;"
        );
    connect(ajouterButton, &QPushButton::clicked, this, &Salle::onAjouterClicked);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(returnButton);
    buttonLayout->addWidget(ajouterButton);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(buttonLayout);
    layout->addWidget(table);
    setLayout(layout);

    loadDataFromFile("/home/medgm/Desktop/Gestion_de_Departement_GI/E22.txt");
}

Salle::~Salle()
{
    delete table;
}

void Salle::onReturnClicked()
{
    this->close();
}

void Salle::loadDataFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int indexJour = 0;
        int indexPlageHoraire = 0;

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(',');

            if (parts.size() >= 5) {
                QString day = parts[1];
                QString time = parts[2];
                QString course = parts[3];
                QString room = parts[4];
                QString availability = parts.size() > 5 ? parts[5] : "";

                int dayIndex = getDayIndex(day);
                int timeIndex = getTimeIndex(time);

                // Store room information in the 3D array based on day, time, and section
                for (int section = 0; section < 3; section++) {
                    if (availability.isEmpty()) {
                        //roomData[dayIndex][timeIndex][section] = room;
                    }
                }
            }
        }
        file.close();
    }
}

int Salle::getDayIndex(const QString &day)
{
    if (day == "LUNDI") return 0;
    if (day == "MARDI") return 1;
    if (day == "MERCREDI") return 2;
    if (day == "JEUDI") return 3;
    if (day == "VENDREDI") return 4;
    if (day == "SAMEDI") return 5;
    return -1;
}

int Salle::getTimeIndex(const QString &time)
{
    if (time == "09H00-10H30") return 0;
    if (time == "10H45-12H15") return 1;
    if (time == "12H30-14H00") return 2;
    if (time == "14H15-15H45") return 3;
    if (time == "16H00-17H30") return 4;

    return -1;
}


void Salle::onAjouterClicked()
{
    QWidget *addSessionWindow = new QWidget(this);
    addSessionWindow->setWindowTitle("Ajouter une Histoire");

    QComboBox *dayComboBox = new QComboBox(addSessionWindow);
    dayComboBox->addItem("Lundi");
    dayComboBox->addItem("Mardi");
    dayComboBox->addItem("Mercredi");
    dayComboBox->addItem("Jeudi");
    dayComboBox->addItem("Vendredi");
    dayComboBox->addItem("Samedi");

    QComboBox *timeComboBox = new QComboBox(addSessionWindow);
    timeComboBox->addItem("09h00 - 10h30");
    timeComboBox->addItem("10h45 - 12h15");
    timeComboBox->addItem("12h30 - 14h00");
    timeComboBox->addItem("14h15 - 15h45");
    timeComboBox->addItem("16h00 - 17h30");

    QLineEdit *courseLineEdit = new QLineEdit(addSessionWindow);
    courseLineEdit->setPlaceholderText("Nom de la matière");

    QLineEdit *roomLineEdit = new QLineEdit(addSessionWindow);
    roomLineEdit->setPlaceholderText("Salle");

    QPushButton *saveButton = new QPushButton("Enregistrer", addSessionWindow);
    QPushButton *cancelButton = new QPushButton("Annuler", addSessionWindow);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(dayComboBox);
    layout->addWidget(timeComboBox);
    layout->addWidget(courseLineEdit);
    layout->addWidget(roomLineEdit);
    layout->addWidget(saveButton);
    layout->addWidget(cancelButton);
    addSessionWindow->setLayout(layout);

    connect(saveButton, &QPushButton::clicked, [this, addSessionWindow, dayComboBox, timeComboBox, courseLineEdit, roomLineEdit]() {
        QString day = dayComboBox->currentText();
        QString time = timeComboBox->currentText();
        QString course = courseLineEdit->text();
        QString room = roomLineEdit->text();

        int dayIndex = getDayIndex(day);
        int timeIndex = getTimeIndex(time);

        if (dayIndex != -1 && timeIndex != -1 && !course.isEmpty() && !room.isEmpty()) {
            table->setItem(dayIndex, timeIndex, new QTableWidgetItem(room));
            qDebug() << "Session added: " << day << time << course << room;
        }

        addSessionWindow->close();
    });

    connect(cancelButton, &QPushButton::clicked, addSessionWindow, &QWidget::close);

    addSessionWindow->show();
}

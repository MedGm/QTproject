#include "ajouter.h"
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

Ajouter::Ajouter(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

Ajouter::~Ajouter()
{
}

void Ajouter::setupUI()
{
    specialityComboBox = new QComboBox(this);
    specialityComboBox->addItem("AD");
    specialityComboBox->addItem("IDAI");
    specialityComboBox->addItem("LSI1");

    materialComboBox = new QComboBox(this);
    materialComboBox->setEnabled(false);  // Disabled until speciality is selected

    addButton = new QPushButton("Add", this);
    removeButton = new QPushButton("Remove", this);

    scheduleTable = new QTableWidget(this);
    scheduleTable->setRowCount(5);
    scheduleTable->setColumnCount(2);
    scheduleTable->setHorizontalHeaderLabels({"Time", "Room"});
    scheduleTable->setVerticalHeaderLabels({"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"});

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout();

    topLayout->addWidget(specialityComboBox);
    topLayout->addWidget(materialComboBox);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(scheduleTable);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(removeButton);

    setLayout(mainLayout);

    connect(specialityComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSpecialityChanged(int)));
    connect(materialComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onMaterialChanged(int)));
    connect(addButton, &QPushButton::clicked, this, &Ajouter::onAddButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &Ajouter::onRemoveButtonClicked);
}

void Ajouter::onSpecialityChanged(int index)
{
    QString speciality = specialityComboBox->currentText();
    loadMaterialsForSpeciality(speciality);
}

void Ajouter::loadMaterialsForSpeciality(const QString &speciality)
{
    materialComboBox->clear();
    if (speciality == "AD") {
        materials = {"Mathématiques pour la science des données", "Développement WEB", "Algorithmique Avancée"};
    } else if (speciality == "IDAI") {
        materials = {"Systèmes et réseaux informatiques", "Programmation Orientée Objet", "Développement Web"};
    } else if (speciality == "LSI1") {
        materials = {"Technologies web 1", "Systèmes d'exploitation", "Langues étrangères 1"};
    }

    materialComboBox->addItems(materials);
    materialComboBox->setEnabled(true);
}

void Ajouter::onMaterialChanged(int index)
{
    QString material = materialComboBox->currentText();
    // Logic to populate the schedule based on the selected material
    // For now, just populate with dummy data
    for (int row = 0; row < 5; ++row) {
        scheduleTable->setItem(row, 0, new QTableWidgetItem("12h00-13h00"));
        scheduleTable->setItem(row, 1, new QTableWidgetItem("Room " + QString::number(row + 1)));
    }
}

void Ajouter::onAddButtonClicked()
{
    // Logic to add the schedule
}

void Ajouter::onRemoveButtonClicked()
{
    // Logic to remove the selected schedule
}

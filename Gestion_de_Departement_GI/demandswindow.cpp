#include "demandswindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QCoreApplication>

DemandsWindow::DemandsWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Gestion des Demandes");
    setMinimumSize(800, 600);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setupDemandsPage();
}

DemandsWindow::~DemandsWindow()
{
}

void DemandsWindow::setupDemandsPage()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QLabel* titleLabel = new QLabel("Les Demandes");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin: 20px; color: #2c3e50;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QWidget* demandsContainer = new QWidget();
    demandsContainer->setStyleSheet(
        "QWidget {"
        "    background-color: white;"
        "    border-radius: 10px;"
        "    padding: 20px;"
        "}"
        "QLabel {"
        "    color: #2c3e50;"
        "    font-size: 16px;"
        "}"
        "QPushButton {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 8px 15px;"
        "    font-weight: bold;"
        "    min-width: 120px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3498db;"
        "}"
        );

    QVBoxLayout* containerLayout = new QVBoxLayout(demandsContainer);

    QStringList demands = {
        "Demande 1: BON DE COMMANDE",
        "Demande 2: DEMANDE D’ENTRETIEN",
    };

    for(const QString& demand : demands) {
        QWidget* optionWidget = new QWidget();
        QHBoxLayout* optionLayout = new QHBoxLayout();

        QLabel* label = new QLabel(demand);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        QPushButton* downloadBtn = new QPushButton("Télécharger");
        downloadBtn->setProperty("demandType", demand.split(":")[0].trimmed());
        downloadBtn->setFixedWidth(120);

        connect(downloadBtn, &QPushButton::clicked, this, &DemandsWindow::onDemandOptionClicked);

        optionLayout->addWidget(label);
        optionLayout->addStretch();
        optionLayout->addWidget(downloadBtn);

        optionLayout->setContentsMargins(20, 10, 20, 10);

        optionWidget->setLayout(optionLayout);
        containerLayout->addWidget(optionWidget);
    }
    mainLayout->addWidget(demandsContainer);
    mainLayout->addStretch();

    setStyleSheet(
        "QMainWindow {"
        "    background-color: #f5f5f5;"
        "}"
        "QWidget {"
        "    font-family: 'Segoe UI', Arial;"
        "}"
        );
}

void DemandsWindow::onDemandOptionClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString demandType = button->property("demandType").toString();

        QString sourceFile;

        if (demandType == "Demande 2") {
            sourceFile = "/home/medgm/Desktop/Gestion_de_Departement_GI/DEMANDE_ENTRETIEN.pdf";
        } else if (demandType == "Demande 1") {
            sourceFile = "/home/medgm/Desktop/Gestion_de_Departement_GI/BON_COMMANDE.pdf";
        }

        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Enregistrer le fichier PDF"),
                                                        QDir::homePath() + "/" + demandType + ".pdf",
                                                        tr("Fichiers PDF (*.pdf)"));

        if (!fileName.isEmpty()) {
            if (QFile::exists(sourceFile)) {
                if (QFile::copy(sourceFile, fileName)) {
                    QMessageBox::information(this, "Succès",
                                             "Le fichier " + demandType + " a été téléchargé avec succès!");
                } else {
                    QMessageBox::warning(this, "Erreur",
                                         "Impossible de sauvegarder le fichier. Vérifiez vos permissions.");
                }
            } else {
                QMessageBox::information(this, "Simulation",
                                         "Le fichier " + demandType + " a été téléchargé avec succès!\n"
                                                                      "(Note: Ceci est une simulation, le fichier PDF réel devrait être ajouté "
                                                                      "dans le dossier resources/demands/)");
            }
        }
    }
}

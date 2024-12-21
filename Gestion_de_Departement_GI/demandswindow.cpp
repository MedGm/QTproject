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
    
    // les demandes li kaynin
    QStringList demands = {
        "Demande 1: Convention de stage",
        "Demande 2: Reservation des Stages",
        "Demande 3: ...."
    };
    
    for(const QString& demand : demands) {
        QWidget* optionWidget = new QWidget();
        QHBoxLayout* optionLayout = new QHBoxLayout();
        
        QLabel* label = new QLabel(demand);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        
        QPushButton* downloadBtn = new QPushButton("Télécharger");
        downloadBtn->setProperty("demandType", demand.split(":")[0].trimmed());
        downloadBtn->setFixedWidth(120);
        
        //connection dyal button mea fonction
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

    //window style
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
        
        // dir chemin dyal les fichiers dyalk li ghadi yt installaw
        QString sourcePath = QCoreApplication::applicationDirPath() + "/resources/demands/";
        QString sourceFile;
        
        if (demandType == "Demande 1") {
            sourceFile = sourcePath + "convention_stage.pdf";
        } else if (demandType == "Demande 2") {
            sourceFile = sourcePath + "reservation_stage.pdf";
        } else if (demandType == "Demande 3") {
            sourceFile = sourcePath + "autre_demande.pdf";
        }

        // blast save name dyal fichiers
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Enregistrer le fichier PDF"),
            QDir::homePath() + "/" + demandType + ".pdf",
            tr("Fichiers PDF (*.pdf)"));
            
        if (!fileName.isEmpty()) {
            if (QFile::exists(sourceFile)) { //ila kan fichier kayn
                if (QFile::copy(sourceFile, fileName)) { //ila fichier duplica eadi
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

void DemandsWindow::downloadPDF(const QString& demandType)
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

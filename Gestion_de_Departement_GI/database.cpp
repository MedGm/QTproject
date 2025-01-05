#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>

QFile Database::file;

bool Database::writeDataToFile(const QString& level, const QStringList& data) {
    QString fileName = (level == "AD" || level == "Analyse des données") ? "/home/medgm/Desktop/Gestion_de_Departement_GI/ad_data.txt" : "/home/medgm/Desktop/Gestion_de_Departement_GI/idai_data.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Error opening file.";
        return false;
    }

    QTextStream out(&file);
    out << data.join(",") << "\n";
    file.close();

    return true;
}

bool Database::readDataFromFile(const QString& filename, QList<QStringList>& studentsData, const QString& selectedLevel) {
    if (filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/idai_data.txt" && filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/ad_data.txt") {
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
        if (fields.size() >= 7) {
            QString level = fields.at(7).trimmed();
            qDebug() << "Level from file: " << level;
            if ((selectedLevel == "AD" && level == "AD") || (selectedLevel == "IDAI" && level == "IDAI")) {
                studentsData.append(fields);
                qDebug() << "Data added: " << fields.join(", ");
            }
        }
    }
    file.close();
    return true;


}


bool Database::readStageDataFromFile(const QString &filename, QList<QStringList> &stageData, const QString &selectedLevel) {
    if (filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/tt/stage_idai.txt" && filename != "/home/medgm/Desktop/Gestion_de_Departement_GI/tt/stage_ad.txt") {
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
        if (fields.size() >= 10) {
            QString level = fields.at(9).trimmed();
            qDebug() << "Level from file: " << level;
            if ((selectedLevel == "AD" && level == "AD") || (selectedLevel == "IDAI" && level == "IDAI")) {
                stageData.append(fields);
                qDebug() << "Stage Data added: " << fields.join(", ");
            }
        }
    }
    qDebug()<<"A9ay tha";
    file.close();
    return true;
}


bool Database::hasDataInFile(const QString& level) {
    QString fileName = (level == "AD" || level == "Analyse des données") ? "/home/medgm/Desktop/Gestion_de_Departement_GI/ad_data.txt" : "/home/medgm/Desktop/Gestion_de_Departement_GI/idai_data.txt";
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file to check data.";
        return false;
    }
    QTextStream in(&file);
    bool hasData = !in.readLine().isEmpty();
    file.close();
    return hasData;
}

void Database::disconnectFromDatabase() {
    qDebug() << "Disconnected from the database!";
}


bool Database::readTimetableDataFromFile(const QString& filename, QList<QStringList>& timetableData, const QString& selectedLevel) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file: " << file.errorString();
        return false;
    }

    QTextStream in(&file);
    QString currentLine;
    QStringList currentData;

    while (!in.atEnd()) {
        currentLine = in.readLine().trimmed();

        if (!currentLine.isEmpty()) {
            QStringList fields = currentLine.split(",");

            if (fields.size() >= 4 && fields.at(0).trimmed() == selectedLevel) {
                timetableData.append(fields);
            }
        }
    }
    file.close();
    return true;
}



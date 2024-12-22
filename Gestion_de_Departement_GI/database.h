#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

class Database {
public:
    static bool connectToDatabase();
    static bool readStageDataFromFile(const QString& filename, QList<QStringList>& stageData, const QString& selectedLevel);
    static bool writeDataToFile(const QString& filename, const QStringList& data);
    static bool hasDataInFile(const QString& filename);
    static void disconnectFromDatabase();
    static bool readDataFromFile(const QString& filename, QList<QStringList>& studentsData, const QString& selectedLevel);

private:
    static QFile file;
};

#endif // DATABASE_H

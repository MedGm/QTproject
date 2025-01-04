#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QString>
#include <QTextStream>
<<<<<<< HEAD
#include <QSqlDatabase>
#include <QDebug>
#include <QObject>

class Database {
public:

=======
#include <QDebug>

class Database {
public:
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    static bool connectToDatabase();
    static bool readStageDataFromFile(const QString& filename, QList<QStringList>& stageData, const QString& selectedLevel);
    static bool writeDataToFile(const QString& filename, const QStringList& data);
    static bool hasDataInFile(const QString& filename);
    static void disconnectFromDatabase();
<<<<<<< HEAD
    bool readTimetableDataFromFile(const QString& filename, QList<QStringList>& timetableData,const QString& selectedLevel);
=======
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    static bool readDataFromFile(const QString& filename, QList<QStringList>& studentsData, const QString& selectedLevel);

private:
    static QFile file;
<<<<<<< HEAD
    QSqlDatabase db;

=======
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
};

#endif // DATABASE_H

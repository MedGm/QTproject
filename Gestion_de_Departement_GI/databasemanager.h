#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QObject>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    static DatabaseManager& instance();
    bool initDatabase();
    bool addStudent(const QString& level, const QString& name, const QString& cne, const QString& cin);
    bool addProfessor(const QString& name, const QString& cin, const QString& speciality);
    bool addInternship(const QString& studentName, const QString& studentCne, 
                      const QString& company, const QString& subject);
    bool removeStudent(const QString& level, const QString& cne);
    bool removeProfessor(const QString& cin);
    bool removeInternship(int id);
    bool addReservation(const QString& professorName, const QString& roomNumber, 
                       const QString& date, const QString& timeSlot);
    bool removeReservation(int id);
    QSqlDatabase getDatabase() const;
    int getInternshipId(const QString& studentCne, const QString& company);

private:
    DatabaseManager();
    ~DatabaseManager();
    bool createTables();
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H

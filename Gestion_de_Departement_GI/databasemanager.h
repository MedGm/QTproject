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
    bool addInternship(const QString& studentCne, const QString& company, const QString& subject);
    bool removeStudent(const QString& level, const QString& cne);
    bool removeProfessor(const QString& cin);
    bool removeInternship(int id);
    QSqlDatabase getDatabase() const;

private:
    DatabaseManager();
    ~DatabaseManager();
    bool createTables();
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
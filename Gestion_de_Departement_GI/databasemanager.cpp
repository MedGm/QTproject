#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("department.db");
}

DatabaseManager::~DatabaseManager()
{
    if (db.isOpen())
        db.close();
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::initDatabase()
{
    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        return false;
    }
    return createTables();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    
    // Create LSI1 table
    if (!query.exec("CREATE TABLE IF NOT EXISTS LSI1 ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "cne TEXT UNIQUE NOT NULL,"
                   "cin TEXT UNIQUE NOT NULL)")) {
        qDebug() << "Error creating LSI1 table:" << query.lastError();
        return false;
    }

    // Create LSI2 table
    if (!query.exec("CREATE TABLE IF NOT EXISTS LSI2 ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "cne TEXT UNIQUE NOT NULL,"
                   "cin TEXT UNIQUE NOT NULL)")) {
        qDebug() << "Error creating LSI2 table:" << query.lastError();
        return false;
    }

    // Create LSI3 table
    if (!query.exec("CREATE TABLE IF NOT EXISTS LSI3 ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "cne TEXT UNIQUE NOT NULL,"
                   "cin TEXT UNIQUE NOT NULL)")) {
        qDebug() << "Error creating LSI3 table:" << query.lastError();
        return false;
    }

    // Create Professors table
    if (!query.exec("CREATE TABLE IF NOT EXISTS Professors ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "cin TEXT UNIQUE NOT NULL,"
                   "speciality TEXT NOT NULL)")) {
        qDebug() << "Error creating Professors table:" << query.lastError();
        return false;
    }

    // Create Internships table
    if (!query.exec("CREATE TABLE IF NOT EXISTS Internships ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "student_cne TEXT NOT NULL,"
                   "company TEXT NOT NULL,"
                   "subject TEXT NOT NULL)")) {
        qDebug() << "Error creating Internships table:" << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::addStudent(const QString& level, const QString& name, const QString& cne, const QString& cin)
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO %1 (name, cne, cin) VALUES (?, ?, ?)").arg(level));
    query.addBindValue(name);
    query.addBindValue(cne);
    query.addBindValue(cin);
    
    return query.exec();
}

bool DatabaseManager::removeStudent(const QString& level, const QString& cne)
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM %1 WHERE cne = ?").arg(level));
    query.addBindValue(cne);
    return query.exec();
}

bool DatabaseManager::removeProfessor(const QString& cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Professors WHERE cin = ?");
    query.addBindValue(cin);
    return query.exec();
}

bool DatabaseManager::removeInternship(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Internships WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}

bool DatabaseManager::addProfessor(const QString& name, const QString& cin, const QString& speciality)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Professors (name, cin, speciality) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(cin);
    query.addBindValue(speciality);
    
    return query.exec();
}

QSqlDatabase DatabaseManager::getDatabase() const
{
    return db;
}

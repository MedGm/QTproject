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
    if (!createTables()) {
        return false;
    }
    return initializeLSI1Data() && 
           initializeLSI2Data() && 
           initializeLSI3Data() && 
           initializeProfessorsData();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    
    // creer LSI1
    if (!query.exec("CREATE TABLE IF NOT EXISTS LSI1 ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "cne TEXT UNIQUE NOT NULL,"
                   "cin TEXT UNIQUE NOT NULL)")) {
        qDebug() << "Error creating LSI1 table:" << query.lastError();
        return false;
    }

    // creer LSI2
    if (!query.exec("CREATE TABLE IF NOT EXISTS LSI2 ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "cne TEXT UNIQUE NOT NULL,"
                   "cin TEXT UNIQUE NOT NULL)")) {
        qDebug() << "Error creating LSI2 table:" << query.lastError();
        return false;
    }

    // Creer LSI3
    if (!query.exec("CREATE TABLE IF NOT EXISTS LSI3 ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "cne TEXT UNIQUE NOT NULL,"
                   "cin TEXT UNIQUE NOT NULL)")) {
        qDebug() << "Error creating LSI3 table:" << query.lastError();
        return false;
    }

    // Creer table d Professeurs
    if (!query.exec("CREATE TABLE IF NOT EXISTS Professors ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "cin TEXT UNIQUE NOT NULL,"
                   "speciality TEXT NOT NULL)")) {
        qDebug() << "Error creating Professors table:" << query.lastError();
        return false;
    }

    // Creer table de Stages
    if (!query.exec("CREATE TABLE IF NOT EXISTS Internships ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "student_name TEXT NOT NULL,"
                   "student_cne TEXT NOT NULL,"
                   "company TEXT NOT NULL,"
                   "subject TEXT NOT NULL,"
                   "FOREIGN KEY (student_cne) REFERENCES LSI1(cne) ON DELETE CASCADE,"
                   "FOREIGN KEY (student_cne) REFERENCES LSI2(cne) ON DELETE CASCADE,"
                   "FOREIGN KEY (student_cne) REFERENCES LSI3(cne) ON DELETE CASCADE)")) {
        qDebug() << "Error creating Internships table:" << query.lastError();
        return false;
    }

    // Create Reservations table
    if (!query.exec("CREATE TABLE IF NOT EXISTS Reservations ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "professor_name TEXT NOT NULL,"
                   "room_number TEXT NOT NULL,"
                   "date TEXT NOT NULL,"
                   "time_slot TEXT NOT NULL,"
                   "FOREIGN KEY (professor_name) REFERENCES Professors(name))")) {
        qDebug() << "Error creating Reservations table:" << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::initializeLSI1Data()
{
    // First, anshufu wash la table LSI1 kayna fiha data
    QSqlQuery checkQuery("SELECT COUNT(*) FROM LSI1");
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        //fhalat ma kan deja kayna data bla mat3ayet
        return true;
    }

    QStringList students = {
        "ELGORRIM MOHAMED",
        "BAHADDOU DOUAA",
        "YOUSSAHOU OUEDRAOGO",
        "OUALLALI MOHAMED AMINE",
        "KCHIBAL ISMAIL",
        "ANDRIAMASY LORRAINE AGNES RAHELIARISOA",
        "RADAH HASSAN",
        "UTHMAN JUNAID",
        "AHMANE YAHYA",
        "FAIK MAROUANE",
        "SALHI MOHAMMED",
        "ALLALI FATIMA-EZZAHRA",
        "EL AZZOUZI ACHRAF",
        "LAFDIL NOHAYLA",
        "ESSALHI SALMA",
        "HOUZANE IKRAME",
        "KHAZRI SALAH EDDINE",
        "MOHAND OMAR MOUSSA",
        "BOUZID MINA",
        "CHIKH IMANE",
        "GANNOUNE OMAR",
        "LAGHRISSI MEHDI",
        "KADDAR MOHAMED ILIASS",
        "KAMOUSS YASSINE",
        "AZHICH SALMA",
        "BADR BERQIA",
        "KANTOS MOHAMED",
        "IBRAHIM ZARYOUH"
    };

    db.transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO LSI1 (name, cne, cin) VALUES (?, ?, ?)");

    bool success = true;
    for (const QString& student : students) {
        query.addBindValue(student);
        // Generate unique CNE and CIN for each student
        QString cne = "LSI1" + QString::number(qHash(student) % 100000);
        QString cin = "CIN" + QString::number(qHash(student + "salt") % 100000);
        query.addBindValue(cne);
        query.addBindValue(cin);
        
        if (!query.exec()) {
            qDebug() << "Error inserting student:" << student << query.lastError();
            success = false;
            break;
        }
    }

    if (success) {
        db.commit();
        return true;
    } else {
        db.rollback();
        return false;
    }
}

bool DatabaseManager::initializeLSI2Data()
{
    QSqlQuery checkQuery("SELECT COUNT(*) FROM LSI2");
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        return true;
    }

    QStringList students = {
        "ACHRAF SABIR",
        "MOHAMED MOUAD RGUIBI",
        "AYOUB AIT SAID",
        "MOUAD ELHANSALI",
        "MOHAMED BARBYCH",
        "BADR BENABDELAH",
        "ABAKHAR ABDESSAMAD"
    };

    db.transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO LSI2 (name, cne, cin) VALUES (?, ?, ?)");

    bool success = true;
    for (const QString& student : students) {
        query.addBindValue(student);
        QString cne = "LSI2" + QString::number(qHash(student) % 100000);
        QString cin = "CIN" + QString::number(qHash(student + "salt") % 100000);
        query.addBindValue(cne);
        query.addBindValue(cin);
        
        if (!query.exec()) {
            qDebug() << "Error inserting LSI2 student:" << student << query.lastError();
            success = false;
            break;
        }
    }

    if (success) {
        db.commit();
        return true;
    } else {
        db.rollback();
        return false;
    }
}

bool DatabaseManager::initializeLSI3Data()
{
    QSqlQuery checkQuery("SELECT COUNT(*) FROM LSI3");
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        return true;
    }

    QStringList students = {
        "BAKR ASSKALLI",
        "MAROUA AMAL",
        "OUAIL LAAMIRI"
    };

    db.transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO LSI3 (name, cne, cin) VALUES (?, ?, ?)");

    bool success = true;
    for (const QString& student : students) {
        query.addBindValue(student);
        QString cne = "LSI3" + QString::number(qHash(student) % 100000);
        QString cin = "CIN" + QString::number(qHash(student + "salt") % 100000);
        query.addBindValue(cne);
        query.addBindValue(cin);
        
        if (!query.exec()) {
            qDebug() << "Error inserting LSI3 student:" << student << query.lastError();
            success = false;
            break;
        }
    }

    if (success) {
        db.commit();
        return true;
    } else {
        db.rollback();
        return false;
    }
}

bool DatabaseManager::initializeProfessorsData()
{
    QSqlQuery checkQuery("SELECT COUNT(*) FROM Professors");
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        return true;
    }

    QList<QPair<QString, QString>> professors = {
        {"EN-NAIMI El Mokhtar", "POO en C++/JAVA"},
        {"EL ACHAK Lotfi", "Front-End/Design Patterns/JEE"},
        {"BAIDA OUAFAE", "Structure de données"},
        {"KHALI ISSA SANAE", "Algorithme et Prog"},
        {"BENABDELWAHAB IKRAM", "Algorithme et prog2"},
        {"EL YOUSSEFI Yassine", "Back-End(PHP)"},
        {"JEBARI Khalid", "Machine Learning"},
        {"Pr. AZMANI Abdellah", "Soft Skills"},
        {"Pr. Ait kbir M'hamed", "Artificial Intelligence"},
        {"EL BRAK Mohammed", "IoT & Systèmes Embarqués"},
        {"ZILI Hassan", "Base de données/DotNet"},
        {"KOUNAIDI Mohamed", "Soft Skills"},
        {"EZZIYYANI Mostafa", "Base de données"},
        {"MAHBOUB Aziz", "Back-End(PHP & Frameworks)"},
        {"ZOUHAIR Abdelhamid", "Réseaux et Systèmes"},
        {"GHADI Abderrahim", "Théorie des graphes/CyberSécurité"},
        {"BOUDHIR Abdelhakim Anouar", "Developpement Web"},
        {"BOUHORMA Mohammed", "Cloud Computing"},
        {"BEN AHMED Mohamed", "Administration Bases de données"},
        {"EL AMRANI Chaker", "UML"},
        {"FENNAN Abdelhadi", "JAVA AVANCÉ"},
        {"Badr-Eddine BOUDRIKI SEMLALI", "Python"},
    };

    db.transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO Professors (name, cin, speciality) VALUES (?, ?, ?)");

    bool success = true;
    for (const auto& prof : professors) {
        query.addBindValue(prof.first);
        QString cin = "PROF" + QString::number(qHash(prof.first) % 100000);
        query.addBindValue(cin);
        query.addBindValue(prof.second);
        
        if (!query.exec()) {
            qDebug() << "Error inserting professor:" << prof.first << query.lastError();
            success = false;
            break;
        }
    }

    if (success) {
        db.commit();
        return true;
    } else {
        db.rollback();
        return false;
    }
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

bool DatabaseManager::addInternship(const QString& studentName, const QString& studentCne, 
                                  const QString& company, const QString& subject)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Internships (student_name, student_cne, company, subject) "
                 "VALUES (?, ?, ?, ?)");
    query.addBindValue(studentName);
    query.addBindValue(studentCne);
    query.addBindValue(company);
    query.addBindValue(subject);
    
    bool success = query.exec();
    if (!success) {
        qDebug() << "Error adding internship:" << query.lastError().text()
                 << "\nQuery:" << query.lastQuery()
                 << "\nValues:" << studentName << studentCne << company << subject;
    }
    return success;
}

int DatabaseManager::getInternshipId(const QString& studentCne, const QString& company)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Internships WHERE student_cne = ? AND company = ?");
    query.addBindValue(studentCne);
    query.addBindValue(company);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

bool DatabaseManager::addReservation(const QString& professorName, const QString& roomNumber, 
                                   const QString& date, const QString& timeSlot)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Reservations (professor_name, room_number, date, time_slot) "
                 "VALUES (?, ?, ?, ?)");
    query.addBindValue(professorName);
    query.addBindValue(roomNumber);
    query.addBindValue(date);
    query.addBindValue(timeSlot);
    
    return query.exec();
}

bool DatabaseManager::removeReservation(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Reservations WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}

QSqlDatabase DatabaseManager::getDatabase() const
{
    return db;
}

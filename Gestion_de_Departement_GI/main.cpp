#include "mainwindow.h"
#include "databasemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // initialisation de base des données
    if (!DatabaseManager::instance().initDatabase()) {
        qDebug() << "Failed to initialize database!";
        return -1;
    }
    
    MainWindow w;
    w.show();
    return a.exec();
}

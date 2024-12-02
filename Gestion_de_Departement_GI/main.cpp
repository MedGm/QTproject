#include "mainwindow.h"
#include "databasemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Initialize database
    if (!DatabaseManager::instance().initDatabase()) {
        qDebug() << "Failed to initialize database!";
        return -1;
    }
    
    MainWindow w;
    w.show();
    return a.exec();
}

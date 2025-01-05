#ifndef RESERVATIONSWINDOW_H
#define RESERVATIONSWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSqlDatabase>
#include "databasemanager.h"

class ReservationsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReservationsWindow(QWidget *parent = nullptr);
    ~ReservationsWindow();

private slots:
    void onAddReservationClicked();
    void onDeleteReservationClicked();

private:
    void setupUI();
    void loadReservations();
    
    QTableWidget* reservationsTable;
};

#endif // RESERVATIONSWINDOW_H

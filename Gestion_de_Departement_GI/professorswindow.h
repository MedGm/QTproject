#ifndef PROFESSORSWINDOW_H
#define PROFESSORSWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QStackedWidget>

class ProfessorsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfessorsWindow(QWidget *parent = nullptr);
    ~ProfessorsWindow();

private slots:
    void onAddProfessorClicked();
    void onDeleteProfessorClicked();
    void onShowReservationsClicked();
    void onAddReservationClicked();
    void onDeleteReservationClicked();

private:
    void setupProfessorsTable();
    void loadProfessors();
    void setupReservationsTable();
    void loadReservations();

    QTableWidget* professorsTable;
    QTableWidget* reservationsTable;
    QWidget* centralWidget;
    QStackedWidget* mainStack;
    QWidget* professorsPage;
    QWidget* reservationsPage;
};

#endif // PROFESSORSWINDOW_H

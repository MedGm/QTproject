#ifndef PROFESSORSWINDOW_H
#define PROFESSORSWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSqlQuery>
#include <QSqlDatabase>

class ProfessorsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfessorsWindow(QWidget *parent = nullptr);
    ~ProfessorsWindow();

private slots:
    void onAddProfessorClicked();
    void onDeleteProfessorClicked();

private:
    void setupProfessorsTable();
    void loadProfessors();
    
    QTableWidget* professorsTable;
    QWidget* centralWidget;
};

#endif // PROFESSORSWINDOW_H

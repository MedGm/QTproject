#ifndef CYCLEMANAGEMENT_H
#define CYCLEMANAGEMENT_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QComboBox>
#include <QTableWidget>
#include <QSqlQuery>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QResizeEvent>
#include "databasemanager.h"
#include <QCheckBox>
#include <QFileDialog>
#include <QDir>

namespace Ui {
class cyclemanagement;
}

class cyclemanagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit cyclemanagement(QWidget *parent = nullptr);
    ~cyclemanagement();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void onLevelChanged(int index);
    void onLogoutClicked();
    void onAddStudentClicked();
    void onDeleteStudentClicked();
    void onProfessorsButtonClicked();
    void onScheduleButtonClicked();
    void showSchedule(const QString& level);
    void onStudentsButtonClicked();
    void onAddProfessorClicked();
    void onDeleteProfessorClicked();
    void onInternshipsButtonClicked();
    void onAddInternshipClicked();
    void onDeleteInternshipClicked();
    void onDemandsButtonClicked();
    void onDemandOptionClicked();

private:
    Ui::cyclemanagement *ui;
    void setupUI();
    void loadStudents(const QString& level);
    void loadProfessors();
    void loadSchedule();
    void loadInternships();
    void loadRequests();
    
    QStackedWidget *mainStack;
    QTableWidget *studentsTable;
    QTableWidget *professorsTable;
    QLabel* scheduleLabel;
    void setupProfessorsTable();
    QWidget* pageWidget;  // Add this line to store the students page widget
    QWidget* professorsPageWidget;  // Add this line
    QWidget* schedulePageWidget;  // Add this line
    QWidget* internshipsPageWidget;
    QTableWidget* internshipsTable;
    void setupInternshipsTable();
    QWidget* demandsPageWidget;
    void setupDemandsPage();
    void downloadPDF(const QString& demandType);
};

#endif // CYCLEMANAGEMENT_H

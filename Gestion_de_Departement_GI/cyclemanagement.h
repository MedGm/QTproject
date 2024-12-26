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
#include <QShortcut>

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
    void onScheduleButtonClicked();
    void showSchedule(const QString& level);
    void onStudentsButtonClicked();
    void onInternshipsButtonClicked();
    void onAddInternshipClicked();
    void onDeleteInternshipClicked();

private:
    Ui::cyclemanagement *ui;
    void setupUI();
    void loadStudents(const QString& level);
    void loadSchedule();
    void loadInternships();
    
    QStackedWidget *mainStack;
    QTableWidget *studentsTable;
    QLabel* scheduleLabel;
    QWidget* pageWidget;
    QWidget* schedulePageWidget;
    QWidget* internshipsPageWidget;
    QTableWidget* internshipsTable;
    void setupInternshipsTable();
};

#endif // CYCLEMANAGEMENT_H

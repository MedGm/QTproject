#ifndef LICENCE_H
#define LICENCE_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>

class licence : public QMainWindow {
    Q_OBJECT

public:
    explicit licence(QWidget *parent = nullptr);
    ~licence();

private slots:
    void onLevelChangedForStudents(int index);
    void onLevelChangedForStages(int index);
    void onLevelChangedForTimetable(int index);
    void updateTimeTableImage(const QString &level);
    void onStudentsButtonClicked();
    void onAddStudentClicked();
    //void onSaveStudentClicked();
    void onShowStudentInfoClicked(int row);
    void onAddInternshipClicked(int row);
    //void onEditStudentClicked(int row);
    void onConfirmDeleteStudent(int row);
    void onstageClicked();
    void onShowStageInfoClicked(int row);
    void onDeleteStageClicked(int row);
    void onBackButtonClicked();
    //void onDeleteStudentClicked();
    void loadStages(const QString &level);
    void onConfirmDeleteStage(int row);
    void hideAllComboBoxes();
    void refreshPage();



<<<<<<< HEAD

=======
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
private:
    QLineEdit *nameEdit, *surnameEdit, *cneEdit, *emailEdit, *phoneEdit, *dobEdit, *specialtyEdit;
    QComboBox *levelComboBoxStudents, *levelComboBoxStages, *levelComboBoxTimetable;
    QTableWidget *studentsTable, *stageTable;
    QPushButton *studentsButton, *addButton, *stage, *backButton, *timetableButton;
    QHBoxLayout *navbarLayout;
    QStackedWidget *stackedWidget;
    QWidget *imageWidget;
    QComboBox *levelComboBox;

    void setupNavbar();
    void setupStudentsTable();
    void setupStageTable();
    void loadStudents(const QString &level);
    void colorSelectedRow(int row);
};

#endif

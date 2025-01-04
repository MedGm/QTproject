#ifndef MASTERMANAGEMENT_H
#define MASTERMANAGEMENT_H


#include <QMainWindow>
//#include <QSqlDatabase>
#include <QLabel>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QObject>


namespace Ui {
class MasterManagement;
}

class MasterManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit MasterManagement(QWidget *parent = nullptr);
    ~MasterManagement();

private slots:
    void addStudent();
    void addStudent2();
    void addStudent3();
    void updateStudent();
    void deleteStudent();
    void showSchedule();
    void showStudents();

    void setupStudentTable();
    void onComboBoxChanged();
    //bool createDatabase();


private:
    Ui::MasterManagement *ui;                // Interface utilisateur
    //QSqlDatabase db;               // Connexion à la base de données
    QLabel *scheduleLabel;         // Widget pour afficher les emplois du temps

    QComboBox *filiereComboBox; // ComboBox pour sélectionner les filières
    QTableWidget *studentTable; // Tableau pour afficher les étudiants
    QStackedWidget *stackedWidget; // Widget empilé pour basculer entre les pages

    QWidget *studentPage;
    QWidget *emploiPage;

    QLabel *emploiLabel;

    // Boutons
    QPushButton *emploitButton;
    QPushButton *moduleButton;
    QPushButton *stageButton;
    QPushButton *addButton;
    QPushButton *delButton;
    QPushButton *etudiantButton;
    QPushButton *profButton;

    // Méthodes privées
    //bool connectToDatabase();

    void loadStudents();
    void emploits(const QString &level);
    bool writeDataToFile(const QStringList& data);
    bool readDataFromFile(QList<QStringList>& studentsData);


    //bool connectToDatabase();      // Connecter à la base de données
    //void loadStudents(const QString &level); // Charger les étudiants d'une filière donnée
    //void emploits(const QString &level);     // Charger et afficher l'image de l'emploi du temps
};



#endif // MASTERMANAGEMENT_H

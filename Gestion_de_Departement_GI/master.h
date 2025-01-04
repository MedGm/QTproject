#ifndef MASTER_H
#define MASTER_H


#include <QMainWindow>
<<<<<<< HEAD
//#include <QSqlDatabase>
=======
#include <QSqlDatabase>
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
#include <QLabel>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QObject>


namespace Ui {
class Master;
}

class Master : public QMainWindow
{
    Q_OBJECT

public:
    explicit Master(QWidget *parent = nullptr);
    ~Master();

private slots:
<<<<<<< HEAD
    void addStudent();
    void delStudent();
    void AjouterStage();
    //void addStudent2();
    //void addStudent3();
    void updateStudent();
    void deleteStudent();
    void showSchedule();
    void showStudents();

    void showStage();
    void onComboBoxChanged();
    //bool createDatabase();


private:
    Ui::Master *ui;                // Interface utilisateur
    //QSqlDatabase db;               // Connexion à la base de données
=======
    void addStudent();             // Ajouter un étudiant
    void updateStudent();          // Mettre à jour un étudiant
    void deleteStudent();          // Supprimer un étudiant
    void showSchedule();           // Afficher l'emploi du temps
    void showStudents();           // Afficher le tableau des étudiants
    void onComboBoxChanged();      // Gérer les changements de niveau dans la ComboBox

private:
    Ui::Master *ui;                // Interface utilisateur
    QSqlDatabase db;               // Connexion à la base de données
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    QLabel *scheduleLabel;         // Widget pour afficher les emplois du temps

    QComboBox *filiereComboBox; // ComboBox pour sélectionner les filières
    QTableWidget *studentTable; // Tableau pour afficher les étudiants
<<<<<<< HEAD
    QTableWidget *stageTable;
    QStackedWidget *stackedWidget; // Widget empilé pour basculer entre les pages

    QWidget *studentPage;
    QWidget *stagePage;
    QWidget *emploiPage;

=======
    QStackedWidget *stackedWidget; // Widget empilé pour basculer entre les pages

    QWidget *studentPage;
    QWidget *emploiPage;
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    QLabel *emploiLabel;

    // Boutons
    QPushButton *emploitButton;
<<<<<<< HEAD
    QPushButton *addStage;
=======
    QPushButton *moduleButton;
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
    QPushButton *stageButton;
    QPushButton *addButton;
    QPushButton *delButton;
    QPushButton *etudiantButton;
<<<<<<< HEAD
    QPushButton *logout;

    // Méthodes privées
    //bool connectToDatabase();

    void loadStudents(const QString& level);
    void loadStage(const QString& level);
    void emploits(const QString &level);
    bool writeDataToFile(const QStringList& data);
    bool writeDataStage(const QStringList& data);
    bool readDataFromFile(QList<QStringList>& studentsData);
    bool readDataStage(QList<QStringList>& studentsData);
    bool removeLigneFromFile(const QStringList& data);

=======
    QPushButton *profButton;

    // Méthodes privées
    bool connectToDatabase();
    void loadStudents(const QString &level);
    void emploits(const QString &level);
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241

    //bool connectToDatabase();      // Connecter à la base de données
    //void loadStudents(const QString &level); // Charger les étudiants d'une filière donnée
    //void emploits(const QString &level);     // Charger et afficher l'image de l'emploi du temps
};










<<<<<<< HEAD
#endif
=======
#endif // MASTER_H
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241

#ifndef MASTER_H
#define MASTER_H


#include <QMainWindow>
#include <QSqlDatabase>
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
    void addStudent();             // Ajouter un étudiant
    void updateStudent();          // Mettre à jour un étudiant
    void deleteStudent();          // Supprimer un étudiant
    void showSchedule();           // Afficher l'emploi du temps
    void showStudents();           // Afficher le tableau des étudiants
    void onComboBoxChanged();      // Gérer les changements de niveau dans la ComboBox

private:
    Ui::Master *ui;                // Interface utilisateur
    QSqlDatabase db;               // Connexion à la base de données
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
    bool connectToDatabase();
    void loadStudents(const QString &level);
    void emploits(const QString &level);

    //bool connectToDatabase();      // Connecter à la base de données
    //void loadStudents(const QString &level); // Charger les étudiants d'une filière donnée
    //void emploits(const QString &level);     // Charger et afficher l'image de l'emploi du temps
};










#endif // MASTER_H

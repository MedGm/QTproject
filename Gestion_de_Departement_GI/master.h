#ifndef MASTER_H
#define MASTER_H


#include <QMainWindow>
//#include <QSqlDatabase>
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
    QLabel *scheduleLabel;         // Widget pour afficher les emplois du temps

    QComboBox *filiereComboBox; // ComboBox pour sélectionner les filières
    QTableWidget *studentTable; // Tableau pour afficher les étudiants
    QTableWidget *stageTable;
    QStackedWidget *stackedWidget; // Widget empilé pour basculer entre les pages

    QWidget *studentPage;
    QWidget *stagePage;
    QWidget *emploiPage;

    QLabel *emploiLabel;

    // Boutons
    QPushButton *emploitButton;
    QPushButton *addStage;
    QPushButton *stageButton;
    QPushButton *addButton;
    QPushButton *delButton;
    QPushButton *etudiantButton;
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


    //bool connectToDatabase();      // Connecter à la base de données
    //void loadStudents(const QString &level); // Charger les étudiants d'une filière donnée
    //void emploits(const QString &level);     // Charger et afficher l'image de l'emploi du temps
};










#endif

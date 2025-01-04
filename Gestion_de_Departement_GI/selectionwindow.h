#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include "cyclemanagement.h"
#include "licence.h"
#include "master.h"
#include "professorswindow.h"
#include "demandswindow.h"
#include "reservationswindow.h"

namespace Ui {
class SelectionWindow;
}

class SelectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectionWindow(QWidget *parent = nullptr);
    ~SelectionWindow();

private slots:
    void onEngineerButtonClicked();
    void onLicenceButtonClicked();
    void onMasterButtonClicked();
    void onProfessorsButtonClicked();
    void onDemandsButtonClicked();
    void onReservationsButtonClicked();
<<<<<<< HEAD
=======

>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
private:
    Ui::SelectionWindow *ui;
    void setupIcons();
    
    ProfessorsWindow* professorsWindow;
    DemandsWindow* demandsWindow;
    ReservationsWindow* reservationsWindow;
<<<<<<< HEAD

=======
>>>>>>> f268020af7b1cd3edf11540eb97593cc035a9241
};

#endif // SELECTIONWINDOW_H

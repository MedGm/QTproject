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
private:
    Ui::SelectionWindow *ui;
    void setupIcons();
    
    ProfessorsWindow* professorsWindow;
    DemandsWindow* demandsWindow;
    ReservationsWindow* reservationsWindow;

};

#endif // SELECTIONWINDOW_H

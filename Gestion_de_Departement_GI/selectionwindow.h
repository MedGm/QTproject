#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include "cyclemanagement.h"
#include "professorswindow.h"
#include "demandswindow.h"

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
    void onProfessorsButtonClicked();
    void onDemandsButtonClicked();

private:
    Ui::SelectionWindow *ui;
    void setupIcons();
    
    ProfessorsWindow* professorsWindow;
    DemandsWindow* demandsWindow;
};

#endif // SELECTIONWINDOW_H
#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include "cyclemanagement.h"

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

private:
    Ui::SelectionWindow *ui;
    void setupIcons();
};

#endif // SELECTIONWINDOW_H
#ifndef DEMANDSWINDOW_H
#define DEMANDSWINDOW_H

#include <QMainWindow>
#include <QWidget>

class DemandsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DemandsWindow(QWidget *parent = nullptr);
    ~DemandsWindow();

private slots:
    void onDemandOptionClicked();

private:
    void setupDemandsPage();
    void downloadPDF(const QString& demandType);
    
    QWidget* centralWidget;
};

#endif // DEMANDSWINDOW_H

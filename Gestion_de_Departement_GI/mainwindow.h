#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QVariantAnimation>
#include <QPainter>
#include "logindialog.h"
#include "selectionwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_Adminbutton_clicked();
    void updateButtonStylesheet(const QVariant &value);
    void updateHeaderStylesheet(const QVariant &value);

private:
    Ui::MainWindow *ui;
    QVariantAnimation *buttonColorAnimation;
    QVariantAnimation *headerColorAnimation;
    void setupAnimations();
};
#endif // MAINWINDOW_H

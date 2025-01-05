#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QVariantAnimation>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_loginButton_clicked();
    void updateButtonStylesheet(const QVariant &value);

private:
    Ui::LoginDialog *ui;
    QVariantAnimation *buttonColorAnimation;
    void setupAnimations();
    void setupInputIcons();
};

#endif // LOGINDIALOG_H

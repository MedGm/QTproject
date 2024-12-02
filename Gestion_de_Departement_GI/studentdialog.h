#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class StudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentDialog(QWidget *parent = nullptr);
    QString getName() const { return nameEdit->text(); }
    QString getCNE() const { return cneEdit->text(); }
    QString getCIN() const { return cinEdit->text(); }

private:
    QLineEdit *nameEdit;
    QLineEdit *cneEdit;
    QLineEdit *cinEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif

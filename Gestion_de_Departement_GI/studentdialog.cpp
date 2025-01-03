#include "studentdialog.h"
#include <QFormLayout>

StudentDialog::StudentDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Add Student");

    nameEdit = new QLineEdit(this);
    cneEdit = new QLineEdit(this);
    cinEdit = new QLineEdit(this);
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("CNE:", cneEdit);
    formLayout->addRow("CIN:", cinEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    formLayout->addRow(buttonLayout);

    setLayout(formLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

#ifndef STAGE_H
#define STAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>

class Salle : public QWidget
{
    Q_OBJECT

public:
    explicit Salle(QWidget *parent = nullptr);
    ~Salle();

private slots:
    void onReturnClicked();
    void onAjouterClicked();

private:
    QTableWidget *table;
    void loadDataFromFile(const QString &filePath);
    int getDayIndex(const QString &day);
    int getTimeIndex(const QString &time);
};

#endif // STAGE_H

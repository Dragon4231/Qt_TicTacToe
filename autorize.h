#ifndef AUTORIZE_H
#define AUTORIZE_H

#include <QDialog>

namespace Ui {
class Autorize;
}

class Autorize : public QDialog
{
    Q_OBJECT

public:
    explicit Autorize(QWidget *parent = nullptr);
    ~Autorize();
    QString person1;
    QString person2;
    void clear();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Autorize *ui;
};

#endif // AUTORIZE_H

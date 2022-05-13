#include "autorize.h"
#include "ui_autorize.h"
#include <QMessageBox>

Autorize::Autorize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Autorize)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::CustomizeWindowHint);
    QCursor cursorTarget = QCursor(QPixmap("D:\\krestiki_noliki\\cursor3.png"));
    this->setCursor(cursorTarget);
}

Autorize::~Autorize()
{
    delete ui;
}

void Autorize::on_pushButton_clicked()
{
    if(ui->textEdit->toPlainText().isEmpty() || ui->textEdit_2->toPlainText().isEmpty()){
        QMessageBox box;
        box.setWindowTitle("Ошибка!");
        box.setText("Одно из полей пустое.");
        box.exec();
        return;
    }
    person1 = ui->textEdit->toPlainText();
    person2 = ui->textEdit_2->toPlainText();
    this->close();
}

void Autorize::on_pushButton_2_clicked()
{
    QApplication::quit();
}

void Autorize::clear()
{
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
}

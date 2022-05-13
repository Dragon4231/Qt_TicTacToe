#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_4->setStyleSheet("font: 81 10pt \"Rockwell Extra Bold\";color: rgb(255, 92, 92)");
    ui->label_4->setDisabled(true);
    ui->label_4->setText("Time of the game ");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    palette.setColor(QPalette::Background,QColor("silver"));
    this->setPalette(palette);
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
    dialog->setModal(true);
    dialog->show();
    QCursor cursorTarget = QCursor(QPixmap("D:\\krestiki_noliki\\cursor3.png"));
    this->setCursor(cursorTarget);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    int l = 3;
    for(int i = 0; i < 3; i ++){
        for(int j = 0; j < 3; j ++){
            game[i][j] = l;
            l++;
        }
        ui->tableWidget->setRowHeight(i,100);
        ui->tableWidget->setColumnWidth(i,100);
    }

    for(int i = 0; i < 3; i ++){
        for(int j = 0; j < 3; j ++){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem());
            ui->tableWidget->item(i,j)->setTextAlignment(4);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimerSlot()
{
    ms++;
    if(ms >= 1000){
        ms = 0;
        s++;
    }
    if(s>=60){
        s = 0;
        m++;
    }
    ui->label_4->setText(QString("Time of the game ") + QString::number(m) + " : " + QString::number(s) + " : " + QString::number(ms));
}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if(!startGame){
        QMessageBox box;
        box.setWindowTitle("Ошибка!");
        box.setText("Игра не началась.");
        box.exec();
        return;
    }
    if(tempPlayer == 1 && game[row][column] != 2){
        game[row][column] = tempPlayer;
        brush.setTextureImage(QImage("D:\\krestiki_noliki\\pngwing.com.png"));
        tempPlayer = 2;
    }else if(tempPlayer == 2 && game[row][column] != 1){
        game[row][column] = tempPlayer;
        brush.setTextureImage(QImage("D:\\krestiki_noliki\\nol.png"));
        tempPlayer = 1;
    }else{
        QMessageBox box;
        box.setWindowTitle("Ошибка!");
        box.setText("Клетка уже занята");
        box.exec();
        return;
    }
    ui->tableWidget->item(row,column)->setBackground(brush);
    playerInfo(tempPlayer);
    if(checkForWin()){
        timer->stop();
        QMessageBox box;
        if(tempPlayer == 0){
            box.setWindowTitle("Ничья!");
            box.setText("Никто не смог победить в этой игре.");
            box.exec();
            stopGame();
            return;
        }
        box.setWindowTitle("Победа!");
        if(tempPlayer == 1) box.setText("Победил игрок " + dialog->person1);
        else box.setText("Победил игрок " + dialog->person2);
        box.exec();
        stopGame();
        return;
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->setText(dialog->person1);
    ui->textEdit_2->setText(dialog->person2);
    startGame = true;
    rg = new QRandomGenerator();
    int temp;
        temp = rg->bounded(1,3);
    tempPlayer = temp;
    ui->pushButton->setDisabled(true);
    playerInfo(tempPlayer);
    s = 0;
    ms = 0;
    m = 0;
    timer->start(1);
}

void MainWindow::playerInfo(int l){
    QString put;
    put.push_back("Player turn : ");
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setStyleSheet("font: 81 10pt \"Rockwell Extra Bold\";color: rgb(175, 255, 71)");
    if(l == 1){
        put.push_back(dialog->person1);
    }else if(l == 2){
        put.push_back(dialog->person2);
    }
    ui->label_3->setText(put);
}

bool MainWindow::checkForWin(){
    if((game[0][0] == game[1][1] && game[0][0] == game[2][2]) ||
            (game[0][2] == game[1][1] && game[0][2] == game[2][0])){
        tempPlayer = game[1][1];
        return true;
    }
    int j = 0;
    for(int i = 0; i < 3; i++){
        if((game[i][j] == game[i][j+1] && game[i][j] == game[i][j+2])){
            tempPlayer = game[i][j];
            return true;
        }
        else if((game[j][i] == game[j+1][i] && game[j][i] == game[j+2][i])){
            tempPlayer = game[j][i];
            return true;
        }
    }
    for(int i = 0; i < 3; i ++){
        for(int l = 0; l < 3; l++){
            if(game[i][l] != 1 && game[i][l] != 2){
                return false;
            }
        }
    }
    tempPlayer = 0;
    return true;
}

void MainWindow::stopGame()
{
    ui->label_4->setText("Time of the game ");
    tempPlayer = 1;
    ms = 0;
    s = 0;
    m = 0;
    dialog->clear();
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
    dialog->show();
    ui->pushButton->setDisabled(false);
    int l = 3;
    for(int i = 0; i < 3; i ++){
        for(int j = 0; j < 3; j ++){
            game[i][j] = l;
            l++;
        }
    }
    for(int i = 0; i < 3; i ++){
        for(int j = 0; j < 3; j ++){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem());
            ui->tableWidget->item(i,j)->setTextAlignment(4);
        }
    }
    startGame = false;
}

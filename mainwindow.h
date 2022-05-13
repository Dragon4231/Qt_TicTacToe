#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <autorize.h>
#include <QTimer>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void TimerSlot();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_clicked();

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_tableWidget_cellActivated(int row, int column);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int ms, s, m;
    Autorize *dialog = new Autorize();
    bool startGame = false;
    int tempPlayer = 1;
    void playerInfo(int l);
    QPalette palette;
    bool checkForWin();
    QBrush brush;
    int game[3][3];
    QRandomGenerator *rg;
    void stopGame();

};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTimer>

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
    void on_twDesk_cellClicked(int row, int column);

    void on_restart_clicked();

    void on_NewGame_clicked();

    void tick();

private:
    int sec;
    int min;
    int hours;
    QTimer *gameTime;
    Ui::MainWindow *ui;
    void showTable();
    QTableWidgetItem *itNode = new QTableWidgetItem;
};
#endif // MAINWINDOW_H

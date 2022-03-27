#include "barleybreak.h"
#include "mainwindow.h"
#include <QPicture>
#include <QMessageBox>
#include "ui_mainwindow.h"

BarleyBreak game;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    for(int i = 0; i < 4 ; i++) {
        ui -> twDesk -> setColumnWidth(i, 120);
        ui -> twDesk -> setRowHeight(i, 120);
    }
    ui->twDesk->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    ui->twDesk->setEditTriggers(QAbstractItemView::NoEditTriggers);
    itNode->setTextAlignment(Qt::AlignCenter);
    gameTime = new QTimer();
    gameTime ->setInterval(1000);
    connect(gameTime,SIGNAL(timeout()),this,SLOT(tick()));
    ui -> leTimer ->setText("00:00:00");
    sec = min = hours = 0;
    showTable();
}

void MainWindow::showTable() {
    if (game.getMovesCount() == 1)
        gameTime->start();
    for (int i =0; i < 4 ; i++)
        for (int j =0; j<4;j++) {
            if (game.getNumber(i,j) == 0) {
                itNode -> setText("   ");
            } else {
                itNode -> setText(QString::number(game.getNumber(i ,j)));
            }
            ui -> twDesk ->setItem(i, j, new QTableWidgetItem(*itNode));
        }
    ui -> ln_counter -> setText(QString::number(game.getMovesCount()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete gameTime;
}

void MainWindow::on_twDesk_cellClicked(int row, int column) {
 game.MoveWhenClicked(row,column);
 showTable();
 if(game.isFinished()) {
         min =hours =0;
         sec =-1;
         tick();
         gameTime->stop();
         if(QMessageBox::question(this,"Игра закончена!","Победа! Желаете ещё сыграть?",
                               QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
         QApplication::quit();
         else {
             game.startGame();
             showTable();
         }
     }
}

void MainWindow::on_restart_clicked() {
    gameTime->stop();
    min = hours = 0;
    sec =-1;
    tick();
    game.restartGame();
    showTable();
}

void MainWindow::on_NewGame_clicked() {
    min = hours = 0;
    sec =-1;
    tick();
    game.startGame();
    gameTime->stop();
    showTable();
}

void MainWindow::tick() {
    sec++;
    if (sec == 60) {
        sec = 0;
        min++;
    }
    if (min == 60) {
        min = 0;
        hours++;
    }
    ui->leTimer->setText(QString::number(hours)+ "h\n" +
                         QString::number(min)+ "m\n" +
                         QString::number(sec)+'s');
}


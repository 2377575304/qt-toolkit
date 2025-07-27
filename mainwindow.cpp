#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_co_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_mine_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


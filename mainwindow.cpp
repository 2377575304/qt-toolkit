#include "mainwindow.h"
#include "./ui_mainwindow.h"


#define DEBUG 0


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog_pix = new Dialog_pix(this);
    // 初始化列表数据
    QStringList items = {"apple", "banana", "cherry", "date", "elderberry","pixpic"};
    ui->listWidget->addItems(items);




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


void MainWindow::on_pushButton_search_clicked()
{
    QString keyword = ui->plainTextEdit->toPlainText().trimmed();//获取用户输入的关键字 -> keyword
    if(DEBUG){ ui->plainTextEdit->setPlainText(QString("user input: %1").arg(keyword));}//%1 %2 %3 ...arg().arg().arg()

    for(int i =0;i < ui->listWidget->count();i++)
    {
        QListWidgetItem *item =ui->listWidget->item(i);
        if (item->text().contains(keyword,Qt::CaseInsensitive)){ //不区分大小写
            item ->setHidden(false);
        }
    else{
            item->setHidden(true);
        }
    }

}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(item->text() == "apple")
    {qDebug() << "this is a apple!"<<item->text();}

    else if(item->text() == "pixpic"){
        dialog_pix->show();
    }
}


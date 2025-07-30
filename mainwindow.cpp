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
    QStringList items = {"apple","pixpic"};
    ui->listWidget->addItems(items);
    //读取收藏得工具
    QSettings settings("YourCompany", "YourApp");
    QStringList favorites = settings.value("favorites", QStringList()).toStringList();
    foreach (const QString& item, favorites)
    {
        ui->listWidget_2->addItem(item);
    }




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
    if(item->text() == "apple")//
    {qDebug() << "this is a apple!"<<item->text();}

    else if(item->text() == "pixpic"){
        dialog_pix->show();//选择相应工具名
    }
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *curitem =ui->listWidget->itemAt(pos);
    if(!curitem)
        return;
    QMenu popmenu(this);
    QAction *collect =new QAction(tr("收藏"),this);

    connect(collect,&QAction::triggered,this,&MainWindow::oncollectitem);

    popmenu.addAction(collect);

    popmenu.exec(QCursor::pos());

}


void MainWindow::oncollectitem()
{
    QListWidgetItem* curItem = ui->listWidget->currentItem();
    if (curItem)
    {
        qDebug() << "收藏了项目：" << curItem->text();
      //  ui->listWidget_2->addItem(curItem-text());
        ui->listWidget_2->addItem(curItem->text());

        QSettings settings("YourCompany", "YourApp");
        QStringList favorites = settings.value("favorites", QStringList()).toStringList();
        favorites.append(curItem->text());
        settings.setValue("favorites", favorites);
    }
}


void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    if(item->text() == "apple")//
    {qDebug() << "this is a apple!"<<item->text();}

    else if(item->text() == "pixpic"){
        dialog_pix->show();//选择相应工具名
    }
}


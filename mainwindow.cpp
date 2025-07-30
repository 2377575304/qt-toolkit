#include "mainwindow.h"
#include "./ui_mainwindow.h"


#define DEBUG 0


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("小璇的工具箱");

    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pixmap("D:/desktop/anything/Qt/toolkits/home.png");  // 加载图片

    // 检查图片是否加载成功
    if (pixmap.isNull()) {
        qDebug() << "图片加载失败，请，请检查路径是否正确";
        return;
    }
    QPixmap scaledPixmap = pixmap.scaled(
        700,
        500,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );


    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(scaledPixmap);  // 现在scaledPixmap已定义

    // QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);

    scene->addItem(pixmapItem);

    // 将场景设置到QGraphicsView
    ui->graphicsView->setScene(scene);


    dialog_pix = new Dialog_pix(this);
    // 初始化列表数据
    QStringList items = {"apple","pixpic","一键抠图工具","视频解析下载","网易云flac转mp3","bilibili","豆包"};
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
    else if(item->text() == "一键抠图工具"){
        QString url = "https://www.koukoutu.com/removebgtool/all";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
    }
    else if(item->text() == "视频解析下载"){
        QString url = "https://greenvideo.cc";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
    }

    else if(item->text() == "网易云flac转mp3"){
        QString url = "https://www.freeconvert.com/zh/flac-to-mp3";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
    }

    else if(item->text() == "bilibili"){
        QString url = "https://www.bilibili.com";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
    }
    else if(item->text() == "豆包"){
        QString url = "https://www.doubao.com/chat/";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
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
void MainWindow::on_listWidget_2_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *curitem = ui->listWidget_2->itemAt(pos);
    if (!curitem)
        return;

    QMenu popmenu(this);
    QAction *decollect = new QAction(tr("取消收藏"), this);
    connect(decollect, &QAction::triggered, this, &MainWindow::deoncollectitem);
    popmenu.addAction(decollect);
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
void MainWindow::deoncollectitem(){
    QListWidgetItem* curItem = ui->listWidget_2->currentItem();
    if (!curItem)
    {
        QMessageBox::warning(this, "提示", "请先选中要删除的项！");
        return;
    }
    else {
        qDebug() << "取消收藏了项目：" << curItem->text();
        // 通过行号删除项
        int row = ui->listWidget_2->row(curItem);
        QListWidgetItem *removedItem = ui->listWidget_2->takeItem(row);//带走item
        delete removedItem; // 必须删除，否则内存泄漏

        QSettings settings("YourCompany", "YourApp");
        QStringList favorites = settings.value("favorites", QStringList()).toStringList();

        // 找到要删除的项的索引
        int index = favorites.indexOf(curItem->text());
        if (index != -1) { // 确保找到了该项
            favorites.removeAt(index); // 删除指定索引的项
            settings.setValue("favorites", favorites); // 保存修改
        }
    }
}
void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    if(item->text() == "apple")//
    {qDebug() << "this is a apple!"<<item->text();}

    else if(item->text() == "pixpic"){
        dialog_pix->show();//选择相应工具名
    }
    else if(item->text() == "一键抠图工具"){
        QString url = "https://www.koukoutu.com/removebgtool/all";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
    }
    else if(item->text() == "视频解析下载"){
        QString url = "https://greenvideo.cc";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
    }

    else if(item->text() == "网易云flac转mp3"){
        QString url = "https://www.freeconvert.com/zh/flac-to-mp3";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
    }

    else if(item->text() == "bilibili"){
        QString url = "https://www.bilibili.com";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
    }
    else if(item->text() == "豆包"){
        QString url = "https://www.doubao.com/chat/";
        bool success = QDesktopServices::openUrl(QUrl(url));
        if (!success) {
            QMessageBox::warning(nullptr, "错误", "无法打开浏览器，请检查URL是否有效");
        }
    }
}


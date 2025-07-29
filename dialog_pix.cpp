#include "dialog_pix.h"
#include "ui_Dialog_pix.h"
#include "QFileDialog"
#include "QMessageBox"

void pix(QString add);
Dialog_pix::Dialog_pix(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog_pix)
{
    ui->setupUi(this);
}

Dialog_pix::~Dialog_pix()
{
    delete ui;
}

void Dialog_pix::on_buttonBox_rejected()
{
    close();
}


void Dialog_pix::on_Bowser_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,                                  // 父窗口
        tr("打开文件"),                         // 对话框标题
        "",
        tr("所有文件 (*.);;文本文件 (*.txt);;图像(*.png)")   // 文件过滤器
        );
    ui->lineEdit->setText(fileName);
}


void Dialog_pix::on_buttonBox_accepted()
{

}

void Dialog_pix::on_convent_clicked()
{
    QString filepath = ui->lineEdit->text();
    pix(filepath);
}

void Dialog_pix::pix( QString add)
{
    QImage image(add);
    if (image.isNull()){
        qDebug()<<"加载失败:"<<add;
        return ;
    }
    else
    {
        QImage grayImage = image.convertToFormat(QImage::Format_Grayscale8);
        int width =grayImage.width();
        int height =grayImage.height();
        int step =qMax(width,height)/5;
        for (int y = 0; y < height; y += step) {
            for (int x = 0; x < width; x += step) {
                int sum = 0;
                int count = 0;
                for (int i = 0; i < step && y + i < height; ++i) {
                    for (int j = 0; j < step && x + j < width; ++j) {
                        sum += grayImage.pixelColor(x + j, y + i).black();
                        count++;
                    }
                }
                int avg = sum / count;
                QColor avgColor(avg, avg, avg);
                for (int i = 0; i < step && y + i < height; ++i) {
                    for (int j = 0; j < step && x + j < width; ++j) {
                        grayImage.setPixelColor(x + j, y + i, avgColor);
                    }
                }
            }
        }
        if (!grayImage.save(add)) {
            qDebug() << "保存图片失败: " << add;
        }
        else {
            QMessageBox::information(this, tr("保存成功"), tr("图片已成功保存"));

        }
    }

}

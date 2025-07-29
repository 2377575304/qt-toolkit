#ifndef DIALOG_PIX_H
#define DIALOG_PIX_H

#include <QDialog>
#include "QImage"
#include "QColor"
#include "ui_Dialog_pix.h"
#include "QDebug"

namespace Ui {
class Dialog_pix;
}

class Dialog_pix : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_pix(QWidget *parent = nullptr);
    ~Dialog_pix();

private slots:
    void on_buttonBox_rejected();

    void on_Bowser_clicked();

    void on_buttonBox_accepted();

    void pix(const QString add);

    void on_convent_clicked();

private:
    Ui::Dialog_pix *ui;
};

#endif // DIALOG_PIX_H

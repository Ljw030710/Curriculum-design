#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"choosemenu.h"
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

void MainWindow::on_LoginButton_clicked()
{
    static int n = 0;
    QString name = ui->UserName->text();
    QString password = ui->Password->text();
    if(name=="cxk"&&password=="123456"){
        qDebug()<<"Success";
        ChooseMenu *choose = new ChooseMenu();
        choose->show();
    }
    else{
        n++;
        if(n==5){//输出五次错误,锁死
            ui->UserName->setEnabled(false);
            ui->Password->setEnabled(false);
        }
    }
}




void MainWindow::on_CancelButton_clicked()
{
    this->close();
}


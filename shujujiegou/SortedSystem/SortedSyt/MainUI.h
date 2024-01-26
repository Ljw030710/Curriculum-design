#pragma once
#include <QMainWindow>

namespace Ui {
class MainUI;
}

//主窗口
class MainUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainUI(QWidget *parent = nullptr);
    ~MainUI();

private:
    //整个图形化界面进行初始化
    void init();

private:
    Ui::MainUI *ui;
};

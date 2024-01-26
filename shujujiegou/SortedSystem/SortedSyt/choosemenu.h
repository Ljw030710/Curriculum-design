#ifndef CHOOSEMENU_H
#define CHOOSEMENU_H

#include <QWidget>

namespace Ui {
class ChooseMenu;
}

class ChooseMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseMenu(QWidget *parent = nullptr);
    ~ChooseMenu();

private slots:
    //排序可视化界面
    void on_KnowButton_clicked();
    //排序信息可视化界面
    void on_BestwayButton_clicked();

private:
    Ui::ChooseMenu *ui;
};

#endif // CHOOSEMENU_H

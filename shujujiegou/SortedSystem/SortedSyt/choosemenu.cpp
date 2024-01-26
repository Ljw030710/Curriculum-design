#include "choosemenu.h"
#include "ui_choosemenu.h"
#include "MainUI.h"
#include "ShowData.h"
ChooseMenu::ChooseMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChooseMenu)
{
    ui->setupUi(this);
}

ChooseMenu::~ChooseMenu()
{
    delete ui;
}

void ChooseMenu::on_KnowButton_clicked()
{
    MainUI *Mainui = new MainUI();
    Mainui->show();
}


void ChooseMenu::on_BestwayButton_clicked()
{
    ShowData *Showdata = new ShowData();
    Showdata->show();
}


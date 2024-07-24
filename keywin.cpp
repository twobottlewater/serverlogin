#include "keywin.h"
#include "ui_keywin.h"

KeyWin::KeyWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyWin)
{
    ui->setupUi(this);
}

KeyWin::~KeyWin()
{
    delete ui;
}

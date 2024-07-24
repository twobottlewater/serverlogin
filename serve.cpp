#include "serve.h"
#include "ui_serve.h"
#include "receive.h"
#include <QMessageBox>

serve::serve(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::serve)
{
    ui->setupUi(this);
}

serve::~serve()
{
    delete ui;
}


void serve::on_loginBt_clicked()
{

    //设置管理员账号为666,密码为123456；
    if(ui->userEdit->text().trimmed()=="666"&&ui->passEdit->text().trimmed()=="123456")
    {
        //餐桌号与密码登录正确时，提示登陆成功
        QMessageBox::question(this,tr("提示"),tr("登录成功"),QMessageBox::Yes,QMessageBox::No);

    }

    else
    {
     //用户餐桌或密码 出现错误时，弹出警告“并显示用户名和密码错误”
        QMessageBox::question(this,tr("警告"),tr("管理员账号或密码错误"),QMessageBox::Yes,QMessageBox::No);
        return;
    }

    //创建另一个界面对象
    receive *v1=new receive();
    v1->show();
    this->close();



}

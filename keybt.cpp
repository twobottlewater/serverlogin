#include "keybt.h"
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>

KeyBt::KeyBt(QWidget *parent):QPushButton(parent)
{
    //把本按钮的点击信号与槽函数关联
    connect(this, &KeyBt::clicked, this, &KeyBt::button_clicked);
}

void KeyBt::button_clicked()
{
    QString ch = this->text();
    //创建一个按键事件
    QKeyEvent *akey = new QKeyEvent(QKeyEvent::KeyPress,ch.at(0).toLatin1(),Qt::NoModifier,ch);
    //发送事件--派发
    QApplication::postEvent(QApplication::focusWidget(),akey);
}

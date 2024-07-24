#ifndef RECEIVE_H
#define RECEIVE_H

#include <QMainWindow>
#include <QTableWidget>


#include <QTableWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork/qtcpserver.h>




namespace Ui {
class receive;
}

class receive : public QMainWindow
{
    Q_OBJECT

public:
    explicit receive(QWidget *parent = nullptr);
    ~receive();

private slots:
    void client_link();
    void read_data();
    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::receive *ui;
    QTcpServer mser;
    QTcpSocket *msoc;
    QTableWidget *tw;
    QString	neuminfo;	//客户端菜单头信息
    QString clientinfo;		//客户服务信息
    int food_num;		//食物的数量

};

#endif // RECEIVE_H


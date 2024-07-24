#include "receive.h"
#include "ui_receive.h"

#include <QTableWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QByteArray>
#include <QMessageBox>
#include<QDebug>

#include <QtNetwork/QTcpSocket>

receive::receive(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::receive)
{
    ui->setupUi(this);
    this->mser.listen(QHostAddress::AnyIPv4, 50001);

    connect(&mser, &QTcpServer::newConnection, this, &receive::client_link);
}

receive::~receive()
{
    delete ui;
}
void receive::client_link()
{
    qDebug() << "客户端链接";
    //获取用户套接字
    msoc = mser.nextPendingConnection();
    connect(msoc, &QTcpSocket::readyRead, this, &receive::read_data);
}

void receive::read_data()
{
       QTcpSocket *now = qobject_cast<QTcpSocket *>(sender());
       if (!now)
           return;

       QByteArray clientData = now->readAll();
       QString message = QString::fromUtf8(clientData);

        // 检查是否是服务请求
        if (message.contains("号桌子需要服务")) {
          ui->listWidget->addItem(message);
          return;
        }
        // 检查是否是支付请求
        if (message.startsWith("B."))
        {
            QStringList lines = message.split("\n");
            for (const QString &line : lines)
            {
                 ui->listWidget_2->addItem(line);
            }
            return;
        }


        //json解析重要的
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(clientData, &parseError);

       if (parseError.error != QJsonParseError::NoError) {
           qDebug() << "JSON parse error:" << parseError.errorString();
           return;
       }

       QJsonObject rootObj = doc.object();

       // 获取餐桌号和就餐人数
       int tableNumber = rootObj.value("餐桌号").toInt();
       int dineNumber = rootObj.value("就餐人数").toInt();
       QJsonArray orderArray = rootObj.value("订单").toArray();
       double totalPrice = rootObj.value("总价").toDouble();

       tw = new QTableWidget();
       ui->tabWidget->addTab(tw, QString::number(tableNumber) + "号桌");
       tw->setColumnCount(3);
       tw->setRowCount(orderArray.size()+2);
       tw->setHorizontalHeaderLabels(QStringList() << "菜名" << "数量" << "单价");
        int i;
       for (i = 0; i < orderArray.size(); ++i) {
           QJsonObject orderObj = orderArray.at(i).toObject();
           QString foodName = orderObj.value("菜名").toString();
           int quantity = orderObj.value("数量").toInt();
           double price = orderObj.value("单价").toDouble();

           tw->setItem(i, 0, new QTableWidgetItem(foodName));
           tw->setItem(i, 1, new QTableWidgetItem(QString::number(quantity)));
           tw->setItem(i, 2, new QTableWidgetItem(QString::number(price, 'f', 2)));
       }
       // 在最后一行显示总价
         tw->setItem(orderArray.size(), 0, new QTableWidgetItem("总价"));
         tw->setItem(orderArray.size(), 1, new QTableWidgetItem(""));
         tw->setItem(orderArray.size(), 2, new QTableWidgetItem(QString::number(totalPrice, 'f', 2)));


         //再加一行显示就餐人数
         tw->setItem(orderArray.size()+1, 0, new QTableWidgetItem("就餐人数"));
         tw->setItem(orderArray.size()+1, 1, new QTableWidgetItem(QString::number(dineNumber)));
         tw->setItem(orderArray.size()+1, 2, new QTableWidgetItem(""));
}

void receive::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}


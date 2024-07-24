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

    this->neuminfo.clear();
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
    QTcpSocket *now = (QTcpSocket *)sender();
    clientinfo = now->readAll();
    if(clientinfo.at(0) == (QChar)'A'){
        QStringList now = clientinfo.split(".");
        ui->listWidget->addItem(now[1]);
        return;
    }
    else if(clientinfo.at(0) == (QChar)'B'){
        QStringList now = clientinfo.split(".");
        ui->listWidget_2->addItem(now[1]);
        return;
    }

    if(this->neuminfo.isEmpty()){
        neuminfo = clientinfo;
        QStringList tat = neuminfo.split(":");
        tw = new QTableWidget();
        ui->tabWidget->addTab(tw, tat[0]+"号桌");
        this->food_num = QString(tat.at(1)).toInt();
        tw->setColumnCount(3);
        tw->setRowCount(food_num);
        tw->setHorizontalHeaderLabels(QStringList()<<"菜名"<<"价格"<<"数量");
    }else{
        QString mdata = clientinfo;
        qDebug() << mdata;
        QJsonParseError erro;
        QByteArray barr = mdata.toUtf8();
        QJsonDocument docu = QJsonDocument::fromJson(barr, &erro);
        if(erro.error != QJsonParseError::NoError){
            qDebug() << "not json data";
            return;
        }
        QJsonObject obje = docu.object();
        QStringList tat = this->neuminfo.split(":");
        QJsonArray arra = obje.value(tat.at(0)).toArray();
        for(int i=0; i<this->food_num; i++)
        {
            QJsonObject objarr = arra.at(i).toObject();
            this->tw->setItem(i, 0, new QTableWidgetItem(objarr.value("菜名").toString()));
            this->tw->setItem(i, 1, new QTableWidgetItem(objarr.value("价格").toString()));
            this->tw->setItem(i, 2, new QTableWidgetItem(QString::number(objarr.value("数量").toInt())));
        }
        neuminfo.clear();
        food_num = 0;
    }
}

void receive::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}


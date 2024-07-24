#ifndef KEYBT_H
#define KEYBT_H

#include <QObject>
#include <QPushButton>
class KeyBt : public QPushButton
{
    Q_OBJECT
public:
    explicit KeyBt(QWidget *parent = nullptr);
protected slots:
    void button_clicked();
};

#endif // KEYBT_H

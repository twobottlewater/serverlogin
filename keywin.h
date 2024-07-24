#ifndef KEYWIN_H
#define KEYWIN_H

#include <QWidget>

namespace Ui {
class KeyWin;
}

class KeyWin : public QWidget
{
    Q_OBJECT

public:
    explicit KeyWin(QWidget *parent = nullptr);
    ~KeyWin();

private:
    Ui::KeyWin *ui;
};

#endif // KEYWIN_H

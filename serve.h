#ifndef SERVE_H
#define SERVE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class serve; }
QT_END_NAMESPACE

class serve : public QMainWindow
{
    Q_OBJECT

public:
    serve(QWidget *parent = nullptr);
    ~serve();

private slots:
    void on_loginBt_clicked();

private:
    Ui::serve *ui;
};
#endif // SERVE_H

#include "serve.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serve w;
    w.show();
    return a.exec();
}

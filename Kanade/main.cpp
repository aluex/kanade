#include "mainwindow.h"
#include "kanade.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow *m = new MainWindow;
    m-> show();
    //QWidget *kanade = new Kanade;
    //kanade -> show();
    return app.exec();
}

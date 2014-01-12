#include "mainwindow.h"
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow *m = new MainWindow;
    m-> show();
    return app.exec();
}
/*
#include "kanade.h"
#include <QApplication>
#include <QScrollArea>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QScrollArea area;
    Kanade w;
//    w.show();
    area.setWidget(&w);
    area.setBackgroundRole(QPalette::Dark);
    area.show();
    area.ensureWidgetVisible(&w);

    return a.exec();
}
*/

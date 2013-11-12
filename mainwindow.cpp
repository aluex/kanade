#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kanade.h"
#include "color_wheel.hpp"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QHBoxLayout *mainLayout = new QHBoxLayout(this);
    //Kanade *k = new Kanade(this);
    //setCentralWidget(k);
    //k->setGeometry(0,0,800,800);
    //Color_Wheel *c = new Color_Wheel;
    //ui->verticalLayout->addWidget(c);
    //ui->verticalLayout->addWidget(c);
    //ui->horizontalLayout->addWidget(k);
    //setLayout(mainLayout);
    setWindowTitle(tr("Kanade2"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

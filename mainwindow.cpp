#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kanade.h"
#include "color_wheel.hpp"
#include <QHBoxLayout>

#include "presets.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->colorWheelholder, SIGNAL(colorChanged(QColor)), ui->canvasHolder, SLOT(setCurrentColor(QColor)));
    connect(ui->hSb_Width, SIGNAL(valueChanged(int)), ui->canvasHolder, SLOT(setWidth(int)));
    connect(ui->hSb_Opacity, SIGNAL(valueChanged(int)), ui->canvasHolder, SLOT(setOpacity(int)));
    ui->hSb_Opacity->setValue(PRE_OPACITY);
    ui->hSb_Width->setValue(PRE_WIDTH);
    ui->colorWheelholder->setColor(PRE_COLOR);

    setWindowTitle(tr("Kanade2"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

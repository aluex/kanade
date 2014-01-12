#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "presets.h"
#include <QMessageBox>
#include <QToolBar>
#include <QFileDialog>
#include <QInputDialog>
#include <qlineedit.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui -> Width_Bar, SIGNAL(valueChanged(int)), ui -> canvasHolder, SLOT(setWidth(int)));
    connect(ui -> Opacity_Bar, SIGNAL(valueChanged(int)), ui -> canvasHolder, SLOT(setOpacity(int)));
    connect(ui -> colorWheel, SIGNAL(colorChanged(QColor)), ui -> canvasHolder, SLOT(setCurrentColor(QColor)));
    connect(ui -> Pencil_Button, SIGNAL(clicked()), ui -> canvasHolder, SLOT(setPenPencil()));
    connect(ui -> Eraser_Button, SIGNAL(clicked()), ui -> canvasHolder, SLOT(setPenEraser()));
    connect(ui -> canvasHolder, SIGNAL(httpGeneratorFailed(QString)), this, SLOT(httpFailed(QString)));
    ui -> Width_Bar -> setValue(PRE_WIDTH);
    ui -> Opacity_Bar -> setValue(PRE_OPACITY);
    ui -> colorWheel -> setColor(PRE_COLOR);
    fileMenu = menuBar()->addMenu(tr("&File"));  //Followed by all the actions in fileMenu

    newAction = new QAction(tr("&New"), this);
    newAction -> setShortcut(QKeySequence::New);
    newAction -> setStatusTip(tr("New a file."));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    fileMenu -> addAction(newAction);

    openAction = new QAction(tr("&Load"), this);
    openAction -> setShortcut(QKeySequence::Open);
    openAction -> setStatusTip(tr("Open a file."));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    fileMenu -> addAction(openAction);

    saveAction = new QAction(tr("&Save"), this);
    saveAction -> setShortcut(QKeySequence::Save);
    saveAction -> setStatusTip(tr("Save a file."));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    fileMenu -> addAction(saveAction);

    networkMenu = menuBar() -> addMenu(tr("&Network"));

    connectAction = new QAction(tr("&Connect"), this);
    connectAction -> setStatusTip(tr("Connect to server"));
    connect(connectAction, SIGNAL(triggered()), this, SLOT(connectToServer()));
    networkMenu -> addAction(connectAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    ui -> canvasHolder -> isModified = false;
    setWindowTitle(tr("%1[*] - %2").arg(curFile).arg(tr("Kanade")));
}

void MainWindow::newFile()
{
    if (ui -> canvasHolder -> isModified)
    {
        int msgBox = QMessageBox::warning(this, tr("Kanade"),
                                          tr("The document has been modified.\n""Do you want to save your changes?"),
                                          QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if ((msgBox == QMessageBox::Yes) && save())
        {
            ui -> canvasHolder -> clear();
            setCurrentFile("");
            ui -> canvasHolder -> isModified = false;
        }
        else if (msgBox == QMessageBox::No)
             {
                 ui -> canvasHolder -> clear();
                 setCurrentFile("");
                 ui -> canvasHolder -> isModified = false;

             }
             else
             {
             };
    }
}

void MainWindow::open()
{
    if (ui -> canvasHolder -> isModified)
    {
        int msgBox = QMessageBox::warning(this, tr("Kanade"),
                                          tr("The document has been modified.\n""Do you want to save your changes?"),
                                          QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if ((msgBox == QMessageBox::Yes) && save())
        {
            QString fileName = QFileDialog::getOpenFileName(this, tr("Open Kanade"), tr("Kanade files (*.knd)"));
            if (!fileName.isEmpty())
                openFile(fileName);
          //  ui -> canvasHolder -> clear();
            //setCurrentFile("");
            //ui -> canvasHolder -> isModified = false;
        }
        else if (msgBox == QMessageBox::No)
             {
                 ui -> canvasHolder -> clear();
                 setCurrentFile("");
                 ui -> canvasHolder -> isModified = false;

             }
             else
             {
             };
    }
    else
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Kanade"), tr("Kanade files (*.knd)"));
        if (!fileName.isEmpty())
            openFile(fileName);
    }
}

bool MainWindow::openFile(const QString &fileName)
{
    if (!ui -> canvasHolder -> readFile(fileName))
    {
        //statusBar() -> shsowMessage(tr("Loading canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    //statusBar() -> showMessage(tr("File loaded"), 2000);
    return true;
}


bool MainWindow::save()
{
    if (curFile.isEmpty())
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

bool MainWindow::saveFile(const QString &fileName)
{
    if (!ui -> canvasHolder -> writeFile(fileName))
    {
        //statusBar() -> showMessage(tr("Saving canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    //statusBar() -> showMessage(tr("File saved", 2000));
    return true;
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Kanade"), ".", tr("Kanade files (*.knd)"));
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

void MainWindow::httpFailed(QString s)
{
    int msgBox = QMessageBox::warning(this, tr("Kanade"),
                                      s + tr("Connection Failed."),
                                      QMessageBox::Ok);
}

void MainWindow::connectToServer()
{
    QString serverName = QInputDialog::getText(this, tr("Kanade"), tr("Please enter the servername:"));
    if (!serverName.isEmpty())
    {
        ui -> canvasHolder -> httpGenerator(serverName);

    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void newFile();
    bool save();
    bool saveAs();
    void open();
    void httpFailed(QString s = "");
    void connectToServer();
private:
    void setCurrentFile(const QString &fileName);
    bool openFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    QString curFile;
    QMenu *fileMenu;
    QStatusBar *statusBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QMenu *networkMenu;
    QAction *connectAction;
    Ui::MainWindow *ui;
signals:
    void serverNameEntered(const QString &serverName);
};

#endif // MAINWINDOW_H

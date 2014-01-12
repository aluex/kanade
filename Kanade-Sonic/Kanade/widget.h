#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QImage>
#include <QFile>
#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
class TabletSupport;

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QSize sizeHint() const;
    void drawLine_Tablet(const QPoint &start, const QPoint &end);
    void drawLine_Mouse(const QPoint &start, const QPoint &end);
    void drawLine_Tablet2(int x12, int y12, int x22, int y22, float w12, float w22, float opacity2, int msgPenType, QColor curColor2);
    void clear();
    bool writeFile(const QString &fileName);
    bool readFile(const QString &fileName);
    bool isModified;
    bool isConnected;
    int id;
    QString s, penType;
    QTimer timer;
    QNetworkAccessManager *networkManager;
    QNetworkAccessManager *receiveManager;
    QNetworkAccessManager *sendManager;
    QNetworkReply *currentReply;
    QNetworkReply *receiveReply;
    QNetworkReply *sendReply;
    QString serverUrl;
    QByteArray data1;
    int x;
    int sendXList[100000];
    int sendYList[100000];
    float sendPList[100000];
    int sendColor[2];
    float sendOpacity;
    int sendWidth;
    int sendPenType;
    int counter;
    int failCounter;
public slots:
    void setOpacity(int opac)
    {
        opacity = opac;
        curColor.setAlpha(opacity);
    }
    void setCurrentColor(QColor c)
    {
        curColor = c;
        curColor.setAlpha(opacity);
    }
    void setWidth(int w)
    {
        maxWidth = w;
    }
    void setPenPencil()
    {
        penType = "Pencil";
    }
    void setPenEraser()
    {
        penType = "Eraser";
    }
    void generatorOnResult(QNetworkReply* currentReply);
    void receiverOnResult(QNetworkReply* receiveReply);

    void httpGenerator(const QString &serverUrl);
    void httpReceiver();

    void httpSender();

protected:
    void paintEvent(QPaintEvent *ev);
    void tabletEvent(QTabletEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    TabletSupport *tabletSupport_;
    QImage *pic;
    QImage *pic2;
    bool drawing;// = false;
    QPoint lastPoint;
    QPoint nowPoint;
    QColor curColor;

    int i, opacity;
    float deltax, deltay , deltaw, j, lineNum, width, lastWidth, nowWidth;
    int maxWidth;

    //Http

signals:
    void httpGeneratorFailed(QString s = "");
    void httpStart();
    void sendAbled();
};

#endif // WIDGET_H

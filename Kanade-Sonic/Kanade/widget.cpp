#include "widget.h"
#include <QTabletEvent>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include <QtGui>
#include <QFile>
#include "presets.h"
#include <QMessageBox>
#include "../tabletsupport.h"
#include <QApplication>
#include <QIODevice>
#include <QObject>

#include <QNetworkAccessManager>
#include <QUrl>;
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtScript>
#include <QTimer>
#include <QJsonArray>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    tabletSupport_(new TabletSupport(this)),
    pic(new QImage(PRE_HEIGHT, PRE_WIDTH, QImage::Format_ARGB32))
{
    networkManager = new QNetworkAccessManager(this);
    receiveManager = new QNetworkAccessManager(this);
    sendManager = new QNetworkAccessManager(this);
    timer.setSingleShot(false);
    timer.start(500);
    pic2 = new QImage(PRE_HEIGHT, PRE_WIDTH, QImage::Format_ARGB32);
    pic2 -> fill(qRgba(255,255,255,255));
    pic -> fill(qRgba(255, 255, 255, 255));
    drawing = false;
    isModified = false;
    isConnected = false;
    failCounter = 0;
    penType = "Pencil";
    tabletSupport_->start();
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(generatorOnResult(QNetworkReply*)));
    connect(&timer, SIGNAL(timeout()), this,  SLOT(httpReceiver()));
    connect(receiveManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiverOnResult(QNetworkReply*)));
}

Widget::~Widget()
{
    delete tabletSupport_;
    delete pic;
}

QSize Widget::sizeHint() const
{
    return QSize(1024,768);
}

void Widget::clear()
{
    pic -> fill(qRgba(255, 255, 255, 0));
}


bool Widget::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Kanade"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_1);
    out << quint32(MAGICNUMBER);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    for (int row = 0; row < PRE_HEIGHT; row ++)
    {
        for (int column = 0; column < PRE_WIDTH; column++)
        {
            out << quint16(row) << quint16(column)
                << quint8(qAlpha(pic -> pixel(row, column)))
                << quint8(qRed(pic -> pixel(row, column)))
                << quint8(qGreen(pic -> pixel(row, column)))
                << quint8(qBlue(pic -> pixel(row, column)));
        }
    }
    QApplication::restoreOverrideCursor();
    return true;
}

bool Widget::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Kanade"),
                             tr ("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_1);
    quint32 magic;
    in >> magic;
    if (magic != MAGICNUMBER)
    {
        QMessageBox::warning(this, tr("Kanade"), tr("The type of file is not supported by Kanade"));
        return false;
    }
    clear();
    quint16 row;
    quint16 column;
    quint8 alpha;
    quint8 red;
    quint8 green;
    quint8 blue;
    QApplication::setOverrideCursor(Qt::WaitCursor);
    while(!in.atEnd())
    {
        in >> row >> column >> alpha >> red >> green >> blue;
        pic -> setPixel(row, column, qRgba(red, green, blue, alpha));
    }
    QApplication::restoreOverrideCursor();
    return true;
}

//Paint
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QColor white;
    white.setAlpha(255);
    white.setRed(255);
    white.setBlue(255);
    white.setGreen(255);
    painter.setPen(QPen(white, 10000, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0,0,1024,768);
    painter.drawImage(0,0,*pic);
}

void Widget::drawLine_Tablet(const QPoint &start, const QPoint &end)
{
    QColor nowColor = curColor;
    isModified = true;
    QPainter p(pic);
    //p.setCompositionMode(QPainter::CompositionMode_Plus);
    if (penType == "Pencil")
    {
 //       p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(QPen(curColor, width, Qt::SolidLine, Qt::RoundCap));
        p.setBrush(QBrush(curColor));
    }
    else if (penType == "Eraser")
    {
        //p.setRenderHint(QPainter::Antialiasing, true);
       // p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        QColor eraserColor;
       // eraserColor.setAlpha(255 - opacity);
        eraserColor.setAlpha(opacity);
        eraserColor.setBlue(255);
        eraserColor.setGreen(255);
        eraserColor.setRed(255);
        nowColor = eraserColor;
        p.setPen(QPen(eraserColor, width, Qt::SolidLine, Qt::RoundCap));
        p.setBrush(QBrush(eraserColor));

    }
    int opa = nowColor.alpha();
    lineNum = sqrt((lastPoint.x() - nowPoint.x()) * (lastPoint.x() - nowPoint.x())+
            (lastPoint.y() - nowPoint.y()) * (lastPoint.y() - nowPoint.y())) / 0.5 ;
    if (lineNum >= 1)
    {
        deltax = (nowPoint.x() - lastPoint.x()) / lineNum;
        deltay = (nowPoint.y() - lastPoint.y()) / lineNum;
        deltaw = (nowWidth - lastWidth) / lineNum;
        i = 1;
        while (i <= lineNum)
        {
            nowColor.setAlpha(int(float(opa) *3/ (lastWidth + (i - 1) * deltaw)));
            p.setPen(QPen(nowColor, lastWidth + (i - 1) * deltaw, Qt::SolidLine, Qt::RoundCap));
            p.drawLine(lastPoint.x() + (i - 1) * deltax, lastPoint.y() + (i - 1) * deltay,
                       lastPoint.x() + i * deltax, lastPoint.y() + i * deltay);
            i = i + 1;
        }
    }
    lastPoint = nowPoint;

}

//Tablet

void Widget::tabletEvent(QTabletEvent *event)
{
    switch(event -> type())
    {
    case QEvent::TabletPress:
        if(!drawing)
        {
            lastPoint = event -> pos();
            lastWidth = maxWidth * event -> pressure();
            counter = 0;
            sendXList[counter] = lastPoint.x();
            sendYList[counter] = lastPoint.y();
            sendPList[counter] = event -> pressure();
            sendOpacity = float(float(opacity) / float(255));
            sendWidth = maxWidth;
            if (penType == "Pencil")
            {
                sendPenType = 0;
                sendColor[0] = curColor.red();
                sendColor[1] = curColor.green();
                sendColor[2] = curColor.blue();
            }
            else if (penType == "Eraser")
            {
                sendPenType = 2;
                sendColor[0] = 255;
                sendColor[1] = 255;
                sendColor[2] = 255;
            }
            drawing = true;
        }
        break;
    case QEvent::TabletMove:
        if(drawing && lastPoint != event -> pos())
        {
            nowWidth = maxWidth * event -> pressure();
            nowPoint = event -> pos();
            drawLine_Tablet(lastPoint, nowPoint);
            lastPoint = nowPoint;
            lastWidth = nowWidth;
            counter = counter + 1;
            sendXList[counter] = lastPoint.x();
            sendYList[counter] = lastPoint.y();
            sendPList[counter] = event -> pressure();
        }
        break;
    case QEvent::TabletRelease:
        if(drawing)
        {
            drawing = false;
            if (isConnected)
                httpSender();
        }
        break;
    default:
        break;
    }
    event -> accept();
    update();
}


//Mouse

void Widget::drawLine_Mouse(const QPoint &start, const QPoint &end)
{
    QColor nowColor = curColor;
    isModified = true;
    QPainter p(pic);

     if (penType == "Pencil")
     {
         p.setRenderHint(QPainter::Antialiasing, true);
         p.setPen(QPen(curColor, width, Qt::SolidLine, Qt::RoundCap));
         p.setBrush(QBrush(curColor));
     }
     else if (penType == "Eraser")
     {
         p.setRenderHint(QPainter::Antialiasing, true);
         p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
         QColor eraserColor;
         eraserColor.setAlpha(255 - opacity);
         eraserColor.setBlue(255);
         eraserColor.setGreen(255);
         eraserColor.setRed(255);
         nowColor = eraserColor;
         p.setPen(QPen(eraserColor, width, Qt::SolidLine, Qt::RoundCap));
         p.setBrush(QBrush(eraserColor));

     }
    lineNum = sqrt((lastPoint.x() - nowPoint.x()) * (lastPoint.x() - nowPoint.x())+
            (lastPoint.y() - nowPoint.y()) * (lastPoint.y() - nowPoint.y())) / 0.5 ;
    if (lineNum >= 1)
    {
        deltax = (nowPoint.x() - lastPoint.x()) / lineNum;
        deltay = (nowPoint.y() - lastPoint.y()) / lineNum;
        i = 1;
        while (i <= lineNum)
        {
            p.drawLine(lastPoint.x() + (i - 1) * deltax, lastPoint.y() + (i - 1) * deltay,
                       lastPoint.x() + i * deltax, lastPoint.y() + i * deltay);
            i = i + 1;
        }
    }
    lastPoint = nowPoint;

}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton) && (!drawing))
    {
        lastPoint = event->pos();
        drawing = true;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if  ((event->buttons() & Qt::LeftButton) && drawing )
    {
        nowPoint = event->pos();
        drawLine_Mouse(lastPoint,nowPoint);
        lastPoint = nowPoint;
        update();
    };
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    drawing = false;
}


//Http
void Widget::httpGenerator(const QString &serverName)
{
    serverUrl = serverName;
    QUrl url(serverUrl + "login");
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager -> get(request);
}

void Widget::generatorOnResult(QNetworkReply *)
{
    if (currentReply -> error() != QNetworkReply::NoError)
    {
        emit httpGeneratorFailed();
        return;
    }
    QByteArray data = currentReply -> readAll();
    QJsonParseError jsonError;
    QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (json.isObject())
        {
            QJsonObject obj = json.object();
            s = obj["s"].toString();
            if (s == "ok")
            {
                id = int(obj["id"].toDouble());
                emit httpStart();
                isConnected = true;
                return;
            }
        }
    }
    emit httpGeneratorFailed("Failed to call login. ");
    return;
}

void Widget::httpReceiver()
{
    timer.start(500);
    if (!isConnected) return;
    QNetworkRequest request;
    QUrl url(serverUrl + "breathe");
    request.setUrl(url);
    QJsonObject json;
    json.insert("id", id);
    QJsonDocument document;
    document.setObject(json);
    QByteArray content = document.toJson(QJsonDocument::Compact);
    receiveReply = receiveManager -> post(request, content);
}

void Widget::receiverOnResult(QNetworkReply*)
{
    if (receiveReply -> error() != QNetworkReply::NoError)
    {
        emit httpGeneratorFailed("Failed to call Breathe. ");
        return;
    }
    QByteArray data = receiveReply -> readAll();
    data1 = data;
    QJsonParseError jsonError;
    QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (json.isObject())
        {
            QJsonObject obj = json.object();
            int msgNum = int(obj["msgNum"].toDouble());
            QJsonArray msgList = obj["msgList"].toArray();
            for (int i = 0; i <= msgNum - 1; i++)
            {
                QJsonObject msgObj = msgList[i].toObject();
                QString msgType = msgObj["msgType"].toString();
                if (msgType == "history")
                {
                    int msgWidth = int(msgObj["size"].toDouble());
                    float msgOpacity = float(msgObj["opacity"].toDouble());
                    int msgPenType = int(msgObj["brushNo"].toDouble());
                    QJsonArray msgX = msgObj["XList"].toArray();
                    QJsonArray msgY = msgObj["YList"].toArray();
                    QJsonArray msgP = msgObj["PList"].toArray();
                    QJsonArray msgC = msgObj["colors"].toArray();
                    QColor curColor2;
                    curColor2.setRed(int(msgC[0].toDouble()));
                    curColor2.setGreen(int(msgC[1].toDouble()));
                    curColor2.setBlue(int(msgC[2].toDouble()));
                    curColor2.setAlpha(int(msgOpacity * 255));
                    for (int j = 0; j < msgX.size() - 1; j++)
                    {
                        drawLine_Tablet2(int(msgX[j].toDouble()),
                                         int(msgY[j].toDouble()),
                                         int(msgX[j + 1].toDouble()),
                                         int(msgY[j + 1].toDouble()),
                                         float(msgP[j].toDouble()) * msgWidth,
                                         float(msgP[j + 1].toDouble()) * msgWidth,
                                         msgOpacity, msgPenType,
                                         curColor2);
                    }
                }
            }
            return;
        }
    }
    failCounter = failCounter + 1;
    if (failCounter = 30)
    {
        emit httpGeneratorFailed("Failed to call breathe. ");
        isConnected = false;
    }
    return;
}



void Widget::drawLine_Tablet2(int x12, int y12, int x22, int y22, float w12, float w22, float opacity2, int msgPenType, QColor curColor2)
{
    x = x12;
    //emit httpGeneratorFailed("yahoo");
    isModified = true;
    QPainter p(pic);
    QColor nowColor2 = curColor2;
    if (msgPenType == 2)
    {
        p.setRenderHint(QPainter::Antialiasing, true);
        //p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        QColor eraserColor2;
        eraserColor2.setAlpha(curColor2.alpha());
        eraserColor2.setBlue(255);
        eraserColor2.setGreen(255);
        eraserColor2.setRed(255);
        nowColor2 = eraserColor2;
        p.setPen(QPen(eraserColor2, w12, Qt::SolidLine, Qt::RoundCap));
        p.setBrush(QBrush(eraserColor2));

    }
    else
    {
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(QPen(curColor2, w12, Qt::SolidLine, Qt::RoundCap));
        p.setBrush(QBrush(curColor2));
    };
    float lineNum2 = sqrt((x12 - x22) * (x12 - x22)+
            (y12 - y22) * (y12 - y22)) / 0.5 ;
    if (lineNum2 >= 1)
    {
        float deltax2 = (x22 - x12) / lineNum2;
        float deltay2 = (y22 - y12) / lineNum2;
        float deltaw2 = (w22 - w12) / lineNum2;
        int i = 1;
        while (i <= lineNum2)
        {
            nowColor2.setAlpha(int(opacity2 * 3 / (w12 + (i - 1) * deltaw2) * 255));
            p.setPen(QPen(nowColor2, w12 + (i - 1) * deltaw2, Qt::SolidLine, Qt::RoundCap));
            p.drawLine(x12 + (i - 1) * deltax2, y12 + (i - 1) * deltay2,
                       x12 + i * deltax2, y12 + i * deltay2);
            i = i + 1;
        }
    }
   /* p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(curColor, w12, Qt::SolidLine, Qt::RoundCap));
    p.setBrush(QBrush(curColor));
    p.drawLine(x12,y12,x22,y22);*/
}

void Widget::httpSender()
{
    int i;
    QJsonObject json;
    json.insert("id", id);
    json.insert("layer", 0);
    json.insert("size", sendWidth);
    json.insert("opacity", double(opacity)/double(255));
    json.insert("wacomOpacity", false);
    json.insert("wacomSize", true);
    json.insert("brushNo", sendPenType);
    QJsonArray XList;
    QJsonArray YList;
    QJsonArray PList;
    for (i = 0; i <= counter; i++)
    {
        XList.insert(i, sendXList[i]);
        YList.insert(i, sendYList[i]);
        PList.insert(i, sendPList[i]);
    }
    QJsonArray CList;
    CList.insert(0, sendColor[0]);
    CList.insert(1, sendColor[1]);
    CList.insert(2, sendColor[2]);
    json.insert("XList", XList);
    json.insert("YList", YList);
    json.insert("PList", PList);
    json.insert("colors", CList);
    QNetworkRequest request;
    QUrl url(serverUrl + "draw");
    request.setUrl(url);
    QJsonDocument document;
    document.setObject(json);
    QByteArray content = document.toJson(QJsonDocument::Compact);
   // emit httpGeneratorFailed(QString(content));
    sendReply = sendManager -> post(request, content);

}

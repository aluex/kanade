#include <QtGui>
#include <Windows.h>
#include "kanade.h"
#include "presets.h"

//API

//#include <msgpack.h>

//API
HCTX Kanade::TabletInit()
{
    LOGCONTEXT myDevice;
    WTInfo(WTI_DEFCONTEXT, 0, &myDevice);

    //wsprintf(myDevice.lcName,"WinTab test %x", AfxGetApp()->m_hInstance);
    myDevice.lcOptions |= CXO_MESSAGES;
    myDevice.lcPktData = PACKETDATA;
    myDevice.lcPktMode = PACKETMODE;
    myDevice.lcMoveMask = PACKETDATA;
    myDevice.lcBtnUpMask = myDevice.lcBtnDnMask;  //Tablet 规模大小默认设定
    myDevice.lcOutOrgX = myDevice.lcOutOrgY = 0;
    myDevice.lcOutExtX = myDevice.lcInExtX;
    myDevice.lcOutExtY = myDevice.lcInExtY;
    //m_tabletSize = CSize(myDevice.lcOutExtX, myDevice.lcOutExtY);
    return WTOpen((HWND)this -> winId(), &myDevice, TRUE);


}

Kanade::Kanade(QWidget *parent)
	:QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    curColor = PRE_COLOR; opacity = PRE_OPACITY ; width = PRE_WIDTH;
	zoom = 1;
    image = QImage(PRE_HEIGHT, PRE_WIDTH, QImage::Format_ARGB32);
    image2 = QImage(PRE_HEIGHT, PRE_WIDTH, QImage::Format_ARGB32);
    image.fill(qRgba(255, 255, 255, 255));
}

QSize Kanade::sizeHint() const
{
	QSize size = zoom * image.size();
	return size;
}

void Kanade::setPenColor(const QColor &newColor)
{
    curColor = newColor;
}

void Kanade::setPicImage(const QImage &newImage)
{
	if (newImage != image)
	{
		image = newImage.convertToFormat(QImage::Format_ARGB32);
		update();
		updateGeometry();
	}
}

void Kanade::setZoomFactor(int newZoom)
{
	if (newZoom < 1)
		newZoom = 1;
	if (newZoom != zoom)
	{
		zoom = newZoom;
		update();
		updateGeometry();
	}
}

void Kanade::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
    painter.drawImage(0, 0, image);
}

QRect Kanade::pixelRect(int i, int j) const
{
    return QRect(zoom * i, zoom * j, zoom, zoom);
}

void Kanade::mouseReleaseEvent(QMouseEvent *event)
{
    drawing = false;
}

void Kanade::drawLine(const QPoint &start, const QPoint &end)
{
    QPainter p(&image);
 //   p.begin();
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(curColor, width, Qt::SolidLine, Qt::RoundCap));
    p.setBrush(QBrush(curColor));
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

void Kanade::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
	{
        lastPoint = event->pos();
        /*GetCursorPos(&lastPoint1);
        lastPoint.setX(lastPoint1.x);
        lastPoint.setY(lastPoint1.y);*/
        drawing = true;

        //image2.fill(qRgba(255, 255, 255, 0));
       // image2 = image;
      //  tmpimage = image;
        //mouseMoveEvent();
        //setImagePixel(event->pos(), true);
	}
    else if (event->button() == Qt::RightButton)
    {
        setImagePixel(event->pos(), false);
    }
}

void Kanade::mouseMoveEvent(QMouseEvent *event)
{
    if  (/*(event->buttons() & Qt::LeftButton) &&*/ drawing )
	{
        /*GetCursorPos(&nowPoint1);
        nowPoint.setX(nowPoint1.x);
        nowPoint.setY(nowPoint1.y);*/
        nowPoint = event->pos();
        drawLine(lastPoint,nowPoint);
        lastPoint = nowPoint;
        update();
        //image = tmpimage;
	}
    /*else	if (event->buttons() & Qt::RightButton)
		{
			setImagePixel(event->pos(),false);
        }*/;
}

void Kanade::setImagePixel(const QPoint &pos, bool opaque)
{
	int i = pos.x() / zoom;
	int j = pos.y() / zoom;
	if (image.rect().contains(i,j))
	{
		if (opaque)
		{
			image.setPixel(i, j, penColor().rgba());
		}
		else
		{
            image.setPixel(i, j, qRgba(255, 255, 255, 255));
		}
		update(pixelRect(i,j));
	}
}


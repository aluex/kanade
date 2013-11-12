#include <QtGui>

#include "kanade.h"

#define PRE_WIDTH 1024
#define PRE_HEIGHT 1024

Kanade::Kanade(QWidget *parent)
	:QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	curColor = Qt::black;
	zoom = 1;
    image = QImage(PRE_HEIGHT, PRE_WIDTH, QImage::Format_ARGB32);
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
   // p.begin();
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    p.setBrush(QBrush(Qt::black));
    p.drawLine(start, end);
}

void Kanade::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
	{
        lastPoint = event->pos();
        drawing = true;
        //setImagePixel(event->pos(), true);
	}
    else if (event->button() == Qt::RightButton)
    {
        setImagePixel(event->pos(), false);
    }
}

void Kanade::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing )
	{
        drawLine(lastPoint, event->pos());
        //setImagePixel(event->pos(), true);
        lastPoint = event->pos();
        update();
	}
	else	if (event->buttons() & Qt::RightButton)
		{
			setImagePixel(event->pos(),false);
		};
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


#ifndef KANADE_H
#define KANADE_H

#include <QColor>
#include <QImage>
#include <QWidget>
//#include <QGraphicsView>

class Kanade: public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
	Q_PROPERTY(QImage picImage READ picImage WRITE setPicImage)
	Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)
public:
	Kanade(QWidget *parent = 0);
	
	void setPenColor(const QColor &newColor);
	
	QColor penColor() const 
	{
		return curColor;
	}

	void setZoomFactor(int newZoom);

	int zoomFactor() const
	{
		return zoom;
	}

	void setPicImage(const QImage &newImage);

	QImage picImage() const 
	{
        return image;
	}

	QSize sizeHint() const;

public slots:
    void setCurrentColor(QColor c)
    {
        curColor = c;
        curColor.setAlpha(opacity);
    }

    void setOpacity(int opac)
    {
        opacity = opac;
        curColor.setAlpha(opacity);
    }

    void setWidth(int w)
    {
        width = w;
    }


protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

private:
	void setImagePixel(const QPoint &pos, bool opaque);
    void drawLine(const QPoint &start, const QPoint &end);
	QRect pixelRect(int i, int j) const;
    QPoint lastPoint;
    QColor curColor;
    QImage image;
    int zoom, opacity, width;
    bool drawing;
};

#endif

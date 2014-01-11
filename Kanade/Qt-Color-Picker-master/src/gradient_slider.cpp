/**

@author Mattia Basaglia

@section License

    Copyright (C) 2013 Mattia Basaglia

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Color Widgets.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "gradient_slider.hpp"
#include <QPainter>
#include <QStyleOptionSlider>
#include "paint_border.hpp"

Gradient_Slider::Gradient_Slider(QWidget *parent) :
    QSlider(parent), back( Qt::darkGray, Qt::DiagCrossPattern )
{
    col_list.push_back(Qt::black);
    col_list.push_back(Qt::white);


    back.setTexture(QPixmap(QString(":/color_widgets/alphaback.png")));

    setOrientation(Qt::Horizontal);
}

void Gradient_Slider::setBackground(QBrush bg)
{
    back = bg;
    update();
}

void Gradient_Slider::setColors(QVector<QColor> bg)
{
    col_list = bg;
    update();
}

void Gradient_Slider::setGradient(QLinearGradient bg)
{
    col_list.clear();
    foreach(const QGradientStop& gs, bg.stops() )
    {
        col_list.push_back(gs.second);
    }
    update();
}

QLinearGradient Gradient_Slider::gradient() const
{
    int ior = orientation() == Qt::Horizontal ? 1 : 0;
    QLinearGradient lg(0,0,ior,1-ior);
    lg.setCoordinateMode(QGradient::StretchToDeviceMode);
    for(int i = 0; i < col_list.size(); i++)
        lg.setColorAt(double(i)/(col_list.size()-1),col_list[i]);
    return lg;
}

void Gradient_Slider::setFirstColor(QColor c)
{
    if ( col_list.empty() )
        col_list.push_back(c);
    else
        col_list.front() = c;
    update();
}

void Gradient_Slider::setLastColor(QColor c)
{

    if ( col_list.size() < 2 )
        col_list.push_back(c);
    else
        col_list.back() = c;
    update();
}

QColor Gradient_Slider::firstColor() const
{
    return col_list.empty() ? QColor() : col_list.front();
}

QColor Gradient_Slider::lastColor() const
{
    return col_list.empty() ? QColor() : col_list.back();
}


void Gradient_Slider::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    painter.setPen(Qt::NoPen);
    painter.setBrush(back);
    painter.drawRect(1,1,geometry().width()-2,geometry().height()-2);
    painter.setBrush(gradient());
    painter.drawRect(1,1,geometry().width()-2,geometry().height()-2);

    paint_tl_border(painter,size(),palette().color(QPalette::Mid),0);
    /*paint_tl_border(painter,size(),palette().color(QPalette::Dark),1);

    paint_br_border(painter,size(),palette().color(QPalette::Light),1);*/
    paint_br_border(painter,size(),palette().color(QPalette::Midlight),0);

    QStyleOptionSlider opt_slider;
    initStyleOption(&opt_slider);
    opt_slider.subControls = QStyle::SC_SliderHandle;
    if (isSliderDown())
        opt_slider.state |= QStyle::State_Sunken;
    style()->drawComplexControl(QStyle::CC_Slider, &opt_slider, &painter, this);



    /*QStyleOptionFrameV3 opt_frame;
    opt_frame.init(this);
    opt_frame.frameShape = QFrame::StyledPanel;
    opt_frame.rect = geometry();
    opt_frame.state = QStyle::State_Sunken;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);
    painter.translate(-geometry().topLeft());
    style()->drawControl(QStyle::CE_ShapedFrame, &opt_frame, &painter, this);*/

}

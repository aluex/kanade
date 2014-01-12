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
#ifndef GRADIENT_SLIDER_HPP
#define GRADIENT_SLIDER_HPP

#include <QSlider>

/**
 * \brief A slider that mover on top of a gradient
 */
class Gradient_Slider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(QBrush background READ background WRITE setBackground)
    Q_PROPERTY(QVector<QColor> colors READ colors WRITE setColors)
    Q_PROPERTY(QLinearGradient gradient READ gradient WRITE setGradient STORED false)
    Q_PROPERTY(QColor firstColor READ firstColor WRITE setFirstColor STORED false)
    Q_PROPERTY(QColor lastColor READ lastColor WRITE setLastColor STORED false)

private:
    QVector<QColor> col_list;
    QBrush back;

public:
    explicit Gradient_Slider(QWidget *parent = 0);

    /// Get the background, it's visible for transparent gradient stops
    QBrush background() const { return back; }
    /// Set the background, it's visible for transparent gradient stops
    void setBackground(QBrush bg);

    /// Get the colors that make up the gradient
    QVector<QColor> colors() const { return col_list; }
    /// Set the colors that make up the gradient
    void setColors(QVector<QColor> bg);

    /**
     * \brief Set the gradient
     * \note  Only the color order is preserved, all stops will be equally spaced
     */
    void setGradient(QLinearGradient bg);
    /// Get the gradient
    QLinearGradient gradient() const ;

    /**
     * Set the first color of the gradient
     *
     * If the gradient is currently empty it will create a stop with the given color
     */
    void setFirstColor(QColor c);
    /**
     * Set the last color of the gradient
     *
     * If the gradient is has less than two colors,
     * it will create a stop with the given color
     */
    void setLastColor(QColor c);
    /**
     * Get the first color
     *
     * Returns QColor() con empty gradient
     */
    QColor firstColor() const;
    /**
     * Get the last color
     *
     * Returns QColor() con empty gradient
     */
    QColor lastColor() const;
    
protected:
    void paintEvent(QPaintEvent *ev);
};

#endif // GRADIENT_SLIDER_HPP

/**
  
\file

\author Mattia Basaglia

\section License
This file is part of Knotter.

Copyright (C) 2012-2013  Mattia Basaglia

Knotter is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Knotter is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef COLOR_LIST_WIDGET_HPP
#define COLOR_LIST_WIDGET_HPP

#include "abstract_widget_list.hpp"

class Color_List_Widget : public Abstract_Widget_List
{
    Q_OBJECT

    Q_PROPERTY(QList<QColor> colors READ colors WRITE setColors NOTIFY colorsChanged )

private:
    QList<QColor> m_colors;
    QSignalMapper mapper;

public:
    explicit Color_List_Widget(QWidget *parent = 0);


    const QList<QColor>& colors() const { return m_colors; }
    void setColors(const QList<QColor>& cols);

    void swap(int a, int b);

    void append();

signals:
    void colorsChanged(const QList<QColor>&);

private slots:
    void emit_changed();
    void handle_removed(int);
    void color_changed(int row);

private:
   void  append_widget(int col);
};

#endif // COLOR_LIST_WIDGET_HPP

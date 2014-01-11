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
#ifndef COLOR_SELECTOR_HPP
#define COLOR_SELECTOR_HPP

#include "color_preview.hpp"

/**
 * Color preview that opens a color dialog
 */
class Color_Selector : public Color_Preview
{
    Q_OBJECT
    Q_ENUMS(Update_Mode)
    Q_PROPERTY(Update_Mode updateMode READ updateMode WRITE setUpdateMode )
    Q_PROPERTY(Qt::WindowModality dialogModality READ dialogModality WRITE setDialogModality )

public:
    enum Update_Mode {
        Confirm, ///< Update color only after the dialog has been accepted
        Continuous ///< Update color as it's being modified in the dialog
    };

private:
    Update_Mode  update_mode;
    class Color_Dialog* dialog;
    QColor old_color;

public:
    explicit Color_Selector(QWidget *parent = 0);

    void setUpdateMode(Update_Mode m);
    Update_Mode updateMode() const { return update_mode; }

    Qt::WindowModality dialogModality() const;
    void setDialogModality(Qt::WindowModality m);

public slots:
    void showDialog();

private:
    /// Connect/Disconnect colorChanged based on Update_Mode
    void connect_dialog();

    /// Disconnect from dialog update
    void disconnect_dialog();

private slots:
    void accept_dialog();
    void reject_dialog();
    void update_old_color(QColor c);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent * event);
    
};

#endif // COLOR_SELECTOR_HPP

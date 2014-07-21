/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef GRID_P_H
#define GRID_P_H

#include "item_p.h"

class GridPrivate;

class Grid : public Item
{
    Q_OBJECT

    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)
    Q_PROPERTY(int horizontalSpacing READ horizontalSpacing WRITE setHorizontalSpacing NOTIFY horizontalSpacingChanged)
    Q_PROPERTY(int verticalSpacing READ verticalSpacing WRITE setVerticalSpacing NOTIFY verticalSpacingChanged)

public:
    explicit Grid(QWidget *parent = 0);
    ~Grid();

    int columns() const;
    void setColumns(int columns);

    int spacing() const;
    void setSpacing(int spacing);

    int horizontalSpacing() const;
    void setHorizontalSpacing(int spacing);

    int verticalSpacing() const;
    void setVerticalSpacing(int spacing);

signals:
    void columnsChanged();
    void spacingChanged();
    void horizontalSpacingChanged();
    void verticalSpacingChanged();

protected:
    Grid(GridPrivate &dd, QWidget *parent = 0);

    virtual void componentComplete();

    Q_DECLARE_PRIVATE(Grid)

private:
    Q_DISABLE_COPY(Grid)
};

QML_DECLARE_TYPE(Grid)

#endif // GRID_P_H

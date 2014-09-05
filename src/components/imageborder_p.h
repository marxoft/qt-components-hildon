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
 
#ifndef IMAGEBORDER_P_H
#define IMAGEBORDER_P_H
 
#include <QObject>
#include <qdeclarative.h>

class ImageBorder : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int left READ left WRITE setLeft RESET resetLeft NOTIFY borderChanged)
    Q_PROPERTY(int right READ right WRITE setRight RESET resetRight NOTIFY borderChanged)
    Q_PROPERTY(int top READ top WRITE setTop RESET resetTop NOTIFY borderChanged)
    Q_PROPERTY(int bottom READ bottom WRITE setBottom NOTIFY resetBottom NOTIFY borderChanged)

public:
    explicit ImageBorder(QObject *parent = 0);
    ~ImageBorder();

    int left() const;
    void setLeft(int left);
    void resetLeft();

    int right() const;
    void setRight(int right);
    void resetRight();

    int top() const;
    void setTop(int top);
    void resetTop();

    int bottom() const;
    void setBottom(int bottom);
    void resetBottom();

signals:
    void borderChanged();

private:
    int m_left;
    int m_right;
    int m_top;
    int m_bottom;

    Q_DISABLE_COPY(ImageBorder)
};

#endif // IMAGEBORDER_P_H

QML_DECLARE_TYPE(ImageBorder)

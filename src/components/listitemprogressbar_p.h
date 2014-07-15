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

#ifndef LISTITEMPROGRESSBAR_P_H
#define LISTITEMPROGRESSBAR_P_H

#include "listitemcontent_p.h"
#include <QStyleOptionProgressBarV2>

class ListItemProgressBar : public ListItemContent, public QStyleOptionProgressBarV2
{
    Q_OBJECT

    Q_PROPERTY(int minimum READ getMinimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(int maximum READ getMaximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(int progress READ getProgress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
    Q_PROPERTY(Qt::Alignment textAlignment READ getTextAlignment WRITE setTextAlignment NOTIFY textAlignmentChanged)
    Q_PROPERTY(bool textVisible READ getTextVisible WRITE setTextVisible NOTIFY textVisibleChanged)
    Q_PROPERTY(Qt::Orientation orientation READ getOrientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(bool invertedAppearance READ getInvertedAppearance WRITE setInvertedAppearance NOTIFY invertedAppearanceChanged)
    Q_PROPERTY(Direction textDirection READ getTextDirection WRITE setTextDirection NOTIFY textDirectionChanged)

    Q_ENUMS(Direction)

public:
    enum Direction {
        TopToBottom = 0,
        BottomToTop
    };

    explicit ListItemProgressBar(QObject *parent = 0);

    int getMinimum() const;
    void setMinimum(int min);

    int getMaximum() const;
    void setMaximum(int max);

    int getProgress() const;
    void setProgress(int p);

    QString getText() const;
    void setText(const QString &t);

    Qt::Alignment getTextAlignment() const;
    void setTextAlignment(Qt::Alignment align);

    bool getTextVisible() const;
    void setTextVisible(bool visible);

    Qt::Orientation getOrientation() const;
    void setOrientation(Qt::Orientation orient);

    bool getInvertedAppearance() const;
    void setInvertedAppearance(bool inverted);

    Direction getTextDirection() const;
    void setTextDirection(Direction dir);

    void paint(QPainter *painter, const QRect &r);

signals:
    void minimumChanged();
    void maximumChanged();
    void progressChanged();
    void textChanged();
    void textAlignmentChanged();
    void textVisibleChanged();
    void orientationChanged();
    void invertedAppearanceChanged();
    void textDirectionChanged();

private:
    Q_DISABLE_COPY(ListItemProgressBar)
};

QML_DECLARE_TYPE(ListItemProgressBar)

#endif // LISTITEMPROGRESSBAR_P_H

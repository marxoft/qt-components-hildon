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

#include "imageborder_p.h"

ImageBorder::ImageBorder(QObject *parent) :
    QObject(parent),
    m_left(0),
    m_right(0),
    m_top(0),
    m_bottom(0)
{
}

ImageBorder::~ImageBorder() {}

int ImageBorder::left() const {
    return m_left;
}

void ImageBorder::setLeft(int left) {
    if (left != this->left()) {
        m_left = left;
        emit borderChanged();
    }
}

void ImageBorder::resetLeft() {
    this->setLeft(0);
}

int ImageBorder::right() const {
    return m_right;
}

void ImageBorder::setRight(int right) {
    if (right != this->right()) {
        m_right = right;
        emit borderChanged();
    }
}

void ImageBorder::resetRight() {
    this->setRight(0);
}

int ImageBorder::top() const {
    return m_top;
}

void ImageBorder::setTop(int top) {
    if (top != this->top()) {
        m_top = top;
        emit borderChanged();
    }
}

void ImageBorder::resetTop() {
    this->setTop(0);
}

int ImageBorder::bottom() const {
    return m_bottom;
}

void ImageBorder::setBottom(int bottom) {
    if (bottom != this->bottom()) {
        m_bottom = bottom;
        emit borderChanged();
    }
}

void ImageBorder::resetBottom() {
    this->setBottom(0);
}


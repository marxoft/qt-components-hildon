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

#include "text_p.h"
#include "text_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

Text::Text(QWidget *parent) :
    QLabel(parent),
    d_ptr(new TextPrivate(this))
{
}

Text::Text(TextPrivate &dd, QWidget *parent) :
    QLabel(parent),
    d_ptr(&dd)
{
}

Text::~Text() {}

void Text::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void Text::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal Text::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void Text::setOpacity(qreal opacity) {
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect());

    if (!effect) {
        effect = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(effect);
    }

    if (opacity != effect->opacity()) {
        effect->setOpacity(opacity);
        emit opacityChanged();
    }
}

QString Text::text() const {
    Q_D(const Text);

    return d->text;
}

void Text::setText(const QString &text) {
    if (text != this->text()) {
        Q_D(Text);
        d->text = text;
        QLabel::setText(QString("<font color='%1'>%2</font>").arg(this->color().name()).arg(text));
        emit textChanged();
    }
}

QColor Text::color() const {
    Q_D(const Text);

    return d->color;
}

void Text::setColor(const QColor &color) {
    if (color != this->color()) {
        Q_D(Text);
        d->color = color;
        QLabel::setText(QString("<font color='%1'>%2</font>").arg(color.name()).arg(this->text()));
        emit colorChanged();
    }
}

AnchorLine Text::left() const {
    Q_D(const Text);

    return d->left;
}

AnchorLine Text::right() const {
    Q_D(const Text);

    return d->right;
}

AnchorLine Text::top() const {
    Q_D(const Text);

    return d->top;
}

AnchorLine Text::bottom() const {
    Q_D(const Text);

    return d->bottom;
}

AnchorLine Text::horizontalCenter() const {
    Q_D(const Text);

    return d->horizontalCenter;
}

AnchorLine Text::verticalCenter() const {
    Q_D(const Text);

    return d->verticalCenter;
}

void Text::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QLabel::changeEvent(event);
}

void Text::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QLabel::moveEvent(event);
}

void Text::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QLabel::resizeEvent(event);
}

void Text::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QLabel::showEvent(event);
}

void Text::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QLabel::hideEvent(event);
}

void Text::classBegin() {}

void Text::componentComplete() {
    Q_D(Text);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void TextPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Text *text = qobject_cast<Text*>(list->object)) {
        text->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            text->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void TextPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (Text *text = qobject_cast<Text*>(list->object)) {
        text->d_func()->childrenList.append(widget);
        text->d_func()->dataList.append(widget);
    }
}

void TextPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Text *text = qobject_cast<Text*>(list->object)) {
        text->d_func()->actionList.append(obj);
        text->d_func()->dataList.append(obj);

        if (!text->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            text->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            text->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> TextPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TextPrivate::data_append);
}

QDeclarativeListProperty<QWidget> TextPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, TextPrivate::children_append);
}

QDeclarativeListProperty<QObject> TextPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TextPrivate::actions_append);
}

#include "moc_text_p.cpp"

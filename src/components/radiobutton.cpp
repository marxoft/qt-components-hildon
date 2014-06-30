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

#include "radiobutton_p.h"
#include "radiobutton_p_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QGraphicsOpacityEffect>

RadioButton::RadioButton(QWidget *parent) :
    QRadioButton(parent),
    d_ptr(new RadioButtonPrivate(this))
{
}

RadioButton::RadioButton(RadioButtonPrivate &dd, QWidget *parent) :
    QRadioButton(parent),
    d_ptr(&dd)
{
}

RadioButton::~RadioButton() {}

void RadioButton::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void RadioButton::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal RadioButton::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void RadioButton::setOpacity(qreal opacity) {
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

QString RadioButton::iconSource() const {
    return this->icon().name();
}

void RadioButton::setIconSource(const QString &source) {
    if (source != this->icon().name()) {
        this->setIcon(source.contains('/') ? QIcon(source) : QIcon::fromTheme(source));
    }
}

AnchorLine RadioButton::left() const {
    Q_D(const RadioButton);

    return d->left;
}

AnchorLine RadioButton::right() const {
    Q_D(const RadioButton);

    return d->right;
}

AnchorLine RadioButton::top() const {
    Q_D(const RadioButton);

    return d->top;
}

AnchorLine RadioButton::bottom() const {
    Q_D(const RadioButton);

    return d->bottom;
}

AnchorLine RadioButton::horizontalCenter() const {
    Q_D(const RadioButton);

    return d->horizontalCenter;
}

AnchorLine RadioButton::verticalCenter() const {
    Q_D(const RadioButton);

    return d->verticalCenter;
}

void RadioButton::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QRadioButton::changeEvent(event);
}

void RadioButton::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QRadioButton::moveEvent(event);
}

void RadioButton::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QRadioButton::resizeEvent(event);
}

void RadioButton::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QRadioButton::showEvent(event);
}

void RadioButton::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QRadioButton::hideEvent(event);
}

void RadioButton::classBegin() {}

void RadioButton::componentComplete() {
    Q_D(RadioButton);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void RadioButtonPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (RadioButton *button = qobject_cast<RadioButton*>(list->object)) {
        button->d_func()->dataList.append(obj);
    }
}

void RadioButtonPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (RadioButton *button = qobject_cast<RadioButton*>(list->object)) {
        button->d_func()->actionList.append(obj);

        if (!button->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            button->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            button->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> RadioButtonPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, RadioButtonPrivate::data_append);
}

QDeclarativeListProperty<QObject> RadioButtonPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, RadioButtonPrivate::actions_append);
}

#include "moc_radiobutton_p.cpp"

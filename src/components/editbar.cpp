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

#include "editbar_p.h"
#include "editbar_p_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QAbstractButton>

EditBar::EditBar(QWidget *parent) :
    QMaemo5EditBar(parent),
    d_ptr(new EditBarPrivate(this))
{
}

EditBar::EditBar(EditBarPrivate &dd, QWidget *parent) :
    QMaemo5EditBar(parent),
    d_ptr(&dd)
{
}

EditBar::~EditBar() {}

void EditBar::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void EditBar::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

AnchorLine EditBar::left() const {
    Q_D(const EditBar);

    return d->left;
}

AnchorLine EditBar::right() const {
    Q_D(const EditBar);

    return d->right;
}

AnchorLine EditBar::top() const {
    Q_D(const EditBar);

    return d->top;
}

AnchorLine EditBar::bottom() const {
    Q_D(const EditBar);

    return d->bottom;
}

AnchorLine EditBar::horizontalCenter() const {
    Q_D(const EditBar);

    return d->horizontalCenter;
}

AnchorLine EditBar::verticalCenter() const {
    Q_D(const EditBar);

    return d->verticalCenter;
}

void EditBar::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QMaemo5EditBar::changeEvent(event);
}

void EditBar::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QMaemo5EditBar::moveEvent(event);
}

void EditBar::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QMaemo5EditBar::resizeEvent(event);
}

void EditBar::classBegin() {}

void EditBar::componentComplete() {
    Q_D(EditBar);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void EditBarPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (EditBar *bar = qobject_cast<EditBar*>(list->object)) {
        bar->d_func()->dataList.append(obj);

        if (!bar->d_func()->complete) {
            return;
        }

        if (QAbstractButton *button = qobject_cast<QAbstractButton*>(obj)) {
            button->setStyleSheet(":pressed { border-image: url(/etc/hildon/theme/images/StylusButtonPressed.png) 8 8 8 8 stretch stretch; border-width: 8px; }"
                                  ":on { border-image: url(/etc/hildon/theme/images/StylusButtonPressed.png) 8 8 8 8 stretch stretch; border-width: 8px; }"
                                  ":disabled { border-image: url(/etc/hildon/theme/images/StylusButtonDisabled.png) 8 8 8 8 stretch stretch; border-width: 8px; }"
                                  ":!pressed:!on:!diabled { border-image: url(/etc/hildon/theme/images/StylusButtonNormal.png) 8 8 8 8 stretch stretch; border-width: 8px; }");
            bar->addButton(button);
        }
    }
}

void EditBarPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (EditBar *bar = qobject_cast<EditBar*>(list->object)) {
        bar->d_func()->actionList.append(obj);

        if (!bar->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            bar->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            bar->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> EditBarPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, EditBarPrivate::data_append);
}

QDeclarativeListProperty<QObject> EditBarPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, EditBarPrivate::actions_append);
}

void EditBarPrivate::componentComplete() {
    Q_Q(EditBar);

    foreach (QObject *obj, dataList) {
        if (QAbstractButton *button = qobject_cast<QAbstractButton*>(obj)) {
            button->setStyleSheet(":pressed { border-image: url(/etc/hildon/theme/images/StylusButtonPressed.png) 8 8 8 8 stretch stretch; border-width: 8px; }"
                                  ":on { border-image: url(/etc/hildon/theme/images/StylusButtonPressed.png) 8 8 8 8 stretch stretch; border-width: 8px; }"
                                  ":disabled { border-image: url(/etc/hildon/theme/images/StylusButtonDisabled.png) 8 8 8 8 stretch stretch; border-width: 8px; }"
                                  ":!pressed:!on:!diabled { border-image: url(/etc/hildon/theme/images/StylusButtonNormal.png) 8 8 8 8 stretch stretch; border-width: 8px; }");
            q->addButton(button);
        }
    }

    ItemPrivate::componentComplete();
}

#include "moc_editbar_p.cpp"

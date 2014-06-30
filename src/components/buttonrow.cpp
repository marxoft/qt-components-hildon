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

#include "buttonrow_p.h"
#include "buttonrow_p_p.h"
#include <QHBoxLayout>
#include <QAbstractButton>

ButtonRow::ButtonRow(QWidget *parent) :
    Item(*new ButtonRowPrivate(this), parent)
{
    Q_D(ButtonRow);
    d->group = new QButtonGroup(this);
    this->setLayout(new QHBoxLayout(this));
    this->layout()->setSpacing(0);
    this->layout()->setContentsMargins(0, 0, 0, 0);
}

ButtonRow::ButtonRow(ButtonRowPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
    this->setLayout(new QHBoxLayout(this));
    this->layout()->setSpacing(0);
    this->layout()->setContentsMargins(0, 0, 0, 0);
}

ButtonRow::~ButtonRow() {}

bool ButtonRow::exclusive() const {
    Q_D(const ButtonRow);

    return d->group->exclusive();
}

void ButtonRow::setExclusive(bool exclusive) {
    Q_D(ButtonRow);

    d->group->setExclusive(exclusive);
}

void ButtonRowPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    obj->setParent(list->object);

    if (ButtonRow *row = qobject_cast<ButtonRow*>(list->object)) {
        row->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            row->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }

        if (!row->d_func()->complete) {
            return;
        }

        if (QAbstractButton *button = qobject_cast<QAbstractButton*>(obj)) {
            row->layout()->addWidget(button);
            row->d_func()->group->addButton(button);
            row->d_func()->updateStyleSheets();
        }
    }
}

void ButtonRowPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (ButtonRow *row = qobject_cast<ButtonRow*>(list->object)) {
        row->d_func()->childrenList.append(widget);
        row->d_func()->dataList.append(widget);

        if (!row->d_func()->complete) {
            return;
        }

        if (QAbstractButton *button = qobject_cast<QAbstractButton*>(widget)) {
            row->layout()->addWidget(button);
            row->d_func()->group->addButton(button);
            row->d_func()->updateStyleSheets();
        }
    }
}

QDeclarativeListProperty<QObject> ButtonRowPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ButtonRowPrivate::data_append);
}

QDeclarativeListProperty<QWidget> ButtonRowPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, ButtonRowPrivate::children_append);
}

void ButtonRowPrivate::updateStyleSheets() {
    if (group->buttons().isEmpty()) {
        return;
    }

    group->buttons().first()->setStyleSheet(":pressed { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalLeftPressed.png) 16 16 16 16 stretch stretch; border-width: 16px; }"
                                            ":on { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalLeftPressed.png) 16 16 16 16 stretch stretch; border-width: 16px; }"
                                            ":disabled { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalLeftDisabled.png) 16 16 16 16 stretch stretch; border-width: 16px; }"
                                            ":!pressed:!on:!diabled { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalLeftNormal.png) 16 16 16 16 stretch stretch; border-width: 16px; }");

    group->buttons().last()->setStyleSheet(":pressed { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalRightPressed.png) 16 16 16 16 stretch stretch; border-width: 16px; }"
                                           ":on { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalRightPressed.png) 16 16 16 16 stretch stretch; border-width: 16px; }"
                                           ":disabled { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalRightDisabled.png) 16 16 16 16 stretch stretch; border-width: 16px; }"
                                           ":!pressed:!on:!disabled { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalRightNormal.png) 16 16 16 16 stretch stretch; border-width: 16px; }");

    for (int i = 1; i < group->buttons().size() - 1; i++) {
        group->buttons().at(i)->setStyleSheet(":pressed { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalMiddlePressed.png) 16 16 16 16 stretch stretch; border-width: 16px; }"
                                              ":on { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalMiddlePressed.png) 16 16 16 16 stretch stretch; border-width: 16px; }"
                                              ":disabled { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalMiddleDisabled.png) 16 16 16 16 stretch stretch; border-width: 16px; }"
                                              ":!pressed:!on:!disabled { border-image: url(/etc/hildon/theme/images/ButtonGroupHorizontalMiddleNormal.png) 16 16 16 16 stretch stretch; border-width: 16px; }");
    }
}

void ButtonRowPrivate::componentComplete() {
    Q_Q(ButtonRow);

    foreach (QWidget *widget, childrenList) {
        if (QAbstractButton *button = qobject_cast<QAbstractButton*>(widget)) {
            q->layout()->addWidget(button);
            group->addButton(button);
        }
    }

    this->updateStyleSheets();

    ItemPrivate::componentComplete();
}

#include "moc_buttonrow_p.cpp"

/*!
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qchapplication.h"
#include <QApplication>

QchApplication::QchApplication(QObject *parent) :
    QObject(parent)
{
    if (qApp) {
        qApp->installEventFilter(this);
    }
}

bool QchApplication::isActive() const {
    return QApplication::activeWindow() != 0;
}

Qt::LayoutDirection QchApplication::layoutDirection() const {
    return QApplication::layoutDirection();
}

QStringList QchApplication::arguments() const {
    return QApplication::arguments();
}

QFont QchApplication::font() const {
    return QApplication::font();
}

void QchApplication::setFont(const QFont &f) {
    QApplication::setFont(f);
}

QString QchApplication::name() const {
    return QApplication::applicationName();
}

void QchApplication::setName(const QString &n) {
    if (n != name()) {
        QApplication::setApplicationName(n);
        emit nameChanged();
    }
}

QString QchApplication::version() const {
    return QApplication::applicationVersion();
}

void QchApplication::setVersion(const QString &v) {
    if (v != version()) {
        QApplication::setApplicationVersion(v);
        emit versionChanged();
    }
}

QString QchApplication::organization() const {
    return QApplication::organizationName();
}

void QchApplication::setOrganization(const QString &o) {
    if (o != organization()) {
        QApplication::setOrganizationName(o);
        emit organizationChanged();
    }
}

QString QchApplication::domain() const {
    return QApplication::organizationDomain();
}

void QchApplication::setDomain(const QString &d) {
    if (d != domain()) {
        QApplication::setOrganizationDomain(d);
        emit domainChanged();
    }
}

bool QchApplication::eventFilter(QObject *watched, QEvent *event) {
    switch (event->type()) {
        case QEvent::ApplicationActivate:
        case QEvent::ApplicationDeactivate:
            emit activeChanged();
            break;
        case QEvent::ApplicationLayoutDirectionChange:
            emit layoutDirectionChanged();
            break;
        case QEvent::ApplicationFontChange:
            emit fontChanged();
            break;
        default:
            break;
    }

    return QObject::eventFilter(watched, event);
}


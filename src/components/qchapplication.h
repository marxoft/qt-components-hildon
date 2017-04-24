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

#ifndef QCHAPPLICATION_H
#define QCHAPPLICATION_H

#include <QObject>
#include <QFont>
#include <QStringList>

class QchApplication : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)
    Q_PROPERTY(Qt::LayoutDirection layoutDirection READ layoutDirection NOTIFY layoutDirectionChanged)
    Q_PROPERTY(QStringList arguments READ arguments CONSTANT)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)
    Q_PROPERTY(QString organization READ organization WRITE setOrganization NOTIFY organizationChanged)
    Q_PROPERTY(QString domain READ domain WRITE setDomain NOTIFY domainChanged)

public:
    explicit QchApplication(QObject *parent = 0);

    bool isActive() const;

    Qt::LayoutDirection layoutDirection() const;

    QStringList arguments() const;

    QFont font() const;
    void setFont(const QFont &f);

    QString name() const;
    void setName(const QString &n);

    QString version() const;
    void setVersion(const QString &v);

    QString organization() const;
    void setOrganization(const QString &o);

    QString domain() const;
    void setDomain(const QString &d);

private:
    bool eventFilter(QObject *watched, QEvent *event);

Q_SIGNALS:
    void activeChanged();
    void layoutDirectionChanged();
    void fontChanged();
    void nameChanged();
    void versionChanged();
    void organizationChanged();
    void domainChanged();
};

#endif // QCHAPPLICATION_H


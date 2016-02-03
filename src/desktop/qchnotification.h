/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHNOTIFICATION_H
#define QCHNOTIFICATION_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchNotificationPrivate;

class QchNotification : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QVariantMap hints READ hints WRITE setHints NOTIFY hintsChanged)
    Q_PROPERTY(QString iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged)
    Q_PROPERTY(QString soundSource READ soundSource WRITE setSoundSource NOTIFY soundSourceChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
    Q_ENUMS(Timeout)
    
public:
    enum Timeout {
        DefaultTimeout = 0,
        NoTimeout
    };
    
    explicit QchNotification(QObject *parent = 0);
    ~QchNotification();
    
    QString category() const;
    void setCategory(const QString &c);
    
    QVariantMap hints() const;
    void setHints(const QVariantMap &h);

    QString iconSource() const;
    void setIconSource(const QString &i);
    
    QString soundSource() const;
    void setSoundSource(const QString &s);
    
    QString text() const;
    void setText(const QString &t);
    
    int timeout() const;
    void setTimeout(int t);
    
    QString title() const;
    void setTitle(const QString &t);
    
    bool isVisible() const;
    void setVisible(bool v);

public Q_SLOTS:
    void hide();
    void open();
    void show();
    
Q_SIGNALS:
    void accepted();
    void categoryChanged();
    void hintsChanged();
    void iconSourceChanged();
    void rejected();
    void soundSourceChanged();
    void textChanged();
    void timeoutChanged();
    void titleChanged();
    void visibleChanged();

protected:
    virtual void classBegin();
    virtual void componentComplete();
    
    QScopedPointer<QchNotificationPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchNotification)
    
private:
    Q_DISABLE_COPY(QchNotification)
};

QML_DECLARE_TYPE(QchNotification)
    
#endif // QCHNOTIFICATION_H

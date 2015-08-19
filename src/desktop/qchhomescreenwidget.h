/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHHOMESCREENWIDGET_H
#define QCHHOMESCREENWIDGET_H

#include <QWidget>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDeclarativeItem;
class QchCloseEvent;
class QchHomescreenWidgetPrivate;

class QchHomescreenWidget : public QWidget, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeItem> children READ children)
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY sizeChanged)
    Q_PROPERTY(bool isOnCurrentHomescreen READ isOnCurrentHomescreen NOTIFY isOnCurrentHomescreenChanged)
    Q_PROPERTY(QString pluginId READ pluginId WRITE setPluginId)
    Q_PROPERTY(bool settingsAvailable READ settingsAvailable WRITE setSettingsAvailable NOTIFY settingsAvailableChanged)
    Q_PROPERTY(QString styleSheet READ styleSheet CONSTANT FINAL)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY sizeChanged)
    Q_PROPERTY(int writePipe READ writePipe WRITE setWritePipe)
    
    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")
    
public:
    explicit QchHomescreenWidget(QWidget *parent = 0);
    ~QchHomescreenWidget();
        
    QDeclarativeListProperty<QDeclarativeItem> children();
    QDeclarativeListProperty<QObject> data();
    
    bool isOnCurrentHomescreen() const;
    
    QString pluginId() const;
    void setPluginId(const QString &id);
    
    bool settingsAvailable() const;
    void setSettingsAvailable(bool enabled);
    
    int writePipe() const;
    void setWritePipe(int pipe);
    
Q_SIGNALS:
    void closing(QchCloseEvent *close);
    void isOnCurrentHomescreenChanged();
    void settingsAvailableChanged();
    void settingsRequested();
    void sizeChanged();
    void visibleChanged();
    
protected:
    virtual void classBegin();
    virtual void componentComplete();
    
    virtual void showEvent(QShowEvent *e);
    virtual void hideEvent(QHideEvent *e);
    virtual void closeEvent(QCloseEvent *e);
    virtual void resizeEvent(QResizeEvent *e);

    QScopedPointer<QchHomescreenWidgetPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchHomescreenWidget)
    
    Q_PRIVATE_SLOT(d_func(), void _q_onSocketException())

private:
    Q_DISABLE_COPY(QchHomescreenWidget)
};

QML_DECLARE_TYPE(QchHomescreenWidget)
    
#endif // QCHHOMESCREENWIDGET_H

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

#ifndef WEBPAGE_P_H
#define WEBPAGE_P_H

#include <QWebPage>
#include <QWebFrame>
#include <QDeclarativeListProperty>
#include <qdeclarative.h>

class QDeclarativeComponent;
class WebHistory;
class WebSettings;
class WebPagePrivate;

class WebPage : public QWebPage
{
    Q_OBJECT

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QUrl baseUrl READ baseUrl NOTIFY urlChanged)
    Q_PROPERTY(QUrl requestedUrl READ requestedUrl NOTIFY urlChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(int contentWidth READ contentWidth NOTIFY contentSizeChanged)
    Q_PROPERTY(int contentHeight READ contentHeight NOTIFY contentSizeChanged)
    Q_PROPERTY(int preferredWidth READ preferredWidth WRITE setPreferredWidth NOTIFY preferredWidthChanged)
    Q_PROPERTY(int preferredHeight READ preferredHeight WRITE setPreferredHeight NOTIFY preferredHeightChanged)
    Q_PROPERTY(qreal zoomFactor READ zoomFactor WRITE setZoomFactor NOTIFY zoomFactorChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(QString selectedText READ selectedText NOTIFY selectedTextChanged)
    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY selectedTextChanged)
    Q_PROPERTY(QDeclarativeComponent* newWindowComponent READ newWindowComponent WRITE setNewWindowComponent NOTIFY newWindowComponentChanged)
    Q_PRIVATE_PROPERTY(WebPage::d_func(), WebHistory* history READ history CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(WebPage::d_func(), WebSettings* settings READ settings CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(WebPage::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(WebPage::d_func(), QDeclarativeListProperty<QObject> javaScriptWindowObjects READ jsObjects)

    Q_ENUMS(Status)

public:
    enum Status {
        Null = 0,
        Loading,
        Ready,
        Error
    };

    explicit WebPage(QObject *parent = 0);
    ~WebPage();

    QUrl url() const;
    void setUrl(const QUrl &url);

    QUrl baseUrl() const;
    QUrl requestedUrl() const;

    QString icon() const;

    QString title() const;

    int contentWidth() const;
    int contentHeight() const;

    int preferredWidth() const;
    void setPreferredWidth(int width);
    int preferredHeight() const;
    void setPreferredHeight(int height);

    qreal zoomFactor() const;
    void setZoomFactor(qreal zoom);

    int progress() const;

    Status status() const;

    QString statusText() const;

    bool hasSelection() const;

    QDeclarativeComponent* newWindowComponent() const;
    void setNewWindowComponent(QDeclarativeComponent *component);

    QObject* newWindowParent() const;
    void setNewWindowParent(QObject *parent);

public slots:
    bool findText(const QString &text);
    bool findAllText(const QString &text);

    void load(const QUrl &url);
    void reload();
    void stop();

    void back();
    void forward();

    void copy();
    void cut();
    void paste();

signals:
    void urlChanged();
    void iconChanged();
    void titleChanged();
    void contentSizeChanged();
    void preferredWidthChanged();
    void preferredHeightChanged();
    void zoomFactorChanged();
    void progressChanged();
    void statusChanged();
    void statusTextChanged();
    void selectedTextChanged();
    void newWindowComponentChanged();
    void newWindowParentChanged();

protected:
    WebPage(WebPagePrivate &dd, QObject *parent = 0);

    QWebPage* createWindow(WebWindowType type);

    QScopedPointer<WebPagePrivate> d_ptr;

    Q_DECLARE_PRIVATE(WebPage)

    Q_PRIVATE_SLOT(d_func(), void _q_onLoadStarted())
    Q_PRIVATE_SLOT(d_func(), void _q_onLoadFinished(bool))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoadProgress(int))
    Q_PRIVATE_SLOT(d_func(), void _q_onStatusBarMessage(QString))
    Q_PRIVATE_SLOT(d_func(), void _q_onJavaScriptWindowObjectCleared())

private:
    Q_DISABLE_COPY(WebPage)
};

QML_DECLARE_TYPE(WebPage)

#endif // WEBPAGE_P_H

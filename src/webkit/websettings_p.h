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

#ifndef WEBSETTINGS_P_H
#define WEBSETTINGS_P_H

#include <QObject>
#include <qdeclarative.h>

class QWebSettings;

class WebSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool autoLoadImages READ autoLoadImages WRITE setAutoLoadImages RESET resetAutoLoadImages)
    Q_PROPERTY(bool javaEnabled READ javaEnabled WRITE setJavaEnabled RESET resetJavaEnabled)
    Q_PROPERTY(bool javascriptCanAccessClipboard READ javascriptCanAccessClipboard WRITE setJavascriptCanAccessClipboard RESET resetJavascriptCanAccessClipboard)
    Q_PROPERTY(bool javascriptCanOpenWindows READ javascriptCanOpenWindows WRITE setJavascriptCanOpenWindows RESET resetJavascriptCanOpenWindows)
    Q_PROPERTY(bool javascriptEnabled READ javascriptEnabled WRITE setJavascriptEnabled RESET resetJavascriptEnabled)
    Q_PROPERTY(bool linksIncludedInFocusChain READ linksIncludedInFocusChain WRITE setLinksIncludedInFocusChain RESET resetLinksIncludedInFocusChain)
    Q_PROPERTY(bool localContentCanAccessRemoteUrls READ localContentCanAccessRemoteUrls WRITE setLocalContentCanAccessRemoteUrls RESET resetLocalContentCanAccessRemoteUrls)
    Q_PROPERTY(bool localStorageDatabaseEnabled READ localStorageDatabaseEnabled WRITE setLocalStorageDatabaseEnabled RESET resetLocalStorageDatabaseEnabled)
    Q_PROPERTY(bool offlineStorageDatabaseEnabled READ offlineStorageDatabaseEnabled WRITE setOfflineStorageDatabaseEnabled RESET resetOfflineStorageDatabaseEnabled)
    Q_PROPERTY(bool offlineWebApplicationCacheEnabled READ offlineWebApplicationCacheEnabled WRITE setOfflineWebApplicationCacheEnabled RESET resetOfflineWebApplicationCacheEnabled)
    Q_PROPERTY(bool pluginsEnabled READ pluginsEnabled WRITE setPluginsEnabled RESET resetPluginsEnabled)
    Q_PROPERTY(bool printElementBackgrounds READ printElementBackgrounds WRITE setPrintElementBackgrounds RESET resetPrintElementBackgrounds)
    Q_PROPERTY(bool privateBrowsingEnabled READ privateBrowsingEnabled WRITE setPrivateBrowsingEnabled RESET resetPrivateBrowsingEnabled)
    Q_PROPERTY(bool zoomTextOnly READ zoomTextOnly WRITE setZoomTextOnly RESET resetZoomTextOnly)
    Q_PROPERTY(bool developerExtrasEnabled READ developerExtrasEnabled WRITE setDeveloperExtrasEnabled RESET resetDeveloperExtrasEnabled)
    Q_PROPERTY(int defaultFixedFontSize READ defaultFixedFontSize WRITE setDefaultFixedFontSize RESET resetDefaultFixedFontSize)
    Q_PROPERTY(int defaultFontSize READ defaultFontSize WRITE setDefaultFontSize RESET resetDefaultFontSize)
    Q_PROPERTY(int minimumFontSize READ minimumFontSize WRITE setMinimumFontSize RESET resetMinimumFontSize)
    Q_PROPERTY(int minimumLogicalFontSize READ minimumLogicalFontSize WRITE setMinimumLogicalFontSize RESET resetMinimumLogicalFontSize)
    Q_PROPERTY(QString cursiveFontFamily READ cursiveFontFamily WRITE setCursiveFontFamily RESET resetCursiveFontFamily)
    Q_PROPERTY(QString fantasyFontFamily READ fantasyFontFamily WRITE setFantasyFontFamily RESET resetFantasyFontFamily)
    Q_PROPERTY(QString fixedFontFamily READ fixedFontFamily WRITE setFixedFontFamily RESET resetFixedFontFamily)
    Q_PROPERTY(QString sansSerifFontFamily READ sansSerifFontFamily WRITE setSansSerifFontFamily RESET resetSansSerifFontFamily)
    Q_PROPERTY(QString serifFontFamily READ serifFontFamily WRITE setSerifFontFamily RESET resetSerifFontFamily)
    Q_PROPERTY(QString standardFontFamily READ standardFontFamily WRITE setStandardFontFamily RESET resetStandardFontFamily)

public:
    explicit WebSettings(QObject *parent = 0);
    explicit WebSettings(QWebSettings *settings, QObject *parent = 0);
    ~WebSettings();

    bool autoLoadImages() const;
    void setAutoLoadImages(bool load);
    void resetAutoLoadImages();

    bool javaEnabled() const;
    void setJavaEnabled(bool enabled);
    void resetJavaEnabled();

    bool javascriptCanAccessClipboard() const;
    void setJavascriptCanAccessClipboard(bool access);
    void resetJavascriptCanAccessClipboard();

    bool javascriptCanOpenWindows() const;
    void setJavascriptCanOpenWindows(bool open);
    void resetJavascriptCanOpenWindows();

    bool javascriptEnabled() const;
    void setJavascriptEnabled(bool enabled);
    void resetJavascriptEnabled();

    bool linksIncludedInFocusChain() const;
    void setLinksIncludedInFocusChain(bool included);
    void resetLinksIncludedInFocusChain();

    bool localContentCanAccessRemoteUrls() const;
    void setLocalContentCanAccessRemoteUrls(bool access);
    void resetLocalContentCanAccessRemoteUrls();

    bool localStorageDatabaseEnabled() const;
    void setLocalStorageDatabaseEnabled(bool enabled);
    void resetLocalStorageDatabaseEnabled();

    bool offlineStorageDatabaseEnabled() const;
    void setOfflineStorageDatabaseEnabled(bool enabled);
    void resetOfflineStorageDatabaseEnabled();

    bool offlineWebApplicationCacheEnabled() const;
    void setOfflineWebApplicationCacheEnabled(bool enabled);
    void resetOfflineWebApplicationCacheEnabled();

    bool pluginsEnabled() const;
    void setPluginsEnabled(bool enabled);
    void resetPluginsEnabled();

    bool printElementBackgrounds() const;
    void setPrintElementBackgrounds(bool enabled);
    void resetPrintElementBackgrounds();

    bool privateBrowsingEnabled() const;
    void setPrivateBrowsingEnabled(bool enabled);
    void resetPrivateBrowsingEnabled();

    bool zoomTextOnly() const;
    void setZoomTextOnly(bool text);
    void resetZoomTextOnly();

    bool developerExtrasEnabled() const;
    void setDeveloperExtrasEnabled(bool enabled);
    void resetDeveloperExtrasEnabled();

    int defaultFixedFontSize() const;
    void setDefaultFixedFontSize(int size);
    void resetDefaultFixedFontSize();

    int defaultFontSize() const;
    void setDefaultFontSize(int size);
    void resetDefaultFontSize();

    int minimumFontSize() const;
    void setMinimumFontSize(int size);
    void resetMinimumFontSize();

    int minimumLogicalFontSize() const;
    void setMinimumLogicalFontSize(int size);
    void resetMinimumLogicalFontSize();

    QString cursiveFontFamily() const;
    void setCursiveFontFamily(const QString &family);
    void resetCursiveFontFamily();

    QString fantasyFontFamily() const;
    void setFantasyFontFamily(const QString &family);
    void resetFantasyFontFamily();

    QString fixedFontFamily() const;
    void setFixedFontFamily(const QString &family);
    void resetFixedFontFamily();

    QString sansSerifFontFamily() const;
    void setSansSerifFontFamily(const QString &family);
    void resetSansSerifFontFamily();

    QString serifFontFamily() const;
    void setSerifFontFamily(const QString &family);
    void resetSerifFontFamily();

    QString standardFontFamily() const;
    void setStandardFontFamily(const QString &family);
    void resetStandardFontFamily();

private:
    QWebSettings *m_settings;

    Q_DISABLE_COPY(WebSettings)
};

QML_DECLARE_TYPE(WebSettings)

#endif // WEBSETTINGS_P_H

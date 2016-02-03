/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qchwebsettings.h"
#include <QWebPage>
#include <QWebSettings>

static QWebSettings* qWebSettings(const QchWebSettings *qws) {
    if (QWebPage *page = qobject_cast<QWebPage*>(qws->parent())) {
        if (QWebSettings *settings = page->settings()) {
            return settings;
        }
    }
    
    return QWebSettings::globalSettings();
}

/*!
    \class WebSettings
    \brief Provides access to the settings of a WebPage or WebView
    
    \ingroup webkit
    
    In addition, there is a 'webSettings' global content property that provides access to the global web settings.
    
    \note This component cannot be created in QML.
    
    \sa WebPage, WebView
*/
QchWebSettings::QchWebSettings(QObject *parent) :
    QObject(parent)
{
}

/*!
    \brief Whether images are automatically loaded in web pages
    
    This is enabled by default.
*/
bool QchWebSettings::autoLoadImages() const {
    return qWebSettings(this)->testAttribute(QWebSettings::AutoLoadImages);
}

void QchWebSettings::setAutoLoadImages(bool load) {
    if (load != autoLoadImages()) {
        qWebSettings(this)->setAttribute(QWebSettings::AutoLoadImages, load);
        emit autoLoadImagesChanged();
    }
}

void QchWebSettings::resetAutoLoadImages() {
    qWebSettings(this)->resetAttribute(QWebSettings::AutoLoadImages);
}

/*!
    \brief Whether Java is enabled.
    
    This is enabled by default.
*/
bool QchWebSettings::javaEnabled() const {
    return qWebSettings(this)->testAttribute(QWebSettings::JavaEnabled);
}

void QchWebSettings::setJavaEnabled(bool enabled) {
    if (enabled != javaEnabled()) {
        qWebSettings(this)->setAttribute(QWebSettings::JavaEnabled, enabled);
        emit javaEnabledChanged();
    }
}

void QchWebSettings::resetJavaEnabled() {
    qWebSettings(this)->resetAttribute(QWebSettings::JavaEnabled);
}

/*!
    \brief Whether JavaScript code can access the system clipboard.
*/
bool QchWebSettings::javascriptCanAccessClipboard() const {
    return qWebSettings(this)->testAttribute(QWebSettings::JavascriptCanAccessClipboard);
}

void QchWebSettings::setJavascriptCanAccessClipboard(bool access) {
    if (access != javascriptCanAccessClipboard()) {
        qWebSettings(this)->setAttribute(QWebSettings::JavascriptCanAccessClipboard, access);
        emit javascriptCanAccessClipboardChanged();
    }
}

void QchWebSettings::resetJavascriptCanAccessClipboard() {
    qWebSettings(this)->resetAttribute(QWebSettings::JavascriptCanAccessClipboard);
}

/*!
    \brief Whether JavaScript code can open new windows.
*/
bool QchWebSettings::javascriptCanOpenWindows() const {
    return qWebSettings(this)->testAttribute(QWebSettings::JavascriptCanOpenWindows);
}

void QchWebSettings::setJavascriptCanOpenWindows(bool open) {
    if (open != javascriptCanOpenWindows()) {
        qWebSettings(this)->setAttribute(QWebSettings::JavascriptCanOpenWindows, open);
        emit javascriptCanOpenWindowsChanged();
    }
}

void QchWebSettings::resetJavascriptCanOpenWindows() {
    qWebSettings(this)->resetAttribute(QWebSettings::JavascriptCanOpenWindows);
}

/*!
    \brief Whether JavaScript is enabled.
    
    This is enabled by default.
*/
bool QchWebSettings::javascriptEnabled() const {
    return qWebSettings(this)->testAttribute(QWebSettings::JavascriptEnabled);
}

void QchWebSettings::setJavascriptEnabled(bool enabled) {
    if (enabled != javascriptEnabled()) {
        qWebSettings(this)->setAttribute(QWebSettings::JavascriptEnabled, enabled);
        emit javascriptEnabledChanged();
    }
}

void QchWebSettings::resetJavascriptEnabled() {
    qWebSettings(this)->resetAttribute(QWebSettings::JavascriptEnabled);
}

/*!
    \brief Whether hyperlinks should be included in the keyboard focus chain.
    
    This is enabled by default.
*/
bool QchWebSettings::linksIncludedInFocusChain() const {
    return qWebSettings(this)->testAttribute(QWebSettings::LinksIncludedInFocusChain);
}

void QchWebSettings::setLinksIncludedInFocusChain(bool included) {
    if (included != linksIncludedInFocusChain()) {
        qWebSettings(this)->setAttribute(QWebSettings::LinksIncludedInFocusChain, included);
        emit linksIncludedInFocusChainChanged();
    }
}

void QchWebSettings::resetLinksIncludedInFocusChain() {
    qWebSettings(this)->resetAttribute(QWebSettings::LinksIncludedInFocusChain);
}

/*!
    \brief  Whether locally loaded documents are allowed to access remote urls.
    
    This is disabled by default.
*/
bool QchWebSettings::localContentCanAccessRemoteUrls() const {
    return qWebSettings(this)->testAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

void QchWebSettings::setLocalContentCanAccessRemoteUrls(bool access) {
    if (access != localContentCanAccessRemoteUrls()) {
        qWebSettings(this)->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, access);
        emit localContentCanAccessRemoteUrlsChanged();
    }
}

void QchWebSettings::resetLocalContentCanAccessRemoteUrls() {
    qWebSettings(this)->resetAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

/*!
    \brief Whether support for the HTML 5 local storage feature is enabled or not
    
    This is disabled by default.
*/
bool QchWebSettings::localStorageDatabaseEnabled() const {
    return qWebSettings(this)->testAttribute(QWebSettings::LocalStorageDatabaseEnabled);
}

void QchWebSettings::setLocalStorageDatabaseEnabled(bool enabled) {
    if (enabled != localStorageDatabaseEnabled()) {
        qWebSettings(this)->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, enabled);
        emit localStorageDatabaseEnabledChanged();
    }
}

void QchWebSettings::resetLocalStorageDatabaseEnabled() {
    qWebSettings(this)->resetAttribute(QWebSettings::LocalStorageDatabaseEnabled);
}

/*!
    \brief Whether support for the HTML 5 offline storage feature is enabled or not
    
    This is disabled by default.
*/
bool QchWebSettings::offlineStorageDatabaseEnabled() const {
    return qWebSettings(this)->testAttribute(QWebSettings::OfflineStorageDatabaseEnabled);
}

void QchWebSettings::setOfflineStorageDatabaseEnabled(bool enabled) {
    if (enabled != offlineStorageDatabaseEnabled()) {
        qWebSettings(this)->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, enabled);
        emit offlineStorageDatabaseEnabledChanged();
    }
}

void QchWebSettings::resetOfflineStorageDatabaseEnabled() {
    qWebSettings(this)->resetAttribute(QWebSettings::OfflineStorageDatabaseEnabled);
}

/*!
    \brief Whether support for the HTML 5 web application cache feature is enabled or not
    
    This is disabled by default.
*/
bool QchWebSettings::offlineWebApplicationCacheEnabled() const {
    return qWebSettings(this)->testAttribute(QWebSettings::OfflineWebApplicationCacheEnabled);
}

void QchWebSettings::setOfflineWebApplicationCacheEnabled(bool enabled) {
    if (enabled != offlineWebApplicationCacheEnabled()) {
        qWebSettings(this)->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, enabled);
        emit offlineWebApplicationCacheEnabledChanged();
    }
}

void QchWebSettings::resetOfflineWebApplicationCacheEnabled() {
    qWebSettings(this)->resetAttribute(QWebSettings::OfflineWebApplicationCacheEnabled);
}

/*!
    \brief Whether persisent settings storage is enabled or not.
    
    This is disabled by default.
*/
bool QchWebSettings::persistentStorageEnabled() const {
    QWebSettings *settings = qWebSettings(this);
    return (!settings->iconDatabasePath().isEmpty())
            || (!settings->localStoragePath().isEmpty())
            || (!settings->offlineStoragePath().isEmpty())
            || (!settings->offlineWebApplicationCachePath().isEmpty());
}

void QchWebSettings::setPersistentStorageEnabled(bool enabled) {
    QWebSettings *settings = qWebSettings(this);
    
    if (enabled) {
        settings->enablePersistentStorage();
    }
    else {
        settings->setIconDatabasePath(QString());
        settings->setLocalStoragePath(QString());
        settings->setOfflineStoragePath(QString());
        settings->setOfflineWebApplicationCachePath(QString());
    }

    emit persistentStorageEnabledChanged();
}

/*!
    \brief Whether plugins are enabled in web pages.
    
    Qt plugins with a mimetype such as "application/x-qt-plugin" are not affected by this setting. 
    
    This is disabled by default.
*/
bool QchWebSettings::pluginsEnabled() const {
    return qWebSettings(this)->testAttribute(QWebSettings::PluginsEnabled);
}

void QchWebSettings::setPluginsEnabled(bool enabled) {
    if (enabled != pluginsEnabled()) {
        qWebSettings(this)->setAttribute(QWebSettings::PluginsEnabled, enabled);
        emit pluginsEnabledChanged();
    }
}

void QchWebSettings::resetPluginsEnabled() {
    qWebSettings(this)->resetAttribute(QWebSettings::PluginsEnabled);
}

/*!
    \brief Whether the background color and images are also drawn when the page is printed
    
    This is enabled by default.
*/
bool QchWebSettings::printElementBackgrounds() const {
    return qWebSettings(this)->testAttribute(QWebSettings::PrintElementBackgrounds);
}

void QchWebSettings::setPrintElementBackgrounds(bool enabled) {
    if (enabled != printElementBackgrounds()) {
        qWebSettings(this)->setAttribute(QWebSettings::PrintElementBackgrounds, enabled);
        emit printElementBackgroundsChanged();
    }
}

void QchWebSettings::resetPrintElementBackgrounds() {
    qWebSettings(this)->resetAttribute(QWebSettings::PrintElementBackgrounds);
}

/*!
    \brief Whether WebKit is prevented from recording visited pages in the history and storing web page icons
    
    This is disabled by default.
*/
bool QchWebSettings::privateBrowsingEnabled() const {
    return qWebSettings(this)->testAttribute(QWebSettings::PrivateBrowsingEnabled);
}

void QchWebSettings::setPrivateBrowsingEnabled(bool enabled) {
    if (enabled != privateBrowsingEnabled()) {
        qWebSettings(this)->setAttribute(QWebSettings::PrivateBrowsingEnabled, enabled);
        emit privateBrowsingEnabledChanged();
    }
}

void QchWebSettings::resetPrivateBrowsingEnabled() {
    qWebSettings(this)->resetAttribute(QWebSettings::PrivateBrowsingEnabled);
}

/*!
    \brief Whether the zoom factor on a frame applies only to the text or to all content
    
    This is disabled by default.
*/
bool QchWebSettings::zoomTextOnly() const {
    return qWebSettings(this)->testAttribute(QWebSettings::ZoomTextOnly);
}

void QchWebSettings::setZoomTextOnly(bool text) {
    if (text != zoomTextOnly()) {
        qWebSettings(this)->setAttribute(QWebSettings::ZoomTextOnly, text);
        emit zoomTextOnlyChanged();
    }
}

void QchWebSettings::resetZoomTextOnly() {
    qWebSettings(this)->resetAttribute(QWebSettings::ZoomTextOnly);
}

/*!
    \brief Whether extra tools are enabled for web developers.
    
    This is disabled by default.
*/
bool QchWebSettings::developerExtrasEnabled() const {
    return qWebSettings(this)->testAttribute(QWebSettings::DeveloperExtrasEnabled);
}

void QchWebSettings::setDeveloperExtrasEnabled(bool enabled) {
    if (enabled != developerExtrasEnabled()) {
        qWebSettings(this)->setAttribute(QWebSettings::DeveloperExtrasEnabled, enabled);
        emit developerExtrasEnabledChanged();
    }
}

void QchWebSettings::resetDeveloperExtrasEnabled() {
    qWebSettings(this)->resetAttribute(QWebSettings::DeveloperExtrasEnabled);
}

/*!
    \brief The default text encoding system.
*/
QString QchWebSettings::defaultTextEncoding() const {
    return qWebSettings(this)->defaultTextEncoding();
}

void QchWebSettings::setDefaultTextEncoding(const QString &encoding) {
    if (encoding != defaultTextEncoding()) {
        qWebSettings(this)->setDefaultTextEncoding(encoding);
        emit defaultTextEncodingChanged();
    }
}

/*!
    \brief The default font size for fixed-pitch text.
*/
int QchWebSettings::defaultFixedFontSize() const {
    return qWebSettings(this)->fontSize(QWebSettings::DefaultFixedFontSize);
}

void QchWebSettings::setDefaultFixedFontSize(int size) {
    if (size != defaultFixedFontSize()) {
        qWebSettings(this)->setFontSize(QWebSettings::DefaultFixedFontSize, size);
        emit defaultFixedFontSizeChanged();
    }
}

void QchWebSettings::resetDefaultFixedFontSize() {
    qWebSettings(this)->resetFontSize(QWebSettings::DefaultFixedFontSize);
}

/*!
    \brief The default font size for regular text.
*/
int QchWebSettings::defaultFontSize() const {
    return qWebSettings(this)->fontSize(QWebSettings::DefaultFontSize);
}

void QchWebSettings::setDefaultFontSize(int size) {
    if (size != defaultFontSize()) {
        qWebSettings(this)->setFontSize(QWebSettings::DefaultFontSize, size);
        emit defaultFontSizeChanged();
    }
}

void QchWebSettings::resetDefaultFontSize() {
    qWebSettings(this)->resetFontSize(QWebSettings::DefaultFontSize);
}

/*!
    \brief The hard minimum font size.
*/
int QchWebSettings::minimumFontSize() const {
    return qWebSettings(this)->fontSize(QWebSettings::MinimumFontSize);
}

void QchWebSettings::setMinimumFontSize(int size) {
    if (size != minimumFontSize()) {
        qWebSettings(this)->setFontSize(QWebSettings::MinimumFontSize, size);
        emit minimumFontSizeChanged();
    }
}

void QchWebSettings::resetMinimumFontSize() {
    qWebSettings(this)->resetFontSize(QWebSettings::MinimumFontSize);
}

/*!
    \brief The minimum logical font size that is applied when zooming out.
*/
int QchWebSettings::minimumLogicalFontSize() const {
    return qWebSettings(this)->fontSize(QWebSettings::MinimumLogicalFontSize);
}

void QchWebSettings::setMinimumLogicalFontSize(int size) {
    if (size != minimumLogicalFontSize()) {
        qWebSettings(this)->setFontSize(QWebSettings::MinimumLogicalFontSize, size);
        emit minimumLogicalFontSizeChanged();
    }
}

void QchWebSettings::resetMinimumLogicalFontSize() {
    qWebSettings(this)->resetFontSize(QWebSettings::MinimumLogicalFontSize);
}

/*!
    \brief The font family used for cursive font.
*/
QString QchWebSettings::cursiveFontFamily() const {
    return qWebSettings(this)->fontFamily(QWebSettings::CursiveFont);
}

void QchWebSettings::setCursiveFontFamily(const QString &family) {
    if (family != cursiveFontFamily()) {
        qWebSettings(this)->setFontFamily(QWebSettings::CursiveFont, family);
        emit cursiveFontFamilyChanged();
    }
}

void QchWebSettings::resetCursiveFontFamily() {
    qWebSettings(this)->resetFontFamily(QWebSettings::CursiveFont);
}

/*!
    \brief The font family used for fantasy font.
*/
QString QchWebSettings::fantasyFontFamily() const {
    return qWebSettings(this)->fontFamily(QWebSettings::FantasyFont);
}

void QchWebSettings::setFantasyFontFamily(const QString &family) {
    if (family != fantasyFontFamily()) {
        qWebSettings(this)->setFontFamily(QWebSettings::FantasyFont, family);
        emit fantasyFontFamilyChanged();
    }
}

void QchWebSettings::resetFantasyFontFamily() {
    qWebSettings(this)->resetFontFamily(QWebSettings::FantasyFont);
}

/*!
    \brief The font family used for fixed font.
*/
QString QchWebSettings::fixedFontFamily() const {
    return qWebSettings(this)->fontFamily(QWebSettings::FixedFont);
}

void QchWebSettings::setFixedFontFamily(const QString &family) {
    if (family != fixedFontFamily()) {
        qWebSettings(this)->setFontFamily(QWebSettings::FixedFont, family);
        emit fixedFontFamilyChanged();
    }
}

void QchWebSettings::resetFixedFontFamily() {
    qWebSettings(this)->resetFontFamily(QWebSettings::FixedFont);
}

/*!
    \brief The font family used for sans-serif font.
*/
QString QchWebSettings::sansSerifFontFamily() const {
    return qWebSettings(this)->fontFamily(QWebSettings::SansSerifFont);
}

void QchWebSettings::setSansSerifFontFamily(const QString &family) {
    if (family != sansSerifFontFamily()) {
        qWebSettings(this)->setFontFamily(QWebSettings::SansSerifFont, family);
        emit sansSerifFontFamilyChanged();
    }
}

void QchWebSettings::resetSansSerifFontFamily() {
    qWebSettings(this)->resetFontFamily(QWebSettings::SansSerifFont);
}

/*!
    \brief The font family used for serif font.
*/
QString QchWebSettings::serifFontFamily() const {
    return qWebSettings(this)->fontFamily(QWebSettings::SerifFont);
}

void QchWebSettings::setSerifFontFamily(const QString &family) {
    if (family != serifFontFamily()) {
        qWebSettings(this)->setFontFamily(QWebSettings::SerifFont, family);
        emit serifFontFamilyChanged();
    }
}

void QchWebSettings::resetSerifFontFamily() {
    qWebSettings(this)->resetFontFamily(QWebSettings::SerifFont);
}

/*!
    \brief The font family used for standard font.
*/
QString QchWebSettings::standardFontFamily() const {
    return qWebSettings(this)->fontFamily(QWebSettings::StandardFont);
}

void QchWebSettings::setStandardFontFamily(const QString &family) {
    if (family != standardFontFamily()) {
        qWebSettings(this)->setFontFamily(QWebSettings::StandardFont, family);
        emit standardFontFamilyChanged();
    }
}

void QchWebSettings::resetStandardFontFamily() {
    qWebSettings(this)->resetFontFamily(QWebSettings::StandardFont);
}

/*!
    \brief The location of a user stylesheet to load with every web page.

    The \a location must be either a path on the local filesystem, or a data URL with UTF-8 and Base64 encoded data, 
    such as:

    "data:text/css;charset=utf-8;base64,cCB7IGJhY2tncm91bmQtY29sb3I6IHJlZCB9Ow=="

    \note If the base64 data is not valid, the style will not be applied.
*/
QUrl QchWebSettings::userStyleSheetUrl() const {
    return qWebSettings(this)->userStyleSheetUrl();
}

void QchWebSettings::setUserStyleSheetUrl(const QUrl &url) {
    if (url != userStyleSheetUrl()) {
        qWebSettings(this)->setUserStyleSheetUrl(url);
        emit userStyleSheetUrlChanged();
    }
}

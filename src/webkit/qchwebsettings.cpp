/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

QchWebSettings::QchWebSettings(QObject *parent) :
    QObject(parent)
{
}

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

QString QchWebSettings::defaultTextEncoding() const {
    return qWebSettings(this)->defaultTextEncoding();
}

void QchWebSettings::setDefaultTextEncoding(const QString &encoding) {
    if (encoding != defaultTextEncoding()) {
        qWebSettings(this)->setDefaultTextEncoding(encoding);
        emit defaultTextEncodingChanged();
    }
}

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

QUrl QchWebSettings::userStyleSheetUrl() const {
    return qWebSettings(this)->userStyleSheetUrl();
}

void QchWebSettings::setUserStyleSheetUrl(const QUrl &url) {
    if (url != userStyleSheetUrl()) {
        qWebSettings(this)->setUserStyleSheetUrl(url);
        emit userStyleSheetUrlChanged();
    }
}

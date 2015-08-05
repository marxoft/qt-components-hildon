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
#include <QWebSettings>

QchWebSettings::QchWebSettings(QObject *parent) :
    QObject(parent),
    m_settings(QWebSettings::globalSettings())
{
}

QchWebSettings::QchWebSettings(QWebSettings *settings, QObject *parent) :
    QObject(parent),
    m_settings(settings)
{
}

bool QchWebSettings::autoLoadImages() const {
    return m_settings->testAttribute(QWebSettings::AutoLoadImages);
}

void QchWebSettings::setAutoLoadImages(bool load) {
    if (load != autoLoadImages()) {
        m_settings->setAttribute(QWebSettings::AutoLoadImages, load);
        emit autoLoadImagesChanged();
    }
}

void QchWebSettings::resetAutoLoadImages() {
    m_settings->resetAttribute(QWebSettings::AutoLoadImages);
}

bool QchWebSettings::javaEnabled() const {
    return m_settings->testAttribute(QWebSettings::JavaEnabled);
}

void QchWebSettings::setJavaEnabled(bool enabled) {
    if (enabled != javaEnabled()) {
        m_settings->setAttribute(QWebSettings::JavaEnabled, enabled);
        emit javaEnabledChanged();
    }
}

void QchWebSettings::resetJavaEnabled() {
    m_settings->resetAttribute(QWebSettings::JavaEnabled);
}

bool QchWebSettings::javascriptCanAccessClipboard() const {
    return m_settings->testAttribute(QWebSettings::JavascriptCanAccessClipboard);
}

void QchWebSettings::setJavascriptCanAccessClipboard(bool access) {
    if (access != javascriptCanAccessClipboard()) {
        m_settings->setAttribute(QWebSettings::JavascriptCanAccessClipboard, access);
        emit javascriptCanAccessClipboardChanged();
    }
}

void QchWebSettings::resetJavascriptCanAccessClipboard() {
    m_settings->resetAttribute(QWebSettings::JavascriptCanAccessClipboard);
}

bool QchWebSettings::javascriptCanOpenWindows() const {
    return m_settings->testAttribute(QWebSettings::JavascriptCanOpenWindows);
}

void QchWebSettings::setJavascriptCanOpenWindows(bool open) {
    if (open != javascriptCanOpenWindows()) {
        m_settings->setAttribute(QWebSettings::JavascriptCanOpenWindows, open);
        emit javascriptCanOpenWindowsChanged();
    }
}

void QchWebSettings::resetJavascriptCanOpenWindows() {
    m_settings->resetAttribute(QWebSettings::JavascriptCanOpenWindows);
}

bool QchWebSettings::javascriptEnabled() const {
    return m_settings->testAttribute(QWebSettings::JavascriptEnabled);
}

void QchWebSettings::setJavascriptEnabled(bool enabled) {
    if (enabled != javascriptEnabled()) {
        m_settings->setAttribute(QWebSettings::JavascriptEnabled, enabled);
        emit javascriptEnabledChanged();
    }
}

void QchWebSettings::resetJavascriptEnabled() {
    m_settings->resetAttribute(QWebSettings::JavascriptEnabled);
}

bool QchWebSettings::linksIncludedInFocusChain() const {
    return m_settings->testAttribute(QWebSettings::LinksIncludedInFocusChain);
}

void QchWebSettings::setLinksIncludedInFocusChain(bool included) {
    if (included != linksIncludedInFocusChain()) {
        m_settings->setAttribute(QWebSettings::LinksIncludedInFocusChain, included);
        emit linksIncludedInFocusChainChanged();
    }
}

void QchWebSettings::resetLinksIncludedInFocusChain() {
    m_settings->resetAttribute(QWebSettings::LinksIncludedInFocusChain);
}

bool QchWebSettings::localContentCanAccessRemoteUrls() const {
    return m_settings->testAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

void QchWebSettings::setLocalContentCanAccessRemoteUrls(bool access) {
    if (access != localContentCanAccessRemoteUrls()) {
        m_settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, access);
        emit localContentCanAccessRemoteUrlsChanged();
    }
}

void QchWebSettings::resetLocalContentCanAccessRemoteUrls() {
    m_settings->resetAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

bool QchWebSettings::localStorageDatabaseEnabled() const {
    return m_settings->testAttribute(QWebSettings::LocalStorageDatabaseEnabled);
}

void QchWebSettings::setLocalStorageDatabaseEnabled(bool enabled) {
    if (enabled != localStorageDatabaseEnabled()) {
        m_settings->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, enabled);
        emit localStorageDatabaseEnabledChanged();
    }
}

void QchWebSettings::resetLocalStorageDatabaseEnabled() {
    m_settings->resetAttribute(QWebSettings::LocalStorageDatabaseEnabled);
}

bool QchWebSettings::offlineStorageDatabaseEnabled() const {
    return m_settings->testAttribute(QWebSettings::OfflineStorageDatabaseEnabled);
}

void QchWebSettings::setOfflineStorageDatabaseEnabled(bool enabled) {
    if (enabled != offlineStorageDatabaseEnabled()) {
        m_settings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, enabled);
        emit offlineStorageDatabaseEnabledChanged();
    }
}

void QchWebSettings::resetOfflineStorageDatabaseEnabled() {
    m_settings->resetAttribute(QWebSettings::OfflineStorageDatabaseEnabled);
}

bool QchWebSettings::offlineWebApplicationCacheEnabled() const {
    return m_settings->testAttribute(QWebSettings::OfflineWebApplicationCacheEnabled);
}

void QchWebSettings::setOfflineWebApplicationCacheEnabled(bool enabled) {
    if (enabled != offlineWebApplicationCacheEnabled()) {
        m_settings->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, enabled);
        emit offlineWebApplicationCacheEnabledChanged();
    }
}

void QchWebSettings::resetOfflineWebApplicationCacheEnabled() {
    m_settings->resetAttribute(QWebSettings::OfflineWebApplicationCacheEnabled);
}

bool QchWebSettings::persistentStorageEnabled() const {
    return (!m_settings->iconDatabasePath().isEmpty())
            || (!m_settings->localStoragePath().isEmpty())
            || (!m_settings->offlineStoragePath().isEmpty())
            || (!m_settings->offlineWebApplicationCachePath().isEmpty());
}

void QchWebSettings::setPersistentStorageEnabled(bool enabled) {
    if (enabled) {
        m_settings->enablePersistentStorage();
    }
    else {
        m_settings->setIconDatabasePath(QString());
        m_settings->setLocalStoragePath(QString());
        m_settings->setOfflineStoragePath(QString());
        m_settings->setOfflineWebApplicationCachePath(QString());
    }

    emit persistentStorageEnabledChanged();
}

bool QchWebSettings::pluginsEnabled() const {
    return m_settings->testAttribute(QWebSettings::PluginsEnabled);
}

void QchWebSettings::setPluginsEnabled(bool enabled) {
    if (enabled != pluginsEnabled()) {
        m_settings->setAttribute(QWebSettings::PluginsEnabled, enabled);
        emit pluginsEnabledChanged();
    }
}

void QchWebSettings::resetPluginsEnabled() {
    m_settings->resetAttribute(QWebSettings::PluginsEnabled);
}

bool QchWebSettings::printElementBackgrounds() const {
    return m_settings->testAttribute(QWebSettings::PrintElementBackgrounds);
}

void QchWebSettings::setPrintElementBackgrounds(bool enabled) {
    if (enabled != printElementBackgrounds()) {
        m_settings->setAttribute(QWebSettings::PrintElementBackgrounds, enabled);
        emit printElementBackgroundsChanged();
    }
}

void QchWebSettings::resetPrintElementBackgrounds() {
    m_settings->resetAttribute(QWebSettings::PrintElementBackgrounds);
}

bool QchWebSettings::privateBrowsingEnabled() const {
    return m_settings->testAttribute(QWebSettings::PrivateBrowsingEnabled);
}

void QchWebSettings::setPrivateBrowsingEnabled(bool enabled) {
    if (enabled != privateBrowsingEnabled()) {
        m_settings->setAttribute(QWebSettings::PrivateBrowsingEnabled, enabled);
        emit privateBrowsingEnabledChanged();
    }
}

void QchWebSettings::resetPrivateBrowsingEnabled() {
    m_settings->resetAttribute(QWebSettings::PrivateBrowsingEnabled);
}

bool QchWebSettings::zoomTextOnly() const {
    return m_settings->testAttribute(QWebSettings::ZoomTextOnly);
}

void QchWebSettings::setZoomTextOnly(bool text) {
    if (text != zoomTextOnly()) {
        m_settings->setAttribute(QWebSettings::ZoomTextOnly, text);
        emit zoomTextOnlyChanged();
    }
}

void QchWebSettings::resetZoomTextOnly() {
    m_settings->resetAttribute(QWebSettings::ZoomTextOnly);
}

bool QchWebSettings::developerExtrasEnabled() const {
    return m_settings->testAttribute(QWebSettings::DeveloperExtrasEnabled);
}

void QchWebSettings::setDeveloperExtrasEnabled(bool enabled) {
    if (enabled != developerExtrasEnabled()) {
        m_settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, enabled);
        emit developerExtrasEnabledChanged();
    }
}

void QchWebSettings::resetDeveloperExtrasEnabled() {
    m_settings->resetAttribute(QWebSettings::DeveloperExtrasEnabled);
}

QString QchWebSettings::defaultTextEncoding() const {
    return m_settings->defaultTextEncoding();
}

void QchWebSettings::setDefaultTextEncoding(const QString &encoding) {
    if (encoding != defaultTextEncoding()) {
        m_settings->setDefaultTextEncoding(encoding);
        emit defaultTextEncodingChanged();
    }
}

int QchWebSettings::defaultFixedFontSize() const {
    return m_settings->fontSize(QWebSettings::DefaultFixedFontSize);
}

void QchWebSettings::setDefaultFixedFontSize(int size) {
    if (size != defaultFixedFontSize()) {
        m_settings->setFontSize(QWebSettings::DefaultFixedFontSize, size);
        emit defaultFixedFontSizeChanged();
    }
}

void QchWebSettings::resetDefaultFixedFontSize() {
    m_settings->resetFontSize(QWebSettings::DefaultFixedFontSize);
}

int QchWebSettings::defaultFontSize() const {
    return m_settings->fontSize(QWebSettings::DefaultFontSize);
}

void QchWebSettings::setDefaultFontSize(int size) {
    if (size != defaultFontSize()) {
        m_settings->setFontSize(QWebSettings::DefaultFontSize, size);
        emit defaultFontSizeChanged();
    }
}

void QchWebSettings::resetDefaultFontSize() {
    m_settings->resetFontSize(QWebSettings::DefaultFontSize);
}

int QchWebSettings::minimumFontSize() const {
    return m_settings->fontSize(QWebSettings::MinimumFontSize);
}

void QchWebSettings::setMinimumFontSize(int size) {
    if (size != minimumFontSize()) {
        m_settings->setFontSize(QWebSettings::MinimumFontSize, size);
        emit minimumFontSizeChanged();
    }
}

void QchWebSettings::resetMinimumFontSize() {
    m_settings->resetFontSize(QWebSettings::MinimumFontSize);
}

int QchWebSettings::minimumLogicalFontSize() const {
    return m_settings->fontSize(QWebSettings::MinimumLogicalFontSize);
}

void QchWebSettings::setMinimumLogicalFontSize(int size) {
    if (size != minimumLogicalFontSize()) {
        m_settings->setFontSize(QWebSettings::MinimumLogicalFontSize, size);
        emit minimumLogicalFontSizeChanged();
    }
}

void QchWebSettings::resetMinimumLogicalFontSize() {
    m_settings->resetFontSize(QWebSettings::MinimumLogicalFontSize);
}

QString QchWebSettings::cursiveFontFamily() const {
    return m_settings->fontFamily(QWebSettings::CursiveFont);
}

void QchWebSettings::setCursiveFontFamily(const QString &family) {
    if (family != cursiveFontFamily()) {
        m_settings->setFontFamily(QWebSettings::CursiveFont, family);
        emit cursiveFontFamilyChanged();
    }
}

void QchWebSettings::resetCursiveFontFamily() {
    m_settings->resetFontFamily(QWebSettings::CursiveFont);
}

QString QchWebSettings::fantasyFontFamily() const {
    return m_settings->fontFamily(QWebSettings::FantasyFont);
}

void QchWebSettings::setFantasyFontFamily(const QString &family) {
    if (family != fantasyFontFamily()) {
        m_settings->setFontFamily(QWebSettings::FantasyFont, family);
        emit fantasyFontFamilyChanged();
    }
}

void QchWebSettings::resetFantasyFontFamily() {
    m_settings->resetFontFamily(QWebSettings::FantasyFont);
}

QString QchWebSettings::fixedFontFamily() const {
    return m_settings->fontFamily(QWebSettings::FixedFont);
}

void QchWebSettings::setFixedFontFamily(const QString &family) {
    if (family != fixedFontFamily()) {
        m_settings->setFontFamily(QWebSettings::FixedFont, family);
        emit fixedFontFamilyChanged();
    }
}

void QchWebSettings::resetFixedFontFamily() {
    m_settings->resetFontFamily(QWebSettings::FixedFont);
}

QString QchWebSettings::sansSerifFontFamily() const {
    return m_settings->fontFamily(QWebSettings::SansSerifFont);
}

void QchWebSettings::setSansSerifFontFamily(const QString &family) {
    if (family != sansSerifFontFamily()) {
        m_settings->setFontFamily(QWebSettings::SansSerifFont, family);
        emit sansSerifFontFamilyChanged();
    }
}

void QchWebSettings::resetSansSerifFontFamily() {
    m_settings->resetFontFamily(QWebSettings::SansSerifFont);
}

QString QchWebSettings::serifFontFamily() const {
    return m_settings->fontFamily(QWebSettings::SerifFont);
}

void QchWebSettings::setSerifFontFamily(const QString &family) {
    if (family != serifFontFamily()) {
        m_settings->setFontFamily(QWebSettings::SerifFont, family);
        emit serifFontFamilyChanged();
    }
}

void QchWebSettings::resetSerifFontFamily() {
    m_settings->resetFontFamily(QWebSettings::SerifFont);
}

QString QchWebSettings::standardFontFamily() const {
    return m_settings->fontFamily(QWebSettings::StandardFont);
}

void QchWebSettings::setStandardFontFamily(const QString &family) {
    if (family != standardFontFamily()) {
        m_settings->setFontFamily(QWebSettings::StandardFont, family);
        emit standardFontFamilyChanged();
    }
}

void QchWebSettings::resetStandardFontFamily() {
    m_settings->resetFontFamily(QWebSettings::StandardFont);
}

QUrl QchWebSettings::userStyleSheetUrl() const {
    return m_settings->userStyleSheetUrl();
}

void QchWebSettings::setUserStyleSheetUrl(const QUrl &url) {
    if (url != userStyleSheetUrl()) {
        m_settings->setUserStyleSheetUrl(url);
        emit userStyleSheetUrlChanged();
    }
}

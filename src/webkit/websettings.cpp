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

#include "websettings_p.h"
#include <QWebSettings>

WebSettings::WebSettings(QObject *parent) :
    QObject(parent),
    m_settings(QWebSettings::globalSettings())
{
}

WebSettings::WebSettings(QWebSettings *settings, QObject *parent) :
    QObject(parent),
    m_settings(settings)
{
}

WebSettings::~WebSettings() {}

bool WebSettings::autoLoadImages() const {
    return m_settings->testAttribute(QWebSettings::AutoLoadImages);
}

void WebSettings::setAutoLoadImages(bool load) {
    if (load != this->autoLoadImages()) {
        m_settings->setAttribute(QWebSettings::AutoLoadImages, load);
        emit autoLoadImagesChanged();
    }
}

void WebSettings::resetAutoLoadImages() {
    m_settings->resetAttribute(QWebSettings::AutoLoadImages);
}

bool WebSettings::javaEnabled() const {
    return m_settings->testAttribute(QWebSettings::JavaEnabled);
}

void WebSettings::setJavaEnabled(bool enabled) {
    if (enabled != this->javaEnabled()) {
        m_settings->setAttribute(QWebSettings::JavaEnabled, enabled);
        emit javaEnabledChanged();
    }
}

void WebSettings::resetJavaEnabled() {
    m_settings->resetAttribute(QWebSettings::JavaEnabled);
}

bool WebSettings::javascriptCanAccessClipboard() const {
    return m_settings->testAttribute(QWebSettings::JavascriptCanAccessClipboard);
}

void WebSettings::setJavascriptCanAccessClipboard(bool access) {
    if (access != this->javascriptCanAccessClipboard()) {
        m_settings->setAttribute(QWebSettings::JavascriptCanAccessClipboard, access);
        emit javascriptCanAccessClipboardChanged();
    }
}

void WebSettings::resetJavascriptCanAccessClipboard() {
    m_settings->resetAttribute(QWebSettings::JavascriptCanAccessClipboard);
}

bool WebSettings::javascriptCanOpenWindows() const {
    return m_settings->testAttribute(QWebSettings::JavascriptCanOpenWindows);
}

void WebSettings::setJavascriptCanOpenWindows(bool open) {
    if (open != this->javascriptCanOpenWindows()) {
        m_settings->setAttribute(QWebSettings::JavascriptCanOpenWindows, open);
        emit javascriptCanOpenWindowsChanged();
    }
}

void WebSettings::resetJavascriptCanOpenWindows() {
    m_settings->resetAttribute(QWebSettings::JavascriptCanOpenWindows);
}

bool WebSettings::javascriptEnabled() const {
    return m_settings->testAttribute(QWebSettings::JavascriptEnabled);
}

void WebSettings::setJavascriptEnabled(bool enabled) {
    if (enabled != this->javascriptEnabled()) {
        m_settings->setAttribute(QWebSettings::JavascriptEnabled, enabled);
        emit javascriptEnabledChanged();
    }
}

void WebSettings::resetJavascriptEnabled() {
    m_settings->resetAttribute(QWebSettings::JavascriptEnabled);
}

bool WebSettings::linksIncludedInFocusChain() const {
    return m_settings->testAttribute(QWebSettings::LinksIncludedInFocusChain);
}

void WebSettings::setLinksIncludedInFocusChain(bool included) {
    if (included != this->linksIncludedInFocusChain()) {
        m_settings->setAttribute(QWebSettings::LinksIncludedInFocusChain, included);
        emit linksIncludedInFocusChainChanged();
    }
}

void WebSettings::resetLinksIncludedInFocusChain() {
    m_settings->resetAttribute(QWebSettings::LinksIncludedInFocusChain);
}

bool WebSettings::localContentCanAccessRemoteUrls() const {
    return m_settings->testAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

void WebSettings::setLocalContentCanAccessRemoteUrls(bool access) {
    if (access != this->localContentCanAccessRemoteUrls()) {
        m_settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, access);
        emit localContentCanAccessRemoteUrlsChanged();
    }
}

void WebSettings::resetLocalContentCanAccessRemoteUrls() {
    m_settings->resetAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

bool WebSettings::localStorageDatabaseEnabled() const {
    return m_settings->testAttribute(QWebSettings::LocalStorageDatabaseEnabled);
}

void WebSettings::setLocalStorageDatabaseEnabled(bool enabled) {
    if (enabled != this->localStorageDatabaseEnabled()) {
        m_settings->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, enabled);
        emit localStorageDatabaseEnabledChanged();
    }
}

void WebSettings::resetLocalStorageDatabaseEnabled() {
    m_settings->resetAttribute(QWebSettings::LocalStorageDatabaseEnabled);
}

bool WebSettings::offlineStorageDatabaseEnabled() const {
    return m_settings->testAttribute(QWebSettings::OfflineStorageDatabaseEnabled);
}

void WebSettings::setOfflineStorageDatabaseEnabled(bool enabled) {
    if (enabled != this->offlineStorageDatabaseEnabled()) {
        m_settings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, enabled);
        emit offlineStorageDatabaseEnabledChanged();
    }
}

void WebSettings::resetOfflineStorageDatabaseEnabled() {
    m_settings->resetAttribute(QWebSettings::OfflineStorageDatabaseEnabled);
}

bool WebSettings::offlineWebApplicationCacheEnabled() const {
    return m_settings->testAttribute(QWebSettings::OfflineWebApplicationCacheEnabled);
}

void WebSettings::setOfflineWebApplicationCacheEnabled(bool enabled) {
    if (enabled != this->offlineWebApplicationCacheEnabled()) {
        m_settings->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, enabled);
        emit offlineWebApplicationCacheEnabledChanged();
    }
}

void WebSettings::resetOfflineWebApplicationCacheEnabled() {
    m_settings->resetAttribute(QWebSettings::OfflineWebApplicationCacheEnabled);
}

bool WebSettings::persistentStorageEnabled() const {
    return (!m_settings->iconDatabasePath().isEmpty())
            || (!m_settings->localStoragePath().isEmpty())
            || (!m_settings->offlineStoragePath().isEmpty())
            || (!m_settings->offlineWebApplicationCachePath().isEmpty());
}

void WebSettings::setPersistentStorageEnabled(bool enabled) {
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

bool WebSettings::pluginsEnabled() const {
    return m_settings->testAttribute(QWebSettings::PluginsEnabled);
}

void WebSettings::setPluginsEnabled(bool enabled) {
    if (enabled != this->pluginsEnabled()) {
        m_settings->setAttribute(QWebSettings::PluginsEnabled, enabled);
        emit pluginsEnabledChanged();
    }
}

void WebSettings::resetPluginsEnabled() {
    m_settings->resetAttribute(QWebSettings::PluginsEnabled);
}

bool WebSettings::printElementBackgrounds() const {
    return m_settings->testAttribute(QWebSettings::PrintElementBackgrounds);
}

void WebSettings::setPrintElementBackgrounds(bool enabled) {
    if (enabled != this->printElementBackgrounds()) {
        m_settings->setAttribute(QWebSettings::PrintElementBackgrounds, enabled);
        emit printElementBackgroundsChanged();
    }
}

void WebSettings::resetPrintElementBackgrounds() {
    m_settings->resetAttribute(QWebSettings::PrintElementBackgrounds);
}

bool WebSettings::privateBrowsingEnabled() const {
    return m_settings->testAttribute(QWebSettings::PrivateBrowsingEnabled);
}

void WebSettings::setPrivateBrowsingEnabled(bool enabled) {
    if (enabled != this->privateBrowsingEnabled()) {
        m_settings->setAttribute(QWebSettings::PrivateBrowsingEnabled, enabled);
        emit privateBrowsingEnabledChanged();
    }
}

void WebSettings::resetPrivateBrowsingEnabled() {
    m_settings->resetAttribute(QWebSettings::PrivateBrowsingEnabled);
}

bool WebSettings::zoomTextOnly() const {
    return m_settings->testAttribute(QWebSettings::ZoomTextOnly);
}

void WebSettings::setZoomTextOnly(bool text) {
    if (text != this->zoomTextOnly()) {
        m_settings->setAttribute(QWebSettings::ZoomTextOnly, text);
        emit zoomTextOnlyChanged();
    }
}

void WebSettings::resetZoomTextOnly() {
    m_settings->resetAttribute(QWebSettings::ZoomTextOnly);
}

bool WebSettings::developerExtrasEnabled() const {
    return m_settings->testAttribute(QWebSettings::DeveloperExtrasEnabled);
}

void WebSettings::setDeveloperExtrasEnabled(bool enabled) {
    if (enabled != this->developerExtrasEnabled()) {
        m_settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, enabled);
        emit developerExtrasEnabledChanged();
    }
}

void WebSettings::resetDeveloperExtrasEnabled() {
    m_settings->resetAttribute(QWebSettings::DeveloperExtrasEnabled);
}

QString WebSettings::defaultTextEncoding() const {
    return m_settings->defaultTextEncoding();
}

void WebSettings::setDefaultTextEncoding(const QString &encoding) {
    if (encoding != this->defaultTextEncoding()) {
        m_settings->setDefaultTextEncoding(encoding);
        emit defaultTextEncodingChanged();
    }
}

int WebSettings::defaultFixedFontSize() const {
    return m_settings->fontSize(QWebSettings::DefaultFixedFontSize);
}

void WebSettings::setDefaultFixedFontSize(int size) {
    if (size != this->defaultFixedFontSize()) {
        m_settings->setFontSize(QWebSettings::DefaultFixedFontSize, size);
        emit defaultFixedFontSizeChanged();
    }
}

void WebSettings::resetDefaultFixedFontSize() {
    m_settings->resetFontSize(QWebSettings::DefaultFixedFontSize);
}

int WebSettings::defaultFontSize() const {
    return m_settings->fontSize(QWebSettings::DefaultFontSize);
}

void WebSettings::setDefaultFontSize(int size) {
    if (size != this->defaultFontSize()) {
        m_settings->setFontSize(QWebSettings::DefaultFontSize, size);
        emit defaultFontSizeChanged();
    }
}

void WebSettings::resetDefaultFontSize() {
    m_settings->resetFontSize(QWebSettings::DefaultFontSize);
}

int WebSettings::minimumFontSize() const {
    return m_settings->fontSize(QWebSettings::MinimumFontSize);
}

void WebSettings::setMinimumFontSize(int size) {
    if (size != this->minimumFontSize()) {
        m_settings->setFontSize(QWebSettings::MinimumFontSize, size);
        emit minimumFontSizeChanged();
    }
}

void WebSettings::resetMinimumFontSize() {
    m_settings->resetFontSize(QWebSettings::MinimumFontSize);
}

int WebSettings::minimumLogicalFontSize() const {
    return m_settings->fontSize(QWebSettings::MinimumLogicalFontSize);
}

void WebSettings::setMinimumLogicalFontSize(int size) {
    if (size != this->minimumLogicalFontSize()) {
        m_settings->setFontSize(QWebSettings::MinimumLogicalFontSize, size);
        emit minimumLogicalFontSizeChanged();
    }
}

void WebSettings::resetMinimumLogicalFontSize() {
    m_settings->resetFontSize(QWebSettings::MinimumLogicalFontSize);
}

QString WebSettings::cursiveFontFamily() const {
    return m_settings->fontFamily(QWebSettings::CursiveFont);
}

void WebSettings::setCursiveFontFamily(const QString &family) {
    if (family != this->cursiveFontFamily()) {
        m_settings->setFontFamily(QWebSettings::CursiveFont, family);
        emit cursiveFontFamilyChanged();
    }
}

void WebSettings::resetCursiveFontFamily() {
    m_settings->resetFontFamily(QWebSettings::CursiveFont);
}

QString WebSettings::fantasyFontFamily() const {
    return m_settings->fontFamily(QWebSettings::FantasyFont);
}

void WebSettings::setFantasyFontFamily(const QString &family) {
    if (family != this->fantasyFontFamily()) {
        m_settings->setFontFamily(QWebSettings::FantasyFont, family);
        emit fantasyFontFamilyChanged();
    }
}

void WebSettings::resetFantasyFontFamily() {
    m_settings->resetFontFamily(QWebSettings::FantasyFont);
}

QString WebSettings::fixedFontFamily() const {
    return m_settings->fontFamily(QWebSettings::FixedFont);
}

void WebSettings::setFixedFontFamily(const QString &family) {
    if (family != this->fixedFontFamily()) {
        m_settings->setFontFamily(QWebSettings::FixedFont, family);
        emit fixedFontFamilyChanged();
    }
}

void WebSettings::resetFixedFontFamily() {
    m_settings->resetFontFamily(QWebSettings::FixedFont);
}

QString WebSettings::sansSerifFontFamily() const {
    return m_settings->fontFamily(QWebSettings::SansSerifFont);
}

void WebSettings::setSansSerifFontFamily(const QString &family) {
    if (family != this->sansSerifFontFamily()) {
        m_settings->setFontFamily(QWebSettings::SansSerifFont, family);
        emit sansSerifFontFamilyChanged();
    }
}

void WebSettings::resetSansSerifFontFamily() {
    m_settings->resetFontFamily(QWebSettings::SansSerifFont);
}

QString WebSettings::serifFontFamily() const {
    return m_settings->fontFamily(QWebSettings::SerifFont);
}

void WebSettings::setSerifFontFamily(const QString &family) {
    if (family != this->serifFontFamily()) {
        m_settings->setFontFamily(QWebSettings::SerifFont, family);
        emit serifFontFamilyChanged();
    }
}

void WebSettings::resetSerifFontFamily() {
    m_settings->resetFontFamily(QWebSettings::SerifFont);
}

QString WebSettings::standardFontFamily() const {
    return m_settings->fontFamily(QWebSettings::StandardFont);
}

void WebSettings::setStandardFontFamily(const QString &family) {
    if (family != this->standardFontFamily()) {
        m_settings->setFontFamily(QWebSettings::StandardFont, family);
        emit standardFontFamilyChanged();
    }
}

void WebSettings::resetStandardFontFamily() {
    m_settings->resetFontFamily(QWebSettings::StandardFont);
}

QUrl WebSettings::userStyleSheetUrl() const {
    return m_settings->userStyleSheetUrl();
}

void WebSettings::setUserStyleSheetUrl(const QUrl &url) {
    if (url != this->userStyleSheetUrl()) {
        m_settings->setUserStyleSheetUrl(url);
        emit userStyleSheetUrlChanged();
    }
}

#include "moc_websettings_p.cpp"
